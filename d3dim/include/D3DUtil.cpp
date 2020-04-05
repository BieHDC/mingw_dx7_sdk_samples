#include "D3DUtil.h"

//-----------------------------------------------------------------------------
// Short cut functions for creating and using DX structures
//-----------------------------------------------------------------------------
VOID
D3DUtil_InitDeviceDesc(D3DDEVICEDESC7& ddDevDesc) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DUtil_InitSurfaceDesc(DDSURFACEDESC2& ddsd, DWORD dwFlags, DWORD dwCaps) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DUtil_InitMaterial(D3DMATERIAL7& mtrl, FLOAT r, FLOAT g, FLOAT b, FLOAT a) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DUtil_InitLight(D3DLIGHT7& light, D3DLIGHTTYPE ltType, FLOAT x, FLOAT y, FLOAT z) {
	DEBUG_MSG("Stub");
	return;
}

const TCHAR*
D3DUtil_GetDXSDKMediaPath() {
	DEBUG_MSG("Stub");
	return "invalid";
}

//-----------------------------------------------------------------------------
// D3D Matrix functions. For performance reasons, some functions are inline.
//-----------------------------------------------------------------------------
HRESULT
D3DUtil_SetViewMatrix(D3DMATRIX& mat, D3DVECTOR& vFrom, D3DVECTOR& vAt, D3DVECTOR& vUp) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
D3DUtil_SetProjectionMatrix(D3DMATRIX& mat, FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane) {
	DEBUG_MSG("Stub");
	return 0;
}
                                    
VOID
D3DUtil_SetRotateXMatrix(D3DMATRIX& mat, FLOAT fRads) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DUtil_SetRotateYMatrix(D3DMATRIX& mat, FLOAT fRads) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DUtil_SetRotateZMatrix(D3DMATRIX& mat, FLOAT fRads) {
	DEBUG_MSG("Stub");
	return;
}


VOID 
D3DUtil_SetRotationMatrix(D3DMATRIX& mat, D3DVECTOR& vDir, FLOAT fRads) {
	DEBUG_MSG("Stub");
	return;
}
