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
          @input="$v.computingMethod.$touch"
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
          @input="$v.computingMethod.$touch"
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
          @input="$v.randomizeMethod.$touch"
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
          @input="$v.randomizeMethod.$touch"
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
          @input="$v.randomizeMethod.$touch"
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
          @input="$v.initialTemp.$touch"
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
          @input="$v.finalTemp.$touch"
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
          @input="$v.reducingFactor.$touch"
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
          @input="$v.spreadingFactor.$touch"
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
          @change="setOutputFile"
          tabindex="-1"
        />
      </div>
      <div class="parameter__field">
        <label for="fileOutput">Nom du fichier de sortie</label>
        <input
          type="text"
          id="fileOutput"
          name="fileOutput"
          v-model="fileOutput"
          @input="$v.fileOutput.$touch"
        />
      </div>
    </div>

    <button
      class="resolve-btn"
      @click="startSimulation"
      :disabled="!this.isBtnActive"
    >
      {{ btnText }}
    </button>
  </div>
</template>

<script>
const fs = require("fs");
const process = require("process");

import { execFile } from "child_process";
import {
  required,
  between,
  numeric,
  decimal,
  minValue,
} from "vuelidate/lib/validators";

export default {
  props: {
    text: { type: String, required: true },
    textInProgress: { type: String, required: true },
  },
  data() {
    return {
      isBtnActive: true,
      isParamValid: false,
      hasInputFile: false,
      btnText: this.text,

      computingMethod: 0,
      randomizeMethod: 0,
      initialTemp: 200,
      finalTemp: 0.05,
      reducingFactor: 0.99999,
      spreadingFactor: 0.025,

      fileInput: null,
      fileOutput: "export",
    };
  },
  validations: {
    computingMethod: {
      required,
      numeric,
      between: between(0, 1),
    },
    randomizeMethod: {
      required,
      numeric,
      bewteen: between(0, 2),
    },
    initialTemp: {
      required,
      numeric,
      minValue: 0,
    },
    finalTemp: {
      required,
      decimal,
      minValue: 0,
    },
    reducingFactor: {
      required,
      decimal,
      between: between(0, 1),
    },
    spreadingFactor: {
      required,
      decimal,
      between: between(0, 1),
    },
    fileOutput: {
      required,
    },
  },
  methods: {
    checkForm() {
      if (this.$v.$invalid || !this.hasInputFile) {
        this.isParamValid = false;
        return false;
      }

      this.isParamValid = true;
      return true;
    },
    setOutputFile(event) {
      if (event.target.files.length <= 0) {
        this.isParamValid = false;
        this.hasInputFile = false;
        return;
      }

      this.fileInput = event.target.files[0].path;
      this.isParamValid = true;
      this.hasInputFile = true;
    },
    activateSimulationBtn() {
      this.isBtnActive = true;
      this.btnText = this.text;
    },
    deactivateSimulationBtn() {
      this.isBtnActive = false;
      this.btnText = this.textInProgress;
    },
    startSimulation() {
      if (!this.checkForm()) {
        this.$toast.error(
          "Impossible de lancer la résolution : paramètres incorrects."
        );
        return;
      }

      if (process.platform != "linux") {
        this.$toast.warning("Système d'exploitation non supporté.");
        return;
      }

      let that = this;
      this.deactivateSimulationBtn();

      if (!fs.existsSync("./outputs")) {
        fs.mkdirSync("./outputs");
      }

      fs.closeSync(fs.openSync("./outputs/" + this.fileOutput + ".csv", "w"));

      let executablePath = "./assets/exec/main";
      let parameters = [
        this.initialTemp,
        this.finalTemp,
        this.reducingFactor,
        this.spreadingFactor,
        this.fileInput,
        "./outputs/" + this.fileOutput,
        this.computingMethod,
        this.randomizeMethod,
        1,
      ];

      console.log("param: " + parameters);

      let proc = execFile(executablePath, parameters, function (
        err,
        stdout,
        stderr
      ) {
        if (err !== null) {
          console.error("exec error: " + err);
          that.$emit("simulation-failed");
        }
      });

      this.$toast.info("La résolution a démarré !");
      this.$emit("simulation-start", {
        path: "./outputs/" + this.fileOutput + ".csv",
        finalTemp: that.finalTemp,
      });

      proc.on("error", (err) => {
        that.toggleSimulationBtn();
        console.log("exec error: " + err);
        that.$emit("simulation-failed");
      });
    },
  },
  mounted() {
    this.$v.$touch();
    this.checkForm();
  },
};
</script>
