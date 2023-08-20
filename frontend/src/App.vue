<script setup>
import Menu from './components/Menu.vue'
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
  </main>
</template>

<style type="text/css">
  aside{
    float:left;
  }
</style>