#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h drawprims.cpp winmain.cpp winmainres.o -ldxguid -lddraw -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o drawprims.exe
rm winmainres.o
