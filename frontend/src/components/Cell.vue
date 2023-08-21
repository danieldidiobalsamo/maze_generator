<template>
    <div :style="drawWalls()"> </div>
</template>

<script>
    export default {
        props : {
            top : Boolean,
            right : Boolean,
            bottom : Boolean,
            left : Boolean
        },

        methods:{
            drawWalls(){
                let style = "width: 1vw; height: 1vw;"

                if(this.top)
                    style += "border-top-style:solid;"

                if(this.right)
                    style += "border-right-style:solid;"

                if(this.bottom)
                    style += "border-bottom-style:solid;"

                if(this.left)
                    style += "border-left-style:solid;"

                return style
            }
        }
    }
</script>