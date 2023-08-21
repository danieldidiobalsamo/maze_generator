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
            wasmBackend: {}
        }
    },

    created(){
        MazeGenerator().then(back => this.wasmBackend = back)
    },

    components: {
        Menu
    },

    methods:{
      generate(algo, width, height){
        this.mazeCells = this.getMaze(width, height)
        this.width = width

        const hello = this.wasmBackend.ccall('helloWasm',
          'number',
          ['null'],
          [])

        document.getElementById("hello").textContent = hello
      },


      getMaze(width, height){
          // TODO : fetch wasm backend result

          let maze = []

          for (let col = 0; col < width; col++) {
              for (let row = 0; row < height; row++) {
                let cell = {
                  top: true,
                  right: false,
                  bottom: true,
                  left: true,
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
    <p id="hello"></p>
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