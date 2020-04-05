#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ -DDEBUG resource.h videotex.cpp winmainres.o ../../include/d3dframe.o -I../../include -ldxguid -lddraw -lgdi32 -lwinmm -lvfw32 -static-libgcc -static-libstdc++ -static -lwinpthread -o videotex.exe
rm winmainres.o