<template>
    <div id="main-item">
    <form id="sidebar" @submit.prevent="shortUrl">
      <input id="generate-btn" type="submit" value="Generate" />
      <button disabled id="solve-btn">Solve</button>
      <button disabled id="download-btn">Download as image <img src="" alt=""></button>

    <select required name="algos" id="algo-select">
      <option value="">--Generation algo--</option>
      <option value="Hunt and kill">Hunt and kill</option>
    </select>

    <label for="width">Width</label><input required min="5" max="999" id=width type="number">
    <label for="height">Height</label><input required min="5" max="999" id=height type="number">

    </form>
    </div>
</template>

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
