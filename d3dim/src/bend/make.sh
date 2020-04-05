#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ -DDEBUG resource.h bend.cpp winmainres.o ../../include/d3dframe.o -I../../include -ldxguid -lddraw -lwinmm -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o bend.exe
rm winmainres.o #-L../../include 