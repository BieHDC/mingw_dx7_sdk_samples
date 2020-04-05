#!/bin/bash
i686-w64-mingw32-windres diex4.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 diex4.cpp winmainres.o -ldxguid -ldinput -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o diex4.exe
rm winmainres.o
