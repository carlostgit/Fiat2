#!/bin/bash
# Script para lanzar el servidor y abrir el Runner

PORT=8000
URL="http://localhost:$PORT/tools/runner/index.html"

echo "Iniciando servidor web en el puerto $PORT..."
echo "Accediendo a: $URL"

# Lanzar el servidor en segundo plano
python3 -m http.server $PORT > /dev/null 2>&1 &
SERVER_PID=$!

# Esperar un segundo para que el servidor arranque
sleep 1

# Intentar abrir el navegador
if command -v xdg-open > /dev/null; then
    xdg-open "$URL"
elif command -v open > /dev/null; then
    open "$URL"
else
    echo "Servidor listo. Por favor, abre manualmente: $URL"
fi

echo "Presiona Ctrl+C para detener el servidor (PID: $SERVER_PID)"

# Esperar a que el usuario detenga el script
wait $SERVER_PID
