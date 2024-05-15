document.addEventListener("svgLoaded", () => {
    flux1();
});

function flux1(){
    position_svg("flux", 0, 0)
    setTimeout(flux2, 200);
}

function flux2(){
    move_svg("flux", 42, 0)
    setTimeout(flux3, 2200);
}

function flux3(){
    move_svg("flux", 0, 0)
    setTimeout(flux1, 2200);
}

