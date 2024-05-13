document.addEventListener("svgLoaded", () => {
    flux1();
});

function flux1(){
    stopanimated_svg("flux");
    move_svg("flux", 0, 0)
    setTimeout(flux2, 200);
}

function flux2(){
    animated_svg("flux",3);
    move_svg("flux", 42, 0)
    setTimeout(flux3, 3200);
}

function flux3(){
    animated_svg("flux",3);
    move_svg("flux", 0, 0)
    setTimeout(flux1, 3200);
}

