#include "pch.h"
#include "RenderTarget.h"
using namespace MediaSdk::Common;

RenderTargetProxy::RenderTargetProxy(IntPtr^ targetSurface)
	: surface(targetSurface),
	  prender_target_view(nullptr)
{
	ID3D11Texture2D* tempSurface = static_cast<ID3D11Texture2D*>(surface->ToPointer());
	ID3D11Device* tempDevice;
	ID3D11DeviceContext* devicecontext;
	ID3D11RenderTargetView* render_target_view;
	IDXGISwapChain* swapChain;
	tempSurface->GetDevice(&tempDevice);
	tempDevice->GetImmediateContext(&devicecontext);
	pDevice = tempDevice;
	pdevicecontext = devicecontext;

	/*ID3D11Texture2D* pBackBuffer = NULL;
	pswapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	prender_target_view = render_target_view;*/
}

void RenderTargetProxy::Update()
{
	//float ClearColor[4] = { 0.5f, 0.1f, 0.2f, 1.0f }; //red,green,blue,alpha
	//pdevicecontext->ClearRenderTargetView(prender_target_view, ClearColor);
	//pswapChain->Present(0, 0);
}

void RenderTargetProxy::CopySource(ID3D11Texture2D* shared_resource)
{
}
