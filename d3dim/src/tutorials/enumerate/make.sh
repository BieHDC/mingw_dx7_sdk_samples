#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h enumerate.cpp enumerate.h render.cpp winmain.cpp winmainres.o -ldxguid -lddraw -lgdi32 -lwinmm -static-libgcc -static-libstdc++ -static -lwinpthread -o enumerate.exe
rm winmainres.o