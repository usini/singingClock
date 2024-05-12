console.log("Product");
audio_element = new Audio();
audio_element.volume = 0.5;
document.addEventListener("svgLoaded", () => {
    refreshTime();

    onNewMinute(() => {
        refreshTime();
    });

    document.getElementById("unmute").addEventListener("click", function () {
        document.getElementById("unmute").style = "display:none"
        document.getElementById("mute").style = ""
        console.log("Unmute invisible");
        audio_element.volume = 0;
    });

    document.getElementById("mute").addEventListener("click", function () {
        document.getElementById("mute").style = "display:none"
        document.getElementById("unmute").style = ""
        console.log("mute invisible");
        audio_element.volume = 0.5;
    });

    document.getElementById("play").addEventListener("click", function () {
        console.log("play pressed");

        randomAudio(true);
    });
});

async function randomAudio(forced) {
    const now = new Date();
    hours = now.getHours();
    minutes = now.getMinutes();
    if (hours < 10) {
        hours = "0" + hours;
    }
    if (minutes < 10) {
        minutes = "0" + minutes;
    }
    if (forced) {
        path = "custom/audio/" + hours + "-00";
    } else {
        path = "custom/audio/" + hours + "-" + minutes;
    }
    const response = await fetch(path + ".txt");
    fileNames = (await response.text()).trim();
    fileNames = fileNames.split("\n");
    audioFile = fileNames[Math.floor(Math.random() * fileNames.length)];
    audio_element.src = path + "/" + audioFile
    audio_element.play();
}

function refreshTime() {
    // Create a Date object for the current time
    const now = new Date();
    // Get the browser's preferred language
    const userLanguage = navigator.language; // Example: 'en-US', 'fr-FR', etc.

    // Use Intl.DateTimeFormat to get the localized weekday name
    const dayFormatter = new Intl.DateTimeFormat(userLanguage, { weekday: 'long' });
    const day = dayFormatter.format(now); // Returns the localized name of the weekday

    // Get the day of the month and the month (months are zero-based)
    const dayOfMonth = now.getDate();
    const month = now.getMonth() + 1; // Add 1 to get the correct month number

    // Format the day of the month and month to ensure they have two digits
    const formattedDayOfMonth = dayOfMonth.toString().padStart(2, '0');
    const formattedMonth = month.toString().padStart(2, '0');

    // Construct the "DAY XX/XX" format
    const formattedDate = `${day} ${formattedDayOfMonth}/${formattedMonth}`;

    // Get the hours and minutes
    const hours = now.getHours();
    const minutes = now.getMinutes();

    // Format with leading zeros to ensure two digits
    const formattedHours = hours.toString().padStart(2, '0');
    const formattedMinutes = minutes.toString().padStart(2, '0');

    // Concatenate the hours and minutes to get the format XX:XX
    const currentTime = `${formattedHours}:${formattedMinutes}`;

    document.getElementById("time").textContent = currentTime;
    document.getElementById("date").textContent = formattedDate;
    randomAudio();
}

function onNewMinute(callback) {
    // D'abord, on obtient le temps actuel
    const now = new Date();

    // Calculer les millisecondes jusqu'au début de la prochaine minute
    const msUntilNextMinute =
        (60 - now.getSeconds()) * 1000 - now.getMilliseconds();

    // Fixer un délai jusqu'à la prochaine minute
    setTimeout(() => {
        // Exécute l'action au début de la minute
        callback();

        // Ensuite, mettre en place un intervalle de 60 secondes
        setInterval(callback, 60 * 1000);
    }, msUntilNextMinute);
}

