#!/bin/bash
i686-w64-mingw32-windres mouseexc.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h mouseexc.cpp mouseexc.h winmain.cpp winmainres.o -ldxguid -ldinput -static-libgcc -static-libstdc++ -static -lwinpthread -o mouseexc.exe
rm winmainres.o