#!/bin/bash
i686-w64-mingw32-windres switcher.rc winmainres.o
i686-w64-mingw32-g++ resource.h switcher.cpp winmainres.o -I../../include -lddraw -ldxguid -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o switcher.exe
rm winmainres.o