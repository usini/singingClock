document.addEventListener("svgLoaded", () => {
    cutter_1();
});

function cutter_1(){
    //console.log("Cutter Reset");
    position_svg("cutter", 0, 0)
    setTimeout(cutter_2, 200);
}

function cutter_2(){
    //console.log("Cutter Down");
    move_svg("cutter", 101, 0)
    setTimeout(cutter_3, 2200);
}

function cutter_3(){
    //console.log("Cutter Up Position");
    position_rotate_svg("cutter",180,165,100)
    setTimeout(cutter_4, 200);
}

function cutter_4(){
    //console.log("Cutter Up");
    //move_svg("cutter", -101, 100);
    rotate_svg("cutter", 180, 115,100);
    setTimeout(cutter_1, 2200);
}

