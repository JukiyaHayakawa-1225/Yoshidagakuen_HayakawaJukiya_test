//=============================================================================
//
// �}�l�[�W������ [manager.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "sound.h"
#include "number.h"
#include "rankingscore.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CManager::MODE	CManager::m_mode = MODE::MODE_TITLE;	//���[�h�̏��
CRenderer		*CManager::m_pRenderer = NULL;			//�����_�����O�|�C���^
CInputKeyboard	*CManager::m_pInputKeyboard = NULL;		//�L�[�{�[�h�|�C���^
CInputJoypad	*CManager::m_pInputJoypad = NULL;		//�W���C�p�b�h�|�C���^
CTitle			*CManager::m_pTitle = NULL;				//�^�C�g���̃|�C���^
CTutorial		*CManager::m_pTutorial = NULL;			//�`���[�g���A���̃|�C���^
CGame			*CManager::m_pGame = NULL;				//�Q�[���̃|�C���^
CResult			*CManager::m_pResult = NULL;			//���U���g�̃|�C���^
CRanking		*CManager::m_pRanking = NULL;			//�����L���O�̃|�C���^
CSound			*CManager::m_pSound = NULL;
CScore			*CManager::m_pScore = NULL;
int				CManager::m_aRankingScore[5] = {};
int				CManager::m_nUpdateSocre = NULL;

//=============================================================================
// �}�l�[�W���̃R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �}�l�[�W���̃f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// �}�l�[�W���̏���������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;			//�����_�����O�̓��I�m��
	}

	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;	//�L�[�{�[�h�̓��I�m��
	}
	if (m_pInputJoypad == NULL)
	{
		m_pInputJoypad = new CInputJoypad;		//�W���C�p�b�h�̓��I�m��
	}
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;					//�T�E���h�̓��I�m��
	}
	//�����_�����O�̏���������
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}

	//�L�[�{�[�h�̏���������
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Init(hInstance,hWnd);
	}

	//�W���C�p�b�h�̏���������
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Init(hInstance, hWnd);
	}

	//�T�E���h�̏���������
	if (m_pSound != NULL)
	{
		m_pSound->InitSound(hWnd);
	}

	//���[�h�̐ݒu
	SetMode(m_mode);
	int nScore = 5000;

	for (int nCntScore = 0; nCntScore < 5; nCntScore++)
	{
		m_aRankingScore[nCntScore] = nScore;
		nScore -= 1000;
	}
	m_nUpdateSocre = 0;
	return S_OK;
}

//=============================================================================
// �}�l�[�W���̏I������
//=============================================================================
void CManager::Uninit(void)
{
	//�L�[�{�[�h�̏I������
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�W���C�p�b�h�̏I������
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	//�����_�����O�̏I������
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�T�E���h�̏I������
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�^�C�g���̏I������
	if (m_pTitle != NULL)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;
	}

	//�`���[�g���A���̏I������
	if (m_pTutorial != NULL)
	{
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = NULL;
	}

	//�Q�[���̏I������
	if (m_pGame != NULL)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;
	}

	//���U���g�̏I������
	if (m_pResult != NULL)
	{
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = NULL;
	}

	//�����L���O�̏I������
	if (m_pRanking != NULL)
	{
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;
	}
	//�S�Ă̊J������
	CScene::ReleaseAll();
}

//=============================================================================
// �}�l�[�W���̍X�V����
//=============================================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//�W���C�p�b�h�̍X�V����
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Update();
	}

	//�����_�����O�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE:				//�^�C�g���̏ꍇ
		if (m_pTitle != NULL)
		{
			//�^�C�g���̍X�V����
			m_pTitle->Update();
		}
		break;
	case MODE_TUTORIAL:				//�`���[�g���A���̏ꍇ
		if (m_pTutorial != NULL)
		{
			//�`���[�g���A���̍X�V����
			m_pTutorial->Update();
		}
		break;
	case MODE_GAME:					//�Q�[���̏ꍇ
		if (m_pGame != NULL)
		{
			//�Q�[���̍X�V����
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:				//���U���g�̏ꍇ
		if (m_pResult != NULL)
		{
			//���U���g�̍X�V����
			m_pResult->Update();
		}
		break;
	case MODE_RANKING:				//�����L���O�̏ꍇ
		if (m_pRanking != NULL)
		{
			//�����L���O�̍X�V����
			m_pRanking->Update();
		}
		break;
	}
}

//=============================================================================
// �}�l�[�W���̕`�揈��
//=============================================================================
void CManager::Draw(void)
{
	//�����_�����O�̕`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// �����_�����O�̎擾
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;			//�l��Ԃ�
}

