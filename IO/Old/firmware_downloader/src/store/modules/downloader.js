import async from 'async';
import ModbusRTU from 'modbus-serial';

//
// step
//
// 1. reading running mode
// 2. entering boot mode
// 3. flashing pages
// 4. exiting bootloader mode
// 5. done
//

let master = null;
const compareBuffer = new Uint8Array(256);

const state = {
  address: 10,
  validAddresses: [
    10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25,
  ],
  downloading: false,
  progress: 0,
  failed: false,
  message: '',
  step: 1,
};

const mutations = {
  DW_SET_ADDRESS(_, address) {
    state.address = address;
  },
  DW_SET_DOWNLOADING(_, v) {
    state.downloading = v;
  },
  DW_SET_PROGRESS(_, v) {
    state.progress = v;
  },
  DW_SET_FAILED(_, v) {
    state.failed = v;
  },
  DW_SET_MESSAGE(_, v) {
    state.message = v;
  },
  DW_SET_STEP(_, v) {
    state.step = v;
  },
};

function buildU16Buffer(start, end, buffer) {
  const u16Buf = [];

  for (let i = start; i < end; i += 2) {
    /* eslint-disable */
    const u16 = buffer[i] << 8 | buffer[i+1];
    /* eslint-enable */

    u16Buf.push(u16);
  }

  return u16Buf;
}

function log(context, msg) {
  console.log(`console: ${msg}`);
  context.commit('DW_SET_MESSAGE', msg);
}

function flashPage(context, pageNum, buffer) {
  return new Promise((resolve, reject) => {
    log(context, `flashing ${pageNum}`);
    async.series([
      (callback) => {
        // 1. write upper 128 bytes to register
        const buf = buildU16Buffer(0, 128, buffer);

        master.writeRegisters(31000, buf)
          .then(() => {
            callback(null);
          })
          .catch((e) => {
            callback(`failed to write first half of data register ${e}`);
          });
      },
      (callback) => {
        // 2. write lower 128 bytes to register
        const buf = buildU16Buffer(128, 256, buffer);

        master.writeRegisters(31064, buf)
          .then(() => {
            callback(null);
          })
          .catch((e) => {
            callback(`failed to write second half of data register ${e}`);
          });
      },
      (callback) => {
        // 3. write pageNum to register
        master.writeRegisters(30000, [pageNum])
          .then(() => {
            callback(null);
          })
          .catch((e) => {
            callback(`failed to write address register ${e}`);
          });
      },
      (callback) => {
        // 4. issue program command
        master.writeRegisters(33000, [1])
          .then(() => {
            callback(null);
          })
          .catch((e) => {
            callback(`failed to write flash write command register ${e}`);
          });
      },
      (callback) => {
        // 5. issue read command
        master.writeRegisters(33000, [2])
          .then(() => {
            callback(null);
          })
          .catch((e) => {
            callback(`failed to write flash read command register ${e}`);
          });
      },
      (callback) => {
        // 6. read back first half
        master.readHoldingRegisters(31000, 64)
          .then((d) => {
            for (let i = 0; i < 64; i += 1) {
              // eslint-disable-next-line no-bitwise
              compareBuffer[i * 2 + 0] = ((d.data[i] >> 8) & 0xff);
              // eslint-disable-next-line no-bitwise
              compareBuffer[i * 2 + 1] = (d.data[i] & 0xff);
            }
            callback(null);
          })
          .catch((e) => {
            callback(`failed to read first half ${e}`);
          });
      },
      (callback) => {
        // 7. read back second half
        master.readHoldingRegisters(31000 + 64, 64)
          .then((d) => {
            for (let i = 0; i < 64; i += 1) {
              // eslint-disable-next-line no-bitwise
              compareBuffer[128 + i * 2 + 0] = ((d.data[i] >> 8) & 0xff);
              // eslint-disable-next-line no-bitwise
              compareBuffer[128 + i * 2 + 1] = (d.data[i] & 0xff);
            }
            callback(null);
          })
          .catch((e) => {
            callback(`failed to read second half ${e}`);
          });
      },
      (callback) => {
        // 8. compare
        for (let i = 0; i < 256; i += 1) {
          if (buffer[i] !== compareBuffer[i]) {
            process.nextTick(() => {
              callback(`compare failed at ${pageNum}:${i} ${buffer[i]} ${compareBuffer[i]}`);
            });
            return;
          }
        }
        callback(null);
      },
    ],
    (err) => {
      if (err) {
        /* eslint-disable */
        reject(`failed to flash page ${err}`);
        /* eslint-enable */
      } else {
        resolve();
      }
    });
  });
}

