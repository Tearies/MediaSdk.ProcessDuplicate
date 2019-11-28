#include "pch.h"
#include "Util.h"
#include <type_traits>

namespace MediaSdk
{
	namespace ProcessDuplicate
	{
		namespace Common
		{
			void Util::SaveTextureToBmp(String^ fileName, ID3D11Texture2D* Texture)
			{
				HRESULT hr;

				// First verify that we can map the texture
				D3D11_TEXTURE2D_DESC desc;
				Texture->GetDesc(&desc);

				// translate texture format to WIC format. We support only BGRA and ARGB.
				GUID wicFormatGuid;
				switch (desc.Format) {
				case DXGI_FORMAT_R8G8B8A8_UNORM:
					wicFormatGuid = GUID_WICPixelFormat32bppRGBA;
					break;
				case DXGI_FORMAT_B8G8R8A8_UNORM:
					wicFormatGuid = GUID_WICPixelFormat32bppBGRA;
					break;
				 
				 
				}

				// Get the device context
				ID3D11Device* d3dDevice;
				Texture->GetDevice(&d3dDevice);
				ID3D11DeviceContext* d3dContext;
				d3dDevice->GetImmediateContext(&d3dContext);

				// map the texture
				ID3D11Texture2D* mappedTexture;
				D3D11_MAPPED_SUBRESOURCE mapInfo;
				mapInfo.RowPitch;
				hr = d3dContext->Map(
					Texture,
					0,  // Subresource
					D3D11_MAP_READ,
					0,  // MapFlags
					&mapInfo);

				if (FAILED(hr)) {
					// If we failed to map the texture, copy it to a staging resource
					if (hr == E_INVALIDARG) {
						D3D11_TEXTURE2D_DESC desc2;
						desc2.Width = desc.Width;
						desc2.Height = desc.Height;
						desc2.MipLevels = desc.MipLevels;
						desc2.ArraySize = desc.ArraySize;
						desc2.Format = desc.Format;
						desc2.SampleDesc = desc.SampleDesc;
						desc2.Usage = D3D11_USAGE_STAGING;
						desc2.BindFlags = 0;
						desc2.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
						desc2.MiscFlags = 0;

						ID3D11Texture2D* stagingTexture;
						hr = d3dDevice->CreateTexture2D(&desc2, nullptr, &stagingTexture);
						if (FAILED(hr)) {

						}

						// copy the texture to a staging resource
						d3dContext->CopyResource(stagingTexture, Texture);

						// now, map the staging resource
						hr = d3dContext->Map(
							stagingTexture,
							0,
							D3D11_MAP_READ,
							0,
							&mapInfo);
						 

						mappedTexture = std::move(stagingTexture);
					}
					else {

					}
				}
				else {
					mappedTexture = Texture;
				}

				d3dContext->Unmap(mappedTexture, 0);


				IWICImagingFactory* wicFactory;
				hr = CoCreateInstance(
					CLSID_WICImagingFactory,
					nullptr,
					CLSCTX_INPROC_SERVER,
					__uuidof(wicFactory),
					reinterpret_cast<void**>(&wicFactory));
				if (FAILED(hr)) {

				}

				IWICBitmapEncoder* wicEncoder;
				hr = wicFactory->CreateEncoder(
					GUID_ContainerFormatBmp,
					nullptr,
					&wicEncoder);
				if (FAILED(hr)) {

				}

				IWICStream* wicStream;
				hr = wicFactory->CreateStream(&wicStream);
				if (FAILED(hr)) {

				}

				hr = wicStream->InitializeFromFilename(StringConvW(fileName), GENERIC_WRITE);
				if (FAILED(hr)) {

				}

				hr = wicEncoder->Initialize(wicStream, WICBitmapEncoderNoCache);
				if (FAILED(hr)) {

				}

				// Encode and commit the frame
				{
					IWICBitmapFrameEncode* frameEncode;
					wicEncoder->CreateNewFrame(&frameEncode, nullptr);


					hr = frameEncode->Initialize(nullptr);


					hr = frameEncode->SetPixelFormat(&wicFormatGuid);
					if (FAILED(hr)) {

					}

					hr = frameEncode->SetSize(desc.Width, desc.Height);


					hr = frameEncode->WritePixels(
						desc.Height,
						mapInfo.RowPitch,
						desc.Height * mapInfo.RowPitch,
						reinterpret_cast<BYTE*>(mapInfo.pData));


					hr = frameEncode->Commit();

				}

				hr = wicEncoder->Commit();


			}
		}
	}
}

