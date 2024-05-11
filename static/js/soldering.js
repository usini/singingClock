function load_svg(svg_file, element) {
    fetch(svg_file).then(function (response) {
        return response.text();
    }).then(function (svg) {
        document.getElementById(element).innerHTML = svg;

        //Resize SVG to the size of the buttons underneath
        resize_svg();

        //Observe any size change
        const ro = new ResizeObserver(entries => {
            resize_svg();
        });
        document.getElementById("diagram").setAttribute("onclick", 'change_box_opacity()');

        ro.observe(document.getElementById("menu"));


    }).catch(function (error) {
    });
}


function resize_svg() {
    document.getElementById("diagram").children[0].setAttribute("width", document.getElementById("menu").offsetWidth);
}

// Responsive SVG

// Observe orientation change to resize SVG
window.addEventListener("orientationchange", (event) => {
    setTimeout(resize_svg, 200);
});


