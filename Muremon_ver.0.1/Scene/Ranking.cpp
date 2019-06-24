//---------------------------------------------
//
//      �����L���O
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#include "Ranking.h"

FILE *fp;
struct RANK data[5];
struct RANK newdata;				//���O�ƃX�R�A�̏������̂���

C_Ranking::C_Ranking(void)
{
	vertex = new C_Vertex();
	texture= new C_Texture();

	scene_change = true;

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

	//name_alpha[5][3]=255;

	//name_red[5][3]=255;

	//name_bule[5][3]=255;

	//name_green[5][3]=255;

	name_blink=false;

	name_alpha_down=false;

	z_key_flag=false;

	z_alpha_up = false;

	z_alpha = 0;

	ranking_flag=false;
}

C_Ranking::~C_Ranking(void)
{
}

void C_Ranking::InitScene(LPDIRECT3DDEVICE9 apDev, /*C_DInput *apinput,*/ C_DFont *apFont, C_DSound *apSound,int score)
{
	C_SceneManage::InitScene(apDev,/*apinput,*/apFont,apSound,0);
	sound = apSound;

	add_score = score;

	texture->LoadTextureData("TextureData\\ranking.txt",apDev);		//�G�̓ǂݍ���
	vertex->LoadRect("RectData\\ranking.txt");
	RankLoad();
	RankCheck();
}

bool C_Ranking::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_Ranking::ControlScene()
{
	sound->SoundPlay(true,S_BGM_TITLE);

	FadeControl();
	RankControl(rank);
	KeyControl();
}

void C_Ranking::RankControl(int rank)
{
	name_blink=true;
	name_alpha_down=true;
	for(int i = 'A'; i <= 'Z'; i++)
	{
		if(GetAsyncKeyState(i))
		{
			sound->SoundPlay(false,S_SE_CURSOR_MOVE);
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
				sound->SoundPlay(false,S_SE_OK);
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

void C_Ranking::KeyControl()
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

void C_Ranking::DrawScene()
{
	RankBackGround();
	RankPlaceDraw();
	RankNameDraw();
	RankScoreDraw();
	ZKeyDraw();
}

int C_Ranking::EndScene()
{
	ChangeScene(TITLE);
	texture->AllReleaseTexture();
	vertex->AllReleaseRect();

	return 0;
}

void C_Ranking::RankBackGround()
{
	vertex->SetTextureData(texture->GetTextureData(T_RANKING_BG),pDevice);
	vertex->SetColor(alpha,255,255,255);
	vertex->DrawF(400.f,300.f,R_RANKING_BG);
}

void C_Ranking::RankPlaceDraw()
{
	for(int i=0;i<5;i++)
	{
			vertex->SetTextureData(texture->GetTextureData(T_RANKING_FONT),pDevice);
			vertex->SetColor(alpha,255,255,255);
			vertex->DrawF((float)PLACE_POSITION_X,(float)POSITION_Y + i * DISLOCATE_Y,R_FONT_1 + i);
			vertex->DrawF((float)DOT_X,(float)POSITION_Y+i * DISLOCATE_Y,R_FONT_DOT);
	}
}

void C_Ranking::RankNameDraw()
{
	for(int j=0;j<5;j++)
	{
		for(int i=0;i<3;i++)
		{
			vertex->SetTextureData(texture->GetTextureData(T_RANKING_FONT),pDevice);
			if(fade_flag==RANK_USUALLY)	vertex->SetColor(name_alpha[j][i],255,255,255);
			else vertex->SetColor(alpha,255,255,255);
			vertex->DrawF((float)NAME_POSITION_X+i*DISLOCATE_X,(float)POSITION_Y+j*DISLOCATE_Y,R_FONT_A + data[j].name[i]);
		}
	}
}

void C_Ranking::RankScoreDraw()
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
			vertex->SetTextureData(texture->GetTextureData(T_RANKING_FONT),pDevice);
			vertex->SetColor(alpha,255,255,255);
			vertex->DrawF((float)SCORE_POSITION_X+(9-j)*DISLOCATE_X,(float)POSITION_Y+i*DISLOCATE_Y,R_FONT_0 + num[9-j]);		
		}
	}
}

void C_Ranking::RankLoad()
{
	fopen_s(&fp,"data\\rankingdata.txt","r");		//�t�@�C�����J��

	if(fp == NULL)					//�t�@�C�����Ȃ������ꍇ
	{
		MessageBox(NULL,"�t�@�C�����J���܂���ł���","�G���[",NULL);	//�Ԃ̕����̂Ƃ����\��
		return;
	}

	for(int i = 0; i < 5; i++)
	{
		fscanf(fp,"%d,%d,%d,%d\n",&data[i].name[0],&data[i].name[1],&data[i].name[2],&data[i].score);
	}
	fclose(fp);
	newdata.name[0] = newdata.name[1] = newdata.name[2] = 0;		//�v���C����name�̏�����
	newdata.score = add_score;	//�v���C�����X�R�A
}

void C_Ranking::RankWrite()
{
	fp = fopen("data\\rankingdata.txt","w");	

	for(int i = 0; i < 5; i++)
	{
		fprintf(fp,"%d,%d,%d,%d\n",data[i].name[0],data[i].name[1],data[i].name[2],data[i].score);
	}
	fclose(fp);
	write_flag=false;
	//RankInit();
	z_key_flag = true;
}

void C_Ranking::FadeControl()
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
			if(alpha==0) scene_change=false;
			break;
	}
}

void C_Ranking::FadeIn()
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

void C_Ranking::FadeOut()
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

void C_Ranking::RankCheck()
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
		RankChenge(rank);
	}
	else z_key_flag = true;
}

void C_Ranking::RankChenge(int get)
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

void C_Ranking::RankInit()
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

void C_Ranking::ZKeyDraw()
{
	vertex->SetTextureData(texture->GetTextureData(T_RANKING_FONT),pDevice);
	vertex->SetColor(z_alpha,255,255,255);
	//vertex->DrawF((float)Z_KEY_POSITION_X,(float)Z_KEY_POSITION_Y,R_Z_KEY);		
}