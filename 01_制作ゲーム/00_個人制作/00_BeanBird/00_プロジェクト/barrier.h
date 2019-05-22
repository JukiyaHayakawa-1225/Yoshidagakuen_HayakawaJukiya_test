//=============================================================================
//
// �o���A�̏��� [barrier.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "main.h"
#include "scene2D.h"

#define TEXTURE_NAME015 "data\\TEXTURE\\barrier.png"			//�e�N�X�`����
#define BARRIER_SIZE (60)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBarrier : public CScene2D
{
public:
	//=========================================================================
	// �o���A�̏��
	//=========================================================================
	typedef enum
	{
		STATE_NONE = 0,	//�o���A���g�p���Ă���
		STATE_USE,		//�o���A���g�p���Ă��Ȃ�
		STATE_MAX,

	} BARRIER_STATE;

	//�����o�֐�
	CBarrier();
	~CBarrier();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void FollowPlayer(void);
	static BARRIER_STATE GetState(void);
	static void SetState(BARRIER_STATE state);

	//�ÓI�����o�֐�
	static CBarrier *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWight, float fHeight);

private:
	//�����o�ϐ�
	static BARRIER_STATE m_state;
	int m_timer;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif