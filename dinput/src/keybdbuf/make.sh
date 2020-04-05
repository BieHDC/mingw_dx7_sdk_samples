#!/bin/bash
i686-w64-mingw32-windres keybdbuf.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h keybdbuf.cpp winmain.cpp winmainres.o -ldinput -static-libgcc -static-libstdc++ -static -lwinpthread -o keybdbuf.exe
rm winmainres.o