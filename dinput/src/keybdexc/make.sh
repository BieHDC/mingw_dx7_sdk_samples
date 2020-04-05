#!/bin/bash
i686-w64-mingw32-windres keybdexc.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h keybdexc.cpp winmainres.o -ldxguid -ldinput -static-libgcc -static-libstdc++ -static -lwinpthread -o keybdexc.exe
rm winmainres.o