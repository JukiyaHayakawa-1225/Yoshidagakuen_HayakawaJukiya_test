//=============================================================================
//
// ���C������ [main.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//�O���錾
class CScene;
class CRenderer;
class CManager;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int GetFPS(void);
CRenderer *GetRenderer(void);
//CScene **GetScene(void);

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <windows.h>
#include <stdlib.h>
#include "d3dx9.h"	//�`�揈���ɕK�v
#include "xaudio2.h"
#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"	//���͏����ɕK�v

//�f�o�b�O�����ɕK�v
#include <crtdbg.h>
#if 0
#define _malloc_dbg(X, _NORMAL_BLOCK, __FILE__, __LINE__)
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#endif

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")		//�V�X�e�������擾�ɕK�v
#pragma comment (lib,"dinput8.lib")		// ���͏����ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//1.0f�ŌŒ�
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;

#endif
