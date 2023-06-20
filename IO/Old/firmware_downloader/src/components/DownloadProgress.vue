<template>
<v-dialog
 v-model="show"
 fullscreen
 hide-overlay
 transition="dialog-bottom-transition"
>
  <v-card tile>
    <v-toolbar flat dark color="primary">
      <v-btn icon dark @click="$emit('close')" :disabled="dw_downloading">
        <v-icon>mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>Downloading Firmware</v-toolbar-title>
    </v-toolbar>
    <v-card-text>
      <v-stepper v-model="dw_step" vertical>
        <v-stepper-step :complete="dw_step > 1" step="1" :rules="[checkStep1]">
          Checking Running Mode
        </v-stepper-step>
        <v-stepper-content step="1">
          {{dw_message}}
        </v-stepper-content>

        <v-stepper-step :complete="dw_step > 2" step="2" :rules="[checkStep2]">
          Entering Boot Mode
        </v-stepper-step>
        <v-stepper-content step="2">
          {{dw_message}}
        </v-stepper-content>

        <v-stepper-step :complete="dw_step > 3" step="3" :rules="[checkStep3]">
          Programming Pages
        </v-stepper-step>
        <v-stepper-content step="3">
          <v-card>
            <v-card-text>
              <v-container fluid grid-list-lg>
                <v-layout row wrap justify-center>
                  <v-flex xs12>
                    <v-layout row wrap justify-center>
                      {{dw_message}}
                    </v-layout>
                  </v-flex>
                  <v-flex xs12>
                    <v-progress-linear
                     v-model="dw_progress"
                     color="blue-grey"
                     rounded
                     striped
                     height="30">
                      <template v-slot="{ value }">
                        <strong>{{ Math.ceil(value) }}%</strong>
                      </template>
                    </v-progress-linear>
                  </v-flex>
                </v-layout>
              </v-container>
            </v-card-text>
          </v-card>
        </v-stepper-content>

        <v-stepper-step :complete="dw_step > 4" step="4" :rules="[checkStep4]">
          Exiting Boot Mode
        </v-stepper-step>
        <v-stepper-content step="4">
          {{dw_message}}
        </v-stepper-content>

        <v-stepper-step :complete="dw_step >= 5" step="5">
          Done
        </v-stepper-step>
      </v-stepper>
    </v-card-text>
  </v-card>
</v-dialog>
</template>

<script>
import { mapGetters } from 'vuex';

export default {
  name: 'DownloadProgress',
  props: {
    show: { type: Boolean },
  },
  computed: {
    ...mapGetters([
      'dw_step',
      'dw_message',
      'dw_failed',
      'dw_progress',
      'dw_downloading',
    ]),
  },
  data() {
    return {
    };
  },
  methods: {
    checkStep(s) {
      if (this.dw_step === s && this.dw_failed === true) {
        return false;
      }
      return true;
    },
    checkStep1() {
      return this.checkStep(1);
    },
    checkStep2() {
      return this.checkStep(2);
    },
    checkStep3() {
      return this.checkStep(3);
    },
    checkStep4() {
      return this.checkStep(4);
    },
  },
};
</script>
