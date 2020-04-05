#include "D3DUtil.h"
#include "D3DFile.h"

CD3DFileObject::CD3DFileObject(TCHAR* strName) {
	m_strName[80]	= {0};
    m_pNext			= NULL;
    m_pChild		= NULL;

    // For file frames
    m_mat			= {0};

    // For file meshes
    m_bHasMeshData				= false;
    m_dwNumVertices				= 0;
    m_pVertices					= NULL;
    m_dwNumIndices				= 0;
    m_pIndices					= NULL;
    m_dwNumMaterials			= 0;
    m_Material[MAX_MATERIAL]	= {0};
    m_bHasAlpha					= false;
    
	DEBUG_MSG("Stub");
}

CD3DFileObject::~CD3DFileObject() {
	DEBUG_MSG("Stub");
	return;
}


// Initializing functions
VOID
CD3DFileObject::AddNext(CD3DFileObject* fo) {
	DEBUG_MSG("Stub");
	return;
}

VOID
CD3DFileObject::AddChild(CD3DFileObject* fo) {
	DEBUG_MSG("Stub");
	return;
}

VOID
CD3DFileObject::SetNormals(D3DVECTOR* pNormals) {
	DEBUG_MSG("Stub");
	return;
}

VOID
CD3DFileObject::SetTextureCoords(FLOAT* pTexCoords) {
	DEBUG_MSG("Stub");
	return;
}

VOID
CD3DFileObject::SetMaterialData(DWORD dwMaterial, D3DMATERIAL7* pmtrl, TCHAR*strName) {
	DEBUG_MSG("Stub");
	return;
}

VOID
CD3DFileObject::AddFace(DWORD dwMaterial, DWORD* pFaceData, DWORD dwNumFaces) {
	DEBUG_MSG("Stub");
	return;
}

HRESULT
CD3DFileObject::ComputeNormals() {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFileObject::SetMeshGeometry(D3DVECTOR* pvVertices, DWORD dwNumVertices, DWORD* pFaces, DWORD dwNumFaces) {
	DEBUG_MSG("Stub");
	return 0;
}

// Access functions
HRESULT
CD3DFileObject::GetMeshGeometry(D3DVERTEX** ppVertices, DWORD* pdwNumVertices, WORD** ppIndices, DWORD* pdwNumIndices) {
	DEBUG_MSG("Stub");
	return 0;
}

// Common functions
VOID
CD3DFileObject::Render(LPDIRECT3DDEVICE7 pd3dDevice , BOOL bAlpha) {
	DEBUG_MSG("Stub");
	return;
}

BOOL
CD3DFileObject::EnumObjects(BOOL(*fnCallback)(CD3DFileObject*,D3DMATRIX*,VOID*), D3DMATRIX* pmat, VOID* pContext) {
	DEBUG_MSG("Stub");
	return 0;
}




//-----------------------------------------------------------------------------
// Name: class CD3DFile
// Desc: 
//-----------------------------------------------------------------------------


CD3DFile::CD3DFile() {
    m_pRoot = NULL;
    
	DEBUG_MSG("Stub");
}

CD3DFile::~CD3DFile() {
	DEBUG_MSG("Stub");
}


HRESULT
CD3DFile::GetMeshVertices(TCHAR* strName, D3DVERTEX** ppVertices, DWORD* pdwNumVertices) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFile::GetMeshIndices(TCHAR* strName, WORD** ppIndices, DWORD* pdwNumIndices) {
	DEBUG_MSG("Stub");
	return 0;
}

CD3DFileObject*
CD3DFile::FindObject(TCHAR* strName) {
	DEBUG_MSG("Stub");
	return 0;
}

VOID
CD3DFile::EnumObjects(BOOL(*fnCallback)(CD3DFileObject*,D3DMATRIX*,VOID*), D3DMATRIX* pmat, VOID* pContext) {
	DEBUG_MSG("Stub");
	return;
}

VOID
CD3DFile::Scale(FLOAT fScale) {
	DEBUG_MSG("Stub");
	return;
}

HRESULT
CD3DFile::Load(TCHAR* strFilename) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
CD3DFile::Render(LPDIRECT3DDEVICE7) {
	DEBUG_MSG("Stub");
	return 0;
}




