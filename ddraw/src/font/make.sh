#!/bin/bash
i686-w64-mingw32-windres font.rc winmainres.o
i686-w64-mingw32-g++ resource.h font.cpp winmainres.o -I../../include -lgdi32 -ldxguid -lddraw -static-libgcc -static-libstdc++ -static -lwinpthread -o font.exe
rm winmainres.o