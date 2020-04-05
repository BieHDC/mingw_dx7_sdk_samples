#!/bin/bash
i686-w64-mingw32-windres joyffeed.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h joyffeed.cpp joyffeed.h winmain.cpp winmainres.o -lgdi32 -ldinput -lwinmm -static-libgcc -static-libstdc++ -static -lwinpthread -o joyffeed.exe
rm winmainres.o