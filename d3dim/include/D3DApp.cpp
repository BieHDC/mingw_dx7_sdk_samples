#include <tchar.h>

#include "D3DUtil.h"
#include "D3DApp.h"

CD3DApplication::CD3DApplication() {
    m_pFramework	= NULL;
    m_bActive		= false;
    m_bReady		= false;

    m_bFrameMoving	= false;
    m_bSingleStep	= false;
    m_dwBaseTime	= 0;
    m_dwStopTime	= 0;

    m_hWnd					= NULL;
    m_pDeviceInfo			= NULL;
    m_pDD					= NULL;
    m_pD3D					= NULL;
    m_pd3dDevice			= NULL;
    m_pddsRenderTarget		= NULL;
    m_pddsRenderTargetLeft	= NULL; // For stereo modes
    m_ddsdRenderTarget		= {0};
    
    m_matLeftView	= {0};
    m_matRightView	= {0};
    m_matView		= {0};

    m_strWindowTitle	= _T((char*)"Null Window");
    m_bAppUseZBuffer	= false;
    m_bAppUseStereo		= false;
    m_bShowStats		= false;
    m_fnConfirmDevice	= NULL;
    
    DEBUG_MSG("CD3DApplication Constructor");
}  


HRESULT
CD3DApplication::Initialize3DEnvironment() {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DApplication::Change3DEnvironment() {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DApplication::Render3DEnvironment() {
	DEBUG_MSG("Stub");
	return 0;
}

VOID
CD3DApplication::Cleanup3DEnvironment() {
	DEBUG_MSG("Stub");
	return;
}

VOID
CD3DApplication::DisplayFrameworkError(HRESULT, DWORD) {
	DEBUG_MSG("Stub");
	return;
}

// Overridable power management (APM) functions
LRESULT 
CD3DApplication::OnQuerySuspend(DWORD dwFlags) {
	DEBUG_MSG("Stub");
	return 0;
}

LRESULT
CD3DApplication::OnResumeSuspend(DWORD dwData) {
	DEBUG_MSG("Stub");
	return 0;
}

// View control functions (for stereo-enabled applications)
VOID
CD3DApplication::SetViewParams(D3DVECTOR* vEyePt, D3DVECTOR* vLookatPt, D3DVECTOR* vUpVec, FLOAT fEyeDistance) {
	DEBUG_MSG("Stub");
	return;
}

// Miscellaneous functions
VOID
CD3DApplication::ShowStats() {
	DEBUG_MSG("Stub");
	return;
}

VOID
CD3DApplication::OutputText(DWORD x, DWORD y, TCHAR* str) {
	DEBUG_MSG("Stub");
	return;
}

//Enuming
char D3Ddevicename[256];
static HRESULT (*g_fnAppConfirmFn)(DDCAPS*, D3DDEVICEDESC7*) = NULL;
static D3DEnum_DeviceInfo g_pDeviceList[20];
static DWORD g_dwNumDevicesEnumerated = 0L;
static DWORD g_dwNumDevices           = 0L;


static HRESULT WINAPI DeviceEnumCallback( TCHAR* strDesc, TCHAR* strName,
		D3DDEVICEDESC7* pDesc, VOID* pParentInfo) {
	
	DEBUG_MSG2("DeviceEnumCallback: %s : %s", strDesc, strName);
	// Keep track of # of devices that were enumerated
	g_dwNumDevicesEnumerated++;

	D3DEnum_DeviceInfo* pDriverInfo = (D3DEnum_DeviceInfo*)pParentInfo;
	D3DEnum_DeviceInfo* pDeviceInfo = &g_pDeviceList[g_dwNumDevices];
	SAFE_DELETE_ARRAY(pDeviceInfo->pddsdModes);
	ZeroMemory(pDeviceInfo, sizeof(D3DEnum_DeviceInfo));

	// Select either the HAL or the HEL device desc:
	pDeviceInfo->bHardware = pDesc->dwDevCaps & D3DDEVCAPS_HWRASTERIZATION;
	memcpy(&pDeviceInfo->ddDeviceDesc, pDesc, sizeof(D3DDEVICEDESC7));

	// Set up device info for this device
	pDeviceInfo->bDesktopCompatible = pDriverInfo->bDesktopCompatible;
	pDeviceInfo->ddDriverCaps       = pDriverInfo->ddDriverCaps;
	pDeviceInfo->ddHELCaps          = pDriverInfo->ddHELCaps;
	pDeviceInfo->guidDevice         = pDesc->deviceGUID;
	pDeviceInfo->pDeviceGUID        = &pDeviceInfo->guidDevice;
	pDeviceInfo->pddsdModes         = new DDSURFACEDESC2[pDriverInfo->dwNumModes];

	// Copy the driver GUID and description for the device
	if(pDriverInfo->pDriverGUID) {
		pDeviceInfo->guidDriver  = pDriverInfo->guidDriver;
		pDeviceInfo->pDriverGUID = &pDeviceInfo->guidDriver;
		lstrcpyn( pDeviceInfo->strDesc, pDriverInfo->strDesc, 39 );
	}
	else {
		pDeviceInfo->pDriverGUID = NULL;
		lstrcpyn(pDeviceInfo->strDesc, strName, 39);
	}

	// Avoid duplicates: only enum HW devices for secondary DDraw drivers.
	if(NULL != pDeviceInfo->pDriverGUID && FALSE == pDeviceInfo->bHardware)
		return D3DENUMRET_OK;

	// Give the app a chance to accept or reject this device.
	if(g_fnAppConfirmFn)
		if(FAILED(g_fnAppConfirmFn(&pDeviceInfo->ddDriverCaps,
									 &pDeviceInfo->ddDeviceDesc)))
			return D3DENUMRET_OK;

	// Build list of supported modes for the device
	DWORD i = 0;
	for(i=0; i<pDriverInfo->dwNumModes; i++) {
		DDSURFACEDESC2 ddsdMode = pDriverInfo->pddsdModes[i];
		DWORD dwRenderDepths    = pDeviceInfo->ddDeviceDesc.dwDeviceRenderBitDepth;
		DWORD dwDepth           = ddsdMode.ddpfPixelFormat.dwRGBBitCount;

		// Accept modes that are compatable with the device
		if(     ((dwDepth == 32) && (dwRenderDepths & DDBD_32)) ||
				((dwDepth == 24) && (dwRenderDepths & DDBD_24)) ||
				((dwDepth == 16) && (dwRenderDepths & DDBD_16))) {
			// Copy compatible modes to the list of device-supported modes
			pDeviceInfo->pddsdModes[pDeviceInfo->dwNumModes++] = ddsdMode;

			// Record whether the device has any stereo modes
			if( ddsdMode.ddsCaps.dwCaps2 & DDSCAPS2_STEREOSURFACELEFT )
				pDeviceInfo->bStereoCompatible = TRUE;
		}
	}

	// Bail if the device has no supported modes
	if( 0 == pDeviceInfo->dwNumModes )
		return D3DENUMRET_OK;

	// Find a 640x480x16 mode for the default fullscreen mode
	for( i=0; i<pDeviceInfo->dwNumModes; i++ ) {
		if((pDeviceInfo->pddsdModes[i].dwWidth == 640) &&
				(pDeviceInfo->pddsdModes[i].dwHeight == 480) &&
				(pDeviceInfo->pddsdModes[i].ddpfPixelFormat.dwRGBBitCount == 16)) {
			pDeviceInfo->ddsdFullscreenMode = pDeviceInfo->pddsdModes[i];
			pDeviceInfo->dwCurrentMode      = i;
		}
	}

	// Select whether the device is initially windowed
	pDeviceInfo->bWindowed = pDeviceInfo->bDesktopCompatible;

	// Accept the device and return
	g_dwNumDevices++;

	return D3DENUMRET_OK;
}

int SortModesCallback(const VOID* arg1, const VOID* arg2)
{
	//DEBUG_MSG2("SortModesCallback: %p %p", arg1, arg2);
	DDSURFACEDESC2* p1 = (DDSURFACEDESC2*)arg1;
	DDSURFACEDESC2* p2 = (DDSURFACEDESC2*)arg2;

	if(p1->dwWidth < p2->dwWidth)
		return -1;
	if(p1->dwWidth > p2->dwWidth)
		return +1;

	if(p1->dwHeight < p2->dwHeight)
		return -1;
	if(p1->dwHeight > p2->dwHeight)
		return +1;

	if(p1->ddpfPixelFormat.dwRGBBitCount < p2->ddpfPixelFormat.dwRGBBitCount)
		return -1;
	if(p1->ddpfPixelFormat.dwRGBBitCount > p2->ddpfPixelFormat.dwRGBBitCount)
		return +1;

	return 0;
}

static HRESULT WINAPI ModeEnumCallback(DDSURFACEDESC2* pddsd, VOID* pParentInfo) {
	//DEBUG_MSG2("ModeEnumCallback: %p : %p", pddsd, pParentInfo);
	D3DEnum_DeviceInfo* pDevice = (D3DEnum_DeviceInfo*)pParentInfo;

	// Reallocate storage for the modes
	DDSURFACEDESC2* pddsdNewModes = new DDSURFACEDESC2[pDevice->dwNumModes+1];
	memcpy(pddsdNewModes, pDevice->pddsdModes,
		   pDevice->dwNumModes * sizeof(DDSURFACEDESC2));
	SAFE_DELETE_ARRAY(pDevice->pddsdModes);
	pDevice->pddsdModes = pddsdNewModes;

	// Add the new mode
	pDevice->pddsdModes[pDevice->dwNumModes++] = (*pddsd);

	return DDENUMRET_OK;
}

static BOOL WINAPI DriverEnumCallback(GUID* pGUID, TCHAR* strDesc, TCHAR* strName, VOID*, HMONITOR) {

	D3DEnum_DeviceInfo d3dDeviceInfo;
	LPDIRECTDRAW7      pDD;
	LPDIRECT3D7        pD3D;
	HRESULT            hr;

	DEBUG_MSG2("Driver callback: %s : %s", strDesc, strName);
	
	// Use the GUID to create the DirectDraw object
	hr = DirectDrawCreateEx(pGUID, (VOID**)&pDD, IID_IDirectDraw7, NULL);
	if(FAILED(hr))
	{
		DEBUG_MSG("Can't create DDraw during enumeration!");
		return D3DENUMRET_OK;
	}

	// Create a D3D object, to enumerate the d3d devices
	hr = pDD->QueryInterface(IID_IDirect3D7, (VOID**)&pD3D);
	if(FAILED(hr))
	{
		pDD->Release();
		DEBUG_MSG("Can't query IDirect3D7 during enumeration!");
		return D3DENUMRET_OK;
	}

	// Copy data to a device info structure
	ZeroMemory(&d3dDeviceInfo, sizeof(d3dDeviceInfo));
	lstrcpyn(d3dDeviceInfo.strDesc, strDesc, 39);
	d3dDeviceInfo.ddDriverCaps.dwSize = sizeof(DDCAPS);
	d3dDeviceInfo.ddHELCaps.dwSize    = sizeof(DDCAPS);
	pDD->GetCaps(&d3dDeviceInfo.ddDriverCaps, &d3dDeviceInfo.ddHELCaps);
	if(pGUID) {
		d3dDeviceInfo.guidDriver = (*pGUID);
		d3dDeviceInfo.pDriverGUID = &d3dDeviceInfo.guidDriver;
	}

	strcpy(D3Ddevicename, d3dDeviceInfo.strDesc);

	// Record whether the device can render into a desktop window
	if(d3dDeviceInfo.ddDriverCaps.dwCaps2 & DDCAPS2_CANRENDERWINDOWED)
		if(NULL == d3dDeviceInfo.pDriverGUID)
			d3dDeviceInfo.bDesktopCompatible = TRUE;

	// Enumerate the fullscreen display modes.
	pDD->EnumDisplayModes(0, NULL, &d3dDeviceInfo, ModeEnumCallback);

	// Sort list of display modes
	qsort(d3dDeviceInfo.pddsdModes, d3dDeviceInfo.dwNumModes,
		   sizeof(DDSURFACEDESC2), SortModesCallback);

	// Now, enumerate all the 3D devices
	pD3D->EnumDevices(DeviceEnumCallback, &d3dDeviceInfo);

	// Clean up and return
	SAFE_DELETE_ARRAY(d3dDeviceInfo.pddsdModes);
	pD3D->Release();
	pDD->Release();

	DEBUG_MSG2("Driver callback: %s : %s END", strDesc, strName);
	return DDENUMRET_OK;
}
// Functions to create, run, pause, and clean up the application
HRESULT
CD3DApplication::Create(HINSTANCE hInst, TCHAR* strCmdLine) {
	DEBUG_MSG2("Stub %p %s", hInst, strCmdLine);
	
	HRESULT hr;
	
	DirectDrawEnumerateEx( DriverEnumCallback, NULL,
						   DDENUM_ATTACHEDSECONDARYDEVICES |
						   DDENUM_DETACHEDSECONDARYDEVICES |
						   DDENUM_NONDISPLAYDEVICES );

	// Make sure devices were actually enumerated
	if( !g_dwNumDevicesEnumerated )
	{
		DEBUG_MSG("No devices and/or modes were enumerated!");
		return D3DENUMERR_ENUMERATIONFAILED;
	}
	if( !g_dwNumDevices )
	{
		DEBUG_MSG("No enumerated devices were accepted!");
		DEBUG_MSG("Try enabling the D3D Reference Rasterizer.");
		return D3DENUMERR_SUGGESTREFRAST;
	}
	
	//we might have to create a window here etc?
	
	return S_OK;
}

INT
CD3DApplication::Run() {
	DEBUG_MSG("Stub");
	
	// Load keyboard accelerators
	HACCEL hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

	// Now we're ready to recieve and process Windows messages.
	BOOL bGotMsg;
	MSG  msg;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
	while( WM_QUIT != msg.message  ) {
		// Use PeekMessage() if the app is active, so we can use idle time to
		// render the scene. Else, use GetMessage() to avoid eating CPU time.
		bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );		

		if( bGotMsg ) {
			// Translate and dispatch the message
			if( 0 == TranslateAccelerator( m_hWnd, hAccel, &msg ) ) {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		} else {
			// Render a frame during idle time (no messages are waiting)
			if( m_bReady ) {
				// 2D, 3D 렌더링 메인 루틴
				//if( FAILED( ProcessNextFrame(m_hWnd) ) )
				//	DestroyWindow( m_hWnd );
				DEBUG_MSG("rdy");
				if(FAILED(Render())) {
					DEBUG_MSG("F");
				}
			}
		}
	}
	
	return msg.wParam;
}


LRESULT
CD3DApplication::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	DEBUG_MSG("Stub");
	return 0;
}

VOID
CD3DApplication::Pause(BOOL bPause) {
	DEBUG_MSG("Stub");
	return;
}

