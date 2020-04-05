#include "D3DUtil.h"
#include "D3DFrame.h"

CD3DFramework7::CD3DFramework7() {
    // Internal variables for the framework class
    m_hWnd					= NULL;		// The window object
    m_bIsFullscreen			= FALSE;	// Fullscreen vs. windowed
    m_bIsStereo				= FALSE;	// Stereo view mode
    m_dwRenderWidth			= 0L;		// Dimensions of the render target
    m_dwRenderHeight		= 0L;
    //m_rcScreenRect			;			// Screen rect for window
    m_pDD					= NULL;		// The DirectDraw object
    m_pD3D					= NULL;		// The Direct3D object
    m_pd3dDevice			= NULL;		// The D3D device
    m_pddsFrontBuffer		= NULL;		// The primary surface
    m_pddsBackBuffer		= NULL;		// The backbuffer surface
    m_pddsBackBufferLeft	= NULL;		// For stereo modes
    m_pddsZBuffer			= NULL;		// The zbuffer surface
    m_dwDeviceMemType		= NULL;
    
	DEBUG_MSG("Stub");
}

	
CD3DFramework7::~CD3DFramework7() {
	DEBUG_MSG("Stub");
	return;
}

// Internal functions for the framework class
HRESULT
CD3DFramework7::CreateZBuffer(GUID * pDeviceGUID) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFramework7::CreateFullscreenBuffers(DDSURFACEDESC2 * pddsd) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFramework7::CreateWindowedBuffers() {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFramework7::CreateDirectDraw(GUID * pDriverGUID, DWORD dwFlags) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFramework7::CreateDirect3D(GUID * pDeviceGUID) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFramework7::CreateEnvironment(GUID * pDriverGUID, GUID * pDeviceGUID, DDSURFACEDESC2 * pMode, DWORD dwFlags) {
	DEBUG_MSG("Stub");
	return 0;
}


// Functions to aid rendering
HRESULT
CD3DFramework7::RestoreSurfaces() {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFramework7::ShowFrame() {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFramework7::FlipToGDISurface(BOOL bDrawFrame) {
	DEBUG_MSG("Stub");
	return 0;
}


// Functions for managing screen and viewport bounds
VOID
CD3DFramework7::Move(INT x, INT y) {
	DEBUG_MSG("Stub");
	return;
}


// Creates the Framework
HRESULT
CD3DFramework7::Initialize(HWND hWnd, GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pddsd, DWORD dwFlags) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFramework7::DestroyObjects() {
	DEBUG_MSG("Stub");
	return 0;
}


