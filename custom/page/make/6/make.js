document.addEventListener("svgLoaded", () => {
    scotch1();
});



function scotch1(){
    position_svg("scotch", 0, 0)
    position_svg("sound", 0, 0)
    setTimeout(scotch2, 200);
}

function scotch2(){
    move_svg("scotch", -80, 1)
    setTimeout(soundcard, 2200);
}

function soundcard(){
    move_svg("sound",-120,1);
    setTimeout(scotch1, 2400);
}