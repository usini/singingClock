document.addEventListener("svgLoaded", () => {
    cutter_reset();
});

function cutter_reset(){
    console.log("Cutter Reset");
    stopanimated_svg("cutter");
    move_svg("cutter", -120, 54)
    setTimeout(cutter_down, 200);
}

function cutter_down(){
    console.log("Cutter Down");
    animated_svg("cutter",3);
    move_svg("cutter", 0, 54)
    setTimeout(cutter_up_position, 3200);
}

function cutter_up_position(){
    console.log("Cutter Up Position");
    stopanimated_svg("cutter");
    rotate_svg("cutter",180,215,72)
    setTimeout(cutter_up, 200);
}

function cutter_up(){
    console.log("Cutter Up");
    animated_svg("cutter",3);
    rotate_svg("cutter", 180, 157,72);
    setTimeout(cutter_reset, 3200);
}

