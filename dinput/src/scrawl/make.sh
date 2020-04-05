#!/bin/bash
i686-w64-mingw32-windres scrawl.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h scrawl.cpp scrawl.h winmain.cpp winmainres.o -lgdi32 -ldinput -static-libgcc -static-libstdc++ -static -lwinpthread -o scrawl.exe
rm winmainres.o