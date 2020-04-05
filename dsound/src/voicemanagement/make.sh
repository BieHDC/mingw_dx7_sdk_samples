#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h voicemanagement.cpp wavread.cpp winmain.cpp winmainres.o -lwinmm -lcomdlg32 -ldsound -lole32 -static-libgcc -static-libstdc++ -static -lwinpthread -o voicemanagement.exe
rm winmainres.o
