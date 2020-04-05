#!/bin/bash
i686-w64-mingw32-windres ddenum.rc winmainres.o
i686-w64-mingw32-g++ resource.h ddenum.cpp winmainres.o -ldxguid -lddraw -static-libgcc -static-libstdc++ -static -lwinpthread -o ddenum.exe
rm winmainres.o