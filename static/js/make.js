// Analyser l'URL pour obtenir les paramètres de requête
const urlParams = new URLSearchParams(window.location.search);

// Récupérer la valeur de la variable "page"
var pageArg = urlParams.get('page');
var script_make_url = "";
var make_page = "";
var make_image = "";

if (pageArg == null) {
    console.log("page is null");
    script_make_url = "custom/page/make/make.js"
    make_page = "custom/page/make/make.";
    make_image = "custom/page/make/make.svg";
} else {
    console.log("Page is not null");
    script_make_url = "custom/page/make/" + pageArg + "/make_" + pageArg + ".js"
    make_page = "custom/page/make/" + pageArg + "/make_" + pageArg + ".";
    make_image = "custom/page/make/" + pageArg + "/make_" + pageArg + ".svg";
}

console.log(script_make_url);
console.log(make_page);

var script_make = document.createElement('script');
script_make.src = script_make_url
document.head.appendChild(script_make);

if (navigator.language.includes("fr")) {
    make_page = make_page + "fr.md";
} else {
    make_page = make_page + ".md";
}

fetch(make_page).then(response => response.text()).then(function (text) {
    generate_make(text);
});


function generate_make(text) {
    document.getElementById('text').innerHTML =
        marked.parse(text);
}

pageArgInt = parseInt(pageArg);
console.log(pageArgInt - 1)

if(pageArg == null){
    document.getElementById("previous").setAttribute("disabled", true);
}
document.addEventListener("settingsLoaded", () => {
    if(pageArg == custom_variable.settings.make_pages - 1){
        document.getElementById("next").setAttribute("disabled", true);
    }
});

document.getElementById("previous").onclick = function () {
    if (pageArgInt == 1) {
        console.log("Second Page")
        document.location.href = "make.html";
    } else {
        document.location.href = "?page=" + (pageArgInt - 1);
    }
}

document.getElementById("next").onclick = function () {
    if (pageArg == null) {
        document.location.href = "?page=1";
    } else {
        document.location.href = "?page=" + (pageArgInt + 1);
    }
}

load_svg(make_image, "image");
