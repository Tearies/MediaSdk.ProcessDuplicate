// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
#include <windows.h> 
#define RemottingSharedHandle "VBI.Media.Shared.HostHwnd"
#define VBIDEFINEMSGCODE 0x4001
#define IFC(x) { hr = (x); if (FAILED(hr)) { goto Cleanup; }}
#define ReleaseInterface(x) { if (NULL != x) { x->Release(); x = NULL; }}
#define ReleaseHandle(x){if(NULL!=x){CloseHandle(x);}}
#endif //PCH_H

