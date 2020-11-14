<template>
  <div>
    <div class="header">
      <h1>Recuit simulator V10.2</h1>
    </div>

    <div class="container">
      <div class="right-section">
        <Form text="Démarrer la résolution" ref="formComponent" textInProgress="Résolution en cours..." @simulation-start="onSimulationStart"></Form>
      </div>

      <div class="left-section">
		  <Simulation ref="simulationComponent"></Simulation>
	  </div>
    </div>
  </div>
</template>

<script>
const path = require('path')
const follow = require('text-file-follower')

import Papa from "papaparse"

import Form from "./components/Form.vue"
import Simulation from "./components/Simulation.vue"

export default {
  components: {
    Form,
    Simulation,
  },
  data() {
    return {
      hasFinished: false
    }
  },
  methods: {
    onSimulationStart(event) {
      let filePath = event.path
      let finalTemp = event.finalTemp

      let count = 0;
      let modulo = 100;
      let follower = follow(filePath)

      follower
      .on('line', (filename, line) => {
        if(count > 0 && (count % modulo) === 0) {
          let parsed = Papa.parse(line)

          parsed.data.forEach(el => {
            this.$refs.simulationComponent.updateData(el);

            let temp = el[0]

            if(parseFloat(temp).toFixed(2) <= finalTemp && !this.hasFinished) {
              this.hasFinished = true;
              this.$refs.formComponent.toggleSimulationBtn()
            }else if(temp < 100) {
              modulo = 1000
            }else if(temp < 15) {
              modulo = 10000
            }else if(temp < 1) {
              modulo = 50000
            }
          });
        }

        count++;
      })
      .on('error', (err) => {
        console.log(err)
      })

      follower.close()
    }
  }
};
</script>
