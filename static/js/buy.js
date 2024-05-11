product_variable = {}


function update_link() {
    fetch("custom/buy/buy.json").then(response => response.json()).then(function (json) {
        product_variable = json;
        reload_save();
        table = "";
        total = 0;
        item_id = 0;
        for (const component of product_variable) {
            price_euros = component.store[custom_variable.buy[item_id].store].price.toString().replace(".", ",");
            table += `
        <tr>
            <td>
            <select onchange="change_store(${item_id})" id="store_${item_id}">
            `;
            store_id = 0
            component.store.forEach((element) => {
                console.log(element);
                if (store_id == custom_variable.buy[item_id].store) {
                    table += `
                    <option value=${store_id} selected>${element.name}</option>
                    `
                } else {
                    table += `
                    <option value=${store_id}>${element.name}</option>
                `
                }
                store_id = store_id + 1;
            });
            table += `
            </select>
            </td>
            <td>${component.name}</td>
            <td><img src="${component.img}"></td>
            <td>${price_euros} €</td>
            <td><a href="${component.store[custom_variable.buy[item_id].store].link}">Achat</a></td>
            <td>
            <select onchange="change_status(${item_id})" id="status_${item_id}">
                <option value=0 selected>Non commandé</option>
                <option value=1>Acheté (0jours)</option>
                <option value=2>Reçu</option>
            </select>
            </td>
        </tr>
    `
            total += component.store[custom_variable.buy[item_id].store].price;
            item_id = item_id + 1;
        }
        total = total.toFixed(2);
        //console.log(table);
        document.getElementById("components").innerHTML = table;
        for(i=0;i< item_id;i++){
            document.getElementById("status_" + i).value = custom_variable.buy[i].status;
        }
        document.getElementById("total").innerHTML = "Total: " + total.toString().replace(".", ",") + " €";
    });
}

function reload_save() {
    if (localStorage.getItem("buy" + custom_variable["id"]) != null) {

        try {
            console.log("Loading save");
        } catch (error) {
            console.log("Save corrupted reset");
            build_save();
        }
    } else {
        console.log("Create save");
        build_save();

    }
    custom_variable.buy = JSON.parse(localStorage.getItem("buy" + custom_variable["id"]));
    if (custom_variable.buy.length != product_variable.length) {
        console.log("Save unsync for product list : need rebuild")
        build_save();
    } else {
        console.log("Save sync");
    }
}

function build_save() {
    custom_variable.buy = [];
    for (const component of product_variable) {
        custom_variable.buy.push({
            "store": 0,
            "status": 0
        })
    };
    console.log(custom_variable.buy);
    save();
}

function save() {
    localStorage.setItem("buy" + custom_variable["id"], JSON.stringify(custom_variable.buy));
}

function change_store(id){
    custom_variable.buy[id].store = parseInt(document.getElementById("store_"+id).value);
    save();
    update_link();
}

function change_status(id){
    custom_variable.buy[id].status = parseInt(document.getElementById("status_"+id).value);
    save();
    update_link();
}

update_link();
