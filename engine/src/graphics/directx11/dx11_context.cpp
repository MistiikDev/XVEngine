#include <graphics/directx11/dx11_context.h>

HWND DX11Context::GetActiveWindowHandle() {
    SDL_Window* win = Window::GetSDLWindow();
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(win, &wmInfo);

    this->m_SDL_HWND = wmInfo.info.win.window;

    return this->m_SDL_HWND;
}

void DX11Context::CreateSwapChain( int screen_w, int screen_h ) {

    DXGI_SWAP_CHAIN_DESC scd    = {0};
    scd.BufferCount             = 1;
    scd.BufferDesc.Format       = DXGI_FORMAT_R8G8B8A8_UNORM;               // Buffer will hold RBGA default 8 bytes values (vector3s)
    scd.BufferDesc.Width        = screen_w;
    scd.BufferDesc.Height       = screen_h;
    scd.BufferUsage             = DXGI_USAGE_RENDER_TARGET_OUTPUT;          // this buffer will be the rendering target
    
    scd.OutputWindow            = this->m_SDL_HWND;
    scd.SampleDesc.Count        = 1;                                        // TODO: Check wtf this is later (AA)?
    scd.Windowed                = TRUE;
    scd.SwapEffect              = DXGI_SWAP_EFFECT_DISCARD;                 // previous buffer is cleared after swap

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
    this->CreateViewport( screen_w, screen_h );

    this->BindRenderTargets();
}

void DX11Context::PrepareRender() {
    const float clearColor[4] = { 0.52f, 0.80f, 0.92f, 1.0f };
    
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

}

void DX11Context::SwapBuffers() {
    m_swapChain->Present(1, 0);
}

void DX11Context::Destroy() {

}