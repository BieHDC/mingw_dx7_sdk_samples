#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ resource.h mingw_missing_defs.h wavread.cpp winmain.cpp play3dsound.cpp winmainres.o -lwinmm -lcomctl32 -lcomdlg32 -ldsound -lole32 -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o play3dsound.exe
rm winmainres.o
