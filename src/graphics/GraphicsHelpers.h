#ifndef GRAPHICS_GRAPHICSHELPERS_H
#define GRAPHICS_GRAPHICSHELPERS_H

#include "shared/studiomodel/CStudioModel.h"
#include "game/entity/CStudioModelEntity.h"

#include "graphics/Constants.h"

#include "graphics/OpenGL.h"

class Color;

namespace graphics
{
namespace helpers
{
/**
*	Converts image dimensions to power of 2.
*	Returns true on success, false otherwise.
*/
bool CalculateImageDimensions( const int iWidth, const int iHeight, int& iOutWidth, int& iOutHeight );

/**
*	Converts an 8 bit image to a 24 bit RGB image.
*/
void Convert8to24Bit( const int iWidth, const int iHeight, const byte* const pData, const byte* const pPalette, byte* const pOutData );

/**
*	Flips an image vertically. This allows conversion between OpenGL and image formats. The image is flipped in place.
*	@param iWidth Image width, in pixels.
*	@param iHeight Image height, in pixels.
*	@param pData Pixel data, in RGB 24 bit.
*/
void FlipImageVertically( const int iWidth, const int iHeight, byte* const pData );

/*
*	Sets up OpenGL for the specified render mode.
*	@param renderMode Render mode to set up. Must be valid.
*	@param bBackfaceCulling Whether backface culling should be enabled or not.
*/
void SetupRenderMode( RenderMode renderMode, const bool bBackfaceCulling );

/**
*	Draws a texture onto the screen. Optionally draws a UV map, either on a black background, or on top of the texture.
*	@param iWidth			Width of the viewport
*	@param iHeight			Height of the viewport
*	@param pEntity			Entity whose model's texture is being drawn
*	@param iTexture			Index of the texture to draw
*	@param flTextureScale	Zoom level
*	@param bShowUVMap		If true, draws the UV map
*	@param bOverlayUVMap	If true, and bShowUVMap is true, overlays the UV map on top of the texture
*	@param bAntiAliasLines	If true, anti aliases UV map lines
*	@param pUVMesh			If specified, is the mesh to use to draw the UV map. If null, all meshes that use the texture are drawn.
*/
void DrawTexture( const int iWidth, const int iHeight,
				  CStudioModelEntity* pEntity,
				  const int iTexture, const float flTextureScale, const bool bShowUVMap, const bool bOverlayUVMap, const bool bAntiAliasLines,
				  const mstudiomesh_t* const pUVMesh );

/**
*	Draws a background texture, fitted to the viewport.
*	@param backgroundTexture OpenGL texture id that represents the background texture
*/
void DrawBackground( GLuint backgroundTexture );

/**
*	Sets the projection matrix to the default perspective settings.
*	@param flFOV Field Of View.
*	@param iWidth Width of the viewport
*	@param iHeight Height of the viewport
*/
void SetProjection( const float flFOV, const int iWidth, const int iHeight );

/**
*	Draws a floor quad.
*	@param flSideLength Length of one side of the floor
*/
void DrawFloorQuad( float flSideLength );

/**
*	Draws a floor, optionally with a texture.
*	@param flSideLength		Length of one side of the floor
*	@param groundTexture	OpenGL texture id of the texture to draw as the floor, or GL_INVALID_TEXTURE_ID to draw a solid color instead
*	@param groundColor		Color of the ground if no texture is specified
*	@param bMirror			If true, draws a solid underside
*/
void DrawFloor( float flSideLength, GLuint groundTexture, const Color& groundColor, const bool bMirror );

/**
*	Draws a wireframe overlay over a model
*	@param pEntity Entity to draw
*/
unsigned int DrawWireframeOverlay( CStudioModelEntity* pEntity );

/**
*	Draws a mirrored model.
*	@param pEntity				Entity to draw
*	@param renderMode			Render mode to use
*	@param bWireframeOverlay	Whether to render a wireframe overlay on top of the model
*	@param flSideLength			Length of one side of the floor
*	@param bBackfaceCulling		Whether to perform backface culling or not
*/
unsigned int DrawMirroredModel( CStudioModelEntity* pEntity, const RenderMode renderMode, const bool bWireframeOverlay, const float flSideLength, const bool bBackfaceCulling );

/**
*	Draws a box using an array of 8 vectors as corner points.
*/
void DrawBox( const glm::vec3* const v );
}
}

#endif //GRAPHICS_GRAPHICSHELPERS_H