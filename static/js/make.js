if (navigator.language.includes("fr")) {
    make_page = "custom/page/make/make.fr.md";
} else {
    make_page = "custom/page/make/make.md";
}

fetch(make_page).then(response => response.text()).then(function (text) {
    generate_make(text);
});


function generate_make(text) {
    document.getElementById('md1').innerHTML =
        marked.parse(text);
}

load_svg("custom/page/make/make.svg", "diagram");
