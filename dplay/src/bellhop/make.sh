#!/bin/bash
i686-w64-mingw32-windres bellhop.rc winmainres.o
i686-w64-mingw32-g++ resource.h bellhop.cpp cgrptree.cpp connset.cpp dialog.cpp winmainres.o -lddraw -ldplayx -luuid -lcomctl32 -lole32 -lgdi32 -static-libgcc -static-libstdc++ -static -lwinpthread -o bellhop.exe
rm winmainres.o