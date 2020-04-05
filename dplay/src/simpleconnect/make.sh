#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h dpconnect.cpp winmain.cpp winmainres.o -ldxguid -lole32 -static-libgcc -static-libstdc++ -static -lwinpthread -o simpleconnect.exe
rm winmainres.o