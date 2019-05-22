//=============================================================================
//
// ���U���g�̏��� [result.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

#define MAX_RESULT (2)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResult
{
public:
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		RESULT_NONE = 0,
		RESULT_CLEAR,	//�N���A
		RESULT_GAMEOVER,	//�Q�[���I�[�o�[
		RESULT_MAX,
	}RESULT;
	//�����o�֐�
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetResult(RESULT result);
	RESULT GetResult(void);

	//�ÓI�����o�֐�
	static CResult *Create(void);

private:
	//�����o�ϐ�
	int m_nTimer;
	static RESULT m_result;
};
#endif