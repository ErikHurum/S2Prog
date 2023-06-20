const MemoryMap = require('nrf-intel-hex');
const fs = require('fs');
const commandLineArgs = require('command-line-args');
const ModbusRTU = require('modbus-serial');
const async = require('async');

const PAGE_SIZE = 256;
const optionDefinitions = [
  {
    name: 'port', alias: 'p', type: String,
  },
  {
    name: 'address', alias: 'a', type: Number,
  },
  {
    name: 'file', alias: 'f', type: String,
  },
];

const options = commandLineArgs(optionDefinitions);
const valid = options.port &&
              options.address &&
              options.file;

const compareBuffer = new Uint8Array(256);

if (!valid) {
  console.log(`--port com port --address address --file hex file`);
  process.exit(1);
}

const intelHexString = fs.readFileSync(options.file, 'utf8');
const pages = [];
const pagesHash = {};
let master;

function buildU16Buffer(start, end, buffer) {
  const u16Buf = [];

  for (let i = start; i < end; i += 2) {
    const u16 = buffer[i] << 8 | buffer[i+1];

    u16Buf.push(u16);
  }

  return u16Buf;
}

function flashPage(pageNum, buffer) {
  return new Promise((resolve, reject) => {
    console.log(`flashing ${pageNum}`);
    async.series([
      function(callback) {
        // 1. write upper 128 bytes to register
        const buf = buildU16Buffer(0, 128, buffer);

        master.writeRegisters(31000, buf)
        .then(() => {
          callback(null);
        })
        .catch((e) => {
          callback('failed to write first half of data register');
        });
      },
      function(callback) {
        // 2. write lower 128 bytes to register
        const buf = buildU16Buffer(128, 256, buffer);

        master.writeRegisters(31064, buf)
        .then(() => {
          callback(null);
        })
        .catch((e) => {
          callback('failed to write second half of data register');
        });
      },
      function(callback) {
        // 3. write pageNum to register
        master.writeRegisters(30000, [ pageNum ])
        .then(() => {
          callback(null);
        })
        .catch((e) => {
          callback('failed to write address register');
        });
      },
      function(callback) {
        // 4. issue program command
        master.writeRegisters(33000, [ 1 ])
        .then(() => {
          callback(null);
        })
        .catch((e) => {
          callback('failed to write flash write command register');
        });
      },
      function(callback) {
        // 5. issue read command
        master.writeRegisters(33000, [ 2 ])
        .then(() => {
          callback(null);
        })
        .catch((e) => {
          callback('failed to write flash read command register');
        });
      },
      function(callback) {
        // 6. read back first half 
        master.readHoldingRegisters(31000, 64)
        .then((d) => {
          for (let i = 0; i < 64; i++)
          {
            compareBuffer[i * 2 + 0] = ((d.data[i] >> 8) & 0xff);
            compareBuffer[i * 2 + 1] = (d.data[i] & 0xff);
          }
          callback(null);
        })
        .catch((e) => {
          callback('failed to read first half');
        });
      },
      function(callback) {
        // 7. read back second half 
        master.readHoldingRegisters(31000 + 64, 64)
        .then((d) => {
          for (let i = 0; i < 64; i++)
          {
            compareBuffer[128 + i * 2 + 0] = ((d.data[i] >> 8) & 0xff);
            compareBuffer[128 + i * 2 + 1] = (d.data[i] & 0xff);
          }
          callback(null);
        })
        .catch((e) => {
          callback('failed to read second half');
        });
      },
      function(callback) {
        // 8. compare
        for(let i = 0; i < 256; i++)
        {
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
    function(err, results) {
      if (err) {
        reject(`failed to flash page ${err}`);
      } else {
        resolve();
      }
    });
  });
}

function doFlashPages(callback, ndx) {
  if (ndx >= pages.length) {
    console.log('done flashing all the pages');
    callback(null);
    return;
  }

  flashPage(pages[ndx].pageNum, pages[ndx].buffer)
  .then(() => {
    doFlashPages(callback, ndx + 1);
  })
  .catch((e) => {
    callback(e);
  })
}

function getOrCreatePage(pageNum) {
  const page = pagesHash[pageNum];

  if (page !== undefined) {
    return page;
  }

  const buffer = Buffer.alloc(PAGE_SIZE);

  for (let ndx = 0; ndx < PAGE_SIZE; ndx += 1) {
    buffer[ndx] = 0xff;
  }

  obj = {
    pageNum: pageNum,
    buffer,
  };

  pagesHash[pageNum] = obj;
  pages.push(obj);

  return obj;
}

function putDataInPage(addr, data) {
  const pageNum = Math.floor(addr / PAGE_SIZE);
  const offset = addr % PAGE_SIZE;
  const page = getOrCreatePage(pageNum);

  page.buffer[offset] = data;
}

function buildFWPages() {
  let memMap = MemoryMap.fromHex(intelHexString);

  memMap.forEach((value, startAddr) => {
    for (let ndx = 0; ndx < value.length; ndx += 1) {
      const addr = startAddr + ndx;
      const data = value[ndx];

      putDataInPage(addr, data);
    }
  });
}

function doFlashFirmware() {
  async.waterfall([
    function(callback) {
      console.log('checkking running mode');
      master.readHoldingRegisters(32000, 1)
        .then((d) => {
          const state = d.data[0];
          callback(null, state);
        })
        .catch((e) => {
          callback('failed to check running mode');
        });
    },
    function(state, callback) {
      if (state === 0) {
        console.log('already in bootloader mode');
        callback(null);
      } else {
        console.log('entering bootloader mode');
        master.writeRegisters(32000, [ 0 ])
          .then((d) => {
            setTimeout(() => {
              callback(null);
            }, 1000);
          })
          .catch((e) => {
            callback('failed to enter bootloader mode');
          });
      }
    },
    function(callback) {
      let pageNdx = 0;
      console.log('start flashing');

      doFlashPages(callback, 0);
    },
    function(callback) {
      console.log('exiting bootloader mode');
      master.writeRegisters(32000, [1])
        .then(() => {
          console.log('done exiting boot mode');
          callback(null, 3);
        })
        .catch((e) => {
          callback('failed to exit bootloader mode');
        });
    }
  ],
  function (err, results) {
    if(err) {
      console.log(`error occurred: ${err}`)
      master.close();
      process.exit(1);
    }
    console.log('flashing done');
    master.close();
  }
  );
}

// console.log(`${intelHexString}`);

master = new ModbusRTU();
master.connectRTUBuffered(options.port, {
  baudRate: 38400,
  dataBits: 8,
  stopBits: 1,
  parity: 'none',
}).then(() => {
  console.log(`opened serial device ${options.port}`)
  master.setID(options.address);
  master.setTimeout(3000);

  buildFWPages();
  doFlashFirmware();
}).catch((err) => {
  console.log(`error occurred ${err}`)
  process.exit(1);
});
