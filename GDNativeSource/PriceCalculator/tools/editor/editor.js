let scenario = {
    reality: {
        products: [],
        option_to_product: {},
        compl_combos: {},
        suppl_combos: {}
    },
    prices: {},
    market_warehouse: {},
    persons: []
};

const DEFAULT_SCENARIO = {
  "reality": {
    "products": ["flour", "sugar", "egg"],
    "option_to_product": {
      "bread_base": "flour",
      "sweetener": "sugar",
      "protein": "egg"
    },
    "compl_combos": {
      "basic_cake": ["bread_base", "sweetener", "protein"]
    },
    "suppl_combos": {
      "pastry_mix": { "bread_base": 0.7, "sweetener": 0.3 }
    }
  },
  "prices": { "flour": 1.5, "sugar": 2.0, "egg": 0.5 },
  "market_warehouse": { "flour": 100, "sugar": 50, "egg": 200 },
  "persons": [
    {
      "name": "Baker Joe",
      "owned_products": { "flour": 10, "sugar": 5, "egg": 20 },
      "option_satisfaction": {
        "bread_base": [1.2, 50],
        "sweetener": [0.8, 20],
        "protein": [1.5, 30]
      },
      "suppl_satisfaction": { "pastry_mix": [1.1, 40] },
      "compl_satisfaction": { "basic_cake": [2.5, 100] }
    },
    {
      "name": "Customer Alice",
      "owned_products": { "flour": 0, "sugar": 0, "egg": 0 },
      "option_satisfaction": {
        "bread_base": [2.0, 80],
        "sweetener": [3.0, 60],
        "protein": [1.0, 40]
      },
      "suppl_satisfaction": { "pastry_mix": [1.5, 50] },
      "compl_satisfaction": { "basic_cake": [4.0, 200] }
    }
  ]
};

// --- Navigation ---
document.querySelectorAll('.nav-item').forEach(item => {
    item.addEventListener('click', () => {
        document.querySelectorAll('.nav-item').forEach(i => i.classList.remove('active'));
        item.classList.add('active');
        
        const section = item.dataset.section;
        document.querySelectorAll('main > section').forEach(s => s.style.display = 'none');
        document.getElementById(`section-${section}`).style.display = 'block';
        
        if (section === 'market') renderMarketSection();
        if (section === 'agents') renderAgentsSection();
    });
});

// --- Reality: Products ---
function addProduct() {
    const input = document.getElementById('new-product');
    const name = input.value.trim();
    if (name && !scenario.reality.products.includes(name)) {
        scenario.reality.products.push(name);
        scenario.prices[name] = 1.0;
        scenario.market_warehouse[name] = 0.0;
        input.value = '';
        renderReality();
        updatePreview();
    }
}

function removeProduct(name) {
    scenario.reality.products = scenario.reality.products.filter(p => p !== name);
    delete scenario.prices[name];
    delete scenario.market_warehouse[name];
    renderReality();
    updatePreview();
}

// --- Reality: Options ---
function addOption() {
    const name = document.getElementById('new-option-name').value.trim();
    const product = document.getElementById('new-option-product').value;
    if (name && product) {
        scenario.reality.option_to_product[name] = product;
        document.getElementById('new-option-name').value = '';
        renderReality();
        updatePreview();
    }
}

function removeOption(name) {
    delete scenario.reality.option_to_product[name];
    // Also remove from combos
    for (let combo in scenario.reality.compl_combos) {
        scenario.reality.compl_combos[combo] = scenario.reality.compl_combos[combo].filter(o => o !== name);
    }
    renderReality();
    updatePreview();
}

// --- Reality: Combos ---
function addComplCombo() {
    const name = document.getElementById('new-compl-name').value.trim();
    const checkboxes = document.querySelectorAll('#compl-option-checks input:checked');
    const options = Array.from(checkboxes).map(c => c.value);
    
    if (name && options.length > 0) {
        scenario.reality.compl_combos[name] = options;
        document.getElementById('new-compl-name').value = '';
        renderReality();
        updatePreview();
    }
}

function addSupplCombo() {
    const name = document.getElementById('new-suppl-name').value.trim();
    if (name) {
        scenario.reality.suppl_combos[name] = {};
        document.getElementById('new-suppl-name').value = '';
        renderReality();
        updatePreview();
    }
}

function updateSupplWeight(combo, opt, weight) {
    scenario.reality.suppl_combos[combo][opt] = parseFloat(weight);
    updatePreview();
}

