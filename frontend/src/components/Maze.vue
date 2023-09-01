<script setup>
import Cell from './Cell.vue'
</script>

<template>
	<div id="maze">
		<div class="cell" v-for="cell in this.wallsList">
			<Cell :top=cell.top :right=cell.right :bottom=cell.bottom :left=cell.left ></Cell>
		</div>
	</div>
</template>

<script>
	export default {
        props : {
            width: Number,
            wallsList: Array,
        },
    }

</script>

<style>

#maze {
	display: grid;
	grid-template-columns: repeat(v-bind(width), 1fr);
}

</style>