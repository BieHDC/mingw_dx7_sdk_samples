#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h winmain.cpp dpconnect.cpp winmainres.o -ldxguid -lole32 -static-libgcc -static-libstdc++ -static -lwinpthread -o chatconnect.exe
rm winmainres.o