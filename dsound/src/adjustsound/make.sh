#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h adjustsound.cpp wavread.cpp winmain.cpp winmainres.o -lwinmm -lcomctl32 -lcomdlg32 -ldsound -lole32 -static-libgcc -static-libstdc++ -static -lwinpthread -o adjustsound.exe
rm winmainres.o
