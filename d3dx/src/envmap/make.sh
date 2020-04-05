#!/bin/bash
i686-w64-mingw32-windres envmap.rc winmainres.o
i686-w64-mingw32-g++ resource.h envmap.cpp envmap.h winmainres.o -I../z_old_mingw/include -L../z_old_mingw/lib -ld3dx8d -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o envmap.exe
rm winmainres.o