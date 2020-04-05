#!/bin/bash
i686-w64-mingw32-windres duel.rc winmainres.o
i686-w64-mingw32-g++ -DDIRECTINPUT_VERSION=0x0700 resource.h ddutil.cpp ddutil.h diutil.cpp diutil.h dpconnect.cpp dputil.cpp dputil.h dsutil.cpp dsutil.h duel.cpp duel.h gameproc.cpp gameproc.h gfx.cpp gfx.h lobby.cpp lobby.h util.cpp winmainres.o -lgdi32 -lddraw -ldinput -ldsound -lole32 -lwinmm -static-libgcc -static-libstdc++ -static -lwinpthread -o duel.exe
rm winmainres.o