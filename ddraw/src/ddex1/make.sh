#!/bin/bash
i686-w64-mingw32-windres ddex1.rc winmainres.o
i686-w64-mingw32-g++ resource.h ddex1.cpp winmainres.o -lgdi32 -ldxguid -lddraw -static-libgcc -static-libstdc++ -static -lwinpthread -o ddex1.exe
rm winmainres.o