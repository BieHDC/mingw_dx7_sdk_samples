#!/bin/bash
i686-w64-mingw32-windres mosquito.rc winmainres.o
i686-w64-mingw32-g++ resource.h mosquito.cpp winmainres.o -I../../include -lddraw -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o mosquito.exe
rm winmainres.o