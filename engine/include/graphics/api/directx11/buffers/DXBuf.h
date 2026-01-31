#ifndef DXBUF_H
#define DXBUF_H

#include <d3dcompiler.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <platform/window.h>
#include <graphics/api/graphic_context.h>

class DX11Buf {

    public:
        DX11Buf();

        void Init(D3D11_USAGE USAGE, UINT BindFlags, UINT MISC_FLAGS);
        void UploadData( const void* data, UINT ELEMENT_COUNT, UINT STRIDE );
        void CreateBuffer( Microsoft::WRL::ComPtr<ID3D11Device>& device );

        Microsoft::WRL::ComPtr<ID3D11Buffer> GetRawBufferPtr() { return buffer; }
    private:
        D3D11_BUFFER_DESC buffer_desc;
        D3D11_SUBRESOURCE_DATA buffer_data_desc;

        Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
};

#endif