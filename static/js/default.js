console.log("~~~~~~ 📄 PAGE GENERATOR ~~~~~~~~~~~~");



// Load translation
//var script_i18n = document.createElement('script');
//script_i18n.src = "static/js/i18n.js"
//document.head.appendChild(script_i18n);
json_to_text("custom/settings.json", "settings");


/* Theme Manager */
// Dark mode manager
if (localStorage.getItem("data-theme") == null) {
  localStorage.setItem("data-theme", "dark")
}


document.addEventListener("langLoaded", () => {
  includeHTML();
});

document.addEventListener("finishLoaded", () => {
  document.title = custom_variable["lang"].product_name;
  document.getElementById("product_name_navbar").innerHTML = custom_variable["lang"].product_name;
  document.getElementById("source_link").href = custom_variable["settings"].git_link;
  document.body.style.opacity = 1;
});

function change_theme() {
  theme = localStorage.getItem("data-theme")
  if (theme == "dark") {
    localStorage.setItem("data-theme", "light")
  } else {
    localStorage.setItem("data-theme", "dark")
  }
  change_theme_icon();
}

function change_theme_icon() {
  if (localStorage.getItem("data-theme") == "dark") {
    html_id = document.getElementById("theme").setAttribute("data-theme", "dark")
    document.getElementById("change-theme").innerHTML = "💡";
  } else {
    html_id = document.getElementById("theme").setAttribute("data-theme", "light")
    document.getElementById("change-theme").innerHTML = "🌑";
  }
}

function includeHTML() {
  var z, i, elmnt, file, xhttp;
  /* Loop through a collection of all HTML elements: */
  z = document.getElementsByClassName("w3");
  for (i = 0; i < z.length; i++) {
    elmnt = z[i];
    /*search for elements with a certain atrribute:*/
    file = elmnt.getAttribute("w3-include-html");
    if (file) {
      /* Make an HTTP request using the attribute value as the file name: */
      xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4) {
          if (this.status == 200) { elmnt.innerHTML = this.responseText; }
          if (this.status == 404) { elmnt.innerHTML = "Page not found."; }
          /* Remove the attribute, and call this function once more: */
          elmnt.removeAttribute("w3-include-html");
          console.log("📖 [HTML] " + file + ' ->  w3-include-html="'+file+'"');
          includeHTML();
          change_theme_icon();
          //console.log("Loading HTML");
          //console.log(i);
          if(i==(z.length-1)){
            translate_all(lang);
          }
        }
      }
      xhttp.open("GET", file, true);
      xhttp.send();
      /* Exit the function: */
      return;
    }
  }
  //translate_all(lang);
}

function includeMD(url, id) {
  return new Promise((resolve, reject) => {
    let page;
    if (navigator.language.includes("fr")) {
      page = "custom/page/" + url + "/translation/" + id + ".fr.md";
    } else {
      page = url + "/" + id + ".md";
    }

    fetch(page)
      .then(response => {
        if (!response.ok) {
          throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.text();
      })
      .then(text => {
        console.log('📖 [MD] ' + page + ' -> id="' + id + '"');
        document.getElementById(id).innerHTML = marked.parse(text);
        resolve();
      })
      .catch(error => {
        console.error('Error loading markdown:', error);
        reject(error);
      });
  });
}