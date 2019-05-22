//=============================================================================
//
// �^�C�}�[�̏��� [timer.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "timer.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "number.h"
#include "result.h"
#include "score.h"
#include "sound.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CTimer::m_nTimer = 0;

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �^�C�}�[�̃R���X�g���N�^
//=============================================================================
CTimer::CTimer() :CScene(6, OBJTYPE_NUMBER)
{
}
//=============================================================================
// �^�C�}�[�̃f�X�g���N�^
//=============================================================================
CTimer::~CTimer()
{

}

//=============================================================================
//�^�C�}�[�̐���
//=============================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTimer *pTimer = NULL;
	if (pTimer == NULL)
	{
		pTimer = new CTimer;		//�V�[���̓��I�m��
		pTimer->m_pos = pos;		//�ʒu�̐ݒu
		pTimer->m_fWidth = fWidth;	//���̐ݒu
		pTimer->m_fHeight = fHeight;//�����̐ݒu
		pTimer->Init();				//����������
	}
	return pTimer;					//�l��Ԃ�
}

//=============================================================================
// �^�C�}�[�̏���������
//=============================================================================
HRESULT CTimer::Init(void)
{
	//���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	int nTimerData = 0;	//�^�C�}�[�̊i�[
	int nTime = 1;		//�^�C�}�[�̌�
	m_bStopTimer = false;
	//���[�h�ʏ���
	switch (mode)
	{
	case CManager::MODE_GAME:	//�Q�[���̏ꍇ
		m_nTimer = 240;	//�^�C�}�[���
		break;
	case CManager::MODE_RESULT:	//���U���g�̏ꍇ
		m_nTimer = CManager::GetTime();	//�^�C�}�[�̎擾
	}

	for (int nCntNumber = 0; nCntNumber < TIMER_DIGIT; nCntNumber++)
	{//���̐������J��Ԃ�
		m_apNumber[nCntNumber] = NULL;
	}

	for (int nCntNumber = 0; nCntNumber < TIMER_DIGIT; nCntNumber++)
	{//���̐������J��Ԃ�
		if (m_apNumber[nCntNumber] == NULL)
		{
			//���[�h�̎擾
			CManager::MODE mode = CManager::GetMode();

			if (mode == CManager::MODE_GAME)
			{//�Q�[���̏ꍇ
				//�����̐���
				m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (70.0f * nCntNumber), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
				nTimerData = m_nTimer % (nTime * 10) / nTime;
				m_apNumber[nCntNumber]->SetNumber(nTimerData);
				nTime *= 10;

			}
			else if(mode == CManager::MODE_RESULT)
			{//���U���g�̏ꍇ
				//�����̐���
				m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (70.0f * nCntNumber), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
				nTimerData = m_nTimer % (nTime * 10) / nTime;
				m_apNumber[nCntNumber]->SetNumber(nTimerData);
				nTime *= 10;
			}
		}
	}
	return S_OK;
}

//=============================================================================
// �^�C�}�[�̏I������
//=============================================================================
void CTimer::Uninit(void)
{
	//�^�C�}�[�̏I������
	for (int nCntNumber = 0; nCntNumber < TIMER_DIGIT; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] != NULL)
		{
			//�I������
			m_apNumber[nCntNumber]->Uninit();
			//�������̊J��
			delete m_apNumber[nCntNumber];
			//NULL�ɂ���
			m_apNumber[nCntNumber] = NULL;
		}
	}
	Release();
}

//=============================================================================
// �^�C�}�[�̍X�V����
//=============================================================================
void CTimer::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	//�t�F�[�h�̎擾����
	CFade *pFade = CManager::GetFade();

	switch (mode)
	{
	case CManager::MODE_GAME:
		int nTimerData;
		if (m_bStopTimer == TIMERSTATE_COUNT)
		{// �^�C�}�[��i�߂��Ԃ�������
			int nTime = 1;
			m_nCountTimer++;
			if (m_nCountTimer % 60 == 0)
			{// ��b�Ԃ�������
				m_nTimer--;
				if (m_nTimer >= 0)
				{
					for (int nCntTimer = 0; nCntTimer < TIMER_DIGIT; nCntTimer++)
					{// �^�C�}�[�̌��������J��Ԃ�
						nTimerData = m_nTimer % (nTime * 10) / nTime;
						m_apNumber[nCntTimer]->SetNumber(nTimerData);
						nTime *= 10;
					}
				}
				else if (m_nTimer < 0 /*&& fade == FADE_NONE*/)
				{// �^�C�}�[��0�ɂȂ�����
					/*SetGameState(GAMESTATE_END);
					SetResult(RESULT_CLEAR);*/
					m_nTimer = 0;
				}
			}
		}
		break;
	case CManager::MODE_RESULT:
		//���[�h�̎擾
		CResult::COUNT_TYPE type;
		type = CResult::GetType();

		if (type == CResult::COUNT_TIMER)
		{
			if (m_bStopTimer == TIMERSTATE_COUNT)
			{
				if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
					pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
				{
					CScore *pScore = CResult::GetScore();
					pScore->AddScore(m_nTimer * 10);
					m_nTimer = 0;
					int nTime = 1;

					for (int nCntTimer = 0; nCntTimer < TIMER_DIGIT; nCntTimer++)
					{// �^�C�}�[�̌��������J��Ԃ�
						nTimerData = m_nTimer % (nTime * 10) / nTime;
						m_apNumber[nCntTimer]->SetNumber(nTimerData);
						nTime *= 10;
					}
					m_bStopTimer = TIMERSTATE_NONE_COUNT;
					CResult::SetType(CResult::COUNT_BIRD);
				}
				int nTime = 1;
				m_nCountTimer++;
				if (m_nCountTimer % 2 == 0
					&& pFade->GetFade() == CFade::FADE_NONE)
				{// ��b�Ԃ�������
					if (m_nTimer > 0)
					{
						m_nTimer--;
						for (int nCntTimer = 0; nCntTimer < TIMER_DIGIT; nCntTimer++)
						{// �^�C�}�[�̌��������J��Ԃ�
							nTimerData = m_nTimer % (nTime * 10) / nTime;
							m_apNumber[nCntTimer]->SetNumber(nTimerData);
							nTime *= 10;
						}
						//�T�E���h�̎擾
						CSound *pSound;
						pSound = CManager::GetSound();
						//�X�R�A�̎擾
						CScore *pScore = CResult::GetScore();
						pScore->AddScore(10);	//�X�R�A�̉��Z
						pSound->PlaySound(CSound::SOUND_LABEL_SE_COUNT);
					}
					else
					{
						CResult::SetType(CResult::COUNT_BIRD);
					}
				}
			}
		}
		break;
	}
}

//=============================================================================
// �^�C�}�[�̕`�揈��
//=============================================================================
void CTimer::Draw(void)
{
	for (int nCntTimer = 0; nCntTimer < TIMER_DIGIT; nCntTimer++)
	{
		//�����̕`�揈��
		m_apNumber[nCntTimer]->Draw();
	}
}

//=============================================================================
// �^�C�}�[�̎擾����
//=============================================================================
int CTimer::GetTimer(void)
{
	return m_nTimer;
}

//=============================================================================
// �^�C�}�[�̏�Ԏ擾����
//=============================================================================
bool CTimer::GetTimerState(void)
{
	return m_bStopTimer;
}

