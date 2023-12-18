
Compilar una librería "WebAssembly":
------------------------------------
El fichero SConstruct (que tenemos a la altura de este "Readme.txt") es un fichero del programa SCons, que se usa para compilar proyectos.
Este fichero SConstruct está preparado para poder compilar con Emscripten el código c y c++ que hay dentro del directorio "src\",
para crear una librería "libPriceCalculatorGDNBind.wasm" dentro del directorio "bin\wasm\javascript\".
Esta librería "libPriceCalculatorGDNBind.wasm", es código compilado a "WebAssembly" que se puede usar como librería externa de GDNative en GODOT, a la hora de,
exportar un proyecto a HTML5.

Para obtener la librería solo hace falta lanzar el siguiente comando en Ubuntu:
scons platform=javascript

Con esto, en el momento de escribir estas líneas el comando de Emscripten que lanza scons es el siguiente:
em++ -o bin/wasm/javascript/libPriceCalculatorGDNBind.wasm -s SIDE_MODULE=1 src/BindToCPP.bc src/PriceCalculatorGDNBind.bc -L/mnt/c/Carlos/GODOT/Proyectos/Fiat2/godotengine3_5/godot-cpp/bin -lgodot-cpp.javascript.debug.wasm

Pero ese comando era suficiento solo antes de meter el proyecto de PriceCalculator. PriceCalculator tiene varios ficheros c++,
con lo que la compilación cuando se incluye PriceCalculator queda con maás comandos em++.

La compilación se realiza en Linux. Yo he usado el Ubuntu que te puedes descargar en el store the Windows, que usa el WSL2. Hace falta descargarse
la versión adecuada de Emscripten se puede saber mirando el fichero:
.github/workflows/javascript_builds.yml
dentro del branch del proyecto godot, en Github.
Dentro del fichero javascript_builds.yml hay que buscar el texto
EM_VERSION


En teoría, para realizar esta compilación, se hace uso de otra librería de código "WebAssembly", que previamente hay que tener compilada con la versión adecuada de godotengine.

Para obtener esa otra librería, ver capítulo "Building the C++ bindings" en:
https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html
Esa otra librería de "C++ bindings" tiene el nombre de "libgodot-cpp.javascript.debug.wasm.a" y se espera que se sitúe en el directorio:
"..\..\godotengine3_5\godot-cpp\bin"
Se usa la librería de bindings asociada a la versión de GODOT 3.5, porque esa es la versión de Godot que estoy usando en el proyecto Godot que va a usar PriceCalculatorGDNBind.
El fichero SConstruct está configurado para que haga uso de esa librería.

En la práctica, hasta ahora yo he conseguido también compilar a "WebAssembly" sin usar la librería de bindings. Para compilar se puede poner lo siguiente:
em++ -o bin/wasm/javascript/libPriceCalculatorGDNBind.wasm -s SIDE_MODULE=1 src/BindToCPP.bc src/PriceCalculatorGDNBind.bc

(Pero ese comando era suficiento solo antes de meter el proyecto de PriceCalculator.)

O sea, quitando la parte que hace referencia a la librería de bindings.
La parte del comando de Emscripten que hace referencia a esa librería es:
 -L/mnt/c/Carlos/GODOT/Proyectos/Fiat2/godotengine3_5/godot-cpp/bin -lgodot-cpp.javascript.debug.wasm



Compilar una librería "dll":
----------------------------
La solución de Visual Studio "PriceCalculatorGDNBind.sln" que hay dentro del directorio "VSProject\" compila una librería dll que se puede usar en GODOT
cuando se compila el proyecto para la plataforma x64.

Hasta ahora no he necesitado usar la librería de bindings, y no está metida como dependencia en el proyecto. En caso de necesitarla en algún momento,
ver capítulo "Building the C++ bindings" en:
https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html

