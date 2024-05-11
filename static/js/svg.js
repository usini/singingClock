function load_svg(svg_file, element) {
    fetch(svg_file).then(function (response) {
        return response.text();
    }).then(function (svg) {
        document.getElementById(element).innerHTML = svg;

        //Resize SVG to the size of the buttons underneath
        //resize_svg(element);
        const event = new Event("svgLoaded");
        document.dispatchEvent(event);
    }).catch(function (error) {
        console.log(error);
    });
}

function resize_svg(element) {
    console.log("Resize_svg");
    document.getElementById(element).children[0].setAttribute("width", document.getElementById("menu").offsetWidth);
}

// Responsive SVG

// Observe orientation change to resize SVG
//window.addEventListener("resize", (event) => {
//    resize_svg()
//});


