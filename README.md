# Microsoft DX7 SDK Samples for MinGW

This is the dx7 sdk from microsoft released around the 2000s. I have fixed up some of the samples (see below) so people can play with it.
I only ship the samples folder and with "make.sh" files in fixes dirs for compilation. The original license allows that (they are also in
this repo) and i just did minimal fixups to compile them without warnings, generally keeping everything as close to original as possible.

You need mingw to compile this.

```
###########Header#####################################################################################################
Path				Compiles?	Works?			Notes

d3dim/src/* Except the ones listed below:
These examples used microsofts engine thing called "d3dframe" which has no source code provided. I couldnt link them against the provided file, so i made a big stub (d3dim/include/) for the whole thing. It doesnt work at all if you link anything against it,
since it doesnt implement anything at this point. The original is in d3dim/lib/ but i couldnt get it linked. Some people attempted to reimplement it already, but they are game-specific and meh-ish useful. The tutorials listed below give a few hints on how it
might look like. Feel free to implement it.

d3dim/src/tutorials/drawprims	Yes		Yes			Contains "Hack" in drawprims.cpp:288, might be rendering wrong
d3dim/src/tutorials/enumerate	Yes		Yes
d3dim/src/tutorials/texture	Yes		Yes
d3dim/src/tutorials/triangle	Yes		Yes
d3dim/src/tutorials/zbuffer	Yes		Yes


d3drm/...			SKIPPING BECAUSE THE ORIGS FAIL IN WINE

d3dx/...			SKIPPING FOR NOW DUE TO MISSING HEADERS AND LIBS
				It has been deprecated in mingw too and i cant find an old version which still has the files needed
				to re-add it. Feel free to link me to it.

ddraw/src/ddenum		Yes		Yes
ddraw/src/ddex1			Yes		Yes			Blank screen under wine: d3d_shader:glsl_blitter_upload_palette P8 texture loaded without a palette.
ddraw/src/ddex2			Yes		Yes
ddraw/src/ddex3			Yes		Yes
ddraw/src/ddex4			Yes		Yes
ddraw/src/ddex5			Yes		Yes
ddraw/src/ddoverlay		Yes		Yes			Fails in wine
ddraw/src/donuts		Yes		Yes
ddraw/src/font			Yes		Yes
ddraw/src/fswindow		Yes		Yes
ddraw/src/modetest		Yes		Yes
ddraw/src/mosquito		Yes		Yes			Fails in wine
ddraw/src/multimon		Yes		Yes
ddraw/src/stretch		Yes		Yes
ddraw/src/switcher		Yes		Yes			Wine fails fullscreen, works in windowed
ddraw/src/wormhole		Yes		Yes


dinput/src/digame		Yes		Yes
dinput/src/ffdonuts		Yes		Yes			You need to attach a controller
dinput/src/fffileread		Yes		No (broken in wine)	fixme:dinput:IDirectInputDevice7AImpl_EnumEffectsInFile stub!
dinput/src/joyffeed		Yes		Yes
dinput/src/joystimm		Yes		Yes
dinput/src/keybdbuf		Yes		Yes			To be tested
dinput/src/keybdexc		Yes		Yes			To be tested
dinput/src/keybdimm		Yes		Yes			To be tested
dinput/src/mouseexc		Yes		Yes			To be tested
dinput/src/mousenon		Yes		Yes			To be tested
dinput/src/scrawl		Yes		Yes
dinput/src/tutorials/diex1	Yes		Yes
dinput/src/tutorials/diex2	Yes		Yes
dinput/src/tutorials/diex3	Yes		Yes
dinput/src/tutorials/diex4	Yes		Yes
dinput/src/tutorials/diex5	Yes		Yes

dmusic/...			SKIPPING BECAUSE THE ORIGS FAIL IN WINE
				Could be fixed with winetricks which provides the missing files.

dplay/src/bellhop		Yes		No (broken in wine)
dplay/src/chatconnect		Yes		No (broken in wine)	SAFE_DELETE_ARRAYT macro might be a dirty hack
dplay/src/dplaunch		Yes		No (broken in wine)
dplay/src/dpslots		Yes		No (broken in wine)	MinGW missing a struct def (reported(fixed in wine))
dplay/src/duel			Yes		No (broken in wine)	SAFE_DELETE_ARRAYT macro might be a dirty hack
dplay/src/override		Yes		No (broken in wine)
dplay/src/simpleconnect		Yes		No (broken in wine)	SAFE_DELETE_ARRAYT macro might be a dirty hack
dplay/src/stagedconnect		Yes		No (broken in wine)	SAFE_DELETE_ARRAYT macro might be a dirty hack


dsound/src/adjustsound		Yes		Yes
dsound/src/capturesound		Yes		Yes
dsound/src/enumdevices		Yes		Yes
dsound/src/fullduplexfilter	Yes		Yes
dsound/src/play3dsound		Yes		Yes			MinGW missing some GUID defs (reported(fixed in wine))
dsound/src/playsound		Yes		Yes
dsound/src/playstreaming	Yes		Yes
dsound/src/voicemanagement	Yes		Yes

dxmisc/src/getdxver		Yes		Yes
dxmisc/src/setup		Yes		No			(missing dsetup.dll, do we somehow generate this?)
```
