# Enable debugging, para que se impriman los comandos en pantalla
set -x

em++ -o bin/wasm/javascript/libPriceCalculatorGDNBind.wasm -s SIDE_MODULE=1 src/BindToCPP.bc src/PriceCalculatorGDNBind.bc

# Disable debugging
set +x
