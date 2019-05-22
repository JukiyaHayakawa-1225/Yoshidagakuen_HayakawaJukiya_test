//=============================================================================
//
// �_�̏��� [cloud.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _CLOUD_H_
#define _CLOUD_H_

#include "main.h"
#include "scene2D.h"

#define CLOUD_SIZE	(50)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCloud : public CScene2D
{
public:
	typedef enum
	{
		CLOUD_NONE = 0,
		CLOUD_BEANS,
		CLOUD_MAX,
	} CLOUD_STATE;

	//�����o�֐�
	CCloud();
	~CCloud();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitCloud(void);
	//�ÓI�����o�֐�
	static CCloud *Create(D3DXVECTOR3 pos, float fWight, float fHeight, CLOUD_STATE state);
	CLOUD_STATE GetCloud(void);

private:
	D3DXVECTOR3					m_move;
	CLOUD_STATE					m_state;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture;
};
#endif