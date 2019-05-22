//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2D.h"

#define PLAYER_NOMAL_SPEED (0.7f)
#define PLAYER_SKILL_SPEED (1.25f);
#define TEXTURE_NAME000 "data\\TEXTURE\\player.png"			//�e�N�X�`����
#define PLAYER_SIZE			(50)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		STATE_NOMAL = 0,	//�ʏ���
		STATE_FEVER,		//�t�B�[�o�[���
		STATE_REVIVAL,		//�������
		STATE_INVINCIBLE,	//���G���
		STATE_END,
	}STATE;
	typedef enum
	{
		BULLET_NOMAL = 0,
		BULLET_SKILL,
		BULLET_MAX,
	}BULLET_TYPE;
	typedef enum
	{
		SPEED_NOMAL = 0,
		SPEED_SKILL,
		SPEED_MAX,
	}PLAYER_SPEED;

	//�����o�֐�
	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	float GetRot(void);
	STATE GetState(void);
	void SetState(STATE state);
	void SetBullet(BULLET_TYPE type);
	BULLET_TYPE GetBullet(void);
	void SetMove(D3DXVECTOR3 move);
	void SetSpeed(PLAYER_SPEED speed);
	void HitDamage(int nDamage);
	float GetSpeed(void);
	//�ÓI�����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos, float fWight, float fHeight,STATE state);
	static HRESULT Load(void);
	static void Unload(void);

private:
	float m_speed;
	int m_nCount;
	D3DXVECTOR3 m_move;
	static BULLET_TYPE m_bulletType;
	static STATE m_state;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif