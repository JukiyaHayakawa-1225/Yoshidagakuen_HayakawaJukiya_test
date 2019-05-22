//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "billboard.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CParticle : public CBillboard
{
public:
	//�����o�֐�
	CParticle();
	~CParticle();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int nLife);
	int GetLife(void);

	//�ÓI�����o�֐�
	static CParticle *Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col,float fLength);

private:
	//�����o�ϐ�
	int m_nLife;		//�̗�
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSkill2Particle : public CParticle
{
public:
	//�����o�֐�
	CSkill2Particle();
	~CSkill2Particle();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CSkill2Particle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fLength,int nLife);

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_move;	//�ړ���
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CDamageParticle : public CParticle
{
public:
	//�����o�֐�
	CDamageParticle();
	~CDamageParticle();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CDamageParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fLength, int nLife);

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_move;	//�ړ���
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSnowParticle : public CParticle
{
public:
	//�����o�֐�
	CSnowParticle();
	~CSnowParticle();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CSnowParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fLength, int nLife);

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_move;	//�ړ���
	int	m_nTimer;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFountainParticle : public CParticle
{
public:
	//�����o�֐�
	CFountainParticle();
	~CFountainParticle();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CFountainParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fLength, int nLife);

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_move;	//�ړ���
	int	m_nTimer;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif