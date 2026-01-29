#include <graphics/api/graphic_context.h>

Scene* GraphicContext::s_activeScene = nullptr;

void GraphicContext::Init( int screen_x, int screen_y, int screen_w, int screen_h ) {};
void GraphicContext::Destroy() {};

void GraphicContext::PassBatch( Scene& scene ) {};
void GraphicContext::RenderActive( ) {};

void GraphicContext::PrepareRender() {};
void GraphicContext::SwapBuffers() {};