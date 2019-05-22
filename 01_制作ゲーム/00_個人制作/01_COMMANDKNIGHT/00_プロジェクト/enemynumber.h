//=============================================================================
//
// �G�̐����� [enemynumber.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _ENEMYNUMBER_H_
#define _ENEMYNUMBER_H_

#include "main.h"
#include "scene.h"

class CNumber;

#define MAX_ENEMY_TYPE (2)
#define ENEMY_DIGIT (2)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBirdNumber : public CScene
{
public:
	//�����o�֐�
	CBirdNumber();
	~CBirdNumber();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�ÓI�����o�֐�
	static CBirdNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
	D3DXVECTOR3							m_pos;						// �ʒu
	float								m_fWidth;
	float								m_fHeight;
	int									m_nCountTimer;
	CNumber			*m_apNumber[ENEMY_DIGIT];	// �e�N�X�`���ւ̃|�C���^
	//�ÓI�����o�ϐ�
	static int		m_nBirdNumber;

protected:
};

class CFrogNumber : public CScene
{
public:
	//�����o�֐�
	CFrogNumber();
	~CFrogNumber();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�ÓI�����o�֐�
	static CFrogNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
	D3DXVECTOR3							m_pos;						// �ʒu
	float								m_fWidth;
	float								m_fHeight;
	int									m_nCountTimer;
	CNumber			*m_apNumber[ENEMY_DIGIT];	// �e�N�X�`���ւ̃|�C���^
												//�ÓI�����o�ϐ�
	static int		m_nFrogNumber;

protected:
};

#endif