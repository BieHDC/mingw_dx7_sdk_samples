#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h zbuffer.cpp winmain.cpp winmainres.o -ldxguid -lddraw -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o zbuffer.exe
rm winmainres.o