function doFlashPages(context, callback, ndx) {
  const pages = context.getters.fw_pages;

  if (ndx >= pages.length) {
    context.commit('DW_SET_STEP', 4);
    context.commit('DW_SET_PROGRESS', 100);
    log(context, 'done flashing all the pages');
    callback(null);
    return;
  }

  flashPage(context, pages[ndx].pageNum, pages[ndx].buffer)
    .then(() => {
      context.commit('DW_SET_PROGRESS', (ndx / (pages.length - 1) * 100));
      doFlashPages(context, callback, ndx + 1);
    })
    .catch((e) => {
      callback(e);
    });
}

function startFirmwareDownload(context) {
  async.waterfall([
    (callback) => {
      log(context, 'checkking running mode');
      master.readHoldingRegisters(32000, 1)
        .then((d) => {
          const s = d.data[0];
          callback(null, s);
        })
        .catch((e) => {
          callback(`failed to check running mode ${e}`);
        });
    },
    (s, callback) => {
      if (state === 0) {
        log(context, 'already in bootloader mode');
        context.commit('DW_SET_STEP', 3);
        callback(null);
      } else {
        log(context, 'entering bootloader mode');
        context.commit('DW_SET_STEP', 2);
        master.writeRegisters(32000, [0])
          .then(() => {
            setTimeout(() => {
              context.commit('DW_SET_STEP', 3);
              callback(null);
            }, 1000);
          })
          .catch((e) => {
            callback(`failed to enter bootloader mode ${e}`);
          });
      }
    },
    (callback) => {
      log(context, 'start flashing');
      doFlashPages(context, callback, 0);
    },
    (callback) => {
      log(context, 'exiting bootloader mode');
      context.commit('DW_SET_STEP', 4);
      master.writeRegisters(32000, [1])
        .then(() => {
          context.commit('DW_SET_STEP', 5);
          log(context, 'done exiting boot mode');
          callback(null, 3);
        })
        .catch((e) => {
          callback(`failed to exit bootloader mode ${e}`);
        });
    },
  ],
  (err) => {
    if (err) {
      log(context, `waterfall: error occurred: ${err}`);

      context.commit('DW_SET_DOWNLOADING', false);
      context.commit('DW_SET_FAILED', true);

      master.close();
      return;
    }

    log(context, 'flashing done');

    context.commit('DW_SET_DOWNLOADING', false);
    context.commit('DW_SET_MESSAGE', 'flashing done');
    master.close();
  });
}

function resetDownloader(context) {
  context.commit('DW_SET_PROGRESS', 0);
  context.commit('DW_SET_FAILED', false);
  context.commit('DW_SET_MESSAGE', '');
  context.commit('DW_SET_STEP', 1);
}

const actions = {
  startDownload(context) {
    context.commit('DW_SET_DOWNLOADING', true);
    resetDownloader(context);

    master = new ModbusRTU();

    master.connectRTUBuffered(context.getters.comm_port, {
      baudRate: 38400,
      dataBits: 8,
      stopBits: 1,
      parity: 'none',
    }).then(() => {
      log(context, `opened comm port ${context.getters.comm_port}`);

      master.setID(context.getters.dw_address);
      master.setTimeout(3000);

      startFirmwareDownload(context);
    }).catch((err) => {
      log(context, `error occurred during firmware download: ${err}`);
      context.commit('DW_SET_FAILED', true);
      context.commit('DW_SET_DOWNLOADING', false);
    });
  },
};

const getters = {
  dw_address() {
    return state.address;
  },
  dw_valid_addresses() {
    return state.validAddresses;
  },
  dw_downloading() {
    return state.downloading;
  },
  dw_progress() {
    return state.progress;
  },
  dw_failed() {
    return state.failed;
  },
  dw_message() {
    return state.message;
  },
  dw_step() {
    return state.step;
  },
};

export default {
  state,
  mutations,
  actions,
  getters,
};
