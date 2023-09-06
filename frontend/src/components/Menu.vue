<template>
    <div id="main-item">
    <form id="sidebar" @submit.prevent="generate">
      <input id="generate-btn" type="submit" value="Generate" />
      <button disabled id="solve-btn" type="button">Solve</button>
      <button id="download-btn" @click="downloadMazeAsImg" type="button">Download as image</button>

    <select required name="algos" v-model="selectedAlgo">
      <option v-for="algo in genAlgos" :value="algo">{{ algo.title }}</option>
    </select>

    <label for="width">Width</label><input required min="5" max="50" id="maze-width" type="number" v-model=width>
    <label for="height">Height</label><input required min="5" max="50" id="maze-height" type="number" v-model=height>

    </form>
    </div>
</template>

<script>
    export default {
        emits: ['generateMaze'],
        data() {
            return {
                genAlgos: [
                    { val: "hunt", title: 'Hunt and kill' },
                    ],
                selectedAlgo: {},
                width: 40,
                height: 30,
            }
        },

        methods:{
            generate(){
                this.$emit('generateMaze', this.selectedAlgo.val, this.width, this.height)
            },

            downloadMazeAsImg(){
                const canvas = document.getElementById("mazeCanvas")
                const img = canvas.toDataURL("image/png")

                let link = document.createElement('a');
                link.download = 'canvas_image.png';
                link.href = img;
                link.click();
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
