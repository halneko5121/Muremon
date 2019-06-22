//---------------------------------------------
//
//      ロゴ
//      作成開始日:	3月17日
//			更新日:	3月20日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"

#define MAXALPHATIME		(51)
#define ALPHADWINDLITIME	(129)

enum TEXTURE_DATA_LOGO
{
	T_LOGO,
};

enum RECT_DATA_LOGO
{
	R_LOGO,
};

class C_Logo:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;

	int time_count;	//ロゴのタイムカウント

	int alpha;	//アルファ値

	bool scene_change;	//シーンが変わる時を知らせる

public:
	void InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score);

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void FadeControl();	//フェード処理

	C_Logo(void);
	~C_Logo(void);
};
