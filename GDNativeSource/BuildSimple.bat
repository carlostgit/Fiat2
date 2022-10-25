REM Generamos una librería dinámica libsimple.so, dentro del directorio simple/release

REM Compilamos el ejemplo con el gcc de MinGW\bin, que genera una librería .so
REM Según la documentación, para Win32 habría que usar el compilador cl de Visual Studio,
REM que genera una librería .dll
REM Pero el ejemplo también funciona generando la librería .so
REM (Como plataforma en godot, hay que poner win32 (en mi tablet), y al ir a seleccionar
REM la librería, por defecto solo te muestra los archivos .dll, pero hay que hacer que muestre
REM todos los archivos, y seleccionar nuestra librería .so)

REM Añadimos el path al compilador gcc de MinGW
set PATH=%PATH%;D:\CodeBlocks20_03\codeblocks-20.03-32bit-mingw-32bit-nosetup\MinGW\bin
cd simple
mkdir release
cd..
gcc -std=c11 -fPIC -c -I../godot-headers simple/simple.c -o simple/release/simple.o

REM En la documentación viene que hay que poner la linea siguiente:
REM gcc -rdynamic -shared simple.o -o ../simple/bin/libsimple.so
REM pero a mi no me reconocía lo de -rdynamic y he probado sin eso, y también ha funcionado
REM En vez del comando de la documentación, usamos el siguiente, donde falta lo de -rdynamic
gcc -shared simple/release/simple.o -o simple/release/libsimple.so