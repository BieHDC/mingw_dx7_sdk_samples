#include "D3DUtil.h"
#include "D3DTextr.h"

//-----------------------------------------------------------------------------
// Access functions for loaded textures. Note: these functions search
// an internal list of the textures, and use the texture associated with the
// ASCII name.
//-----------------------------------------------------------------------------
LPDIRECTDRAWSURFACE7
D3DTextr_GetSurface(TCHAR* strName) {
	DEBUG_MSG("Stub");
	return 0;
}


//-----------------------------------------------------------------------------
// Texture invalidation and restoration functions
//-----------------------------------------------------------------------------
HRESULT
D3DTextr_Invalidate(TCHAR* strName) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
D3DTextr_Restore(TCHAR* strName, LPDIRECT3DDEVICE7 pd3dDevice) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
D3DTextr_InvalidateAllTextures() {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
D3DTextr_RestoreAllTextures(LPDIRECT3DDEVICE7 pd3dDevice) {
	DEBUG_MSG("Stub");
	return 0;
}


//-----------------------------------------------------------------------------
// Texture creation and deletion functions
//-----------------------------------------------------------------------------

HRESULT
D3DTextr_CreateTextureFromFile(TCHAR* strName, DWORD dwStage, DWORD dwFlags) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
D3DTextr_CreateEmptyTexture(TCHAR* strName, DWORD dwWidth, DWORD dwHeight, DWORD dwStage, DWORD dwFlags) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
D3DTextr_DestroyTexture(TCHAR* strName) {
	DEBUG_MSG("Stub");
	return 0;
}

VOID
D3DTextr_SetTexturePath(TCHAR* strTexturePath) {
	DEBUG_MSG("Stub");
	return;
}
