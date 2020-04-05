#!/bin/bash
i686-w64-mingw32-windres modetest.rc winmainres.o
i686-w64-mingw32-g++ -DDDSMT_ISTESTREQUIRED=0x00000001 -DDDEM_MODEPASSED=0x00000001 -DDDEM_MODEFAILED=0x00000002 resource.h modetest.cpp winmainres.o -I../../include -lddraw -static-libgcc -static-libstdc++ -static -lwinpthread -o modetest.exe
rm winmainres.o



