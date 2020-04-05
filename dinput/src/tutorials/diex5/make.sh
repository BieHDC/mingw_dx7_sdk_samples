#!/bin/bash
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 diex5.cpp -ldxguid -ldinput -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o diex5.exe
