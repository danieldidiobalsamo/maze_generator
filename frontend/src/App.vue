<script setup>
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
  <p id="hello"></p>
</template>