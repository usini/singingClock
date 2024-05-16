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
    svg_element = document.getElementById(element).children[0];
    console.log("💻 Viewport: " + window.visualViewport.width +"x"+ window.visualViewport.height);
    svg_element.setAttribute("width", window.visualViewport.width);
    svg_element.setAttribute("height", window.visualViewport.height);
    if(window.visualViewport.width < window.visualViewport.height){
        console.log("📱Mobile detected - Change Orientation");
    }

    outside_screen_height = svg_element.getBoundingClientRect().bottom - window.visualViewport.height

    //Check if svg is outside screen
    if(outside_screen_height > 0){
        svg_element.setAttribute("height", svg_element.getAttribute("height") - outside_screen_height);
        outside_screen_height = svg_element.getBoundingClientRect().bottom - window.visualViewport.height
    }

    //Check if svg has unneeded space before previous element
    margin_previous_element = document.getElementById(element).previousElementSibling.getBoundingClientRect().bottom - svg_element.getBoundingClientRect().top
    console.log(margin_previous_element);
    if(margin_previous_element < 0){
        document.getElementById(element).style.marginTop = margin_previous_element + "px"
    }
    //onsole.log(svg_element.getBoundingClientRect().bottom);
    //console.log(window.visualViewport.height);


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

function transform_animation_svg(element, transform_text){
    anime({
        targets: "#"+element,
        transform: transform_text,
        easing:"linear",
        duration:2000
    })
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

