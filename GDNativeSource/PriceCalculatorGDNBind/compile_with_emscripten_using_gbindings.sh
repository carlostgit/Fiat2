
# Enable debugging, para que se imprima todo en consola
set -x

em++ -o bin/wasm/javascript/libPriceCalculatorGDNBind.wasm -s SIDE_MODULE=1 src/BindToCPP.bc src/PriceCalculatorGDNBind.bc -L/mnt/c/Carlos/GODOT/Proyectos/Fiat2/godotengine3_5/godot-cpp/bin -lgodot-cpp.javascript.debug.wasm

# Disable debugging
set +x
