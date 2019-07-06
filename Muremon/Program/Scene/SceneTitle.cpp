//---------------------------------------------
//
//      �^�C�g��
//			�쐬��:	����
//
//---------------------------------------------
#include "SceneTitle.h"

#include "Library/Sound/DirectSound.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilInput.h"

#define MENU_MAX		(3)		
#define MENU_MAX_GAME	(2)

namespace
{
	// �\�����W
	const float cDispTitleBgX = 400.f;
	const float cDispTitleBgY = 300.f;
	const float cDispZPushX = 400.f;
	const float cDispZPushY = 450.f;
	const float cDispStartX = 400.f;
	const float cDispStartY = 340.f;
	const float cDispRankingX = 400.f;
	const float cDispRankingY = 420.f;
	const float cDispGameEndX = 400.f;
	const float cDispGameEndY = 500.f;
	const float cDispGameNormalX = 400.f;
	const float cDispGameNormalY = 380.f;
	const float cDispGameRefreshX = 400.f;
	const float cDispGameRefreshY = 460.f;
	const float cDispGameTitleX = 400.f;
	const float cDispGameTitleY = 130.f;
	const float cDispCursorX = 260.f;
	const float cDispCursorY = 340.f;
	const float cDispCursor2X = 280.f;
	const float cDispCursor2Y = 380.f;
	const float cDispCursorYRemove = 80.f;

	enum TEXTURE_DATA_TITLE	//�G
	{
		T_TITLE_BG,		//�^�C�g���w�i
		T_FONT,			//�t�H���g
	};

	enum RECT_DATA_TITLE	//��`
	{
		R_TITLE_BG,		//�^�C�g���w�i
		R_ZPUSH,		//�y�L�[�������Ă�
		R_START,		//�����[��
		R_RANKING,		//�����L���O
		R_END,			//�����
		R_NORMAL,		//�́[�܂���[��
		R_REFRESH,		//����������[��
		R_TUTORIAL_T,	//�������
		R_TITLE,		//�^�C�g��
		R_CURSOR1,		//�J�[�\��1
		R_CURSOR2,		//�J�[�\��2
	};

	enum TITLE_DRAW_SCENE
	{
		DRAW_Z_PUSH,
		DRAW_MENU,
		DRAW_GAME_MENU,
	};

	enum MENU_SCENE
	{
		G_START,		//�X�^�[�g
		G_RANKING,		//�����L���O
		G_END,			//�I��
	};

	enum GAME_MODE
	{
		G_CLEARLY,	//�������胂�[�h
		G_NORMAL,	//�m�[�}�����[�h
		G_TUTORIAL
	};
}

SceneTitle::SceneTitle()
	: cursor_posi(cDispCursorX, cDispCursorY)
	, title_posi(cDispGameTitleX, -100.f)
	, time_count(0)
	, alpha_z(0)
	, draw_scene_change(DRAW_Z_PUSH)
	, flag_scene_change(0)
	, anime_cursor(0)
	, flag_z(false)
	, flag_draw(0)
	, cnt_move(0)
{
	mIsSceneChange = true;
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::ImpleInit()
{
	mTexture->LoadTextureData("Data\\TextureData\\title.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->LoadRect("Data\\RectData\\title.txt");

	GetDirectSound()->SoundPlayLoop(S_BGM_TITLE);
}

bool SceneTitle::Update()
{
	if (!flag_z) 
	{
		alpha_z += 5;
		if (alpha_z == 200)
		{
			flag_z = true;
		}
	}
	else 
	{
		alpha_z -= 5;
		if (alpha_z == 0)
		{
			flag_z = false;
		}
	}

	PosiDrawControl();
	KeyControl();

	time_count++;

	if(time_count % 16 == 0)
	{
		anime_cursor++;
	}

	return mIsSceneChange;
}

void SceneTitle::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_TITLE_BG), mDevice);
	mVertex->DrawF(cDispTitleBgX, cDispTitleBgY, R_TITLE_BG);

	mVertex->SetTextureData(mTexture->GetTextureData(T_FONT), mDevice);
	mVertex->DrawF(title_posi.x,title_posi.y,R_TITLE);
	
	if(draw_scene_change == DRAW_Z_PUSH)
	{
		mVertex->SetColor(alpha_z, 255, 255, 255);
		mVertex->DrawF(cDispZPushX, cDispZPushY, R_ZPUSH);
	}
	else if(draw_scene_change == DRAW_MENU)
	{
		mVertex->DrawF(cDispStartX, cDispStartY, R_START);
		mVertex->DrawF(cDispRankingX, cDispRankingY, R_RANKING);
		mVertex->DrawF(cDispGameEndX,cDispGameEndY, R_END);
	}
	else
	{
		//���[�h�I��(��������E�́[�܂�E�������)
		mVertex->DrawF(cDispStartX, cDispStartY, R_REFRESH);
		mVertex->DrawF(cDispRankingX, cDispRankingY, R_NORMAL);
		mVertex->DrawF(cDispGameEndX,cDispGameEndY, R_TUTORIAL_T);
	}
	
	//�J�[�\��
	if(draw_scene_change != DRAW_Z_PUSH)
	{
		mVertex->DrawF(cursor_posi.x, cursor_posi.y, (R_CURSOR1 + (anime_cursor % 2)));
		mVertex->DrawF(cursor_posi.x + cDispCursor2X, cursor_posi.y, (R_CURSOR1 + (anime_cursor % 2)));
	}
}

