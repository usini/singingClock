document.addEventListener("langLoaded", () => {
    document.getElementById("product_name").innerHTML = custom_variable["lang"].product_name;
    document.getElementById("product_description").innerHTML = custom_variable["lang"].product_description;
});

load_svg("custom/page/index.svg", "product");