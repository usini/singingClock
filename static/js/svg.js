function load_svg(svg_file, element) {
    console.log("🖼️ [SVG] " + svg_file + " -> " + element);
    fetch(svg_file).then(function (response) {
        return response.text();
    }).then(function (svg) {
        document.getElementById(element).innerHTML = svg;

        //Resize SVG to the size of the buttons underneath
        resize_svg(element);
        // Observe orientation change to resize SVG
        window.addEventListener("resize", (event) => {
            resize_svg(element)
        });
        const event = new Event("svgLoaded");
        document.dispatchEvent(event);
    }).catch(function (error) {
        console.log(error);
    });
}

function resize_svg(element) {
    document.getElementById(element).children[0].setAttribute("width", window.visualViewport.width);
}
function move_svg(element, x, y) {
    //document.getElementById(element).setAttribute("transform", "translate(" + x + "," + y + ")");
    anime({
        targets: "#"+element,
        transform: "translate(" + x + "," + y + ")",
        easing: "linear",
        duration:2000
        //translateY: y
    })
}

function position_svg(element, x,y) {
    document.getElementById(element).setAttribute("transform", "translate(" + x + "," + y + ")");
}

function position_rotate_svg(element, deg, x,y) {
    document.getElementById(element).setAttribute("transform", "rotate(" + deg + "," + x + "," + y + ")");
}

// Responsive SVG
function animated_svg(element, speed) {
    document.getElementById(element).style.transition = "transform " + speed + "s ease";

}

function stopanimated_svg(element) {
    document.getElementById(element).style.transition = "";
}

function rotate_svg(element, deg, x, y) {
    anime({
        targets: "#"+element,
        transform: "rotate(" + deg + "," + x + "," + y + ")",
        easing:"linear",
        duration:2000
        //translateY: y
    })
}