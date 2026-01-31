#ifndef DXSHADER_H
#define DXSHADER_H

#include <d3dcompiler.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <unordered_map>

#include <platform/window.h>
#include <graphics/api/graphic_context.h>

struct CB_Data {
    glm::mat4 mvp;
};

class DXShader {
    public: 
        DXShader( Microsoft::WRL::ComPtr<ID3D11Device>* device, Microsoft::WRL::ComPtr<ID3D11DeviceContext>* context ): m_device(device), m_context(context) {} ;

        void CreateConstantBuffers( );
        void CompileShaders( const wchar_t* hlsl_shader_source );
        void PassMat4( glm::mat4 data );

        Microsoft::WRL::ComPtr<ID3DBlob>& GetVSShaderBuffer() { return mVS_shader_buffer; }
    private:
        Microsoft::WRL::ComPtr<ID3D11Buffer> mShader_ctx_buffer;
        Microsoft::WRL::ComPtr<ID3DBlob> mVS_shader_buffer;
        Microsoft::WRL::ComPtr<ID3DBlob> mPS_shader_buffer;

        Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS_shader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS_shader;
        
        // Active DX11 Context
        Microsoft::WRL::ComPtr<ID3D11Device>* m_device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>* m_context;
};

#endif