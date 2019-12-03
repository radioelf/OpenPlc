#!/bin/bash
if [ $# -eq 0 ]; then
    echo "Error: Debe proporcionar un archivo como argumento para poder ser compilado"
    exit 1
fi

#move into the scripts folder if you're not there already
cd scripts &>/dev/null

OPENPLC_PLATFORM=$(cat openplc_platform)

#store the active program filename
echo "$1" > ../active_program

#compiling the ST file into C
cd ..
echo "Optimizando el programa ST..."
./st_optimizer ./st_files/"$1" ./st_files/"$1"
echo "Generando ficheros C..."
./iec2c ./st_files/"$1"
if [ $? -ne 0 ]; then
    echo "Error al generar los ficheros C"
    echo "compilacion terminada con errores.!"
    exit 1
fi
echo "Moviendo ficheros..."
mv -f POUS.c POUS.h LOCATED_VARIABLES.h VARIABLES.csv Config0.c Config0.h Res0.c ./core/
if [ $? -ne 0 ]; then
    echo "Error moviendo ficheros"
    echo "Compilacion finalizada con errores!"
    exit 1
fi

#compiling for each platform
cd core
if [ "$OPENPLC_PLATFORM" = "win" ]; then
    echo "Compilacion para Windows"
    echo "Generando ficheros objetos..."
    g++ -I ./lib -c Config0.c -w
    if [ $? -ne 0 ]; then
        echo "Error compilando ficheros C"
        echo "Compilacion finalizada con errores!"
        exit 1
    fi
    g++ -I ./lib -c Res0.c -w
    if [ $? -ne 0 ]; then
        echo "Error compiling C files"
        echo "Compilacion finalizada con errores!"
        exit 1
    fi
    echo "Generando glueVars..."
    ./glue_generator
    echo "Compiling main program..."
    g++ *.cpp *.o -o openplc -I ./lib -pthread -fpermissive -I /usr/local/include/modbus -L /usr/local/lib -lmodbus -w
    if [ $? -ne 0 ]; then
        echo "Error compilando ficheros C"
        echo "Compilacion finalizada con errores!"
        exit 1
    fi
    echo "La compilacion finalizo correctamente!"
    exit 0
    
elif [ "$OPENPLC_PLATFORM" = "linux" ]; then
    echo "Compilando for Linux"
    echo "Generando ficheros objetos..."
    g++ -std=gnu++11 -I ./lib -c Config0.c -lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w
    if [ $? -ne 0 ]; then
        echo "Error compilando ficheros C"
        echo "Compilacion finalizada con errores!"
        exit 1
    fi
    g++ -std=gnu++11 -I ./lib -c Res0.c -lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w
    if [ $? -ne 0 ]; then
        echo "Error compilando ficheros C"
        echo "Compilacion finalizada con errores!"
        exit 1
    fi
    echo "Generando glueVars..."
    ./glue_generator
    echo "Compilando main program..."
    g++ -std=gnu++11 *.cpp *.o -o openplc -I ./lib -pthread -fpermissive `pkg-config --cflags --libs libmodbus` -lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w
    if [ $? -ne 0 ]; then
        echo "Error compilando ficheros C"
        echo "Compilacion finalizada con errores!"
        exit 1
    fi
    echo "La compilacion finalizo correctamente!"
    exit 0
    
elif [ "$OPENPLC_PLATFORM" = "rpi" ]; then
    echo "Compilando para Raspberry Pi"
    echo "Generando ficheros objetos..."
    g++ -std=gnu++11 -I ./lib -c Config0.c -lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w
    if [ $? -ne 0 ]; then
        echo "Error compilando ficheros C"
        echo "Compilacion finalizada con errores!"
        exit 1
    fi
    g++ -std=gnu++11 -I ./lib -c Res0.c -lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w
    if [ $? -ne 0 ]; then
        echo "Error compilando ficheros C"
        echo "Compilacion finalizada con errores!"
        exit 1
    fi
    echo "Generando glueVars..."
    ./glue_generator
    echo "Compilando programa principal..."
    g++ -std=gnu++11 *.cpp *.o -o openplc -I ./lib -lrt -lwiringPi -lpthread -fpermissive `pkg-config --cflags --libs libmodbus` -lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w
    if [ $? -ne 0 ]; then
        echo "Error compilando ficheros C"
        echo "Compilacion finalizada con errores!"
        exit 1
    fi
    echo "La compilacion finalizo correctamente!"
    exit 0
else
    echo "Error: Plataforma desconocida! OpenPLC solo puede compilarse para Windows, Linux y Raspberry Pi"
    echo "Compilacion finalizada con errores!"
    exit 1
fi
