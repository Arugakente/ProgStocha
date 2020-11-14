<template>
  <div>
    <h2>Paramètres</h2>

    <div class="parameter">
      <h3 class="parameter__title">
        Méthode de calcul d'une 1ère sol. approchée
      </h3>

      <div class="parameter__field">
        <input
          type="radio"
          id="computingMethod0"
          name="computingMethod"
          v-model="computingMethod"
          :value="0"
        />
        <label for="computingMethod0">Aléatoire</label>
      </div>
      <div class="parameter__field">
        <input
          type="radio"
          id="computingMethod1"
          name="computingMethod"
          v-model="computingMethod"
          :value="1"
        />
        <label for="computingMethod1">Glouton</label>
      </div>
    </div>

    <div class="parameter">
      <h3 class="parameter__title">Randomisation</h3>

      <div class="parameter__field">
        <input
          type="radio"
          id="randomizeMethod0"
          name="randomizeMethod"
          v-model="randomizeMethod"
          :value="0"
        />
        <label for="randomizeMethod0">Simple</label>
      </div>
      <div class="parameter__field">
        <input
          type="radio"
          id="randomizeMethod1"
          name="randomizeMethod"
          v-model="randomizeMethod"
          :value="1"
        />
        <label for="randomizeMethod1">Multiple</label>
      </div>
      <div class="parameter__field">
        <input
          type="radio"
          id="randomizeMethod2"
          name="randomizeMethod"
          v-model="randomizeMethod"
          :value="2"
        />
        <label for="randomizeMethod2">Par bloc de taille 3</label>
      </div>
    </div>

    <div class="parameter">
      <h3 class="parameter__title">Recuit simulé</h3>

      <div class="parameter__field">
        <label for="initialTemp">Température initiale</label>
        <input
          type="number"
          id="initialTemp"
          name="initialTemp"
          v-model="initialTemp"
          min="0"
        />
      </div>
      <div class="parameter__field">
        <label for="finalTemp">Température finale</label>
        <input
          type="number"
          id="finalTemp"
          name="finalTemp"
          v-model="finalTemp"
          min="0"
          step="0.01"
        />
      </div>
      <div class="parameter__field">
        <label for="reducingFactor">Facteur de diminution</label>
        <input
          type="number"
          id="reducingFactor"
          name="reducingFactor"
          v-model="reducingFactor"
          min="0"
          max="1"
          step="0.01"
        />
      </div>

      <h3 class="parameter__title">Stochastique</h3>

      <div class="parameter__field">
        <label for="spreadingFactor">Facteur d'étalement</label>
        <input
          type="number"
          id="spreadingFactor"
          name="spreadingFactor"
          v-model="spreadingFactor"
          min="0"
          max="1"
          step="0.01"
        />
      </div>
    </div>

    <div class="parameter">
      <h3 class="parameter__title">Entrée/Sortie</h3>

      <div class="parameter__field">
        <label for="datasetInput">Dataset à charger</label>
        <input
          type="file"
          id="datasetInput"
          name="datasetInput"
          accept=".tsp"
        />
      </div>
      <div class="parameter__field">
        <label for="fileOutput">Fichier de sortie</label>
        <input
          type="file"
          id="fileOutput"
          name="fileOutput"
          webkitdirectory
          mozdirectory
          msdirectory
          odirectory
          directory
        />
      </div>
    </div>

    <button class="resolve-btn" @click="startSimulation" :disabled="!this.isBtnActive">
      {{ btnText }}
    </button>
  </div>
</template>

<script>
const fs = require('fs')

import {execFile} from 'child_process'

export default {
  props: {
    text: {type:String, required:true},
    textInProgress: {type:String, required:true}
  },
  data() {
    return {
      isBtnActive: true,
      btnText: this.text,

      computingMethod: 0,
      randomizeMethod: 0,
      initialTemp: 200,
      finalTemp: 0.05,
      reducingFactor: 0.99999,
      spreadingFactor: 0.025,
    };
  },
  methods: {
    toggleSimulationBtn() {
      if(this.isBtnActive) {
        this.isBtnActive = false
        this.btnText = this.textInProgress
      }else{
        this.isBtnActive = true
        this.btnText = this.text
      }
    },
    startSimulation() {
      this.toggleSimulationBtn()

      console.log("exec param : " + this.initialTemp + " " + this.finalTemp + " " + this.reducingFactor + " " + this.spreadingFactor + " /in /out " + this.computingMethod + " " + this.randomizeMethod);

      fs.closeSync(fs.openSync("./test.csv", 'w'))

      let executablePath = './assets/exec/main';
      let parameters = [this.initialTemp, this.finalTemp, this.reducingFactor, this.spreadingFactor, "../data/berlin52.tsp", "./test", this.computingMethod, this.randomizeMethod, 1];
      let proc = execFile(executablePath, parameters, function(err, stdout, stderr) {
        if(err !== null) {
          console.error('exec error: ' + err)
        }
      })

      this.$emit('simulation-start', {path:"./test.csv", finalTemp: this.finalTemp})

      proc.on('error', (err) => {
        this.toggleSimulationBtn()
        console.log('exec error: ' + err)
        this.$emit('simulation-failed')
      })
    }
  },
};
</script>
