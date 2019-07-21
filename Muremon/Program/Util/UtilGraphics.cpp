/******************************************************************
 *	@file	UtilGraphics.h
 *	@brief	グラフィックス関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilGraphics.h"

#include "Library/Graphics/DirectGraphics.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

/**
 * @biref グラフィックスデバイスを取得する
 */
LPDIRECT3DDEVICE9
UtilGraphics::getGraphicsDevice()
{
	return getDirectGraphics()->getDevice();
}

/**
 * @biref バーテックス/テクスチャ情報のロード
 */
void
UtilGraphics::loadVertexAndTexture(Vertex* vertex, Texture* texture, const char* file_name)
{
	std::string str_texture_path("Data\\TextureData\\");
	std::string str_vertex_path("Data\\RectData\\");
	std::string file_ext(".txt");

	// バーテックス情報のロード
	str_vertex_path.append(file_name);
	str_vertex_path.append(file_ext);
	vertex->load(str_vertex_path.c_str());

	// テクスチャ情報のロード
	str_texture_path.append(file_name);
	str_texture_path.append(file_ext);
	texture->load(str_texture_path.c_str(), getGraphicsDevice());
}

/**
 * @biref テクスチャの設定
 */
void
UtilGraphics::setTexture(Vertex* vertex, const Texture& texture, int texture_id)
{
	APP_POINTER_ASSERT(vertex);
	vertex->setTextureData(texture.getTextureData(texture_id), getGraphicsDevice());
}

/**
 * @biref バーテックスカラーの設定
 */
void
UtilGraphics::setVerTexColor(Vertex* vertex, int alpha, int red, int green, int blue)
{
	APP_POINTER_ASSERT(vertex);
	vertex->setColor(alpha, red, green, blue);
}

/**
 * @biref バーテックスカラーの設定
 */
void
UtilGraphics::setVertexAngle(Vertex* vertex, float degree)
{
	APP_POINTER_ASSERT(vertex);
	vertex->setAngle(degree);
}

/**
 * @biref 描画（原点：下）
 */
void
UtilGraphics::drawCB(Vertex* vertex, const Vector2f& pos, int rect_num)
{
	APP_POINTER_ASSERT(vertex);
	vertex->drawCB(pos, rect_num);
}

/**
 * @biref 描画（原点：中心）
 */
void
UtilGraphics::drawF(Vertex* vertex, const Vector2f& pos, int rect_num)
{
	APP_POINTER_ASSERT(vertex);
	vertex->drawF(pos, rect_num);
}