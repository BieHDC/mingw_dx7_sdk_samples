#include <objbase.h>
#include <initguid.h>

//
// DirectSound3D Algorithms
//

//MISSING IN MINGW dsound.h

// Default DirectSound3D algorithm {00000000-0000-0000-0000-000000000000}
#define DS3DALG_DEFAULT GUID_NULL

// No virtualization {C241333F-1C1B-11d2-94F5-00C04FC28ACA}
DEFINE_GUID(DS3DALG_NO_VIRTUALIZATION, 0xc241333f, 0x1c1b, 0x11d2, 0x94, 0xf5, 0x0, 0xc0, 0x4f, 0xc2, 0x8a, 0xca);

// High-quality HRTF algorithm {C2413340-1C1B-11d2-94F5-00C04FC28ACA}
DEFINE_GUID(DS3DALG_HRTF_FULL, 0xc2413340, 0x1c1b, 0x11d2, 0x94, 0xf5, 0x0, 0xc0, 0x4f, 0xc2, 0x8a, 0xca);

// Lower-quality HRTF algorithm {C2413342-1C1B-11d2-94F5-00C04FC28ACA}
DEFINE_GUID(DS3DALG_HRTF_LIGHT, 0xc2413342, 0x1c1b, 0x11d2, 0x94, 0xf5, 0x0, 0xc0, 0x4f, 0xc2, 0x8a, 0xca);
