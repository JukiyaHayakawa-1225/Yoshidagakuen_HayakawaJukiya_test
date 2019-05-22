//=============================================================================
//
// �^�C�}�[�̏��� [timer.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"
#include "scene.h"

class CNumber;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTimer : public CScene
{
public:
	//**********************************
	// �^�C�}�[�̏��
	//**********************************
	typedef enum
	{
		TIMERSTATE_COUNT = 0,
		TIMERSTATE_NONE_COUNT,
		TIMERSTATE_MAX
	}TIMERSTATE;
	//�����o�֐�
	CTimer();
	~CTimer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�ÓI�����o�֐�
	static CTimer *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static int GetTimer(void);
	bool GetTimerState(void);
private:
	D3DXVECTOR3							m_pos;						// �ʒu
	float								m_fWidth;
	float								m_fHeight;
	int									m_nCountTimer;
	bool								m_bStopTimer;

	CNumber			*m_apNumber[TIMER_DIGIT];	// �e�N�X�`���ւ̃|�C���^
	//�ÓI�����o�ϐ�
	static int		m_nTimer;
protected:
};
#endif