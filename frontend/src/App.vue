<script setup>
import Menu from './components/Menu.vue'
import Maze from './components/Maze.vue'
import Cell from './components/Cell.vue'
</script>

<script>
import MazeGenerator from './assets/wasm/mazeGenerator.js'; // generated file (emcc wasm compiler)

export default {

    data(){
        return{
            mazeCells: [],
            width: 0,
            wasmInstance: {},
        }
    },

    created(){
      MazeGenerator().then(instance => {
        this.wasmInstance = instance
        this.backend = new instance["BackEnd"]()
      })
    },

    components: {
        Menu
    },

    methods:{
      generate(algo, width, height){

        this.backend.setGenParams(width, height, algo)
        this.backend.generateMaze();

        this.mazeCells = this.getMazeCells(width, height)
        this.width = width
      },


      getMazeCells(width, height){
          let maze = []

          for (let row = 0; row < height; row++) {
              for (let col = 0; col < width; col++) {
                const walls = this.backend.getCell(row, col)

                const cell = {
                  top: walls.north,
                  right: walls.east,
                  bottom: walls.south,
                  left: walls.west,
                }

                maze.push(cell)
              }
          }
          return maze
      }
  }
}
</script>

<template>

  <aside>
    <Menu @generateMaze="(algo, w, h) => this.generate(algo, w, h)" />
  </aside>

  <main>
    <Maze :maze="this.mazeCells" :width="this.width"/>
  </main>
</template>

<style type="text/css">
  aside{
    float:left;
  }

  main{
    float:left;
    margin-left: 3vw;
  }
</style>