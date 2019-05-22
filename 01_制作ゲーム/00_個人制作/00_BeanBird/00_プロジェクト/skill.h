//=============================================================================
//
// �X�L������ [skill.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SKILL_H_
#define _SKILL_H_

#include "main.h"
#include "scene.h"

#define MAX_SKILL   (SKILL_MAX)               // �X�L���̑���

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSkill : public CScene
{
public:
	//*************************************
	// ���ڂ̏��
	//*************************************
	typedef enum
	{
		SKILL_STATE_NONE = 0,			// �I������Ă��Ȃ����
		SKILL_STATE_USE,			    // �I������Ă�����
		SKILL_STATE_MAX
	}SKILL_STATE;

	typedef enum
	{
		SKILL_2WAY = 0,		//2Way
		SKILL_SPEED,		//�X�s�[�h
		SKILL_BARRIER,		//�o���A
		SKILL_AVATAR,		//���g
		SKILL_MAX
	}SKILL;

	//�����o�֐�
	CSkill();
	~CSkill();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	void SetSkill(SKILL skill, SKILL_STATE state);

	//�ÓI�����o�֐�
	static CSkill *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
	//�����o�ϐ�
	D3DXVECTOR3					m_pos;							//�ʒu
	float						m_fWidth;						//��
	float						m_fHeight;						//����
	D3DXCOLOR					m_aCol[MAX_SKILL];
	//static SKILL				m_skill;
	static SKILL_STATE			m_state[MAX_SKILL];
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_SKILL];
protected:
};
#endif