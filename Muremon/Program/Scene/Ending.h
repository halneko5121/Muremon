//---------------------------------------------
//
//      エンディング
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

enum TEXTURE_DATA_ENDING
{
	T_ENDING,
};

enum RECT_DATA_ENDING
{
	R_ENDING,
};

class C_Ending:public C_SceneBase
{
public:
	void InitScene() override;
	bool ControlScene() override;
	void DrawScene() override;
	int EndScene() override;

	C_Ending(void);
	~C_Ending(void);
};
