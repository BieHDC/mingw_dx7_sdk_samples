#include "D3DUtil.h"
#include "D3DEnum.h"

//-----------------------------------------------------------------------------
// Name: D3DEnum_EnumerateDevices()
// Desc: Enumerates all drivers, devices, and modes. The callback function is
//       called each device, to confirm that the device supports the feature
//       set required by the app.
//-----------------------------------------------------------------------------
HRESULT
D3DEnum_EnumerateDevices(HRESULT (*fn)(DDCAPS*, D3DDEVICEDESC7*)) {
	DEBUG_MSG("Stub");
	return 0;
}


//-----------------------------------------------------------------------------
// Name: D3DEnum_FreeResources()
// Desc: Cleans up any memory allocated during device enumeration
//-----------------------------------------------------------------------------
VOID
D3DEnum_FreeResources() {
	DEBUG_MSG("Stub");
	return;
}


//-----------------------------------------------------------------------------
// Name: D3DEnum_GetDevices()
// Desc: Returns a ptr to the array of enumerated D3DDEVICEINFO structures.
//-----------------------------------------------------------------------------
VOID
D3DEnum_GetDevices(D3DEnum_DeviceInfo** ppDevices, DWORD* pdwCount) {
	DEBUG_MSG("Stub");
	return;
}


//-----------------------------------------------------------------------------
// Name: D3DEnum_SelectDefaultDevice()
// Desc: Picks a driver based on a set of passed in criteria. The
//       D3DENUM_SOFTWAREONLY flag can be used to pick a software device.
//-----------------------------------------------------------------------------
HRESULT
D3DEnum_SelectDefaultDevice(D3DEnum_DeviceInfo** pDevice, DWORD dwFlags) {
	DEBUG_MSG("Stub");
	return 0;
}


//-----------------------------------------------------------------------------
// Name: D3DEnum_UserChangeDevice()
// Desc: Pops up a dialog which allows the user to select a new device.
//-----------------------------------------------------------------------------
HRESULT
D3DEnum_UserChangeDevice(D3DEnum_DeviceInfo** ppDevice) {
	DEBUG_MSG("Stub");
	return 0;
}
