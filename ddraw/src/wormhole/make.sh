#!/bin/bash
i686-w64-mingw32-windres wormhole.rc winmainres.o
i686-w64-mingw32-g++ resource.h wormhole.cpp winmainres.o -I../../include -lddraw -ldxguid -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o wormhole.exe
rm winmainres.o