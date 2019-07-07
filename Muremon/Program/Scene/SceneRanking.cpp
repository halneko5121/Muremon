//---------------------------------------------
//
//      ランキング
//			作成者:	平野
//
//---------------------------------------------
#include "SceneRanking.h"
#include "Program/Util/UtilSound.h"
#include "Program/DefineGame.h"

FILE *fp;
struct RANK data[5];
struct RANK newdata;				//名前とスコアの初期化のため

SceneRanking::SceneRanking(void)
{
	mIsSceneChange = true;

	fade_flag=RANK_FADE_IN;

	alpha=0;

	font_alpha=0;

	alpha_count=0;

	time_count = 0;

	rank=-1;

	key_no = 0;

	flag = 0;
	in = 0;
	deray = 0;
	keep_key[3]=0;

	write_flag=false;
	
	//sum_score=50000000;

	add_score=0;

	key_state = 0;

	for(int j=0;j<5;j++){
		for(int i=0;i<3;i++){
			name_alpha[j][i]=255;
		}
	}

	name_blink=false;

	name_alpha_down=false;

	z_key_flag=false;

	z_alpha_up = false;

	z_alpha = 0;

	ranking_flag=false;
}

SceneRanking::~SceneRanking(void)
{
}

void
SceneRanking::ImpleInit()
{
}

void SceneRanking::InitScene(int score)
{
	add_score = score;

	mTexture->load("Data\\TextureData\\ranking.txt", mDevice);		//絵の読み込み
	mVertex->LoadRect("Data\\RectData\\ranking.txt");
	RankLoad();
	RankCheck();
}

bool SceneRanking::update()
{
	UtilSound::playLoop(S_BGM_TITLE);

	FadeControl();
	RankControl(rank);
	KeyControl();
	return mIsSceneChange;
}

void SceneRanking::RankControl(int rank)
{
	name_blink=true;
	name_alpha_down=true;
	for(int i = 'A'; i <= 'Z'; i++)
	{
		if(GetAsyncKeyState(i))
		{
			UtilSound::playOnce(S_SE_CURSOR_MOVE);
			key_no = i - 'A';
			keep_key[flag] = key_no;
			//newdata.name[flag] = key;
			data[rank].name[flag] = key_no;
			break;
		}
	}

	if(key_no != -1 && flag < 3)
	{
		in = 1;
	}

	if(in)
	{
		if(name_blink)
		{
			if(name_alpha_down)
			{
				name_alpha[rank][flag]-=5;
				if(name_alpha[rank][flag]==0) name_alpha_down = false;
			}else{
				name_alpha[rank][flag]+=5;
				if(name_alpha[rank][flag]=255) name_alpha_down = true;
			}
		}
		else name_alpha[5][3]=255;

		if(deray++ > 3)
		{
			if(GetAsyncKeyState(VK_RETURN))
			{
				UtilSound::playOnce(S_SE_OK);
				name_alpha[rank][flag]=255;
				flag++;
				deray = 0;
				in = 0;
				if(flag==3)
				{
					name_blink=false;
					write_flag=true;
					if(write_flag) RankWrite();
				}
			}
		}
	}
}

void SceneRanking::KeyControl()
{
	if(z_key_flag)
	{
		if(GetAsyncKeyState(VK_RETURN))
		{
			z_key_flag = false;
			fade_flag = RANK_FADE_OUT;
		}
		z_alpha_up=true;
		if(z_alpha_up)
		{
			z_alpha+=Z_KEY_ALPHA;
			if(z_alpha>=254) z_alpha_up=false;
		}else{
			z_alpha-=Z_KEY_ALPHA;
			if(z_alpha<=0) z_alpha_up=true;
		}
	}else{
		z_alpha_up =false;
		z_alpha=0;
	}

	//if(key_state == KEY_Z)
	//{
	//	z_key_flag = false;
	//	fade_flag = RANK_FADE_OUT;
	//}
}

void SceneRanking::Draw()
{
	RankBackGround();
	RankPlaceDraw();
	RankNameDraw();
	RankScoreDraw();
	ZKeyDraw();
}

int SceneRanking::End()
{
	ChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->AllReleaseRect();

	return 0;
}

void SceneRanking::RankBackGround()
{
	mVertex->SetTextureData(mTexture->getTextureData(T_RANKING_BG), mDevice);
	mVertex->SetColor(alpha,255,255,255);
	mVertex->DrawF(400.f,300.f,R_RANKING_BG);
}

void SceneRanking::RankPlaceDraw()
{
	for(int i=0;i<5;i++)
	{
			mVertex->SetTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
			mVertex->SetColor(alpha,255,255,255);
			mVertex->DrawF((float)PLACE_POSITION_X,(float)POSITION_Y + i * DISLOCATE_Y,R_FONT_1 + i);
			mVertex->DrawF((float)DOT_X,(float)POSITION_Y+i * DISLOCATE_Y,R_FONT_DOT);
	}
}

