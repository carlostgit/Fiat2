El archivo "api.json" lo he generado con el comando:
Godot_v3.5.2-stable_win64.exe --gdnative-generate-json-api api.json

Y para generar el fichero de bindings, he usado el siguiente comando:
carlos@Carlos_HP:/mnt/c/carlos/GODOT/Proyectos/Fiat2/godotengine3_5/godot-cpp$ scons platform=javascript custom_api_file=../../godot_3_5_api_json/api.json

El fichero de bindings se ha generado en la siguiente ubicación:
C:\Carlos\GODOT\Proyectos\Fiat2\godotengine3_5\godot-cpp\bin\libgodot-cpp.javascript.debug.wasm.a