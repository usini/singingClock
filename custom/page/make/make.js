document.addEventListener("svgLoaded", () => {
    cutter_1();
});

function cutter_1(){
    console.log("Cutter Reset");
    stopanimated_svg("cutter");
    move_svg("cutter", 0, 0)
    setTimeout(cutter_2, 200);
}

function cutter_2(){
    console.log("Cutter Down");
    animated_svg("cutter",3);
    move_svg("cutter", 101, 1)
    setTimeout(cutter_3, 3200);
}

function cutter_3(){
    console.log("Cutter Up Position");
    stopanimated_svg("cutter");
    rotate_svg("cutter",180,165,100)
    setTimeout(cutter_4, 200);
}

function cutter_4(){
    console.log("Cutter Up");
    animated_svg("cutter",3);
    rotate_svg("cutter", 180, 115,100);
    setTimeout(cutter_1, 3200);
}

