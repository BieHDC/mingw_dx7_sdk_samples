#!/bin/bash
i686-w64-mingw32-windres mousenon.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h mousenon.cpp mousenon.h winmain.cpp winmainres.o -ldxguid -ldinput -static-libgcc -static-libstdc++ -static -lwinpthread -o mousenon.exe
rm winmainres.o