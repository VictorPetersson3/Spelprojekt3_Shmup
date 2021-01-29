function valueOf(id, value) {
    if (value == undefined)
        return document.getElementById(id).value;
    else
        document.getElementById(id).value = value;
}

// Download file to Client
function downloadToFile(content, filename, contentType)
{
    const file = new Blob([content], { type: contentType });

    const a = document.createElement("a");
    a.href = URL.createObjectURL(file);
    a.download = filename;
    a.click();

    URL.revokeObjectURL(a.href);
}

// Save level to file
function exportEnemy()
{
    let data = {};

    // Hp
    data["HealthPoints"] = ~~valueOf("health-points");

    let option = valueOf("m-select");
    let movement = {};
    movement["Type"] = option;
    switch (option) {
        case "Straight":
            movement["Speed"] = ~~valueOf("mp-speed");
            break;
        case "Diagonal":
            movement["Speed"] = ~~valueOf("mp-speed");
            movement["SpawnInCorner"] = valueOf("mp-corner");
            break;
        case "Wave":
            movement["HorizontalSpeed"] = ~~valueOf("mp-horizontal-speed");
            movement["VerticalSpeed"] = ~~valueOf("mp-vertical-speed");
            movement["Height"] = ~~valueOf("mp-height");
            break;
        case "Bobbing":
            movement["Speed"] = ~~valueOf("mp-speed");
            movement["Height"] = ~~valueOf("mp-height");
            break;
        case "Seeking":
            movement["Speed"] = ~~valueOf("mp-speed");
            movement["Acceleration"] = ~~valueOf("mp-acceleration");
            break;
        case "Homing":
            movement["Speed"] = ~~valueOf("mp-speed");
            break;
        case "U-Turn":
            movement["Speed"] = ~~valueOf("mp-speed");
            movement["Width"] = ~~valueOf("mp-width");
            movement["Height"] = ~~valueOf("mp-height");
            break;
        default: break;
    }
    data["Movement"] = movement;

    let bullet = {};
    bullet["Type"] = valueOf("bullet-type");
    bullet["Speed"] = ~~valueOf("bullet-speed");
    bullet["ShootTowardsPlayer"] = valueOf("bullet-pattern") == "Yes" ? true : false;
    data["Bullet"] = bullet;

    let name = valueOf("file-name");
    downloadToFile(JSON.stringify(data) + "\n", name, "application/json");

    console.log("Exported", data);
}

// Read file
function importEnemy(e)
{
    const file = e.target.files[0];
    document.getElementById("file-name").value = file.name;
    const reader = new FileReader();
    reader.onload = function (e)
    {
        let content = JSON.parse(e.target.result);
        console.log("Imported", content);

        let movement = content["Movement"];
        document.getElementById("m-select").value = movement["Type"];
        changeMovementParameters(undefined);

        switch (movement["Type"])
        {
        case "Straight":
            valueOf("mp-speed", movement["Speed"]);
            break;
        case "Diagonal":
            valueOf("mp-speed", movement["Speed"]);
            valueOf("mp-corner", movement["SpawnInCorner"]);
            break;
        case "Wave":
            valueOf("mp-speed", movement["Speed"]);
            valueOf("mp-horizontal-speed", movement["HorizontalSpeed"]);
            valueOf("mp-vertical-speed", movement["VerticalSpeed"]);
            valueOf("mp-height", movement["Height"]);
            break;
        case "Bobbing":
            valueOf("mp-speed", movement["Speed"]);
            valueOf("mp-height", movement["Height"]);
            break;
        case "Seeking":
            valueOf("mp-speed", movement["Speed"]);
            valueOf("mp-acceleration", movement["Acceleration"]);
            break;
        case "Homing":
            valueOf("mp-speed", movement["Speed"]);
            break;
        case "U-Turn":
            valueOf("mp-speed", movement["Speed"]);
            valueOf("mp-width", movement["Width"]);
            valueOf("mp-height", movement["Height"]);
            break;
        default: break;
        }

        let bullet = content["Bullet"];
        valueOf("bullet-type", bullet["Type"]);
        valueOf("bullet-speed", bullet["Speed"]);
        valueOf("bullet-pattern", bullet["ShootTowardsPlayer"] ? "Yes" : "No");
    }
    reader.readAsText(file);
}

changeMovementParameters(undefined);
function changeMovementParameters(e)
{
    let option = e == undefined ? valueOf("m-select") : e.target.value;
    console.log("Selected", option);

    let holder = document.getElementById("movement-parameters");

    let template = "null";
    switch (option) {
        case "Straight":
            template = `
                <p>
                    Speed
                    <input id="mp-speed" type="number" value="0">
                    (pixels/second)
                </p>
            `;
            break;
        case "Diagonal":
            template = `
                <p>
                    Speed
                    <input id="mp-speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    <span>Path: Start from</span>
                    <select id="mp-corner">
                        <option>Top</option>
                        <option>Bottom</option>
                    </select>
                </p>
            `;
            break;
        case "Wave":
            template = `
                <p>
                    Horizontal (&#8644;) Speed 
                    <input id="mp-horizontal-speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Vertical (&#8645;) Speed 
                    <input id="mp-vertical-speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Wave Height
                    <input id="mp-height" type="number" value="0">
                    (pixels)
                </p>
            `;
            break;
        case "Bobbing":
            template = `
                <p>
                    Speed 
                    <input id="mp-speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Wave Height
                    <input id="mp-height" type="number" value="0">
                    (pixels)
                </p>
            `;
            break;
        case "Seeking":
            template = `
                <p>
                    Speed
                    <input id="mp-speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Acceleration
                    <input id="mp-acceleration" type="number" value="0">
                    (pixels/second&sup2;)
                </p>
            `;
            break;
        case "Homing":
            template = `
                <span class="error">Ej Implementerat</span>
                <p>
                    Speed
                    <input id="mp-speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Turning Speed <span class="error">Ej Implementerat</span>
                </p>
            `;
            break;
        case "U-Turn":
            template = `
                <span class="error">Ej Implementerat</span>
                <p>
                    Speed
                    <input id="mp-speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Width
                    <input id="mp-width" type="number" value="0">
                    (pixels)
                </p>
                <p>
                    Height
                    <input id="mp-height" type="number" value="0">
                    (pixels)
                </p>
            `;
            break;
        default: break;
    }
    holder.innerHTML = template;
}

function updateBobbingPercentage(e)
{
    document.getElementById("mp-bobbing-range-indicator").textContent = `${e.target.value}%`;
}