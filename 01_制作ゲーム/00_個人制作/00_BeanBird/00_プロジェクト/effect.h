//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2D.h"

#define TEXTURE_NAME012 "data\\TEXTURE\\effect000.jpg"			//�e�N�X�`����

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEffect : public CScene2D
{
public:
	//�����o�֐�
	CEffect();
	~CEffect();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CEffect *Create(D3DXVECTOR3 pos,D3DXCOLOR col, float fWight, float fHeight);

private:
	//�����o�ϐ�
	int m_nLife;		//�̗�
	D3DXVECTOR3 m_move;	//�ړ���
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif