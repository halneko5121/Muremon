//---------------------------------------------
//
//      エンディング
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"

enum TEXTURE_DATA_ENDING
{
	T_ENDING,
};

enum RECT_DATA_ENDING
{
	R_ENDING,
};

class C_Ending:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;

	bool scene_change;	//シーンが変わる時を知らせる
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev, C_DFont* apFont, C_DSound* apSound, int score) override;
	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();
	C_Ending(void);
	~C_Ending(void);
};
