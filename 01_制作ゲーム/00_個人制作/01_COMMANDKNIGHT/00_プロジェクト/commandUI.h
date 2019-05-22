//=============================================================================
//
// �R�}���hUI�̏��� [commandUI.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _COMMANDUI_H_
#define _COMMANDUI_H_

#include "main.h"
#include "scene2D.h"

#define MAX_COMMANDUI (3)											//�w�i�̍ő吔

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCommandUI : public CScene2D
{
public:
	typedef enum
	{
		COMMAND_MAIN = 0,
		COMMAND_SKILL,
		COMMAND_ITEM,
		COMMAND_MAX,
	}COMMAND;
	typedef enum
	{
		COMMAND_HEIGHT_NONE = 0,		//�R�}���h�ʏ���
		COMMAND_HEIGHT_PROCESS,			//�R�}���h�g����
	}COMMAND_HEIGHT;

	//�����o�֐�
	CCommandUI();
	~CCommandUI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	COMMAND GetCommandState(void);
	COMMAND_HEIGHT GetCommandHeightState(void);
	void SetCommandState(COMMAND state);
	void SetCommandHeightState(COMMAND_HEIGHT heightState);
	//�ÓI�����o�֐�
	static CCommandUI *Create(void);
	static HRESULT Load(void);
	static void Unload(void);
private:
	//�����o�ϐ�
	float						m_fHeight;		//����
	COMMAND						m_state;		//�R�}���h���
	COMMAND_HEIGHT				m_heightState;	//�R�}���h�̍������
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_apTexture[3];	//�e�N�X�`���̃|�C���^

};
#endif