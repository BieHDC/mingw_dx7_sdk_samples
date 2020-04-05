#!/bin/bash
i686-w64-mingw32-windres donuts.rc winmainres.o
i686-w64-mingw32-gcc -DUSE_DSOUND -DDIRECTINPUT_VERSION=0x0700 resource.h ddutil.cpp donuts.c donuts.h dsutil.c input.c input.h winmainres.o -I../../include -lgdi32 -ldinput -ldxguid -lddraw -ldsound -lwinmm -static-libgcc -static-libstdc++ -static -lwinpthread -o donuts.exe
rm winmainres.o