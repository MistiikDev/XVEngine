#include <graphics/api/directx11/buffers/DXShader.h>

void DXShader::CreateConstantBuffers() {
    // Create "unforms" vertex constant buffers
    D3D11_BUFFER_DESC CB_desc = {};

    CB_desc.ByteWidth = sizeof( CB_Data );
    CB_desc.Usage = D3D11_USAGE_DYNAMIC;
    CB_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    CB_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = m_device->Get()->CreateBuffer(&CB_desc, nullptr, &this->mShader_ctx_buffer);

    if (FAILED(hr)) {
        XV_LOG_ERROR("Failed to create CST buffer. HRESULT: {}", static_cast<int>(hr));
    }
}

void DXShader::PassMat4( glm::mat4 mat ) {
    D3D11_MAPPED_SUBRESOURCE map_out;
    CB_Data shader_data;

    shader_data.mvp = glm::transpose(mat); // dx11 is row major, not glm
        
    // MOVE DATA FROM CPU TO GPU
    m_context->Get()->Map(this->mShader_ctx_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map_out );

    memcpy(map_out.pData, &shader_data, sizeof(shader_data));

    m_context->Get()->Unmap(this->mShader_ctx_buffer.Get(), 0);
    m_context->Get()->VSSetConstantBuffers(0, 1, this->mShader_ctx_buffer.GetAddressOf());
}

void DXShader::CompileShaders( const wchar_t* hlsl_shader_source ) {
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
    HRESULT hr;

    hr = D3DCompileFromFile(hlsl_shader_source, nullptr, nullptr, "VS", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_ENABLE_STRICTNESS, 0, &this->mVS_shader_buffer, &errorBlob);
    
    if (FAILED(hr)) {
        if (errorBlob) {
            XV_LOG_ERROR( "DX11 VS compile error:\n{}", (char*)errorBlob->GetBufferPointer() );
        } else {
            XV_LOG_ERROR("DX11 VS compile error: unknown");
        }
    }

    hr = D3DCompileFromFile(hlsl_shader_source, nullptr, nullptr, "PS", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_ENABLE_STRICTNESS, 0, &this->mPS_shader_buffer, nullptr );
    
    if (FAILED(hr)) {
        if (errorBlob) {
            XV_LOG_ERROR( "DX11 PS compile error:\n{}", (char*)errorBlob->GetBufferPointer() );
        } else {
            XV_LOG_ERROR("DX11 PS compile error: unknown");
        }
    }

    hr = m_device->Get()->CreateVertexShader(this->mVS_shader_buffer->GetBufferPointer(), this->mVS_shader_buffer->GetBufferSize(), NULL, &this->mVS_shader);

    if (FAILED(hr)) {
        XV_LOG_ERROR("{} : {}", "DirectX11 Shader Error", "Failed to Create VS on DEFAULT.hlsl");
    }

    hr = m_device->Get()->CreatePixelShader(this->mPS_shader_buffer->GetBufferPointer(), mPS_shader_buffer->GetBufferSize(), NULL, &this->mPS_shader);

    if (FAILED(hr)) {
        XV_LOG_ERROR("{} : {}", "DirectX11 Shader Error", "Failed to Create PS on DEFAULT.hlsl");
    }

    m_context->Get()->VSSetShader(this->mVS_shader.Get(), 0, 0);
    m_context->Get()->PSSetShader(this->mPS_shader.Get(), 0, 0);
}