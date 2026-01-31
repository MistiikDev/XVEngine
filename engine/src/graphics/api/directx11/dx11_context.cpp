#include <graphics/api/directx11/dx11_context.h>

DX11Context::DX11Context() {
    
}

HWND DX11Context::GetActiveWindowHandle() {
    SDL_Window* win = Window::GetSDLWindow();
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(win, &wmInfo);

    this->m_SDL_HWND = wmInfo.info.win.window;

    return this->m_SDL_HWND;
}

void DX11Context::CreateSwapChain( int screen_w, int screen_h ) {
    DXGI_SWAP_CHAIN_DESC scd                = {0};
    scd.BufferCount                         = 1;
    scd.BufferDesc.Format                   = DXGI_FORMAT_R8G8B8A8_UNORM;               // Buffer will hold RBGA default 8 bytes values (vector3s)
    scd.BufferDesc.Width                    = screen_w;
    scd.BufferDesc.Height                   = screen_h;
    scd.BufferDesc.RefreshRate.Numerator    = 144;
    scd.BufferDesc.RefreshRate.Denominator  = 1;
    scd.BufferUsage                         = DXGI_USAGE_RENDER_TARGET_OUTPUT;          // this buffer will be the rendering target
    
    scd.OutputWindow                        = this->m_SDL_HWND;
    scd.SampleDesc.Count                    = 1;                                        // TODO: Check wtf this is later (AA)?
    scd.Windowed                            = TRUE;
    scd.SwapEffect                          = DXGI_SWAP_EFFECT_DISCARD;                 // previous buffer is cleared after swap

    // flags
    UINT flags = D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 }; // force strict at dx11

    D3D11CreateDeviceAndSwapChain(
        nullptr,                            // default adapter for gpu
        D3D_DRIVER_TYPE_HARDWARE,           // TODO: Currently set as GPU rendering, can be set by user later if needed
        nullptr,                            
        flags,
        featureLevels,
        1,
        D3D11_SDK_VERSION,
        &scd,
        &m_swapChain,
        &m_device,
        nullptr,
        &m_context
    );
}


void DX11Context::CreateRenderTarget() {
    ID3D11Texture2D* back_buffer;
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(&back_buffer));
    m_device->CreateRenderTargetView(back_buffer, nullptr, &m_renderTargetView);

    back_buffer->Release();
}

void DX11Context::CreateDepthStencil( int screen_w, int screen_h ) {
    // 2D Texture Where depth is drawn
    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width              = screen_w;
    depthDesc.Height             = screen_h;
    depthDesc.MipLevels          = 1;
    depthDesc.ArraySize          = 1;
    depthDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT; 
    depthDesc.SampleDesc.Count   = 1;
    depthDesc.Usage              = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;

    HRESULT hr = m_device->CreateTexture2D(
        &depthDesc,
        nullptr,
        m_depthBuffer.GetAddressOf()
    );

    if (FAILED(hr)) {
        // TODO: Handle error on texture creation failure
        return;
    }

    hr = m_device->CreateDepthStencilView(
        m_depthBuffer.Get(),
        nullptr,
        m_depthStencilView.GetAddressOf()
    );

    if (FAILED(hr)) {
        // TODO: Handle error on depth stencil view creation failure
        return;
    }
}

void DX11Context::CreateRasterizer() {
    // how to draw the shape
    D3D11_RASTERIZER_DESC rasterDesc = {};
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.CullMode = D3D11_CULL_NONE; // Disable culling
    rasterDesc.FrontCounterClockwise = FALSE;

    m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
    m_context->RSSetState(m_rasterState.Get());
}

void DX11Context::CreateViewport( int screen_w, int screen_h ) {
    D3D11_VIEWPORT vp = {};
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width    = screen_w;
    vp.Height   = screen_h;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;

    m_context->RSSetViewports(1, &vp);
}

void DX11Context::BindRenderTargets() {
    // Merge Render View and Depth View
    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
}

void DX11Context::Init( int screen_x, int screen_y, int screen_w, int screen_h ) {
    // Get HWND First
    XV_LOG_DEBUG("{} : {}", "DirectX11", "INIT");

    this->GetActiveWindowHandle();
    this->CreateSwapChain( screen_w, screen_h );
    this->CreateRenderTarget();
    this->CreateDepthStencil( screen_w, screen_h );
    this->CreateRasterizer();
    this->CreateViewport( screen_w, screen_h );

    this->BindRenderTargets();

    
    this->m_activeShader = new DXShader( &m_device, &m_context );
    this->m_activeShader->CreateConstantBuffers();

    this->mVertexLayout = new DX11Layout();
    this->mVertexLayout->LinkAttribute( "POSITION", DXGI_FORMAT_R32G32B32_FLOAT, 0 );
    this->mVertexLayout->LinkAttribute( "COLOR", DXGI_FORMAT_R32G32B32_FLOAT, offsetof(Vertex, color) );
    this->mVertexLayout->CompileAttributeLayer(this->m_device, this->m_context, m_activeShader->GetVSShaderBuffer() );

    this->m_activeShader->CompileShaders(L"engine/src/graphics/api/directx11/shaders/default.hlsl");
}

void DX11Context::PassBatch ( Scene& scene ) {
    this->s_activeScene = &scene;
    UINT STRIDE = sizeof( Vertex );

    for (Mesh* mesh : this->s_activeScene->meshes) {
        // create data buffers for each of the meshs' verticies
        DX11Buf* buffer = new DX11Buf();
        DX11Buf* indexBuffer = new DX11Buf();

        buffer->Init( D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0 ); // Vertex Buffer
        buffer->UploadData( mesh->verticies.data(), mesh->verticies.size(), sizeof( Vertex ) );
        buffer->CreateBuffer( m_device );

        indexBuffer->Init( D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0);
        indexBuffer->UploadData( mesh->indicies.data(), mesh->indicies.size(), sizeof( uint32_t ) );
        indexBuffer->CreateBuffer( m_device );

        this->mVertexBuffers[mesh->ID] = buffer;
        this->mIndexBuffers[mesh->ID] = indexBuffer;
    }
}

void DX11Context::PrepareRender() {
    const float clearColor[4] = { 0.52f, 0.80f, 0.92f, 1.0f };
    
    // clear front buffer to prepare swap
    m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor );
    m_context->ClearDepthStencilView(
        m_depthStencilView.Get(), 
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
        1.0f,
        0
    );

    this->BindRenderTargets();
}

void DX11Context::RenderActive() {
    // TRIANGLELIST works without indicies but is less efficient
    m_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
    
    UINT STRIDE = sizeof( Vertex );
    UINT OFFSET = 0;

    for (const Mesh* mesh : this->s_activeScene->meshes) {
        if (this->mVertexBuffers.find(mesh->ID) == this->mVertexBuffers.end()) {
            XV_LOG_ERROR("{}", " Mesh not found inside buffer list");
        };

        DX11Buf* vertexbuffer = this->mVertexBuffers[mesh->ID];
        DX11Buf* indexBuffer = this->mIndexBuffers[mesh->ID];

        this->m_activeShader->PassMat4( mesh->transform );

        // activate buffer then draw from active buffer to back buffer
        m_context->IASetVertexBuffers( 0, 1, (vertexbuffer->GetRawBufferPtr().GetAddressOf()), &STRIDE, &OFFSET);
        m_context->IASetIndexBuffer( indexBuffer->GetRawBufferPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
        m_context->DrawIndexed(static_cast<UINT>(mesh->indicies.size()), 0, 0);
    }
}

void DX11Context::SwapBuffers() {
    m_swapChain->Present(1, 0);
}

void DX11Context::Destroy() {

}