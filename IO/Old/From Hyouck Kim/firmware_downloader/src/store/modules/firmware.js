import MemoryMap from 'nrf-intel-hex';
import fs from 'fs';
import path from 'path';

const { dialog } = require('electron').remote;

const PAGE_SIZE = 256;

function getOrCreatePage(pageMap, pageNum) {
  const map = pageMap;
  const page = map.pagesHash[pageNum];

  if (page !== undefined) {
    return page;
  }

  const buffer = Buffer.alloc(PAGE_SIZE);

  for (let ndx = 0; ndx < PAGE_SIZE; ndx += 1) {
    buffer[ndx] = 0xff;
  }

  const obj = {
    pageNum,
    buffer,
  };

  map.pagesHash[pageNum] = obj;
  map.pages.push(obj);

  return obj;
}

function putDataInPage(pageMap, addr, data) {
  const pageNum = Math.floor(addr / PAGE_SIZE);
  const offset = addr % PAGE_SIZE;
  const page = getOrCreatePage(pageMap, pageNum);

  page.buffer[offset] = data;
}

function buildFWPages(memMap) {
  const obj = {
    size: 0,
    pages: [],
    pagesHash: {},
  };

  memMap.forEach((value, startAddr) => {
    obj.size += value.length;

    for (let ndx = 0; ndx < value.length; ndx += 1) {
      const addr = startAddr + ndx;
      const data = value[ndx];

      putDataInPage(obj, addr, data);
    }
  });

  return obj;
}

const state = {
  valid: false,
  filename: null,
  pages: [],
  size: 0,
};

const mutations = {
  FW_SET_FILENAME(_, filename) {
    state.filename = filename;
  },
  FW_SET_PAGES(_, pages) {
    state.pages = pages;
  },
  FW_SET_VALID(_, valid) {
    state.valid = valid;
  },
  FW_SET_SIZE(_, size) {
    state.size = size;
  },
};

const actions = {
  loadFirmware(context) {
    dialog.showOpenDialog({
      title: 'Load Firmware',
      filters: [
        { name: 'Hex file', extension: ['hex'] },
      ],
    }, (filePaths) => {
      if (filePaths === undefined) {
        return;
      }

      fs.readFile(filePaths[0], (err, data) => {
        if (err) {
          console.log(err);
          return;
        }

        try {
          const memMap = MemoryMap.fromHex(data);
          const pageMap = buildFWPages(memMap);

          context.commit('FW_SET_FILENAME', path.basename(filePaths[0]));
          context.commit('FW_SET_PAGES', pageMap.pages);
          context.commit('FW_SET_SIZE', pageMap.size);
          context.commit('FW_SET_VALID', true);
        } catch (e) {
          console.log(`failed to parse hex file ${e}`);
        }
      });
    });
  },
};

const getters = {
  fw_valid() {
    return state.valid;
  },
  fw_filename() {
    return state.filename;
  },
  fw_pages() {
    return state.pages;
  },
  fw_num_pages() {
    return state.pages.length;
  },
  fw_size() {
    return state.size;
  },
};

export default {
  state,
  mutations,
  actions,
  getters,
};
