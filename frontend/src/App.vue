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

function getMaze(width, height){

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

</script>

<template>

  <aside>
    <Menu/>
  </aside>

  <main>
    <p id="hello"></p>
    <Maze :maze="getMaze(15, 20)" :width="15"/>
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