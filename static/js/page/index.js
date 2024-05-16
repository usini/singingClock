document.addEventListener("translateLoaded", function (event) {
    includeMD("index", "index")
    .then(() => {
        return load_svg("custom/page/index/index.svg", "index_image");
    })
        .then(() => {
            const event = new Event("finishLoaded");
            document.dispatchEvent(event);
        })
});

