#include <graphics/api/directx11/buffers/DXBuf.h>

DX11Buf::DX11Buf() {

}

void DX11Buf::Init( D3D11_USAGE USAGE, UINT BindFlags, UINT MISC_FLAGS ) {
    this->buffer_desc = {};
    this->buffer_data_desc = {};

    this->buffer = nullptr;
        
    //
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.BindFlags = BindFlags;
    buffer_desc.Usage = USAGE;
    buffer_desc.MiscFlags = MISC_FLAGS;
}

void DX11Buf::UploadData(const void* data, UINT ELEMENT_COUNT, UINT STRIDE) {
    buffer_desc.ByteWidth = ELEMENT_COUNT * STRIDE;
    buffer_desc.StructureByteStride = STRIDE;

    buffer_data_desc.pSysMem = data;
}

void DX11Buf::CreateBuffer( Microsoft::WRL::ComPtr<ID3D11Device>& device ) {
    HRESULT hr = device->CreateBuffer( &buffer_desc, &buffer_data_desc, &buffer );

    if (FAILED(hr)) {
        XV_LOG_ERROR("Failed to create buffer. HRESULT: {}", static_cast<int>(hr));
    }
}