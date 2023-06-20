<template>
  <v-app>
    <v-app-bar app>
      <v-toolbar-title class="headline text-uppercase">
        <span>Firmware Downloader</span>
      </v-toolbar-title>
      <v-spacer></v-spacer>

      <span class="mr-2">Version 0.1</span>
    </v-app-bar>

    <v-content>
      <FirmwareDownloader/>
    </v-content>
  </v-app>
</template>

<script>
import FirmwareDownloader from './components/FirmwareDownloader.vue';

export default {
  name: 'App',
  components: {
    FirmwareDownloader,
  },
  data: () => ({
    //
  }),
};
</script>
