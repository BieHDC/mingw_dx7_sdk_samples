#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h texture.cpp render.cpp winmain.cpp winmainres.o -ldxguid -lddraw -lgdi32 -lwinmm -static-libgcc -static-libstdc++ -static -lwinpthread -o texture.exe
rm winmainres.o