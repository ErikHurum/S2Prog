module.exports = {
  /*
  configureWebpack: {
    externals: {
      bindings: "require('bindings')",
      serialport: "require('serialport')",
    },
  }, */
  pluginOptions: {
    electronBuilder: {
      externals: ['serialport'],
    },
  },
};
