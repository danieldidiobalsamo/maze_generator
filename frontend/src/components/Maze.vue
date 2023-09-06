<script setup>
import Cell from './Cell.vue'
</script>

<template>
    <canvas id="mazeCanvas">Maze</canvas>
</template>

<script>
    export default {
        props : {
            mazeWidth: Number,
            mazeHeight: Number,
            cellsMetadata: Array,
        },

        data(){
            return{
                canvas: {},
                ctx: {},
                cellWidth: 20,
                cellHeight: 20,
            }
        },

        mounted(){
            let canvas = document.getElementById("mazeCanvas");
            let ctx = canvas.getContext("2d");
            this.ctx = ctx;
            this.canvas = canvas;
        },

        watch:{
            cellsMetadata(list){
                this.ctx.canvas.width = (this.mazeWidth * this.cellWidth) + this.cellWidth
                this.ctx.canvas.height = (this.mazeHeight * this.cellHeight) + this.cellHeight

                this.ctx.beginPath();

                list.forEach((metadata, index)=>{
                    const row = (Math.floor(index % this.mazeWidth) * this.cellWidth) + this.cellWidth
                    // "+ this.cellWidth" to not start at borders, otherwise walls won't be rendered
                    const col = (Math.floor(index / this.mazeWidth) * this.cellHeight) + this.cellHeight

                    this.drawCell(row, col, this.cellWidth, this.cellHeight, metadata)
                })

                this.ctx.stroke();
            }
        },

        methods:{
            drawCell(x, y, w, h, metadata){
                const walls = metadata.walls;

                if(metadata.isPath){
                    this.ctx.fillStyle = "red";
                    this.ctx.fillRect(x - w / 4, y - h / 4, w*0.5, h*0.5);
                    this.ctx.fillStyle = "black";
                }

                if(walls.top){
                    this.drawWall(x - w/2, y - h/2, w + (h / 10), h / 10, false)
                }

                if(walls.bottom){
                    this.drawWall(x - w/2, y + h/2, w + (h / 10), h / 10, false)
                }

                if(walls.left){
                    this.drawWall(x - w/2, y - h/2, w, h / 10, true)
                }

                if(walls.right){
                    this.drawWall(x + w/2, y - h/2, w, h / 10, true)
                }
            },

            drawWall(x, y, w, h, vertical){

                if(vertical)
                {
                    this.ctx.fillRect(x, y, h, w);
                }
                else{
                    this.ctx.fillRect(x, y, w, h);
                }
            }
        }
    }

</script>

<style>

#maze {
    display: grid;
    grid-template-columns: repeat(v-bind(mazeWidth), 1fr);
}

</style>