// Analyser l'URL pour obtenir les paramètres de requête
const urlParams = new URLSearchParams(window.location.search);

// Récupérer la valeur de la variable "page"
var pageArg = urlParams.get('page');
var script_make_url = "";
var make_page = "";
var make_image = "";

if (pageArg == null) {
    //console.log("page is null");
    script_make_url = "custom/page/make/1/make.js"
    make_page = "/1";
    make_image = "custom/page/make/1/make.svg";
} else {
    //console.log("Page is not null");
    script_make_url = "custom/page/make/" + pageArg + "/make.js"
    make_page = "/" + pageArg + "/";
    make_image = "custom/page/make/" + pageArg + "/make.svg";
}

console.log("🖲️ [JS] " + script_make_url);

var script_make = document.createElement('script');
script_make.src = script_make_url
document.head.appendChild(script_make);

includeMD("make" + make_page, "make");


pageArgInt = parseInt(pageArg);
//console.log(pageArgInt - 1)

if (pageArg == null) {
    document.getElementById("previous").setAttribute("disabled", true);
}
document.addEventListener("settingsLoaded", () => {
    if (pageArg == custom_variable.settings.make_pages) {
        document.getElementById("next").setAttribute("disabled", true);
    }
});

document.getElementById("previous").onclick = function () {
    previousPage();
}

document.getElementById("next").onclick = function () {
    nextPage();
}

function nextPage() {
    if (pageArg == null) {
        document.location.href = "?page=2";
    } else {
        document.location.href = "?page=" + (pageArgInt + 1);
    }
}

function previousPage() {
    if (pageArgInt >= 1) {
        if (pageArgInt == 2) {
            //console.log("Second Page")
            document.location.href = "make.html";
        } else {
            document.location.href = "?page=" + (pageArgInt - 1);
        }
    }
}

/*
function checkDirection() {
    if (touchendY < touchstartY) nextPage();
    if (touchendY > touchstartY) previousPage();
}

document.addEventListener('touchstart', e => {
    touchstartY = e.changedTouches[0].screenY
})

document.addEventListener('touchend', e => {
    touchendY = e.changedTouches[0].screenY
    checkDirection()
})
*/

document.addEventListener("keydown", function (event) {
    // Check if the pressed key is the one you're interested in
    console.log(event.key);
    if (event.key === "ArrowRight") {
        nextPage();
    }
    if (event.key === "ArrowLeft") {
        previousPage();
    }
});

load_svg(make_image, "image");
