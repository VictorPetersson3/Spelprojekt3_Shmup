function presetChange(e)
{
    document.getElementById("input-type").value = e.target.value;
}

// Load Presets from file
function loadPresets(e)
{
    const file = e.target.files[0];
    const reader = new FileReader();
    reader.onload = function (e)
    {
        let content = e.target.result;
        presets = content.split('\n').map(line => line.split('').filter(char => char != '\r').join(''));
        let selectElement = document.getElementById("presets");
        selectElement.innerHTML = "";

        presets.forEach(function(line){
            let option = document.createElement("option");
            option.value = line;
            option.textContent = line;
            selectElement.appendChild(option);
        });

    }
    reader.readAsText(file);
}

function clearParameters()
{
    document.getElementById("input-type").value = "";
    document.getElementById("input-x").value = 0;
    document.getElementById("input-y").value = 0;
    document.getElementById("input-timer").value = 0;
}

function createEnemyElement(type, pos, timer)
{
    let enemyBox = document.createElement("div");
    enemyBox.innerHTML = `
        <table>
            <tr class="enemy-table-header-row">
                <th>Type</th>
                <th>Position</th>
                <th>Timer</th>
            </tr>
            <tr>
                <td>
                    <input onchange="updateValue(event, 'type')" class="enemy-box-input" type="text" value="${type}">
                </td>
                <td>
                    <input onchange="updateValue(event, 'x')" class="enemy-box-input enemy-box-input-position" type="number" value="${pos.X}" placeholder="x">
                    <input onchange="updateValue(event, 'y')" class="enemy-box-input enemy-box-input-position" type="number" value="${pos.Y}" placeholder="y">
                </td>
                <td>
                    <input onchange="updateValue(event, 'timer')" class="enemy-box-input" type="number" value="${timer}">
                </td>
            </tr>
        </table>
    `;
    enemyBox.dataset["type"] = type;
    enemyBox.dataset["x"] = pos.X;
    enemyBox.dataset["y"] = pos.Y;
    enemyBox.dataset["timer"] = timer;
    enemyBox.classList.add("enemy-box");
    clean(enemyBox);
    return enemyBox;
}

createEnemy();
function createEnemy()
{
    data = {};
    data.Type = document.getElementById("input-type").value;
    data.Position = {};
    data.Position.X = ~~document.getElementById("input-x").value;
    data.Position.Y = ~~document.getElementById("input-y").value;
    data.Timer = ~~document.getElementById("input-timer").value;

    if (data.Type == "")
    {
        data.Type = "Enemy";
    }

    let enemyBox = createEnemyElement(data.Type, data.Position, data.Timer);

    let spawner = document.getElementById("enemy-spawner");
    spawner.innerHTML = "";
    spawner.appendChild(enemyBox);
}

// Update values of enemy
function updateValue(e, key)
{
    let value = e.target.value;

    let enemyBox = e.target // input
        .parentNode // td
        .parentNode // tr
        .parentNode // tbody
        .parentNode // table
        .parentNode; // div

    enemyBox.dataset[key] = value;
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
function exportLevel()
{
    let data = { "Packs": [] };

    let packElements = document.getElementById("level-window").children;
    [...packElements].forEach(function(packElement)
    {
        let pack = {
            "ExitCondition": {
                "Type": "None"
            },
            "Enemies": []
        };

        [...packElement.children].forEach(function(enemyElement, i)
        {
            let enemy = {
                Type: null,
                Position: { X: null, X: null },
                Timer: null
            };

            enemy.Type = enemyElement.dataset["type"];
            enemy.Timer = ~~enemyElement.dataset["timer"];
            enemy.Position.X = ~~enemyElement.dataset["x"];
            enemy.Position.Y = ~~enemyElement.dataset["y"];

            pack["Enemies"].push(enemy);
        })

        data["Packs"].push(pack);
    });

    let name = document.getElementById("file-name").value;
    downloadToFile(JSON.stringify(data) + "\n", name, "application/json");
}

// Read file
function importLevel(e)
{
    const file = e.target.files[0];
    document.getElementById("file-name").value = file.name;
    const reader = new FileReader();
    reader.onload = function (e)
    {
        let content = JSON.parse(e.target.result);
        console.log(content);

        // Clear packs
        document.getElementById("level-window").innerHTML = "";

        // Add packs
        content.Packs.forEach(function(packObject, i)
        {
            // Create pack elemet
            let pack = document.createElement("div");
            pack.classList.add("pack");

            // Add enemies
            packObject.Enemies.forEach(function(enemyObject)
            {
                console.log(enemyObject);
                pack.appendChild(createEnemyElement(enemyObject.Type, enemyObject.Position, enemyObject.Timer));
            });

            document.getElementById("level-window").appendChild(pack);
        });

        addDragulaToPacks();
    }
    reader.readAsText(file);
}

// Dragula stuff
var dragger = dragula(
        [document.getElementById("enemy-spawner"), document.getElementById("trashcan")]
    ).on('drop', function (element, container) {
        if (container.id = "trashcan") {
            element.remove();
        }
    });
addDragulaToPacks();
function addDragulaToPacks()
{
    document.querySelectorAll(".pack").forEach(function(element){
        dragger.containers.push(element);
    });
}
