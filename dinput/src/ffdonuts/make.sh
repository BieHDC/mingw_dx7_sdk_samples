#!/bin/bash
i686-w64-mingw32-windres ffdonuts.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h ddutil.cpp ddutil.h diutil.cpp diutil.h dsutil.cpp dsutil.h ffdonuts.cpp ffdonuts.h  winmainres.o -lgdi32 -ldinput -lddraw -ldsound -luuid -static-libgcc -static-libstdc++ -static -lwinpthread -o ffdonuts.exe
rm winmainres.o