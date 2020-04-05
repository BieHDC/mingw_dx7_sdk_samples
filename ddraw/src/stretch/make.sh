#!/bin/bash
i686-w64-mingw32-windres stretch.rc winmainres.o
i686-w64-mingw32-g++ resource.h ddutil.cpp stretch.cpp winmainres.o -I../../include -lddraw -ldxguid -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o stretch.exe
rm winmainres.o