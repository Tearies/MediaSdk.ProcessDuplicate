// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
#include <windows.h> 
#include <d3d11.h>
#include <D3Dcompiler.h>
#define RemottingSharedHandle "VBI.Media.Shared.HostHwnd"
#define VBIDEFINEMSGCODE 0x4001
#define IFC(x) { hr = (x); if (FAILED(hr)) { goto Cleanup; }}
#define ReleaseInterface(x) { if (NULL != x) { x->Release(); x = NULL; }}
#define ReleaseHandle(x){if(NULL!=x){CloseHandle(x);}}
HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D10Blob** ppBlobOut);
typedef public struct RawVector3
{

	float x;
	float y;
	float z;
	RawVector3() = default;

	RawVector3(const RawVector3&) = default;
	RawVector3& operator=(const RawVector3&) = default;

	RawVector3(RawVector3&&) = default;
	RawVector3& operator=(RawVector3&&) = default;

	constexpr RawVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	explicit RawVector3(_In_reads_(3) const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}

}RawVector3;

typedef public struct RawVector2
{
	float x;
	float y;

	RawVector2() = default;

	RawVector2(const RawVector2&) = default;
	RawVector2& operator=(const RawVector2&) = default;

	RawVector2(RawVector2&&) = default;
	RawVector2& operator=(RawVector2&&) = default;

	constexpr RawVector2(float _x, float _y) : x(_x), y(_y) {}
	explicit RawVector2(_In_reads_(2) const float* pArray) : x(pArray[0]), y(pArray[1]) {}

}RawVector2;

typedef public  struct Vertex
{
	RawVector3* Position;
	RawVector2* TexCoord;
} Vertex;
#endif //PCH_H

