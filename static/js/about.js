if (navigator.language.includes("fr")) {
    about_page = "custom/md/about.fr.md";
} else {
    about_page = "custom/md/about.md";
}

fetch(about_page).then(response => response.text()).then(function (text) {
   generate_about(text);
});


function generate_about(text){
document.getElementById('content').innerHTML =
      marked.parse(text);
}

