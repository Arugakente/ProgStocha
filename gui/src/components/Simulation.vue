<template>
  <div>
    <h2>Résultats en temps réel</h2>

    <div class="chart">
      <canvas id="simulation" width="100%"></canvas>
    </div>

    <ul>
      <li>
        <p>Référence actuelle : <span v-if="actualRef !== null">{{ actualRef }}</span><span v-else>Non calculé</span></p>
      </li>
      <li>
        <p>Meilleur global : <span v-if="globalBest !== null">{{ globalBest }}</span><span v-else>Non calculé</span></p>
      </li>
      <li>
        <p>Meilleur chemin : <span v-if="globalBestPath !== null">{{ globalBestPath }}</span><span v-else>Non calculé</span></p>
      </li>
    </ul>
  </div>
</template>

<script>
import { Chart } from "chart.js";

export default {
  data() {
    return {
      actualRef: null,
      globalBest: null,
      globalBestPath: null,
      chart: null,
    };
  },
  methods: {
    clearData() {
      this.chart.data.labels = [];
      this.chart.data.datasets[0].data = [];
      this.chart.data.datasets[1].data = [];
      this.chart.data.datasets[2].data = [];
      this.chart.update();

      this.actualRef = null;
      this.globalBest = null;
      this.globalBestPath = null;
    },
    updateData(inData) {
      this.chart.data.labels.push(parseFloat(inData[0]).toFixed(2));

      // Global best
      this.chart.data.datasets[0].data.push(inData[3]);

      // Current reference
      this.chart.data.datasets[1].data.push(inData[2]);

      // Current energy
      this.chart.data.datasets[2].data.push(inData[1]);

      this.actualRef = parseFloat(inData[2]).toFixed(4);
      this.globalBest = parseFloat(inData[3]).toFixed(4);
      this.globalBestPath = inData[4];

      this.chart.update();
    },
  },
  mounted() {
    var ctx = document.getElementById("simulation").getContext("2d");

    this.chart = new Chart(ctx, {
      type: "line",
      data: {
        labels: [],
        datasets: [
          {
            label: "Meilleur global",
            data: [],
            fill: false,
            id: "y-axis-0",
            backgroundColor: "#db525a",
            borderColor: "#db525a",
            type: "line",
          },
          {
            label: "Référence actuelle",
            data: [],
            fill: false,
            id: "y-axis-1",
            backgroundColor: "#ff9c1d",
            borderColor: "#ff9c1d",
            type: "line",
          },
          {
            label: "Energie courante",
            data: [],
            fill: false,
            id: "y-axis-2",
            backgroundColor: "#4fadcf",
            borderColor: "#4fadcf",
            type: "scatter",
          },
        ],
      },
      options: {
        scales: {
          xAxes: [
            {
              labelString: "Température",
              display: true,
              reverse: true,
              ticks: {
                beginAtZero: true,
                suggestedMax: 200,
                stepSize: 100,
                autoSkip: true,
                maxTicksLimit: 12,
              },
              gridLines: {
                drawOnChartArea: false,
              },
            },
          ],
          yAxes: [
            {
              display: true,
              id: "y-axis-0",
              ticks: {
                beginAtZero: false,
                stepSize: 5000,
              },
            },
            {
              display: false,
              position: "left",
              id: "y-axis-1",
              ticks: {
                beginAtZero: false,
                stepSize: 5000,
              },
            },
            {
              display: false,
              id: "y-axis-2",
              ticks: {
                beginAtZero: false,
                stepSize: 5000,
              },
            },
          ],
        },
      },
    });
  },
};
</script>
