//-----------------------------------------------------------------------------
// File: DXReadme.txt
//
// Desc: Readme file for the DirectX SDK samples directory
//
// Copyright (c) 1998-1999 Microsoft Corporation. All rights reserved.
//
// EDITED BY ME
//
//-----------------------------------------------------------------------------

This directory structure contains all the samples for the DirectX SDK.


The samples are organized by component, where appropriate. For example, samples
specific to one component can be found in the following sub-directories:
        D3DIM     - Direct3D immediate-mode samples
        D3DRM     - Direct3D retained-mode samples
        D3DX      - D3DX samples
        DDraw     - DirectDraw samples
        DInput    - DirectInput samples
        DMusic    - DirectMusic samples
        DPlay     - DirectPlay samples
        DSound    - DirectSound samples
        DXMisc    - Miscellaneous code and libraries (DSetup sample)

Some of the these directories, such as D3DIM, are broken down even further, 
due to the large number of samples for those components. Please see
the readme.txt files in the individual directories for more information.


HOW TO BUILD
------------

NOTES FOR USERS OF VISUAL C++
-----------------------------
FIXME


NOTES FOR D3DIM SAMPLES
-----------------------

Release Notes for Samples:

General:

	These samples are based on a common framework provided in the D3DFrame
directory.  This framework is intended to conceal most of the initialization
work so that the technique being demonstrated is clearly shown.  This
framework does not necessarily represent the optimal initialization code for
a major application.

	The samples do not currently operate in 8-bit screen depths.

	Some samples require features that may not be present on your
current hardware.  To see the effect of these features, the reference
rasterizer may be selected, *however it is not enabled by default.*
A registry key required to enable it and utility .reg files have
been provided in the bin directory for this purpose.


Commands:
        <F1>            About, this list of commands
        <F2>            Change Device Dialog
				Device
				Display Mode (these are stored per device)
        <Alt-Enter>     Toggle full-screen/windowed operation
        <Esc>           Exit


Sample Descriptions:

For detailed information on a particular sample see the readme.txt in each samples'
\src folder.

    Bend
        Demonstrates drawprimitive with a simple technique for smooth
        skinning of a joint between two segments.

    BillBoard
	Demonstrates colorkey for both objects and their shadows.

    Boids
	Demonstrates DrawPrim usage

    Bump Earth
	Demonstrates the usage of the BUMPENVMAP bump mapping approach.
	Try using other images in earthenvmap.bmp to simulate different
	number/colors of light sources.  16x16 textures work fine.

    Bump Waves
	Another bump mapping sample.

    Clip Mirror
	Demonstrates usage of custom-defined clipping planes.

    Compress
	Demonstrates how to load a DDS texture file and deal with DXTN-compressed
	surfaces.

    Dolphin
	Demonstrates mesh blending.

    EnumTex
	Demonstrates how to properly enumerate texture formats.

    Environment Cube
	Shows how to set up dynamic cubic environment mapping.

    Filter
	Demonstrates quality differences in different texture filtering methods.
	Currently both objects are rendered using the current device.
	Known issue:  Sample never sets max anisotropy high enough for
			  anisotropic filtering to kick in.

    Fireworks
	Cool demo.

    Flare
	How to add lens flare to just about anything.

    Light Map
	Shows how to implement light maps via multitexture.

    Lights
	Demonstrates use of the various Direct3D light source types.

    MFC Fog
	Demonstrates Direct3D geometry pipeline's vertex fog, and how to use MFC
	with Direct3D.

    MFCTex
        Tool written in MFC, used to interactively play with Direct3D's
        multitexturing API.

    MipMap
	Demonstrates/tests mip mapping capabilities
	Image on left is not mipmapped, image on right is.

    MultiTexture
	Demonstrates a dual texture technique of applying a light map to a
        base texture.

        There is a bug in certain Rage II drivers where the driver uses the 
        MODULATE blend mode even when DECAL is requested.  This causes the 
        sample to render all black when running on HAL on this driver.

    Screen Saver
	Shows how to write a screen saver that uses D3D.

    Shadow Volume
	Demonstrates use of stencil buffers to display real-time shadows cast
        on arbitrary surfaces.  This requires the software rasterizers or hardware
        supporting stencil buffers.  Other hardware will not appear in the dialog.

    Shadow Volume 2
        This sample demonstrates more sophisticated shadowing techniques that
	require more than one bit of stencil buffer, such as when object shadows
	are intersecting.  This source code does not demonstrate ideal usage of
	the API for applications beyond visual demonstrations.

    Sphere Map
	Shows how to use a spherical environment map.

    Stencil Depth
	Shows how to use the stencil buffer to measure depth complexity.

    Stencil Mirror
	Shows how to use the stencil buffer to create a mirror.

    Vertex Buffer
	Demonstrates a usage scenario for vertex buffers.

    Video Texture
	Shows how to use an AVI as a texture map.

    W-Buffer
	Demonstrates eye-relative z-buffering.  This requires either the
        Reference Software rasterizer or hardware that supports this technique.
        Other hardware (and the std software device) will not appear in the dialog.

    X File
	Shows how to load an "X" file in D3D Immediate Mode.

