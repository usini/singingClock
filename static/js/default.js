console.log("~~~~~~ 📄 PAGE GENERATOR ~~~~~~~~~~~~");

includeHTML();
custom_variable = {};

async function json_to_text(var_link, variable) {
  try {
    const response = await fetch(var_link);
    if (!response.ok) {
      throw new Error("Can't find " + var_link)
    }
    const jsonData = await response.json();
    console.log("🗓️ [JSON] " + var_link + " -> custom_variable." + variable);
    custom_variable[variable] = jsonData;
    const event = new Event(variable + "Loaded");
    document.dispatchEvent(event);
  } catch (error) {
    console.error('Fetch Error:', error);
    return null;
  }
}

// Load translation
var script_i18n = document.createElement('script');
script_i18n.src = "static/js/i18n.js"
document.head.appendChild(script_i18n);
json_to_text("custom/settings.json", "settings");


/* Theme Manager */
// Dark mode manager
if (localStorage.getItem("data-theme") == null) {
  localStorage.setItem("data-theme", "dark")
}

document.addEventListener("langLoaded", () => {
  document.getElementById("product_name_navbar").innerHTML = custom_variable["lang"].product_name;
  document.title = custom_variable["lang"].product_name;
});

document.addEventListener("settingsLoaded", () => {
  document.getElementById("source_link").href = custom_variable["settings"].git_link;
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
  z = document.getElementsByTagName("*");
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
        }
      }
      xhttp.open("GET", file, true);
      xhttp.send();
      /* Exit the function: */
      return;
    }
  }
}

function includeMD(url, id) {
  if (navigator.language.includes("fr")) {
    page = "custom/page/" + url + "/translation/"+id+".fr.md";
  } else {
    page = url +"/" + id+".md";
  }

  fetch(page).then(response => response.text()).then(function (text) {
    console.log('📖 [MD] ' + page + ' -> id="' + id + '"');
    document.getElementById(id).innerHTML = marked.parse(text);
  });
}