// --- Rendering ---
function renderReality() {
    // Products
    const prodList = document.getElementById('product-list');
    prodList.innerHTML = scenario.reality.products.map(p => `
        <div class="tag">
            ${p} <span class="close" onclick="removeProduct('${p}')">×</span>
        </div>
    `).join('');

    // Update product selectors
    const selectors = ['new-option-product'];
    selectors.forEach(id => {
        const el = document.getElementById(id);
        const currentVal = el.value;
        el.innerHTML = scenario.reality.products.map(p => `<option value="${p}">${p}</option>`).join('');
        el.value = currentVal || scenario.reality.products[0] || '';
    });

    // Options
    const optList = document.getElementById('option-list');
    optList.innerHTML = Object.entries(scenario.reality.option_to_product).map(([name, prod]) => `
        <div class="tag" style="background: rgba(34, 211, 238, 0.1); color: var(--accent);">
            <b>${name}</b> → ${prod} <span class="close" onclick="removeOption('${name}')">×</span>
        </div>
    `).join('');

    // Combo Option Selection
    const complChecks = document.getElementById('compl-option-checks');
    complChecks.innerHTML = Object.keys(scenario.reality.option_to_product).map(opt => `
        <label style="display: flex; align-items: center; gap: 0.5rem; margin-bottom: 0.2rem; cursor: pointer;">
            <input type="checkbox" value="${opt}"> ${opt}
        </label>
    `).join('');

    // Compl Combos List
    const complList = document.getElementById('compl-list');
    complList.innerHTML = Object.entries(scenario.reality.compl_combos).map(([name, opts]) => `
        <div class="card" style="padding: 1rem; margin-bottom: 0.5rem;">
            <div style="display:flex; justify-content: space-between;">
                <strong>${name}</strong>
                <span class="close" style="color:var(--danger); cursor:pointer;" onclick="delete scenario.reality.compl_combos['${name}']; renderReality(); updatePreview();">Delete</span>
            </div>
            <div class="tag-container">${opts.map(o => `<span class="tag">${o}</span>`).join('')}</div>
        </div>
    `).join('');

    // Suppl Combos List
    const supplList = document.getElementById('suppl-list');
    const allOptions = Object.keys(scenario.reality.option_to_product);
    supplList.innerHTML = Object.entries(scenario.reality.suppl_combos).map(([name, weights]) => `
        <div class="card" style="padding: 1rem; margin-bottom: 0.5rem;">
            <div style="display:flex; justify-content: space-between; margin-bottom: 1rem;">
                <strong>${name}</strong>
                <span class="close" style="color:var(--danger); cursor:pointer;" onclick="delete scenario.reality.suppl_combos['${name}']; renderReality(); updatePreview();">Delete</span>
            </div>
            ${allOptions.map(opt => `
                <div style="display:flex; align-items:center; gap: 1rem; margin-bottom: 0.3rem;">
                    <span style="flex:1; font-size:0.8rem;">${opt}</span>
                    <input type="number" step="0.1" value="${weights[opt] || 0}" style="width: 80px;" onchange="updateSupplWeight('${name}', '${opt}', this.value)">
                </div>
            `).join('')}
        </div>
    `).join('');
}

// --- Market State ---
function renderMarketSection() {
    const pricesDiv = document.getElementById('price-inputs');
    pricesDiv.innerHTML = scenario.reality.products.map(p => `
        <div class="input-group">
            <label>${p} Price</label>
            <input type="number" step="0.01" value="${scenario.prices[p]}" onchange="scenario.prices['${p}'] = parseFloat(this.value); updatePreview();">
        </div>
    `).join('');

    const warehouseDiv = document.getElementById('warehouse-inputs');
    warehouseDiv.innerHTML = scenario.reality.products.map(p => `
        <div class="input-group">
            <label>${p} Stock</label>
            <input type="number" step="0.1" value="${scenario.market_warehouse[p]}" onchange="scenario.market_warehouse['${p}'] = parseFloat(this.value); updatePreview();">
        </div>
    `).join('');
}

// --- Agents ---
function addAgent() {
    const name = document.getElementById('new-agent-name').value.trim();
    if (name) {
        const agent = {
            name: name,
            owned_products: {},
            option_satisfaction: {},
            suppl_satisfaction: {},
            compl_satisfaction: {}
        };
        // Init with defaults
        scenario.reality.products.forEach(p => agent.owned_products[p] = 0);
        Object.keys(scenario.reality.option_to_product).forEach(o => agent.option_satisfaction[o] = [1.0, 100.0]);
        Object.keys(scenario.reality.compl_combos).forEach(c => agent.compl_satisfaction[c] = [1.0, 100.0]);
        Object.keys(scenario.reality.suppl_combos).forEach(s => agent.suppl_satisfaction[s] = [1.0, 100.0]);

        scenario.persons.push(agent);
        document.getElementById('new-agent-name').value = '';
        renderAgentsSection();
        updatePreview();
    }
}

function updateAgentProduct(index, prod, val) {
    scenario.persons[index].owned_products[prod] = parseFloat(val);
    updatePreview();
}

function updateAgentSatisf(index, type, key, subIdx, val) {
    scenario.persons[index][type][key][subIdx] = parseFloat(val);
    updatePreview();
}

