#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h triangle.cpp winmain.cpp winmainres.o -ldxguid -lddraw -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o triangle.exe
rm winmainres.o