int SceneTitle::End()
{
	ChangeScene(flag_scene_change);
	GetDirectSound()->SoundPouse(S_BGM_TITLE);

	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

void SceneTitle::PosiDrawControl()
{
	//�J�[�\���ʒu���v�Z
	cursor_posi.y = cDispCursorY + cDispCursorYRemove * flag_select;

	//�^�C�g���ʒu���v�Z
	if(flag_draw == 7) { return ; }
	if(flag_draw%2 == 0)
	{
		if(title_posi.y < cDispGameTitleY)
		{
			title_posi.y += 5.f;
		}
		else
		{
			flag_draw++;
		}
	}
	else if(flag_draw%2 == 1)
	{
		title_posi.y -= 5.f;
		if(title_posi.y == 70.f + 20.f * cnt_move)
		{
			flag_draw++;
			cnt_move++;
		}
	}
}

void SceneTitle::KeyControl()
{
	// �߂�����㉺������Ă���a���ɂȂ��悤��
	if(GetDirectSound()->IsPlaySound(S_SE_CURSOR_MOVE))
	{
		if (UtilInput::IsKeyDown(DIK_UP) ||
			UtilInput::IsKeyDown(DIK_DOWN))
		{
			GetDirectSound()->SoundStop(S_SE_CURSOR_MOVE);
		}
	}

	if(UtilInput::IsKeyPushed(DIK_Z))
	{
		GetDirectSound()->SoundPlayOnce(S_SE_OK);
		// PUSH_Z���\������Ă��鎞�ɂy�L�[�������ꂽ��
		if(draw_scene_change == DRAW_Z_PUSH)
		{
			draw_scene_change = DRAW_MENU;
		}
		// ���j���[���\������Ă��鎞�ɂy�L�[�������ꂽ��
		else if(draw_scene_change == DRAW_MENU)
		{
			if(flag_select == G_START)
			{
				draw_scene_change = DRAW_GAME_MENU;
				flag_select = 0;
			}
			else if(flag_select == G_RANKING)
			{
				mIsSceneChange = false;
				flag_scene_change = cSceneName_Ranking;
			}
			else
			{
				PostQuitMessage(0);
			}
		}
		//�Q�[�����j���[���\������Ă��鎞�ɂy�L�[�������ꂽ��
		else
		{
			if(flag_select == G_CLEARLY)
			{
				//�������胂�[�h���J�n������悤�Ƀt���O��ς���
				flag_scene_change = cSceneName_GameRefresh;
			}
			else if(flag_select == G_NORMAL)
			{
				//�́[�܂郂�[�h���J�n������悤�Ƀt���O��ς���
				flag_scene_change = cSceneName_GameNormal;
			}
			else
			{
				flag_scene_change = cSceneName_Tutorial;
			}
			mIsSceneChange = false;
		}
		time_count = 0;
	}

	// ���L�[�������ꂽ��
	if (UtilInput::IsKeyPushed(DIK_UP))
	{
		if (draw_scene_change != DRAW_Z_PUSH)
		{
			GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		}
		flag_select--;

		if(draw_scene_change == DRAW_MENU)
		{
			if(flag_select < G_START)
			{
				flag_select = G_END;
			}
		}
		else if(draw_scene_change == DRAW_GAME_MENU)
		{
			if(flag_select < G_CLEARLY)
			{
				flag_select = G_TUTORIAL;
			}
		}
		else
		{
			flag_select++;
		}
		time_count = 0;
	}

	// ���L�[�������ꂽ��
	if (UtilInput::IsKeyPushed(DIK_DOWN))
	{
		if (draw_scene_change != DRAW_Z_PUSH)
		{
			GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		}
		flag_select++;

		if(draw_scene_change == DRAW_MENU)
		{
			if(flag_select > G_END)
			{
				flag_select = G_START;
			}
		}
		else if(draw_scene_change == DRAW_GAME_MENU)
		{
			if(flag_select > G_TUTORIAL)
			{
				flag_select = G_CLEARLY;
			}
		}
		else{
			flag_select--;
		}
		time_count = 0;
	}

	if (UtilInput::IsKeyPushed(DIK_X))
	{
		GetDirectSound()->SoundPlayOnce(S_CANCEL);

		if(draw_scene_change == DRAW_MENU)
		{
			draw_scene_change = DRAW_Z_PUSH;
			flag_select = G_START;
		}
		else if(draw_scene_change == DRAW_GAME_MENU)
		{
			draw_scene_change = DRAW_MENU;
			flag_select = G_CLEARLY;
		}
		time_count = 0;
	}
}