function renderAgentsSection() {
    const grid = document.getElementById('agents-grid');
    grid.innerHTML = scenario.persons.map((p, idx) => `
        <div class="card">
            <div style="display:flex; justify-content:space-between; margin-bottom: 1rem;">
                <h3>${p.name}</h3>
                <button class="btn-danger" style="padding: 0.2rem 0.6rem;" onclick="scenario.persons.splice(${idx}, 1); renderAgentsSection(); updatePreview();">×</button>
            </div>
            
            <details>
                <summary style="cursor:pointer; color:var(--accent); margin-bottom:0.5rem;">Backpack (Products)</summary>
                ${scenario.reality.products.map(prod => `
                    <div class="input-group" style="display:flex; align-items:center; gap:0.5rem;">
                        <span style="flex:1; font-size:0.8rem;">${prod}</span>
                        <input type="number" value="${p.owned_products[prod] || 0}" style="width:70px;" onchange="updateAgentProduct(${idx}, '${prod}', this.value)">
                    </div>
                `).join('')}
            </details>

            <details style="margin-top:0.5rem;">
                <summary style="cursor:pointer; color:var(--accent);">Utility Curves (Pref@0, Max)</summary>
                <div style="font-size:0.75rem; margin-top:0.5rem;">
                    <strong>Options:</strong>
                    ${Object.keys(scenario.reality.option_to_product).map(o => `
                        <div style="display:flex; gap:0.3rem; margin-bottom:0.2rem;">
                            <span style="flex:1;">${o}</span>
                            <input type="number" step="0.1" value="${p.option_satisfaction[o][0]}" style="width:50px;" onchange="updateAgentSatisf(${idx}, 'option_satisfaction', '${o}', 0, this.value)">
                            <input type="number" step="1" value="${p.option_satisfaction[o][1]}" style="width:50px;" onchange="updateAgentSatisf(${idx}, 'option_satisfaction', '${o}', 1, this.value)">
                        </div>
                    `).join('')}
                    
                    <strong style="display:block; margin-top:0.5rem;">Combos:</strong>
                    ${Object.keys(scenario.reality.compl_combos).map(c => `
                        <div style="display:flex; gap:0.3rem;">
                            <span style="flex:1;">${c}</span>
                            <input type="number" step="0.1" value="${p.compl_satisfaction[c][0]}" style="width:50px;" onchange="updateAgentSatisf(${idx}, 'compl_satisfaction', '${c}', 0, this.value)">
                            <input type="number" step="1" value="${p.compl_satisfaction[c][1]}" style="width:50px;" onchange="updateAgentSatisf(${idx}, 'compl_satisfaction', '${c}', 1, this.value)">
                        </div>
                    `).join('')}
                </div>
            </details>
        </div>
    `).join('');
}

// --- IO ---
function updatePreview() {
    document.getElementById('json-preview').innerText = JSON.stringify(scenario, null, 2);
}

async function downloadJSON() {
    const json = JSON.stringify(scenario, null, 2);
    
    // Attempt to use File System Access API (allows choosing path and name)
    if ('showSaveFilePicker' in window) {
        try {
            const handle = await window.showSaveFilePicker({
                suggestedName: 'scenario.json',
                types: [{
                    description: 'JSON Files',
                    accept: { 'application/json': ['.json'] },
                }],
            });
            const writable = await handle.createWritable();
            await writable.write(json);
            await writable.close();
            return;
        } catch (err) {
            // If user cancels or if it's not supported in this context (like file://)
            if (err.name === 'AbortError') return;
            console.warn("File System Access API not available or failed, using fallback.", err);
        }
    }

    // Fallback: Prompt for filename and use the traditional download method
    let filename = prompt("Choose a name for your scenario file:", "scenario.json");
    if (!filename) return;
    if (!filename.endsWith(".json")) filename += ".json";

    const dataStr = "data:text/json;charset=utf-8," + encodeURIComponent(json);
    const downloadAnchorNode = document.createElement('a');
    downloadAnchorNode.setAttribute("href", dataStr);
    downloadAnchorNode.setAttribute("download", filename);
    document.body.appendChild(downloadAnchorNode);
    downloadAnchorNode.click();
    downloadAnchorNode.remove();
}

function loadJSON(event) {
    const file = event.target.files[0];
    if (!file) return;
    const reader = new FileReader();
    reader.onload = function(e) {
        try {
            scenario = JSON.parse(e.target.result);
            renderReality();
            updatePreview();
        } catch (err) {
            alert("Error parsing JSON file!");
        }
    };
    reader.readAsText(file);
}

function loadDefaultScenario() {
    try {
        // Deep clone to avoid modifying the constant
        scenario = JSON.parse(JSON.stringify(DEFAULT_SCENARIO));
        renderReality();
        updatePreview();
    } catch (err) {
        console.error(err);
        alert("Error loading default scenario: " + err.message);
    }
}

// Initial Render
renderReality();
updatePreview();
