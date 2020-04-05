#!/bin/bash
i686-w64-mingw32-windres fswindow.rc winmainres.o
i686-w64-mingw32-g++ resource.h fswindow.cpp fswindow.h winmain.cpp winmainres.o -I../../include -lgdi32 -ldxguid -lddraw -lwinmm -static-libgcc -static-libstdc++ -static -lwinpthread -o fswindow.exe
rm winmainres.o