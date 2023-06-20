import SerialPort from 'serialport';

const state = {
  commPortList: [],
  commPort: 'None',
};

const mutations = {
  COMM_PORT_UPDATE_LIST(_, list) {
    state.commPortList = list;
  },
  COMM_PORT_SET(_, port) {
    state.commPort = port;
  },
};

const actions = {
  refreshPortList(context, cb) {
    context.commit('COMM_PORT_SET', 'None');
    SerialPort.list((err, results) => {
      if (err) {
        cb(err);
        return;
      }

      const portList = [];

      results.forEach((port) => {
        console.log(`port ${port.comName}`);
        portList.push(port.comName);
      });
      context.commit('COMM_PORT_UPDATE_LIST', portList);

      if (cb !== undefined) {
        cb(undefined, results);
      }
    });
  },
};

const getters = {
  comm_port_list() {
    return state.commPortList;
  },
  comm_port() {
    return state.commPort;
  },
};

export default {
  state,
  mutations,
  actions,
  getters,
};
