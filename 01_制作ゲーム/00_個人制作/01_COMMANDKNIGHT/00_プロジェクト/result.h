//=============================================================================
//
// ���U���g�̏��� [result.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

#define MAX_RESULT (RESULT_MAX)	//���U���g�̐�
class CScore;
class CTimer;
class CMap;
class CBirdNumber;
class CFrogNumber;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResult
{
public:	//�N������A�N�Z�X�\
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		RESULT_NONE = 0,
		RESULT_CLEAR,		//�N���A
		RESULT_GAMEOVER,	//�Q�[���I�[�o�[
		RESULT_MAX,
	}RESULT;
	typedef enum
	{
		COUNT_TIMER = 0,
		COUNT_BIRD,
		COUNT_FROG,
		COUNT_END,
		COUNT_MAX
	}COUNT_TYPE;
	//�����o�֐�
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetResult(RESULT result);
	RESULT GetResult(void);
	static void SetType(COUNT_TYPE);
	static COUNT_TYPE GetType(void);

	//�ÓI�����o�֐�
	static CResult *Create(void);
	static CScore		*GetScore(void);
	static CBirdNumber	*GetBirdNumber(void);
	static CFrogNumber	*GetFrogNumber(void);

private:	//�����������A�N�Z�X�\
	//�����o�ϐ�
	int m_nTimer;			//�^�C�}�[
	static	CScore			*m_pScore;	// �e�N�X�`���ւ̃|�C���^
	static CTimer			*m_pTimer;		//�^�C�}�[�̃|�C���^
	static CMap				*m_pMap;
	static CBirdNumber		*m_pBirdNumber;
	static CFrogNumber		*m_pFrogNumber;
	//�ÓI�����o�ϐ�
	static RESULT m_result;	//���U���g�̏��
	static COUNT_TYPE				m_type;
};
#endif