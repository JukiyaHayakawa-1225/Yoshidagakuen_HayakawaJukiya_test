//=============================================================================
//
// ���g�̏��� [avatar.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _AVATAR_H_
#define _AVATAR_H_

#include "main.h"
#include "scene2D.h"

#define MAX_AVATAR (2)											//���g�̐�

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CAvatar : public CScene2D
{
public:
	//=========================================================================
	// ���g�̏��
	//=========================================================================
	typedef enum
	{
		AVATAR_NONE = 0,		//�g�p���Ă��Ȃ����
		AVATAR_USE,				//�g�p���Ă�����
	} AVATAR_STATE;
	//�����o�֐�
	CAvatar();
	~CAvatar();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void FollowPlayer(void);
	static AVATAR_STATE GetAvatar(void);
	static void SetAvatar(AVATAR_STATE);
	//�ÓI�����o�֐�
	static CAvatar *Create(D3DXVECTOR3 pos, float fWight, float fHeight);
	static HRESULT Load(void);
	static void Unload(void);

private:
	D3DXVECTOR3 m_move;						//�ړ���
	//�ÓI�����o�ϐ�
	static	AVATAR_STATE m_state;			//���g�̏��
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
};
#endif