void SceneRanking::RankNameDraw()
{
	for(int j=0;j<5;j++)
	{
		for(int i=0;i<3;i++)
		{
			mVertex->SetTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
			if(fade_flag==RANK_USUALLY)	mVertex->SetColor(name_alpha[j][i],255,255,255);
			else mVertex->SetColor(alpha,255,255,255);
			mVertex->DrawF((float)NAME_POSITION_X+i*DISLOCATE_X,(float)POSITION_Y+j*DISLOCATE_Y,R_FONT_A + data[j].name[i]);
		}
	}
}

void SceneRanking::RankScoreDraw()
{
	int j=0;

	for(int i = 0; i < 5; i++)
	{	
		int num[9]={0};
		int figure=0;

		figure = (int)log10((double)data[i].score) + 1;	//スコアの桁を計算する
		for(int j = figure ; j > 0 ; j--)															//桁ごとの数字算出
		{
			num[9-j] = data[i].score/ (int)pow((double)10,j - 1) - data[i].score / (int)pow((double)10,j) * 10;
		}
		for(int j = figure ; j > 0 ; j--)
		{
			mVertex->SetTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
			mVertex->SetColor(alpha,255,255,255);
			mVertex->DrawF((float)SCORE_POSITION_X+(9-j)*DISLOCATE_X,(float)POSITION_Y+i*DISLOCATE_Y,R_FONT_0 + num[9-j]);
		}
	}
}

void SceneRanking::RankLoad()
{
	fopen_s(&fp,"Data\\rankingdata.txt","r");		//ファイルを開く

	if(fp == NULL)					//ファイルがなかった場合
	{
		MessageBox(NULL,"ファイルを開けませんでした","エラー",NULL);	//赤の文字のところを表示
		return;
	}

	for(int i = 0; i < 5; i++)
	{
		fscanf(fp,"%hhd,%hhd,%hhd,%d\n",&data[i].name[0],&data[i].name[1],&data[i].name[2],&data[i].score);
	}
	fclose(fp);
	newdata.name[0] = newdata.name[1] = newdata.name[2] = 0;		//プレイしたnameの初期化
	newdata.score = add_score;	//プレイしたスコア
}

void SceneRanking::RankWrite()
{
	fopen_s(&fp, "Data\\rankingdata.txt", "w");

	for(int i = 0; i < 5; i++)
	{
		fprintf(fp,"%d,%d,%d,%d\n",data[i].name[0],data[i].name[1],data[i].name[2],data[i].score);
	}
	fclose(fp);
	write_flag=false;
	//RankInit();
	z_key_flag = true;
}

void SceneRanking::FadeControl()
{
	switch(fade_flag)
	{
		case RANK_FADE_IN:
			FadeIn();
			if(alpha==255) fade_flag=RANK_USUALLY;
			break;
		case RANK_USUALLY:
			name_alpha[5][3]=255;
			alpha=255;
			alpha_count=0;
			break;
		case RANK_FADE_OUT:
			FadeOut();
			if(alpha==0) mIsSceneChange = false;
			break;
	}
}

void SceneRanking::FadeIn()
{
	if(alpha_count++>1)
	{
		alpha+=5;
		alpha_count=0;
	}

	if(alpha>255)
	{
		alpha=255;
		alpha_count=0;
	}

}

void SceneRanking::FadeOut()
{
	if(alpha_count++>1)
	{
		alpha-=5;
		alpha_count=0;
	}
	if(alpha<0)
	{
		alpha=0;
		alpha_count=0;
	}
}

void SceneRanking::RankCheck()
{
	//ランクインしてるかチェックする
	for(int i = 0; i < 5 ;i++){
		if(data[i].score < newdata.score) {
			rank = i;
			break;
		}
	}
	//ランクインしていればRankChengeへ
	if(rank != -1)
	{
		RankChenge(rank);
	}
	else z_key_flag = true;
}

void SceneRanking::RankChenge(int get)
{
	//ランクインした順位からずれていく
	if (get < 5) {
		for (int j = 4 ; j > get ; j--) {
			data[j] = data[j-1];
			}
		//ランクインしたところにプレイしたデータを入れる
		data[get].name[0]=newdata.name[0];
		data[get].name[1]=newdata.name[1];
		data[get].name[2]=newdata.name[2];
		data[get].score = newdata.score;
	}
}

void SceneRanking::RankInit()
{
	rank=-1;

	key_no = -1;

	flag = 0;
	in = 0;
	deray = 0;
	keep_key[3]=0;
	
	name_alpha[5][3]=255;

	write_flag=false;
}

void SceneRanking::ZKeyDraw()
{
	mVertex->SetTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
	mVertex->SetColor(z_alpha,255,255,255);
	//vertex->DrawF((float)Z_KEY_POSITION_X,(float)Z_KEY_POSITION_Y,R_Z_KEY);		
}