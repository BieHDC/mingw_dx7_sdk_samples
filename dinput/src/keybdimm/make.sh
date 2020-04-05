#!/bin/bash
i686-w64-mingw32-windres keybdimm.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h keybdimm.cpp keybdimm.h winmain.cpp winmainres.o -ldxguid -ldinput -static-libgcc -static-libstdc++ -static -lwinpthread -o keybdimm.exe
rm winmainres.o