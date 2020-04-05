#!/bin/bash
i686-w64-mingw32-windres dpslots.rc winmainres.o
i686-w64-mingw32-g++ resource.h dpslots.h dpslots.cpp dialog.cpp client.cpp lobby.cpp server.cpp mingw_missing_defs.h winmainres.o -luuid -lgdi32 -lwinmm -lole32 -static-libgcc -static-libstdc++ -static -lwinpthread -o dpslots.exe
rm winmainres.o