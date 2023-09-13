<template>
    <div id="main-item">
    <form id="sidebar" @submit.prevent="generate">
        <input id="generate-btn" type="submit" value="Generate" />

        <select required name="algos" v-model="selectedAlgo">
          <option v-for="algo in genAlgos" :value="algo">{{ algo }}</option>
        </select>

        <button id="solve-btn" @click="solve" type="button">Solve</button>
        <select required name="solver" v-model="selectedSolver">
          <option v-for="solver in solverAlgos" :value="solver">{{ solver }}</option>
        </select>

        <button id="download-btn" @click="downloadMazeAsImg" type="button">Download as image</button>
        <label for="width">Width</label><input required min="5" max="200" id="maze-width" type="number" v-model=width>
        <label for="height">Height</label><input required min="5" max="200" id="maze-height" type="number" v-model=height>
    </form>
    </div>
</template>

<script>

    import {GenAlgos, SolveAlgos} from "../enums.js"

    export default {
        emits: ['generateMaze', 'solve'],
        data() {
            return {
                genAlgos: [GenAlgos.HUNT, GenAlgos.BACKTRACKING],
                selectedAlgo: GenAlgos.BACKTRACKING,
                solverAlgos : [SolveAlgos.A_STAR, SolveAlgos.DIJKSTRA],
                selectedSolver: SolveAlgos.A_STAR,
                width: 40,
                height: 30,
            }
        },

        methods:{
            generate(){
                this.$emit('generateMaze', this.selectedAlgo, this.width, this.height)
            },

            downloadMazeAsImg(){
                const canvas = document.getElementById("mazeCanvas")
                const img = canvas.toDataURL("image/png")

                let link = document.createElement('a');
                link.download = 'canvas_image.png';
                link.href = img;
                link.click();
            },

            solve(){
                this.$emit('solve', this.selectedSolver);
            }
        },
    }
</script>

<style type="text/css">
  #main-item{
    display: flex;
    flex-direction: column;
    flex-wrap: wrap;

    align-content: center;
    justify-content: center;
  }

  #main-item > form{
    display: flex;
    flex-direction: column;
    flex-wrap: wrap;

    align-content: center;
    justify-content: center;
  }
</style>
