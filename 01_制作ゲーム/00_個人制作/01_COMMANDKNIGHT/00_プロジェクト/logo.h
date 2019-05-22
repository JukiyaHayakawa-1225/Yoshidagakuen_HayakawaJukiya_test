//=============================================================================
//
// ���S���� [logo.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"
#include "scene.h"
#include "result.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLogo : public CScene
{
public:
	//�����o�֐�
	CLogo(int nPriority = 6);
	~CLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	void SetPos(D3DXVECTOR3 pos);
	void SetWidth(float fWidth);
	void SetHeight(float Height);
	void SetCol(D3DXCOLOR col);

private:
	LPDIRECT3DTEXTURE9					m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3							m_pos;				// �ʒu
	float								m_fWidth;			//��
	float								m_fHeight;			//����
	D3DXCOLOR							m_col;				//�F

protected:
};
#endif

//=============================================================================
//
// �^�C�g�����S�̏��� [logo.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitleLogo : public CLogo
{
public:
	//�����o�֐�
	CTitleLogo();
	~CTitleLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CTitleLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	D3DXVECTOR3		m_pos;								// �ʒu

														//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};

//=============================================================================
//
// �`���[�g���A������ [logo.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTutorialLogo : public CLogo
{
public:
	//�����o�֐�
	CTutorialLogo();
	~CTutorialLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CTutorialLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	D3DXVECTOR3		m_pos;								// �ʒu

														//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};


//=============================================================================
//
// ���U���g���S���� [logo.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResultLogo : public CLogo
{
public:
	//�����o�֐�
	CResultLogo();
	~CResultLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CResultLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	D3DXVECTOR3		m_pos;								// �ʒu

														//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};

//=============================================================================
//
// ���U���g�X�R�A���S���� [logo.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResultScoreLogo : public CLogo
{
public:
	//�����o�֐�
	CResultScoreLogo();
	~CResultScoreLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CResultScoreLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	D3DXVECTOR3		m_pos;								// �ʒu

														//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};

//=============================================================================
//
// �����L���O���S���� [logo.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRankingLogo : public CLogo
{
public:
	//�����o�֐�
	CRankingLogo();
	~CRankingLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CRankingLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	D3DXVECTOR3		m_pos;								// �ʒu

														//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};

//=============================================================================
//
// �����L���O�����N���S���� [logo.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRankingRank : public CLogo
{
public:
	//�����o�֐�
	CRankingRank();
	~CRankingRank();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CRankingRank *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	D3DXVECTOR3		m_pos;								// �ʒu

														//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};

//=============================================================================
//
// HP���S���� [logo.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CHPLogo : public CLogo
{
public:
	//�����o�֐�
	CHPLogo();
	~CHPLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CHPLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};

//=============================================================================
//
// HP���S���� [logo.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMPLogo : public CLogo
{
public:
	//�����o�֐�
	CMPLogo();
	~CMPLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CMPLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};