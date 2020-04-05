#!/bin/bash
i686-w64-mingw32-windres dinstall.rc dinstallres.o
i686-w64-mingw32-gcc dsetup.h dinstall.c resource.h wincode.c dinstallres.o -ldsetup -lgdi32 -o dinstall.exe
rm dinstallres.o
