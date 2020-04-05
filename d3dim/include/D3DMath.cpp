#include "D3DUtil.h"
#include "D3DMath.h"

//-----------------------------------------------------------------------------
// Matrix functions
//-----------------------------------------------------------------------------
VOID
D3DMath_MatrixMultiply(D3DMATRIX& q, D3DMATRIX& a, D3DMATRIX& b) {
	DEBUG_MSG("Stub");
	return;
}

HRESULT
D3DMath_MatrixInvert(D3DMATRIX& q, D3DMATRIX& a) {
	DEBUG_MSG("Stub");
	return 0;
}


//-----------------------------------------------------------------------------
// Vector functions
//-----------------------------------------------------------------------------
HRESULT
D3DMath_VectorMatrixMultiply( D3DVECTOR& vDest, D3DVECTOR& vSrc, D3DMATRIX& mat) {
	DEBUG_MSG("Stub");
	return 0;
}

HRESULT
D3DMath_VertexMatrixMultiply(D3DVERTEX& vDest, D3DVERTEX& vSrc, D3DMATRIX& mat) {
	DEBUG_MSG("Stub");
	return 0;
}


//-----------------------------------------------------------------------------
// Quaternion functions
//-----------------------------------------------------------------------------
VOID
D3DMath_QuaternionFromRotation(FLOAT& x, FLOAT& y, FLOAT& z, FLOAT& w,
                               D3DVECTOR& v, FLOAT fTheta) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DMath_RotationFromQuaternion(D3DVECTOR& v, FLOAT& fTheta,
                               FLOAT x, FLOAT y, FLOAT z, FLOAT w) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DMath_QuaternionFromAngles(FLOAT& x, FLOAT& y, FLOAT& z, FLOAT& w,
                             FLOAT fYaw, FLOAT fPitch, FLOAT fRoll) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DMath_MatrixFromQuaternion(D3DMATRIX& mat, FLOAT x, FLOAT y, FLOAT z, FLOAT w) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DMath_QuaternionFromMatrix(FLOAT &x, FLOAT &y, FLOAT &z, FLOAT &w, D3DMATRIX& mat) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DMath_QuaternionMultiply(FLOAT& Qx, FLOAT& Qy, FLOAT& Qz, FLOAT& Qw,
                           FLOAT Ax, FLOAT Ay, FLOAT Az, FLOAT Aw,
                           FLOAT Bx, FLOAT By, FLOAT Bz, FLOAT Bw) {
	DEBUG_MSG("Stub");
	return;
}

VOID
D3DMath_QuaternionSlerp(FLOAT& Qx, FLOAT& Qy, FLOAT& Qz, FLOAT& Qw,
                        FLOAT Ax, FLOAT Ay, FLOAT Az, FLOAT Aw,
                        FLOAT Bx, FLOAT By, FLOAT Bz, FLOAT Bw,
                        FLOAT fAlpha) {
	DEBUG_MSG("Stub");
	return;
}

