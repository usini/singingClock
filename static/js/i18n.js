//Translator

// Language Selector
var script_lang = document.createElement('script');
translation = false;

if (navigator.language.includes("fr")) {
    script_lang.src = "static/js/lang/fr.js"
    document.head.appendChild(script_lang);
    translation = true;
    json_to_text("custom/text/fr.json", "lang");
} else {
    lang = {}
    translation = false;
    json_to_text("custom/text/en.json", "lang");
}

function translate_all(lang) {
    if (translation) {
        for (const [key, value] of Object.entries(document.querySelectorAll(".i18n"))) {
            translation = value.innerHTML;
            if (lang[translation] !== undefined) {
                value.innerHTML = lang[translation];
            }
        }
    }
    document.body.style.opacity = 1;
}
