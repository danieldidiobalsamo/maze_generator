<script setup>
import Menu from './components/Menu.vue'
import Maze from './components/Maze.vue'
import Cell from './components/Cell.vue'
</script>

<script type="module">
import MazeGenerator from './assets/wasm/mazeGenerator.js'; // generated file (emcc wasm compiler)
let mazeGenerator = MazeGenerator().then(mod => {
    console.log("wasm loaded")

    const hello = mod.ccall('helloWasm',
          'number',
          ['null'],
          [])

    console.log(hello)
    document.getElementById("hello").textContent = hello
})

export default {

    data(){
        return{
            mazeCells: [],
            width: 0
        }
    },

    components: {
        Menu
    },

    methods:{
        generate(algo, width, height){
          this.mazeCells = this.getMaze(width, height)
          this.width = width
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