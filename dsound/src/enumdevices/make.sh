#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h winmain.cpp winmainres.o -ldsound -lole32 -static-libgcc -static-libstdc++ -static -lwinpthread -o enumdevices.exe
rm winmainres.o
