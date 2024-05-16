//Translator
custom_variable = {};
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

function translate_all(lang) {
    if (translation) {
        for (const [key, value] of Object.entries(document.querySelectorAll(".i18n"))) {
            translation = value.innerHTML;
            if (lang[translation] !== undefined) {
                console.log("🗣️[LANG] " + value.innerHTML + " -> " + lang[translation]);
                value.innerHTML = lang[translation];
            }
        }
    }
    const event = new Event("translateLoaded");
    document.dispatchEvent(event);
}
