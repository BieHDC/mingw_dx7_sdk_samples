#!/bin/bash
i686-w64-mingw32-windres diex3.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 diex3.cpp winmainres.o -ldxguid -ldinput -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o diex3.exe
rm winmainres.o
