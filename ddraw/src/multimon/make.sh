#!/bin/bash
i686-w64-mingw32-windres multimon.rc winmainres.o
i686-w64-mingw32-g++ resource.h multimon.cpp winmainres.o -I../../include -lddraw -ldxguid -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o multimon.exe
rm winmainres.o