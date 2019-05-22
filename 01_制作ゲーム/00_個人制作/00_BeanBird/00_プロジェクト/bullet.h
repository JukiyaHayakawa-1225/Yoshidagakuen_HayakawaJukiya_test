//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

#define TEXTURE_NAME001 "data\\TEXTURE\\bullet000.png"			//�e�N�X�`����
#define MAX_BULLET			(3)
#define BULLET_HIT			(30)								// �����蔻��

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBullet : public CScene2D
{
public:
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		BULLETTYPE_NONE = 0,
		BULLETTYPE_PLAYER_SALIVA,		//�v���C���[�̑�
		BULLETTYPE_PLAYER_SHIT,			//�v���C���[�̕�
		BULLETTYPE_ENEMY,				//�G
		BULLETTYPE_MAX,
	} BULLETTYPE;
	//�����o�֐�
	CBullet();
	~CBullet();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Collision(void);
	//�ÓI�����o�֐�
	static CBullet *Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, float fWight, float fHeight,BULLETTYPE type);

private:
	//�����o�ϐ�
	int m_nLife;						//�̗�
	D3DXVECTOR3 m_move;					//�ړ���
	BULLETTYPE m_bulletType;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BULLET];
};
#endif