#!/bin/bash
i686-w64-mingw32-g++ -shared d3dapp.cpp libd3dframe.a -o d3dapp.dll -I../../include -Wl,--out-implib,libd3dapp.a -ldxguid -lddraw -ld3dim