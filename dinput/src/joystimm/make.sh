#!/bin/bash
i686-w64-mingw32-windres joystimm.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h joystimm.cpp winmain.cpp winmainres.o -ldinput -static-libgcc -static-libstdc++ -static -lwinpthread -o joyffeed.exe
rm winmainres.o