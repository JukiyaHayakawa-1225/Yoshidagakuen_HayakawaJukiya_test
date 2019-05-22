//=============================================================================
//
// �����̏��� [explotion.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _EXPLOTION_H_
#define _EXPLOTION_H_

#include "main.h"
#include "scene2D.h"

#define TEXTURE_NAME002 "data\\TEXTURE\\explosion000.png"			//�e�N�X�`����
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CExplotion : public CScene2D
{
public:
	//�����o�֐�
	CExplotion();
	~CExplotion();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CExplotion *Create(D3DXVECTOR3 pos, float fWight, float fHeight);

private:
	//�����o�ϐ�
	int m_nCounterAnim;	// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	// �A�j���[�V�����p�^�[��

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif