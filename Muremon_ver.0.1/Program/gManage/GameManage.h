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

#include "program/gManage/Window.h"
#include "program/gManage/SceneManage.h"
#include "Library/DirectFont.h"
#include "LIbrary/DirectSound.h"
#include "LIbrary/Vertex.h"

#include "program/Scene/Logo.h"
#include "program/Scene/Title.h"
#include "program/Scene/Tutorial.h"
#include "program/Scene/GameRefresh.h"
#include "program/Scene/GameNormal.h"
#include "program/Scene/Ranking.h"

//#include "..\\GameScene.h"
//#include "..\\TitleScene.h"
//#include "..\\Fps.h"
//#include "..\\MapRead.h"

class C_GameMain
{
private:
	C_Window		*wind;	//ウィンドウクラスへのポインタ
	//C_DInput		*input;	//インプットクラスへのポインタ
	C_DGraphics		*gra;	//グラフィッククラスへのポインタ
	C_DSound		*sou;	//サウンドクラスへのポインタ
    C_DFont			*font;  //フォントクラスへのポインタ
	C_SceneManage	*scene;	//シーンクラスへのポインタ

	DWORD background;

	int score;
	//CFps		*fps;
	//MapRead		*mapread;
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