//=============================================================================
//
// UI���� [ui.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include "main.h"
#include "scene.h"

#define MAX_GAUGE_TEXTURE (2)		//UI�Q�[�W�̃e�N�X�`���ő吔
#define MAX_GAUGE_WIDTH (300.0f)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CUI
{
public:
	//�����o�֐�
	CUI();
	~CUI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	void SetPos(D3DXVECTOR3 pos);
	void SetCol(D3DXCOLOR col);
	void SetWidth(float fWidth);
	void SetHeight(float fHeight);
	void SetVtxPos(D3DXVECTOR3 pos);
	void SetSideCut(int nType);

	D3DXVECTOR3 GetPos(void);
	D3DXCOLOR	GetCol(void);
	float GetWidth(void);
	float GetHeight(void);

	//�ÓI�����o�֐�
	static CUI *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	LPDIRECT3DTEXTURE9					m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3							m_pos;				// �ʒu
	D3DXCOLOR							m_col;				// �F
	float								m_fWidth;			// ��
	float								m_fHeight;			// ����

protected:
};

//*****************************************************************************
// �̗̓Q�[�W�̃N���X��`
//*****************************************************************************
class CUI_LifeGauge : public CScene
{
public:
	//�����o�֐�
	CUI_LifeGauge();
	~CUI_LifeGauge();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CutLifeGauge(int cut);
	void ResetLifeGauge(int nLife);

	//�ÓI�����o�֐�
	static CUI_LifeGauge *Create(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CUI *GetLifeGauge(void);

private:
	//�����o�ϐ�

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9			m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	static CUI							*m_pUI;		// UI�ւ̃|�C���^

protected:
};
//*****************************************************************************
// �Ƃ����Q�[�W�̃N���X��`
//*****************************************************************************
class CUI_SkillGauge : public CScene
{
public:
	//�����o�֐�
	CUI_SkillGauge();
	~CUI_SkillGauge();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CutSkillGauge(int cut);

	//�ÓI�����o�֐�
	static CUI_SkillGauge *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//�����o�ϐ�

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9			m_apTexture[MAX_GAUGE_TEXTURE];	// �e�N�X�`���ւ̃|�C���^
	static CUI							*m_apUI[MAX_GAUGE_TEXTURE];		// UI�ւ̃|�C���^

protected:
};

//*****************************************************************************
// �_���[�W�Q�[�W�̃N���X��`
//*****************************************************************************
class CUI_DamageGauge : public CScene
{
public:
	typedef enum
	{
		STATE_NOMAL = 0,
		STATE_MINUS,
		STATE_MAX,
	}DAMAGE_STATE;

	//�����o�֐�
	CUI_DamageGauge();
	~CUI_DamageGauge();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetDamageState(DAMAGE_STATE state);

	//�ÓI�����o�֐�
	static CUI_DamageGauge *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//�����o�ϐ�
	DAMAGE_STATE m_state;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9			m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	static CUI							*m_pUI;		// UI�ւ̃|�C���^

protected:
};

//*****************************************************************************
//	�x�[�X�Q�[�W�̃N���X��`
//*****************************************************************************
class CUI_BaseGauge : public CScene
{
public:
	//�����o�֐�
	CUI_BaseGauge();
	~CUI_BaseGauge();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CUI_BaseGauge *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9			m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	static CUI							*m_pUI;		// UI�ւ̃|�C���^

protected:
};

#endif