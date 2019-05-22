//=============================================================================
//
// �r���{�[�h�Q�[�W���� [billboardgauge.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _BILLBOARDGAUGE_H_
#define _BILLBOARDGAUGE_H_

#include "main.h"
#include "billboard.h"
#define MAX_BILLBOARDGAGE_WIDTH (15.0f)	//�r���{�[�h�̕��̍ő�l

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBillboardLifeGauge : public CBillboard
{
public:
	//�����o�֐�
	CBillboardLifeGauge();
	~CBillboardLifeGauge();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CutLifeGauge(int cut);

	//�ÓI�����o�֐�
	static CBillboardLifeGauge *Create(D3DXVECTOR3 pos, int nLife, int nMaxLife);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//�����o�ϐ�
	int m_nLife;		//�̗�
	int	m_nMaxLife;		//�̗͍ő�l

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
};
#endif