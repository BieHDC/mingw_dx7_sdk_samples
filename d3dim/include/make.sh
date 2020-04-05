#!/bin/bash
rm d3dframe.o
i686-w64-mingw32-g++ -shared -DDEBUG D3DRes.h D3DApp.cpp D3DApp.h D3DEnum.cpp D3DEnum.h D3DFile.cpp D3DFile.h D3DFrame.cpp D3DFrame.h D3DMath.cpp D3DMath.h D3DTextr.cpp D3DTextr.h D3DUtil.cpp D3DUtil.h -lgdi32 -c
i686-w64-mingw32-ld -relocatable *.o -o d3dframe.o