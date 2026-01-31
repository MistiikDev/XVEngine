#include <graphics/api/directx11/buffers/DXLayout.h>

DX11Layout::DX11Layout() {

}

void DX11Layout::LinkAttribute( const char* LAYOUT_NAME, DXGI_FORMAT FORMAT, UINT offset ) {
    D3D11_INPUT_ELEMENT_DESC attribute_desc = {
        LAYOUT_NAME, 0, FORMAT, 0, offset, D3D11_INPUT_PER_VERTEX_DATA, 0
    };

    this->attributes.push_back(attribute_desc);
}

void DX11Layout::CompileAttributeLayer( Microsoft::WRL::ComPtr<ID3D11Device>& device, Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context, Microsoft::WRL::ComPtr<ID3DBlob>& vertex_shader_buffer ) {
    if (!vertex_shader_buffer) {
        XV_LOG_ERROR("Cannot create input layout: vertex shader buffer is null");
        return;
    }

    device->CreateInputLayout( attributes.data(), attributes.size(), vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(), &VS_LAYOUT);
    context->IASetInputLayout( VS_LAYOUT );
}

