///////////////////////////////////////////////////////
// Beehive: A complete SEGA Mega Drive content tool
//
// (c) 2016 Matt Phillips, Big Evil Corporation
///////////////////////////////////////////////////////

#pragma once

#include "UIBase.h"
#include "RenderResources.h"

#include <ion/renderer/Renderer.h>
#include <ion/renderer/Viewport.h>
#include <ion/renderer/Camera.h>
#include <ion/renderer/Primitive.h>
#include <ion/renderer/Material.h>

#include <wx/glcanvas.h>

class SpriteCanvas : public wxGLCanvas
{
public:
	SpriteCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxFrameNameStr);
	virtual ~SpriteCanvas();

	void SetupRendering(ion::render::Renderer* renderer, wxGLContext* glContext, RenderResources* renderResources);
	void SetSpriteSheetDimentionsCells(const ion::Vector2i& spriteSheetDimentionsCells);
	void SetPreview(ion::render::Texture* previewTexture);

	//Refresh panel
	virtual void Refresh(bool eraseBackground = true, const wxRect *rect = NULL);
	virtual void OnResize(wxSizeEvent& event);

protected:
	//Render callback
	virtual void OnRender(ion::render::Renderer& renderer, const ion::Matrix4& cameraInverseMtx, const ion::Matrix4& projectionMtx, float& z, float zOffset);

private:
	//Event handlers
	void EventHandlerPaint(wxPaintEvent& event);
	void EventHandlerResize(wxSizeEvent& event);

	//Primitive creation
	void CreateGrid(int width, int height, int cellsX, int cellsY);

	//Rendering
	void RenderSpriteSheet(ion::render::Renderer& renderer, const ion::Matrix4& cameraInverseMtx, const ion::Matrix4& projectionMtx, float z);
	void RenderPreview(ion::render::Renderer& renderer, const ion::Matrix4& cameraInverseMtx, const ion::Matrix4& projectionMtx, float z);
	void RenderGrid(ion::render::Renderer& renderer, const ion::Matrix4& cameraInverseMtx, const ion::Matrix4& projectionMtx, float z);

	//Rendering resources
	ion::render::Renderer* m_renderer;
	ion::render::Camera m_camera;
	ion::render::Viewport m_viewport;
	RenderResources* m_renderResources;

	//Rendering primitives
	ion::render::Grid* m_gridPrimitive;

	//Preview texture
	ion::render::Texture* m_previewTexture;

	//Panel size (pixels)
	ion::Vector2i m_panelSize;

	//Prev panel size (for filtering resize events)
	ion::Vector2i m_prevPanelSize;

	//Sprite sheet cells
	ion::Vector2i m_spriteSheetDimentionsCells;
};
