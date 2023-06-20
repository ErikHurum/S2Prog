<template>
<v-container>
  <v-layout
    text-center
    wrap
  >
    <v-flex xs12>
      <v-img
        :src="require('../assets/logo.svg')"
        class="my-3"
        contain
        height="200"
      ></v-img>
    </v-flex>

    <v-flex mb-4>
      <h1 class="display-2 font-weight-bold mb-3">
        Welcome to Firmware Downloader
      </h1>
    </v-flex>

    <v-flex mb-5 xs12>
      <v-stepper v-model="config_step" vertical>
        <v-stepper-step :complete="fw_valid" step="1">
          Select Firmware
          <small>Select Firmware File to Download</small>
        </v-stepper-step>
        <v-stepper-content step="1">
          <v-card color="grey lighten-1" class="mb-12">
            <v-card-title>
              {{fw_valid ? fw_filename : 'No Firmware Selected'}}
              <v-spacer></v-spacer>
              <v-btn color="primary"
               @click="$store.dispatch('loadFirmware')">
                Select Firmware
              </v-btn>
            </v-card-title>
            <v-card-text>
              <v-container fluid grid-list-lg>
                <v-layout row wrap>
                  <v-flex xs3>
                    <h3>Size</h3>
                  </v-flex>
                  <v-flex xs9>
                    <h3>{{fw_size}}&nbsp;bytes</h3>
                  </v-flex>

                  <v-flex xs3>
                    <h3>Number of Pages</h3>
                  </v-flex>
                  <v-flex xs9>
                    <h3>{{fw_num_pages}}&nbsp; pages</h3>
                  </v-flex>

                </v-layout>
              </v-container>
            </v-card-text>
          </v-card>
          <v-btn color="primary" :disabled="!fw_valid" @click="config_step = 2">Continue</v-btn>
        </v-stepper-content>

        <v-stepper-step :complete="commPort !== 'None'" step="2">
          Select Communication Port
        </v-stepper-step>
        <v-stepper-content step="2">
          <v-card color="grey lighten-1" class="mb-12">
            <v-card-title>
              <v-select v-model="commPort"
                        :items="comm_port_list"
                        label="Comm Port"/>
              <v-spacer></v-spacer>

              <v-tooltip bottom>
                <template v-slot:activator="{ on }">
                  <v-btn text icon v-on="on" @click="refreshPortList()">
                    <v-icon large>mdi-refresh</v-icon>
                  </v-btn>
                </template>
                <span>Refresh Port List</span>
              </v-tooltip>

            </v-card-title>
          </v-card>
          <v-btn color="primary"
                 :disabled="commPort === 'None'"
                 @click="config_step = 3">
            Continue
          </v-btn>
          <v-btn text @click="config_step = 1">Back</v-btn>
        </v-stepper-content>

        <v-stepper-step :complete="config_step > 3" step="3">
          Select Slave Address
        </v-stepper-step>
        <v-stepper-content step="3">
          <v-card color="grey lighten-1" class="mb-12">
            <v-card-title>
              <v-select v-model="slaveAddress"
                        :items="dw_valid_addresses"
                        label="Slave Address"/>
            </v-card-title>
          </v-card>
          <v-btn color="primary" @click="config_step = 4">Continue</v-btn>
          <v-btn text @click="config_step = 2">Back</v-btn>
        </v-stepper-content>

        <v-stepper-step :complete="config_step > 4" step="4">
          Download Firmware
        </v-stepper-step>
        <v-stepper-content step="4">
          <v-card color="grey lighten-1" class="mb-12">
            <v-card-title>
              Ready to Download
              <v-spacer></v-spacer>
            </v-card-title>
            <v-card-text>
              <v-container fluid grid-list-lg>
                <v-layout row wrap>
                  <v-flex xs3>
                    <h3>Size</h3>
                  </v-flex>
                  <v-flex xs9>
                    <h3>{{fw_size}}&nbsp;bytes</h3>
                  </v-flex>

                  <v-flex xs3>
                    <h3>Number of Pages</h3>
                  </v-flex>
                  <v-flex xs9>
                    <h3>{{fw_num_pages}}&nbsp; pages</h3>
                  </v-flex>

                  <v-flex xs3>
                    <h3>Comm Port</h3>
                  </v-flex>
                  <v-flex xs9>
                    <h3>{{commPort}}</h3>
                  </v-flex>

                  <v-flex xs3>
                    <h3>Slave Address</h3>
                  </v-flex>
                  <v-flex xs9>
                    <h3>{{slaveAddress}}</h3>
                  </v-flex>

                </v-layout>
              </v-container>
            </v-card-text>
          </v-card>
          <v-btn color="primary" @click="startDownload()">Download</v-btn>
          <v-btn text @click="config_step = 3">Back</v-btn>
        </v-stepper-content>
      </v-stepper>
    </v-flex>
  </v-layout>

  <v-dialog max-width="50%"
    persistent
    v-model="portRefreshDlg.show"
    hide-overlay>
    <v-card color="primary">
      <v-card-text>
        <v-container fluid grid-list-lg>
          <v-layout row wrap justify-center>
            Updating Port List
          </v-layout>
          <v-divider/>
          <v-layout row wrap justify-center>
            <v-progress-circular :size="50"
             color="green"
             indeterminate
            />
          </v-layout>
        </v-container>
      </v-card-text>
    </v-card>
  </v-dialog>

  <DownloadProgress :show="progress.show" @close="progress.show = false"/>
</v-container>
</template>

<script>
import { mapGetters } from 'vuex';
import DownloadProgress from './DownloadProgress.vue';

export default {
  name: 'FirmwareDownloader',
  components: {
    DownloadProgress,
  },
  data: () => ({
    portRefreshDlg: {
      show: false,
    },
    progress: {
      show: false,
    },
    config_step: 1,
  }),
  computed: {
    ...mapGetters([
      'fw_valid',
      'fw_filename',
      'fw_pages',
      'fw_size',
      'fw_num_pages',
      'comm_port_list',
      'comm_port',
      'dw_address',
      'dw_valid_addresses',
    ]),
    commPort: {
      get() {
        return this.comm_port;
      },
      set(v) {
        this.$store.commit('COMM_PORT_SET', v);
      },
    },
    slaveAddress: {
      get() {
        return this.dw_address;
      },
      set(v) {
        this.$store.commit('DW_SET_ADDRESS', v);
      },
    },
  },
  methods: {
    refreshPortList() {
      this.portRefreshDlg.show = true;
      this.$store.dispatch('refreshPortList', () => {
        setTimeout(() => {
          this.portRefreshDlg.show = false;
        }, 1000);
      });
    },
    startDownload() {
      this.progress.show = true;
      this.$store.dispatch('startDownload');
    },
  },
  mounted() {
    this.refreshPortList();
  },
};
</script>
