#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h fullduplexfilter.cpp winmain.cpp winmainres.o -ldsound -lole32 -static-libgcc -static-libstdc++ -static -lwinpthread -o fullduplexfilter.exe
rm winmainres.o
