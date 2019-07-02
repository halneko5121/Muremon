//---------------------------------------------
//
//      ゲーム全体の管理を行う
//      作成開始日:	3月17日
//			更新日:	3月17日
//			作成者:	平野
//
//---------------------------------------------

#ifndef _GAMEMANAGE_H_
#define _GAMEMANAGE_H_

#include "Library/Window/Window.h"
#include "Program/Scene/SceneBase.h"
#include "Library/Font/DirectFont.h"
#include "Library/Graphics/Vertex.h"

#include "Program/Scene/Logo.h"
#include "Program/Scene/Title.h"
#include "Program/Scene/Tutorial.h"
#include "Program/Scene/GameRefresh.h"
#include "Program/Scene/GameNormal.h"
#include "Program/Scene/Ranking.h"

class C_GameMain
{
private:
	C_Window*		mWindow;	// ウィンドウクラスへのポインタ
	C_DGraphics*	mGraphics;	// グラフィッククラスへのポインタ
    C_DFont*		mFont;		// フォントクラスへのポインタ
	C_SceneBase*	mScene;		// シーンクラスへのポインタ
	DWORD			mBackground;
	int				mScore;

public:
    //////////////////////////////////////////////////////////
    //
    //      説明　：ゲームで使うメンバの初期化
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
    void InitGameMain(void);

	//////////////////////////////////////////////////////////
    //
    //      説明　：メイン関数
    //      引数  ：HINSTANCE   hInstance   インスタンスハンドル
    //              HINSTANCE   hPrevInst   実際のWinMainに渡す
    //              LPSTR       lpCmdLine   実際のWinMainに渡す
    //              int         nShowCmd    実際のWinMainに渡す
    //      戻り値：int         メッセージループを返す
    //
    //////////////////////////////////////////////////////////
	int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd);

	//////////////////////////////////////////////////////////
    //
    //      説明　：ゲーム内ループ関数
    //      引数  ：なし
    //      戻り値：int     メッセージ
    //
    //////////////////////////////////////////////////////////
	int MsgLoop(void);

    //////////////////////////////////////////////////////////
    //
    //      説明　：ゲームで使うメンバの開放処理
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
    void ReleaseGameMain(void);

    //////////////////////////////////////////////////////////
    //
    //      説明　：メイン部分のコントロールを行う
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
    void ControlGame(void);
};

#endif	//_GAMEMANAGE_H_