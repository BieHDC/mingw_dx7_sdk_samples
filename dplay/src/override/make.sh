#!/bin/bash
i686-w64-mingw32-windres override.rc winmainres.o
i686-w64-mingw32-g++ resource.h override.cpp winmainres.o -lole32 -luuid -ldplayx -static-libgcc -static-libstdc++ -static -lwinpthread -o override.exe
rm winmainres.o