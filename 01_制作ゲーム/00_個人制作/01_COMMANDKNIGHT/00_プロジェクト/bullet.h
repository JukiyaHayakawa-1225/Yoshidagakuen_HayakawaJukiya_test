//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "billboard.h"
#define MAX_BILLBOARDGAGE_WIDTH (15.0f)	//�r���{�[�h�Q�[�W�̕��ő�l
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBullet : public CBillboard
{
public:
	//�����o�֐�
	CBullet();
	~CBullet();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CBullet *Create(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//�����o�ϐ�
	int m_nLife;		//�̗�

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif