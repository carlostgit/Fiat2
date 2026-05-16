let runner = null;
let stepCount = 0;
let isRunning = false;
let animationId = null;

// Esperar a que el módulo WASM esté listo
// Nota: 'Module' es el objeto global creado por el JS generado por Emscripten
if (typeof Module !== 'undefined') {
    Module.onRuntimeInitialized = () => {
        const badge = document.getElementById('status-badge');
        if (badge) {
            badge.innerText = 'Ready';
            badge.className = 'badge status-ready';
        }
        console.log("WASM Runtime Initialized");
    };
}

function log(msg, type = 'system') {
    const container = document.getElementById('log-container');
    if (!container) return;
    const entry = document.createElement('div');
    entry.className = `log-entry ${type}`;
    entry.innerText = msg;
    container.appendChild(entry);
    container.scrollTop = container.scrollHeight;
}

document.getElementById('btn-load-scenario').onclick = () => {
    document.getElementById('file-input').click();
};

document.getElementById('file-input').onchange = (e) => {
    const file = e.target.files[0];
    if (!file) return;

    const reader = new FileReader();
    reader.onload = (event) => {
        try {
            const scenarioJson = event.target.result;
            // Instanciar el Runner de C++ (vía Embind)
            if (runner) runner.delete();
            runner = new Module.MarketRunner();
            
            if (runner.loadScenario(scenarioJson)) {
                log(`Scenario loaded: ${file.name}`);
                document.getElementById('btn-run').disabled = false;
                document.getElementById('btn-step').disabled = false;
                stepCount = 0;
                updateUI();
            } else {
                log("Error: Failed to load scenario into engine", "error");
            }
        } catch (err) {
            log(`Error parsing JSON: ${err.message}`, "error");
        }
    };
    reader.readAsText(file);
};

function updateUI() {
    if (!runner) return;
    document.getElementById('step-count').innerText = stepCount;
    
    try {
        const prices = JSON.parse(runner.getPricesJson());
        const list = document.getElementById('price-list');
        list.innerHTML = Object.entries(prices).map(([name, price]) => `
            <div class="price-item">
                <span>${name}</span>
                <span class="price-val">${price.toFixed(4)}</span>
            </div>
        `).join('');
    } catch (e) {
        console.error("Error updating UI:", e);
    }
}

function runStep() {
    if (!runner) return;
    runner.step();
    stepCount++;
    updateUI();
    log(`Step ${stepCount} completed`, 'step');
}

document.getElementById('btn-step').onclick = runStep;

document.getElementById('btn-run').onclick = () => {
    if (isRunning) {
        stopSimulation();
    } else {
        startSimulation();
    }
};

function startSimulation() {
    isRunning = true;
    document.getElementById('btn-run').innerText = '⏸ Pause';
    document.getElementById('status-badge').innerText = 'Running';
    document.getElementById('status-badge').className = 'badge status-running';
    simulationLoop();
}

function stopSimulation() {
    isRunning = false;
    document.getElementById('btn-run').innerText = '▶ Run Simulation';
    document.getElementById('status-badge').innerText = 'Ready';
    document.getElementById('status-badge').className = 'badge status-ready';
    if (animationId) cancelAnimationFrame(animationId);
}

function simulationLoop() {
    if (!isRunning) return;
    runStep();
    // Controlamos la velocidad de la simulación
    setTimeout(() => {
        animationId = requestAnimationFrame(simulationLoop);
    }, 200); 
}

document.getElementById('btn-clear-logs').onclick = () => {
    document.getElementById('log-container').innerHTML = '';
};
