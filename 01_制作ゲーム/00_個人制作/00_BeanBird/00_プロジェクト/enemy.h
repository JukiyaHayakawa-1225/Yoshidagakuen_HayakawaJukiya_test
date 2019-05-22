//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2D.h"

#define TEXTURE_NAME006 "data\\TEXTURE\\enemy000.png"			//�e�N�X�`����
#define TEXTURE_NAME010 "data\\TEXTURE\\enemy001.png"			//�e�N�X�`����

#define MAX_ENEMY_TEXTURE (2)
#define ENEMY_SIZE		  (50)
#define BOSS_SIZE		  (100)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	typedef enum
	{// �G�̏��
		ENEMYSTATE_NORMAL = 0,	// �ʏ���
		ENEMYSTATE_DAMEGE,		// �_���[�W���
		ENEMYSTATE_MAX			// �G�̏�Ԃ̎�ނ̑���
	} ENEMYSTATE;
	typedef enum
	{
		ENEMY_TYPE_NOMAL = 0,
		ENEMY_TYPE_BOSS,
		ENEMY_TYPE_MAX,
	}ENEMY_TYPE;

	//�����o�֐�
	CEnemy(int nPriority = 4);
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void HitDamage(int nDamage,ENEMY_TYPE type);
	void Collision(void);

private:
	float			m_fSpin;
	D3DXVECTOR3		m_pos;
	ENEMYSTATE		m_enemyState;
	int				m_nCountState;

	//�ÓI�����o�ϐ�
	static		    int m_nNumEnemy;
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected :
	int				m_nLife;

};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemySlide : public CEnemy
{
public:
	typedef enum
	{
		SLIDE_R = 0,	//�E
		SLIDE_L,		//��
		SLIDE_MAX,
	}SLIDE;
	//�����o�֐�
	CEnemySlide();
	~CEnemySlide();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CEnemySlide *Create(D3DXVECTOR3 pos, float fWight, float fHeight,SLIDE slide);

private:
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_move;
	SLIDE			m_slide;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

//*****************************************************************************
// �J�[�u�G
//*****************************************************************************
class CEnemyCurve : public CEnemy
{
public:
	typedef enum
	{
		CURVE_R = 0,	//�E
		CURVE_L,		//��
		CURVE_MAX,
	}CURVE;

	//�����o�֐�
	CEnemyCurve();
	~CEnemyCurve();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CEnemyCurve *Create(D3DXVECTOR3 pos, float fWight, float fHeight,CURVE curve);

private:
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_move;
	int				m_nCounter;
	CURVE			m_curve;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
//*****************************************************************************
// �֍s
//*****************************************************************************
class CEnemyMeandering : public CEnemy
{
public:
	typedef enum
	{
		MEANDERING_R = 0,	//�E
		MEANDERING_L,		//��
		MEANDERING_MAX,
	}MEANDERING;

	//�����o�֐�
	CEnemyMeandering();
	~CEnemyMeandering();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CEnemyMeandering *Create(D3DXVECTOR3 pos, float fWight, float fHeight, MEANDERING meandering);

private:
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_move;
	int				m_nCounter;
	MEANDERING		m_meandering;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
//*****************************************************************************
// �ǔ�
//*****************************************************************************
class CEnemyTracking : public CEnemy
{
public:
	//�����o�֐�
	CEnemyTracking();
	~CEnemyTracking();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CEnemyTracking *Create(D3DXVECTOR3 pos, float fWight, float fHeight);

private:
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_move;
	int				m_nCounter;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

//*****************************************************************************
// �l��
//*****************************************************************************
class CEnemyHuman : public CEnemy
{
public:
	//�����o�֐�
	CEnemyHuman();
	~CEnemyHuman();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CEnemyHuman *Create(D3DXVECTOR3 pos, float fWight, float fHeight);

private:
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_move;
	int				m_nCounter;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

//*****************************************************************************
// �{�X
//*****************************************************************************
class CEnemyBoss : public CEnemy
{
public:
	//�����o�֐�
	CEnemyBoss();
	~CEnemyBoss();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CEnemyBoss *Create(D3DXVECTOR3 pos, float fWight, float fHeight);

private:
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_move;
	int				m_nCounter;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif