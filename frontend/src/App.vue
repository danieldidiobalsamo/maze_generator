<script setup>
import Menu from './components/Menu.vue'
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
</script>

<template>

  <aside>
    <Menu/>
  </aside>

  <main>
    <p id="hello"></p>
    <Cell :top="true" :right="true" :bottom="false" :left="true"></Cell>
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