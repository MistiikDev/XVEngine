#ifndef DX11_CONTEXT
#define DX11_CONTEXT

#include <d3d11.h>
#include <wrl/client.h>

#include <graphics/api/graphic_context.h>
#include <platform/window.h>
#include <sdl2/SDL_syswm.h>

class DX11Context : public GraphicContext {
    public:
        DX11Context();
        
        void Init( int screen_x, int screen_y, int screen_w, int screen_h ) override;
        void RenderActive( ) override;
        void Destroy() override;

        void PrepareRender() override;
        void SwapBuffers() override;

    private:
        HWND m_SDL_HWND;
        HWND GetActiveWindowHandle();

        void CreateSwapChain(  int screen_w, int screen_h  );
        void CreateRenderTarget();
        void CreateDepthStencil( int screen_w, int screen_h );
        void CreateViewport( int screen_w, int screen_h );

        void BindRenderTargets();

        Microsoft::WRL::ComPtr<ID3D11Device> m_device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;
        Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;

        Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthBuffer;

        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
};

#endif