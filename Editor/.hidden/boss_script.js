function valueOf(id, value = true) {
    if (value)
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
function exportBoss()
{
    let data = {};

    
    // Get Conditions
    data["Conditions"] = ExportConditions();
    
    // Get Phases
    data["Phases"] = ExportPhases();

    // Save HTML
    data["LazyHTML"] = document.getElementById("container").innerHTML;

    let name = valueOf("file-name");
    downloadToFile(JSON.stringify(data) + "\n", name, "application/json");

    console.log("Exported", data);
}

// Read file
function importBoss(e)
{
    const file = e.target.files[0];
    document.getElementById("file-name").value = file.name;
    const reader = new FileReader();
    reader.onload = function (e)
    {
        let content = JSON.parse(e.target.result);
        console.log("Imported", content);

        document.getElementById("container").innerHTML = content["LazyHTML"];
    }
    reader.readAsText(file);
}

//* Toolkit Dragula
var toolbox = dragula(
    [
        document.getElementById("trashcan"),
        document.getElementById("toolbox"),
        document.getElementById("conditions-container")
    ],
    {
        revertOnSpill: false,
        copy: function (el, source) {
            return source === document.getElementById("toolbox");
        },
        accepts: function (el, target) {
            if (target.id == "trashcan" && el.dataset["keep"] != undefined)
            {
                el.setAttribute("hidden", true);
                el.remove();
                return true;
            }

            return el.dataset["target"].split(" ").indexOf(target.dataset["accept"]) >= 0;
        }
    }
).on("drop", function (el, target, source) {
    if (source.id == "toolbox") {
        TransformToolkit(el, target);
    }
})

addPhase();
function addPhase()
{
    let fieldset = document.createElement("fieldset");
    fieldset.classList.add("phase-fieldset");
    fieldset.innerHTML = `
        <legend>
            Phase
            <button class="bad" onclick="event.target.parentNode.parentNode.remove()">Delete</button>
        </legend>
        <div class="phase" data-accept="tk-mod"></div>`;
    document.getElementById("phase-container").appendChild(fieldset);
    updatePhaseDragula();
}

// TransformToolkit into correct Module/Condition
function TransformToolkit(toolkit)
{
    if (toolkit.dataset.target == "tk-mod")
    {
        toolkit.outerHTML = GetModule(toolkit.id).outerHTML;
    }
    if (toolkit.dataset.target = "tk-con")
    {
        toolkit.outerHTML = GetCondition(toolkit.id).outerHTML;
    }
}

function updatePhaseDragula()
{
    document.querySelectorAll(".phase").forEach(el => toolbox.containers.push(el));
}

//* Comments
function Text()
{
    let text = document.createElement("div");
    text.classList.add("module");
    text.classList.add("tk-text");
    text.dataset.target = "tk-con tk-mod";
    text.dataset.keep = true;
    text.dataset["module"] = "Text";
    text.dataset["type"] = "Text";
    text.setAttribute("spellcheck", false);
    text.setAttribute("contenteditable", true);
    text.textContent = "Text";
    return text;
}

//* Conditions
function GetCondition(id)
{
    switch (id) {
        case "tk-below-hp":
            return ConditionBelowHealth();
        case "tk-time":
            return ConditionTime();
        case "tk-timed":
            return ConditionTimed();
        case "tk-once":
            return ConditionOnce();
        default:
            return Text();
    }
}
//? BaseClass
function Condition()
{
    let condition = document.createElement("div");
    condition.dataset.target = "tk-con";
    condition.dataset.keep = true;
    condition.classList.add("condition");
    condition.textContent = "[Error] Condition";
    return condition;
}

function ConditionOnce()
{
    let condition = Condition();
    condition.dataset["type"] = "Once";
    condition.innerHTML = `Do Once`;
    return condition;
}

function ConditionBelowHealth()
{
    let condition = Condition();
    condition.dataset["type"] = "BelowHealth";
    condition.innerHTML = `When below <input class="percentage-input" type="number" value="0" min="0" max="100"> % of HP`;
    return condition;
}

function ConditionTime()
{
    let condition = Condition();
    condition.dataset["type"] = "Time";
    condition.innerHTML = `After <input type="number" value="0" min="0" step="0.01"> seconds`;
    return condition;
}

function ConditionTimed()
{
    let condition = Condition();
    condition.classList.add("timed");
    condition.dataset["type"] = "Timed";
    condition.innerHTML = `Kill after <input type="number" value="0" min="0" max="10" step="0.1"> minutes`;
    return condition;
}

//* Modules
function GetModule(id)
{
    switch (id) {
        case "tk-enemy":
            return ModuleEnemy();
        case "tk-ability":
            return ModuleAbility();
        case "tk-movement":
            return ModuleMovement();
        case "tk-shoot":
            return ModuleShoot();
        case "tk-immunity":
            return ModuleImmmunity();
        case "tk-delay":
            return ModuleDelay();
        case "tk-laser":
            return ModuleLaser();
        default:
            return Text();
    }
}
//? BaseClass
function Module()
{
    let module = document.createElement("div");
    module.dataset.target = "tk-mod";
    module.dataset.keep = true;
    module.classList.add("module");
    module.textContent = "[Error] Module";
    return module;
}

function ModuleEnemy()
{
    let module = Module();
    module.dataset["module"] = "Enemy";
    module.classList.add("mod-enemy");
    module.innerHTML = `
        <table>
            <tr class="enemy-table-header-row">
                <th>Type</th>
                <th>Position</th>
                <th>Style</th>
            </tr>
            <tr>
                <td>
                    <input data-input="Type" class="enemy-box-input" type="text" value="Default">
                </td>
                <td>
                    <input data-input="X" class="enemy-box-input enemy-box-input-position" type="number" value="0" placeholder="x">
                    <input data-input="Y" class="enemy-box-input enemy-box-input-position" type="number" value="0" placeholder="y">
                </td>
                <td>
                    <select data-input="Style">
                        <option>Absolute</option>
                        <option>Relative</option>
                    </select>
                </th>
            </tr>
        </table>`;
    return module;
}

function ModuleAbility()
{
    let module = Module();
    module.dataset["module"] = "Ability";
    module.classList.add("mod-ability");
    module.innerHTML = `
        <p>
            Ability
            <select data-input="Ability" onchange="changeAbility(event.target)">
                <option>Shield</option>
                <option>Missile</option>
            </select>
        </p>
        <div></div>`;
    changeAbility(module.querySelector("select"));
    return module;
}

function ModuleMovement()
{
    let module = Module();
    module.dataset["module"] = "Movement";
    module.classList.add("mod-movement");
    module.innerHTML = `
        <p>
            Type
            <select onchange="changeMovementParameters(event.target)" data-input="Type">
                <option>Straight</option>
                <option>Diagonal</option>
                <option>Wave</option>
                <option>Bobbing</option>
                <option>Seeking</option>
                <option>Homing</option>
                <option>U-Turn</option>
            </select>
        </p>
        <div class="m-parameters"></div>`;
    changeMovementParameters(module.querySelector("select"));
    return module;
}

function ModuleShoot()
{
    let module = Module();
    module.dataset["module"] = "Shoot";
    module.classList.add("mod-shoot");
    module.innerHTML = `
        <p>
            Type <input data-input="Type" type="text" placeholder="I.e Missile">
        </p>
        <p>
            Speed <input data-input="Speed" type="number" value="0"> (pixels/second)
        </p>
        <p>
            Shoot towards player
            <select data-input="ShootTowardsPlayer">
                <option>No</option>
                <option>Yes</option>
            </select>
        </p>
        <p>
            Interval <input data-input="Interval" type="number" min="0" value="100" step="10"> (milliseconds)
        </p>
        <p>
            Duration <input data-input="Duration" type="number" min="0" value="0" step="0.1"> (seconds)
        </p>
        <p>
            Spawn Position
            <input data-input="X" class="enemy-box-input enemy-box-input-position" type="number" value="0" placeholder="x">
            <input data-input="Y" class="enemy-box-input enemy-box-input-position" type="number" value="0" placeholder="y">
        </p>
        <p>
            Style
            <select data-input="Style">
                <option>Absolute</option>
                <option>Relative</option>
            </select>
        </p>
        `;
    return module;
}

function ModuleImmmunity()
{
    let module = Module();
    module.dataset["module"] = "Immunity";
    module.classList.add("mod-immunity");
    module.innerHTML = `
        Immunity
        <select data-input="On">
            <option>On</option>
            <option>Off</option>
        </select>`;
    return module;
}

function ModuleDelay()
{
    let module = Module();
    module.dataset["module"] = "Delay";
    module.classList.add("mod-delay");
    module.innerHTML = `
        Wait <input type="number" data-input="Seconds" min="0" step="0.1" value="0"> (seconds)
    `;
    return module;
}

function ModuleLaser()
{
    let module = Module();
    module.dataset["module"] = "Laser";
    module.classList.add("mod-laser");
    module.innerHTML = `
        Duration <input type="number" data-input="Duration" min="0" step="0.1" value="0"> (seconds)
    `;
    return module;
}

function changeMovementParameters(element)
{
    let template = "null";
    switch (element.value) {
        case "Straight":
            template = `
                <p>
                    Speed
                    <input data-input="Speed" type="number" value="0">
                    (pixels/second)
                </p>
            `;
            break;
        case "Diagonal":
            template = `
                <p>
                    Speed
                    <input data-input="Speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    <span>Path: Start from</span>
                    <select data-input="Corner">
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
                    <input data-input="HorizontalSpeed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Vertical (&#8645;) Speed 
                    <input data-input="VerticalSpeed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Wave Height
                    <input data-input="Height" type="number" value="0">
                    (pixels)
                </p>
            `;
            break;
        case "Bobbing":
            template = `
                <p>
                    Speed 
                    <input data-input="Speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Wave Height
                    <input data-input="Height" type="number" value="0">
                    (pixels)
                </p>
            `;
            break;
        case "Seeking":
            template = `
                <p>
                    Speed
                    <input data-input="Speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Acceleration
                    <input data-input="Acceleration" type="number" value="0">
                    (pixels/second&sup2;)
                </p>
            `;
            break;
        case "Homing":
            template = `
                <span class="error">Ej Implementerat</span>
                <p>
                    Speed
                    <input data-input="Speed" type="number" value="0">
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
                    <input data-input="Speed" type="number" value="0">
                    (pixels/second)
                </p>
                <p>
                    Width
                    <input data-input="Width" type="number" value="0">
                    (pixels)
                </p>
                <p>
                    Height
                    <input data-input="Height" type="number" value="0">
                    (pixels)
                </p>
            `;
            break;
        default: break;
    }
    let next = element.parentElement.nextElementSibling;
    next.innerHTML = template;
}

function changeAbility(element)
{
    let template = "Unknown Ability";
    switch (element.value)
    {
        case "Shield":
            template = `
                <p>
                    HitPoints <input data-input="HitPoints" type="number" min="0" value="0" step="1">
                </p>`;
            break;
        case "Missile":
            template = `
                <p>
                    Init Speed <input data-input="InitialSpeed" type=number" value="0"> (pixels/second)
                </p>
                <p>
                    Deacceleration <input data-input="Deacceleration" type=number" value="0"> (pixels/second&sup2;)
                </p>
                <p>
                    Acceleration <input data-input="Acceleration" type=number" value="0"> (pixels/second&sup2;)
                </p>
                <p>
                    Spawn Position
                    <input data-input="X" class="enemy-box-input enemy-box-input-position" type="number" value="0" placeholder="x">
                    <input data-input="Y" class="enemy-box-input enemy-box-input-position" type="number" value="0" placeholder="y">
                </p>
                <p>
                    Style
                    <select data-input="Style">
                        <option>Absolute</option>
                        <option>Relative</option>
                    </select>
                </p>
            `;
            break;
        default: break;
    }
    let next = element.parentElement.nextElementSibling;
    next.innerHTML = template;
}

function ExportConditions()
{
    let arr = [];
    let conditions = document.getElementById("conditions-container");
    [...conditions.children].forEach(function(child) {
        
        let data = {};
        data["Type"] = child.dataset["type"];
        switch (child.dataset["type"])
        {
            case "BelowHealth":
                data["Percentage"] = ~~child.querySelector("input").value;
                break;
            case "Time":
                data["Seconds"] =  Number(child.querySelector("input").value);
                break;
            case "Timed":
                data["Minutes"] =  Number(child.querySelector("input").value);
                break;
            default: break;
        }

        arr.push(data);
    });
    return arr;
}

function ExportPhases()
{
    let arr = [];
    let phases = document.getElementById("phase-container");
    [...phases.querySelectorAll(".phase")].forEach(function(child) {
        arr.push(ExportPhase(child));
    });
    return arr;
}

function ExportPhase(child)
{
    let arr = [];
    [...child.children].forEach(function(module) {

        let data = {};
        data["Module"] = module.dataset["module"];

        console.group("Data Input", data["Module"]);

        [...module.querySelectorAll("[data-input]")].forEach((input) => {

            let key = input.dataset["input"];
            let value = input.value;
            
            if (value !== "" && !isNaN(value))
            {
                value = Number(value);
            };

            console.log(key, value);
            data[key] = value;
        });

        console.groupEnd();

        arr.push(data);
    });
    return arr;
}