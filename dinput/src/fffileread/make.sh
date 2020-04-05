#!/bin/bash
i686-w64-mingw32-windres winmain.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h ffeedfileread.cpp winmain.cpp winmainres.o -ldinput -lcomdlg32 -static-libgcc -static-libstdc++ -static -lwinpthread -o fffileread.exe
rm winmainres.o