//=============================================================================
// �L�[�{�[�h�̎擾
//=============================================================================
CInputKeyboard *CManager::GetKeyboard(void)
{
	return m_pInputKeyboard;	//�l��Ԃ�
}

//=============================================================================
// �L�[�{�[�h�̎擾
//=============================================================================
CInputJoypad *CManager::GetJoypad(void)
{
	return m_pInputJoypad;	//�l��Ԃ�
}

//=============================================================================
// �T�E���h�̎擾
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;				//�l��Ԃ�
}
//=============================================================================
// ���[�h�̎擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;				//�l��Ԃ�
}
//=============================================================================
// ���[�h�̐ݒu
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:				//�^�C�g���̏ꍇ
		if (m_pTitle != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM000);
			//�^�C�g���̏I������
			m_pTitle->Uninit();
			//�������̊J��
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_TUTORIAL:				//�`���[�g���A���̏ꍇ
		if (m_pTutorial != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM001);

			//�`���[�g���A���̏I������
			m_pTutorial->Uninit();
			//�������̊J��
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
	case MODE_GAME:					//�Q�[���̏ꍇ
		if (m_pGame != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM002);

			//�Q�[���̏I������
			m_pGame->Uninit();
			//�������̊J��
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:				//���U���g�̏ꍇ
		if (m_pResult != NULL)
		{
			if (m_pResult->GetResult() == CResult::RESULT_CLEAR)
			{
				m_pSound->StopSound(CSound::SOUND_LABEL_BGM003);
			}
			else if (m_pResult->GetResult() == CResult::RESULT_GAMEOVER)
			{
				m_pSound->StopSound(CSound::SOUND_LABEL_BGM004);
			}
			//���U���g�̏I������
			m_pResult->Uninit();
			//�������̊J��
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case MODE_RANKING:				//�����L���O�̏ꍇ
		if (m_pRanking != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM005);

			//�����L���O�̏I������
			m_pRanking->Uninit();
			//�������̊J��
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	}

	m_mode = mode;	//���

	switch (mode)
	{
	case MODE_TITLE:				//�^�C�g���̏ꍇ
		if (m_pTitle == NULL)
		{
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM000);
			//�^�C�g���̐���
			m_pTitle = CTitle::Create();
			m_nUpdateSocre = 6;
		}
		break;
	case MODE_TUTORIAL:				//�`���[�g���A���̏ꍇ
		if (m_pTutorial == NULL)
		{
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM001);
			//�`���[�g���A���̐���
			m_pTutorial = CTutorial::Create();
		}
		break;
	case MODE_GAME:					//�Q�[���̏ꍇ
		if (m_pGame == NULL)
		{
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM002);
			//�Q�[���̐���
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT:				//���U���g�̏ꍇ
		if (m_pRanking == NULL)
		{
			if (m_pResult->GetResult() == CResult::RESULT_CLEAR)
			{
				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM003);
			}
			else if (m_pResult->GetResult() == CResult::RESULT_GAMEOVER)
			{
				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM004);
			}
			//���U���g�̐���
			m_pResult = CResult::Create();
		}
		break;
	case MODE_RANKING:				//�����L���O�̏ꍇ
		if (m_pRanking == NULL)
		{
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM005);
			//�����L���O�̐���
			m_pRanking = CRanking::Create();
		}
		break;

	}
}

//=============================================================================
// �Q�[���X�R�A�̔�r�ݒu����
//=============================================================================
void CManager::SetGameScore(int score)
{
	int nData;	//�f�[�^�i�[
	int nUpdateScore = 0;
	if (m_aRankingScore[4] < score)
	{//��ԉ��̃X�R�A���傫���ꍇ�������
		m_aRankingScore[4] = score;
		nUpdateScore = score;
	}
	else
	{
		m_nUpdateSocre = 6;
	}

	//�~������(�o�u���\�[�g)
	for (int nCntData = 0; nCntData < 5; nCntData++)
	{
		for (int nCntNumber = nCntData + 1; nCntNumber < 5; nCntNumber++)
		{
			if (m_aRankingScore[nCntData] < m_aRankingScore[nCntNumber])
			{
				nData = m_aRankingScore[nCntNumber];
				m_aRankingScore[nCntNumber] = m_aRankingScore[nCntData];
				m_aRankingScore[nCntData] = nData;
			}
		}
			if (m_aRankingScore[nCntData] == nUpdateScore)
			{
				m_nUpdateSocre = nCntData;
			}
	}
}

//=============================================================================
// �����̐ݒu����
//=============================================================================
int CManager::GetGameScore(int nIdx)
{
	return m_aRankingScore[nIdx];
}

//=============================================================================
// �����̐ݒu����
//=============================================================================
int CManager::GetUpdateScore(void)
{
	return m_nUpdateSocre;
}