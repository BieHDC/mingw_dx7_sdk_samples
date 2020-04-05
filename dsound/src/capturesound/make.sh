#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h wavwrite.cpp capturesound.cpp winmain.cpp winmainres.o -lwinmm -lcomdlg32 -ldsound -lole32 -static-libgcc -static-libstdc++ -static -lwinpthread -o capturesound.exe
rm winmainres.o
