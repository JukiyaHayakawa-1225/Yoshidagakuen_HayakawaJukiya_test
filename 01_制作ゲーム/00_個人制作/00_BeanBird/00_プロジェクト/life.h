//=============================================================================
//
// �̗͂̏��� [life.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"

#define MAX_LIFE (3)	//����

class CPolygon;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLife : public CScene
{
public:
	//�����o�֐�
	CLife();
	~CLife();
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int nLife);
	int GetLife(void);
	void SetPos(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CLife *Create(D3DXVECTOR3 pos, float fWight, float fHeight);
	void CutLife(int nLife);
private:
	D3DXVECTOR3		m_pos;						// �ʒu
	//�ÓI�����o�ϐ�
	static CPolygon			*m_apPolygon[MAX_LIFE];	// �e�N�X�`���ւ̃|�C���^
	static int				m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};
#endif