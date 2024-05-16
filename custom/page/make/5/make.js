document.addEventListener("svgLoaded", () => {
    hot_air1();
    tweezers1();
});



function hot_air1(){
    position_svg("hot_air", 0, 0)
    setTimeout(hot_air2, 200);
}

function hot_air2(){
    move_svg("hot_air", 10, 0)
    setTimeout(hot_air3, 2200);
}

function hot_air3(){
    move_svg("hot_air", 0, 0)
    setTimeout(hot_air1, 2200);
}

function tweezers1(){
    position_svg("led",0,0);
    position_svg("tweezers", 0, 0)
    setTimeout(tweezers2, 200);
}

function tweezers2(){
    move_svg("tweezers", -75, 0)
    setTimeout(tweezers3, 2200);
}

function tweezers3(){
    move_svg("tweezers", 0, 0)
    move_svg("led", 52,0);
    setTimeout(tweezers1, 2200);
}