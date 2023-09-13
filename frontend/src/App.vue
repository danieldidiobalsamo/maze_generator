<script setup>
import Menu from './components/Menu.vue'
import Maze from './components/Maze.vue'

import { defineComponent } from 'vue'
</script>

<script>
import MazeGenerator from './assets/wasm/mazeGenerator.js'; // generated file (emcc wasm compiler)
import {GenAlgos, SolveAlgos} from "./enums.js"

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
        this.engineFacade = new instance["EngineFacade"]()
      })
    },

    components: {
        Menu
    },

    methods:{
      generate(algo, width, height){

        let cppEnum = {};

        switch(algo){
          case GenAlgos.HUNT:
            cppEnum = this.wasmInstance.GenerationAlgo.HuntAndKill
            break;
          case GenAlgos.BACKTRACKING:
            cppEnum = this.wasmInstance.GenerationAlgo.Backtracking
            break;
        }

        this.engineFacade.generateMaze(width, height, cppEnum);

        const metadataVector = this.engineFacade.getCellsMetadata()
        this.cellsMetadata = []

        for (let i = 0; i < metadataVector.size(); i++) {
          this.cellsMetadata.push(metadataVector.get(i))
        }

        this.width = width
        this.height = height
      },

      solve(algo){
        if(this.width != 0 || this.height !=0){
          let cppEnum = {};

          switch(algo){
            case SolveAlgos.A_STAR:
              cppEnum = this.wasmInstance.SolverAlgo.AStar
              break;
            case SolveAlgos.DIJKSTRA:
              cppEnum = this.wasmInstance.SolverAlgo.Dijkstra
              break;
          }

          let r = this.engineFacade.solve(cppEnum);

          const metadataVector = this.engineFacade.getCellsMetadata()
          this.cellsMetadata = []

          for (let i = 0; i < metadataVector.size(); i++) {
            this.cellsMetadata.push(metadataVector.get(i))
          }
        }
      },
  }
}
</script>

<template>

  <aside>
    <Menu @generateMaze="(algo, w, h) => this.generate(algo, w, h)" @solve="(algo) => this.solve(algo)"/>
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