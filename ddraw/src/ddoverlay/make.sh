#!/bin/bash
i686-w64-mingw32-windres ddoverlay.rc winmainres.o
i686-w64-mingw32-g++ resource.h ddoverlay.cpp ddutil.cpp winmainres.o -I../../include -lgdi32 -ldxguid -lddraw -static-libgcc -static-libstdc++ -static -lwinpthread -o ddoverlay.exe
rm winmainres.o