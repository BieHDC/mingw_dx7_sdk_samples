#!/bin/bash
i686-w64-mingw32-windres digame.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h digame.cpp gameplay.cpp winmainres.o -lgdi32 -lwinmm -ldinput -ldxguid -luuid -static-libgcc -static-libstdc++ -static -lwinpthread -o digame.exe
rm winmainres.o