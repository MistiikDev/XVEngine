#ifndef DX11_LAYOUT_H
#define DX11_LAYOUT_H

#include <d3dcompiler.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <platform/window.h>
#include <graphics/api/graphic_context.h>

class DX11Layout {
    public:
        DX11Layout();

        void LinkAttribute( const char* LAYOUT_NAME, DXGI_FORMAT FORMAT, UINT offest );
        void CompileAttributeLayer( Microsoft::WRL::ComPtr<ID3D11Device>& device, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context, Microsoft::WRL::ComPtr<ID3DBlob>& shader_buffer );
    
        ID3D11InputLayout** GetInputLayoutPtr() { return &(this->VS_LAYOUT); }
        
        private:
            std::vector<D3D11_INPUT_ELEMENT_DESC> attributes;
            ID3D11InputLayout* VS_LAYOUT;
};

#endif