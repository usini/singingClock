document.addEventListener("svgLoaded", () => {
    hot_air1();
    tweezers1();
});



function hot_air1(){
    stopanimated_svg("hot_air");
    move_svg("hot_air", 0, 0)
    setTimeout(hot_air2, 200);
}

function hot_air2(){
    animated_svg("hot_air",3);
    move_svg("hot_air", 42, 0)
    setTimeout(hot_air3, 3200);
}

function hot_air3(){
    animated_svg("hot_air",3);
    move_svg("hot_air", 0, 0)
    setTimeout(hot_air1, 3200);
}

function tweezers1(){
    stopanimated_svg("tweezers");
    stopanimated_svg("amp_chipset");
    move_svg("amp_chipset",0,0);
    move_svg("tweezers", 0, 0)
    setTimeout(tweezers2, 200);
}

function tweezers2(){
    animated_svg("tweezers",3);
    move_svg("tweezers", -60, 0)
    setTimeout(tweezers3, 3200);
}

function tweezers3(){
    animated_svg("tweezers",3);
    animated_svg("amp_chipset",3);
    move_svg("tweezers", 0, 0)
    move_svg("amp_chipset",42,0);
    setTimeout(tweezers1, 3200);
}