svg_debug = false;

svg_container = null;
svg_image = null;

computed_height = null;
computed_width = null;
computed_margintop = 0;
offset = 20;
offset_navbar = 90;

function load_svg(svg_file, element) {
    return new Promise((resolve, reject) => {
        console.log("🖼️ [SVG] " + svg_file + " -> " + element);
        fetch(svg_file)
            .then(response => {
                if (!response.ok) {
                    throw new Error(`HTTP error! status: ${response.status}`);
                }
                return response.text();
            })
            .then(svg => {
                document.getElementById(element).innerHTML = svg;

                // Resize SVG to the size of the buttons underneath
                resize_svg(element);

                // Observe orientation change to resize SVG
                window.addEventListener("resize", () => {
                    resize_svg(element);
                });

                resolve();
            })
            .catch(error => {
                console.error('Error loading SVG:', error);
                reject(error);
            });
    });
}

function resize_svg(element) {
    svg_container = document.getElementById(element);
    svg_image = document.getElementById(element).children[0];

    computed_width = svg_image.getAttribute("width");
    computed_height = svg_image.getAttribute("height");

    console.log("💻 Viewport: " + window.visualViewport.width + "x" + window.visualViewport.height);

    computed_width = window.visualViewport.width;
    computed_height = window.VisualViewport.height;

    if (svg_debug) {
        svg_image.style.backgroundColor = "purple";
    }
    //svg_element.setAttribute("height", window.visualViewport.height);

    if (window.visualViewport.width < window.visualViewport.height) {
        console.log("📱 Mobile detected ");
    }

    //no_margin_previous_svg();
    svg_max_height();

    svg_image.style.marginTop = computed_margintop + "px"
    svg_image.setAttribute("width", computed_width);
    svg_image.setAttribute("height", computed_height);
    console.log("🖼️ SVG WIDTH: " + computed_width);
    console.log("🖼️ SVG HEIGHT: " + computed_height);
    console.log("🖼️ SVG MARGIN:" + computed_margintop);

    //onsole.log(svg_element.getBoundingClientRect().bottom);
    //console.log(window.visualViewport.height);
}

function svg_max_height() {
    computed_height = window.visualViewport.height - svg_image.getBoundingClientRect().top;
    /*
    computed_height = window.visualViewport.height
    outside_screen_height = svg_image.getBoundingClientRect().bottom - window.visualViewport.height
    console.log("📏 [HEIGHT BOTTOM <--> SVG] " + outside_screen_height);

    computed_height = computed_height - outside_screen_height;
    console.log(computed_height);
    //computed_height = computed_height - 1000;
    */
}

//Check if svg has unneeded space before previous element
function no_margin_previous_svg() {
    var margin_previous_element = svg_container.previousElementSibling.getBoundingClientRect().bottom - svg_image.getBoundingClientRect().top
    console.log("📏 [MARGIN] WEB " + svg_container.previousElementSibling.getBoundingClientRect().bottom + " <--> " + svg_image.getBoundingClientRect().top + " SVG =" + margin_previous_element);
    computed_margintop = (margin_previous_element + offset);

}


// SVG Animation

function move_svg(element, x, y) {
    //document.getElementById(element).setAttribute("transform", "translate(" + x + "," + y + ")");
    anime({
        targets: "#" + element,
        transform: "translate(" + x + "," + y + ")",
        easing: "linear",
        duration: 2000
        //translateY: y
    })
}

function position_svg(element, x, y) {
    document.getElementById(element).setAttribute("transform", "translate(" + x + "," + y + ")");
}

function position_rotate_svg(element, deg, x, y) {
    document.getElementById(element).setAttribute("transform", "rotate(" + deg + "," + x + "," + y + ")");
}

// Responsive SVG
function animated_svg(element, speed) {
    document.getElementById(element).style.transition = "transform " + speed + "s ease";
}

function stopanimated_svg(element) {
    document.getElementById(element).style.transition = "";
}

function transform_animation_svg(element, transform_text) {
    anime({
        targets: "#" + element,
        transform: transform_text,
        easing: "linear",
        duration: 2000
    })
}

function rotate_svg(element, deg, x, y) {
    anime({
        targets: "#" + element,
        transform: "rotate(" + deg + "," + x + "," + y + ")",
        easing: "linear",
        duration: 2000
        //translateY: y
    })
}

