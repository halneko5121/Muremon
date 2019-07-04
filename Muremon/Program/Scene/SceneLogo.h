//---------------------------------------------
//
//      ロゴ
//      作成開始日:	3月17日
//			更新日:	3月20日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

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

class SceneLogo : public SceneBase
{
private:
	int time_count;	//ロゴのタイムカウント

	int alpha;	//アルファ値

public:
	void Init() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void FadeControl();	//フェード処理

	SceneLogo();
	~SceneLogo();
};
