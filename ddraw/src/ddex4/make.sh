#!/bin/bash
i686-w64-mingw32-windres ddex4.rc winmainres.o
i686-w64-mingw32-g++ resource.h ddex4.cpp ddutil.cpp winmainres.o -I../../include -lgdi32 -ldxguid -lddraw -static-libgcc -static-libstdc++ -static -lwinpthread -o ddex4.exe
rm winmainres.o