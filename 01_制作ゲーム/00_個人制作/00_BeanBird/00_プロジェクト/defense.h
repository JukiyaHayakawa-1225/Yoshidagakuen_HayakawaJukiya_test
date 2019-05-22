//=============================================================================
//
// �G�̖h�q���� [defense.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _DEFENSE_H_
#define _DEFENSE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CDefense : public CScene2D
{
public:
	//�����o�֐�
	CDefense();
	~CDefense();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void FollowPlayer(void);
	//�ÓI�����o�֐�
	static CDefense *Create(D3DXVECTOR3 pos, float fWight, float fHeight);
	static HRESULT Load(void);
	static void Unload(void);

private:
	int			m_nCounter;
	D3DXVECTOR3 m_move;						//�ړ���
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
};
#endif