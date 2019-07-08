/******************************************************************
 *	@file	SceneRanking.cpp
 *	@brief	�����L���O�V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "SceneRanking.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/DefineGame.h"

#define POSITION_Y	(150)			// ���O��Y�̒��S�ʒu
#define PLACE_POSITION_X	(50)	// ���ʂ̃t�H���gX�̒��S�ʒu
#define DOT_X	(100)
#define NAME_POSITION_X	(150)		// ���O��X�̒��S�ʒu
#define SCORE_POSITION_X	(350)	// �X�R�A��X�̒��S�ʒu
#define DISLOCATE_X	(50)			// X�̈ʒu�����炷(�A���A�����l�ł��炳�Ȃ��ƈӖ����Ȃ�)
#define DISLOCATE_Y	(100)			// Y�̈ʒu�����炷(�A���A�����l�ł��炳�Ȃ��ƈӖ����Ȃ�)

namespace
{
	struct RANK
	{
		char name[3];
		int score;
	};

	enum RANK_FADE_MODE
	{
		RANK_FADE_IN,
		RANK_USUALLY,
		RANK_FADE_OUT,
	};

	enum TEXTURE_DATA_RANKING
	{
		T_RANKING_BG,
		T_RANKING_FONT,
	};

	enum RECT_DATA_RANKING
	{
		R_RANKING_BG,
		R_FONT_A,
		R_FONT_B,
		R_FONT_C,
		R_FONT_D,
		R_FONT_E,
		R_FONT_F,
		R_FONT_G,
		R_FONT_H,
		R_FONT_I,
		R_FONT_J,
		R_FONT_K,
		R_FONT_L,
		R_FONT_M,
		R_FONT_N,
		R_FONT_O,
		R_FONT_P,
		R_FONT_Q,
		R_FONT_R,
		R_FONT_S,
		R_FONT_T,
		R_FONT_U,
		R_FONT_V,
		R_FONT_W,
		R_FONT_X,
		R_FONT_Y,
		R_FONT_Z,
		R_FONT_0,
		R_FONT_1,
		R_FONT_2,
		R_FONT_3,
		R_FONT_4,
		R_FONT_5,
		R_FONT_6,
		R_FONT_7,
		R_FONT_8,
		R_FONT_9,
		R_FONT_DOT,
	};

	FILE *fp;
	struct RANK data[5];
	struct RANK newdata;				//���O�ƃX�R�A�̏������̂���
}

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

	ranking_flag=false;
}

SceneRanking::~SceneRanking(void)
{
}

void
SceneRanking::impleInit()
{
}

void SceneRanking::init(LPDIRECT3DDEVICE9 apDev, int score)
{
	mDevice = apDev;
	add_score = score;

	mTexture->load("Data\\TextureData\\ranking.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->load("Data\\RectData\\ranking.txt");
	loadRanking();
	checkRanking();
}

bool SceneRanking::update()
{
	UtilSound::playLoop(S_BGM_TITLE);

	updateFade();
	updateRanking(rank);
	updateInput();
	return mIsSceneChange;
}

void SceneRanking::updateRanking(int rank)
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
					if(write_flag) writeRanking();
				}
			}
		}
	}
}

void SceneRanking::updateInput()
{
	if(GetAsyncKeyState(VK_RETURN))
	{
		fade_flag = RANK_FADE_OUT;
	}
}

void SceneRanking::draw()
{
	drawBackGround();
	drawRankingPlace();
	drawRankingName();
	drawRankingScore();
}

int SceneRanking::end()
{
	requestChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->release();

	return 0;
}

void SceneRanking::drawBackGround()
{
	mVertex->setTextureData(mTexture->getTextureData(T_RANKING_BG), mDevice);
	mVertex->setColor(alpha,255,255,255);
	mVertex->drawF(400.f,300.f,R_RANKING_BG);
}

void SceneRanking::drawRankingPlace()
{
	for(int i=0;i<5;i++)
	{
			mVertex->setTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
			mVertex->setColor(alpha,255,255,255);
			mVertex->drawF((float)PLACE_POSITION_X,(float)POSITION_Y + i * DISLOCATE_Y,R_FONT_1 + i);
			mVertex->drawF((float)DOT_X,(float)POSITION_Y+i * DISLOCATE_Y,R_FONT_DOT);
	}
}

void SceneRanking::drawRankingName()
{
	for(int j=0;j<5;j++)
	{
		for(int i=0;i<3;i++)
		{
			mVertex->setTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
			if(fade_flag==RANK_USUALLY)	mVertex->setColor(name_alpha[j][i],255,255,255);
			else mVertex->setColor(alpha,255,255,255);
			mVertex->drawF((float)NAME_POSITION_X+i*DISLOCATE_X,(float)POSITION_Y+j*DISLOCATE_Y,R_FONT_A + data[j].name[i]);
		}
	}
}

void SceneRanking::drawRankingScore()
{
	int j=0;

	for(int i = 0; i < 5; i++)
	{	
		int num[9]={0};
		int figure=0;

		figure = (int)log10((double)data[i].score) + 1;	//�X�R�A�̌����v�Z����
		for(int j = figure ; j > 0 ; j--)															//�����Ƃ̐����Z�o
		{
			num[9-j] = data[i].score/ (int)pow((double)10,j - 1) - data[i].score / (int)pow((double)10,j) * 10;
		}
		for(int j = figure ; j > 0 ; j--)
		{
			mVertex->setTextureData(mTexture->getTextureData(T_RANKING_FONT), mDevice);
			mVertex->setColor(alpha,255,255,255);
			mVertex->drawF((float)SCORE_POSITION_X+(9-j)*DISLOCATE_X,(float)POSITION_Y+i*DISLOCATE_Y,R_FONT_0 + num[9-j]);
		}
	}
}

void SceneRanking::loadRanking()
{
	fopen_s(&fp,"Data\\rankingdata.txt","r");		//�t�@�C�����J��

	if(fp == NULL)					//�t�@�C�����Ȃ������ꍇ
	{
		MessageBox(NULL,"�t�@�C�����J���܂���ł���","�G���[",NULL);	//�Ԃ̕����̂Ƃ����\��
		return;
	}

	for(int i = 0; i < 5; i++)
	{
		fscanf(fp,"%hhd,%hhd,%hhd,%d\n",&data[i].name[0],&data[i].name[1],&data[i].name[2],&data[i].score);
	}
	fclose(fp);
	newdata.name[0] = newdata.name[1] = newdata.name[2] = 0;		//�v���C����name�̏�����
	newdata.score = add_score;	//�v���C�����X�R�A
}

void SceneRanking::writeRanking()
{
	fopen_s(&fp, "Data\\rankingdata.txt", "w");

	for(int i = 0; i < 5; i++)
	{
		fprintf(fp,"%d,%d,%d,%d\n",data[i].name[0],data[i].name[1],data[i].name[2],data[i].score);
	}
	fclose(fp);
	write_flag=false;
	//RankInit();
}

void SceneRanking::updateFade()
{
	switch(fade_flag)
	{
		case RANK_FADE_IN:
			fadeIn();
			if(alpha==255) fade_flag=RANK_USUALLY;
			break;
		case RANK_USUALLY:
			name_alpha[5][3]=255;
			alpha=255;
			alpha_count=0;
			break;
		case RANK_FADE_OUT:
			fadeOut();
			if(alpha==0) mIsSceneChange = false;
			break;
	}
}

void SceneRanking::fadeIn()
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

void SceneRanking::fadeOut()
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

void SceneRanking::checkRanking()
{
	//�����N�C�����Ă邩�`�F�b�N����
	for(int i = 0; i < 5 ;i++){
		if(data[i].score < newdata.score) {
			rank = i;
			break;
		}
	}
	//�����N�C�����Ă����RankChenge��
	if(rank != -1)
	{
		sortRanking(rank);
	}
}

void SceneRanking::sortRanking(int get)
{
	//�����N�C���������ʂ��炸��Ă���
	if (get < 5) {
		for (int j = 4 ; j > get ; j--) {
			data[j] = data[j-1];
			}
		//�����N�C�������Ƃ���Ƀv���C�����f�[�^������
		data[get].name[0]=newdata.name[0];
		data[get].name[1]=newdata.name[1];
		data[get].name[2]=newdata.name[2];
		data[get].score = newdata.score;
	}
}

void SceneRanking::initRanking()
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