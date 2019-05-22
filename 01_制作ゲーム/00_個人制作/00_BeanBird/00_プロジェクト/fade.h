//=============================================================================
//
// �t�F�[�h�̏��� [fade.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFade : public CScene
{
public:
	//*************************************
	// �t�F�[�h�̏��
	//*************************************
	typedef enum
	{
		FADE_NONE = 0,		// �������Ă��Ȃ����
		FADE_IN,			// �t�F�[�h�C�����
		FADE_OUT,			// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;
	//�����o�֐�
	CFade();
	~CFade();
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�ÓI�����o�֐�
	static CFade *Create(CManager::MODE modeNext, D3DXVECTOR3 pos, float fWight, float fHeight);
	FADE GetFade(void);				//�t�F�[�h�̎擾����

private:
	//�����o�ϐ�
	D3DXVECTOR3		m_pos;
	float			m_fWidth;
	float			m_fHeight;
	LPDIRECT3DTEXTURE9				m_pTexture;
	//�ÓI�����o�ϐ�
	static FADE		m_fade;
	CManager::MODE	m_modeNext;
	D3DXCOLOR		m_colorFade;
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
};
#endif