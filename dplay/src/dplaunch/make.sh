#!/bin/bash
i686-w64-mingw32-windres dplaunch.rc winmainres.o
i686-w64-mingw32-g++ resource.h dplaunch.cpp winmainres.o -ldplayx -lole32 -static-libgcc -static-libstdc++ -static -lwinpthread -o dplaunch.exe
rm winmainres.o