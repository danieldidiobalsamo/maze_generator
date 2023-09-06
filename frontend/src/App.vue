<script setup>
import Menu from './components/Menu.vue'
import Maze from './components/Maze.vue'

import { defineComponent } from 'vue'
</script>

<script>
import MazeGenerator from './assets/wasm/mazeGenerator.js'; // generated file (emcc wasm compiler)

export default {

    data(){
        return{
            width: 0,
            height: 0,
            wasmInstance: {},
            cellsMetadata: [],
        }
    },

    created(){
      MazeGenerator().then(instance => {
        this.wasmInstance = instance
        this.backend = new instance["Backend"]()
      })
    },

    components: {
        Menu
    },

    methods:{
      generate(algo, width, height){

        this.backend.generateMaze(width, height, algo);

        const metadataVector = this.backend.getCellsMetadata()
        this.cellsMetadata = []

        for (let i = 0; i < metadataVector.size(); i++) {
          this.cellsMetadata.push(metadataVector.get(i))
        }

        this.width = width
        this.height = height
      },
  }
}
</script>

<template>

  <aside>
    <Menu @generateMaze="(algo, w, h) => this.generate(algo, w, h)" />
  </aside>

  <main>
    <Maze :cellsMetadata="this.cellsMetadata" :mazeWidth="this.width" :mazeHeight="this.height"/>
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

  #maze {
    display: grid;
    grid-template-columns: repeat(v-bind(width), 1fr);
  }
</style>