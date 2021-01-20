function presetChange(e)
{
    document.getElementById("input-type").value = e.target.value;
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
                <td>${type}</td>
                <td>{${pos.X}, ${pos.Y}}</td>
                <td>${timer}ms</td>
            </tr>
        </table>
    `;
    enemyBox.dataset["type"] = type;
    enemyBox.dataset["x"] = pos.X;
    enemyBox.dataset["y"] = pos.Y;
    enemyBox.dataset["timer"] = timer;
    enemyBox.classList.add("enemy-box");
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
                "Type": "WaitTillAllEnemiesAreDead"
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

    downloadToFile(JSON.stringify(data) + "\n", "level_x", "application/json");
}

// Read file
function importLevel(e)
{
    const file = e.target.files[0];
    document.getElementById("file-name").textContent = file.name;
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

var dragger = dragula([document.getElementById("enemy-spawner")]);
addDragulaToPacks();
function addDragulaToPacks()
{
    document.querySelectorAll(".pack").forEach(function(element){
        dragger.containers.push(element);
    });
}
