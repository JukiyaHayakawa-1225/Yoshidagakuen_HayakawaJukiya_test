//=============================================================================
//
// �G�̐��̏��� [enemynumber.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "enemynumber.h"
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
int CBirdNumber::m_nBirdNumber = 0;

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�̐��̃R���X�g���N�^
//=============================================================================
CBirdNumber::CBirdNumber() :CScene(6, OBJTYPE_NUMBER)
{
}
//=============================================================================
// �G�̐��̃f�X�g���N�^
//=============================================================================
CBirdNumber::~CBirdNumber()
{

}

//=============================================================================
//�G�̐��̐���
//=============================================================================
CBirdNumber *CBirdNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CBirdNumber *pEnemyNumber = NULL;
	if (pEnemyNumber == NULL)
	{
		pEnemyNumber = new CBirdNumber;		//�V�[���̓��I�m��
		pEnemyNumber->m_pos = pos;		//�ʒu�̐ݒu
		pEnemyNumber->m_fWidth = fWidth;	//���̐ݒu
		pEnemyNumber->m_fHeight = fHeight;//�����̐ݒu
		pEnemyNumber->Init();				//����������
	}
	return pEnemyNumber;					//�l��Ԃ�
}

//=============================================================================
// �G�̐��̏���������
//=============================================================================
HRESULT CBirdNumber::Init(void)
{
	CManager::MODE mode;
	mode = CManager::GetMode();
	int nEnemyNumberData = 0;
	int nEnemy = 1;

	//�����擾
	m_nBirdNumber = CManager::GetBird();

	for (int nCntNumber = 0; nCntNumber < ENEMY_DIGIT; nCntNumber++)
	{
		m_apNumber[nCntNumber] = NULL;
	}

	for (int nCntNumber = 0; nCntNumber < ENEMY_DIGIT; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] == NULL)
		{
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (70.0f * nCntNumber), m_pos.y, m_pos.z), m_fWidth, m_fHeight);

			nEnemyNumberData = m_nBirdNumber % (nEnemy * 10) / nEnemy;

			m_apNumber[nCntNumber]->SetNumber(nEnemyNumberData);
			nEnemy *= 10;
		}
	}
	return S_OK;
}

//=============================================================================
// �G�̐��̏I������
//=============================================================================
void CBirdNumber::Uninit(void)
{
	//�G�̐��̏I������
	for (int nCntNumber = 0; nCntNumber < ENEMY_DIGIT; nCntNumber++)
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
// �G�̐��̍X�V����
//=============================================================================
void CBirdNumber::Update(void)
{
	//�t�F�[�h�̎擾����
	CFade *pFade = CManager::GetFade();
	//���[�h�̎擾
	CResult::COUNT_TYPE type;
	type = CResult::GetType();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	if (type == CResult::COUNT_BIRD)
	{
		int nData;
		int nEnemy = 1;

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
		{
			CScore *pScore = CResult::GetScore();
			pScore->AddScore(m_nBirdNumber * 500);
			m_nBirdNumber = 0;
			int nTime = 1;

			for (int nCntTimer = 0; nCntTimer < ENEMY_DIGIT; nCntTimer++)
			{// �^�C�}�[�̌��������J��Ԃ�
				nData = m_nBirdNumber % (nEnemy * 10) / nEnemy;
				m_apNumber[nCntTimer]->SetNumber(nData);
				nEnemy *= 10;
			}
			CResult::SetType(CResult::COUNT_FROG);
		}

		m_nCountTimer++;
		if (m_nCountTimer % 10 == 0
			&& pFade->GetFade() == CFade::FADE_NONE)
		{// ��b�Ԃ�������
			if (m_nBirdNumber > 0)
			{
				m_nBirdNumber--;
				for (int nCntTimer = 0; nCntTimer < ENEMY_DIGIT; nCntTimer++)
				{// �^�C�}�[�̌��������J��Ԃ�
					nData = m_nBirdNumber % (nEnemy * 10) / nEnemy;
					m_apNumber[nCntTimer]->SetNumber(nData);
					nEnemy *= 10;
				}
				CSound *pSound;
				pSound = CManager::GetSound();

				CScore *pScore = CResult::GetScore();
				pScore->AddScore(500);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_COUNT);
			}
			else
			{
				CResult::SetType(CResult::COUNT_FROG);
			}
		}
	}
}

//=============================================================================
// �G�̐��̕`�揈��
//=============================================================================
void CBirdNumber::Draw(void)
{
	for (int nCntEnemyNumber = 0; nCntEnemyNumber < ENEMY_DIGIT; nCntEnemyNumber++)
	{
		//�����̕`�揈��
		m_apNumber[nCntEnemyNumber]->Draw();
	}
}

//=============================================================================
//
// �G�̐��̏��� [enemynumber.cpp]
//
//=============================================================================
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CFrogNumber::m_nFrogNumber = 0;

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�̐��̃R���X�g���N�^
//=============================================================================
CFrogNumber::CFrogNumber() :CScene(6, OBJTYPE_NUMBER)
{
}
//=============================================================================
// �G�̐��̃f�X�g���N�^
//=============================================================================
CFrogNumber::~CFrogNumber()
{

}

//=============================================================================
//�G�̐��̐���
//=============================================================================
CFrogNumber *CFrogNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CFrogNumber *pEnemyNumber = NULL;
	if (pEnemyNumber == NULL)
	{
		pEnemyNumber = new CFrogNumber;		//�V�[���̓��I�m��
		pEnemyNumber->m_pos = pos;		//�ʒu�̐ݒu
		pEnemyNumber->m_fWidth = fWidth;	//���̐ݒu
		pEnemyNumber->m_fHeight = fHeight;//�����̐ݒu
		pEnemyNumber->Init();				//����������
	}
	return pEnemyNumber;					//�l��Ԃ�
}

//=============================================================================
// �G�̐��̏���������
//=============================================================================
HRESULT CFrogNumber::Init(void)
{
	CManager::MODE mode;
	mode = CManager::GetMode();
	int nEnemyNumberData = 0;
	int nEnemy = 1;

	//�����擾
	m_nFrogNumber = CManager::GetFrog();

	for (int nCntNumber = 0; nCntNumber < ENEMY_DIGIT; nCntNumber++)
	{
		m_apNumber[nCntNumber] = NULL;
	}

	for (int nCntNumber = 0; nCntNumber < ENEMY_DIGIT; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] == NULL)
		{
			//�����̐���
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (70.0f * nCntNumber), m_pos.y, m_pos.z), m_fWidth, m_fHeight);

			nEnemyNumberData = m_nFrogNumber % (nEnemy * 10) / nEnemy;

			m_apNumber[nCntNumber]->SetNumber(nEnemyNumberData);
			nEnemy *= 10;
		}
	}
	return S_OK;
}

//=============================================================================
// �G�̐��̏I������
//=============================================================================
void CFrogNumber::Uninit(void)
{
	//�G�̐��̏I������
	for (int nCntNumber = 0; nCntNumber < ENEMY_DIGIT; nCntNumber++)
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
// �G�̐��̍X�V����
//=============================================================================
void CFrogNumber::Update(void)
{
	//�t�F�[�h�̎擾����
	CFade *pFade = CManager::GetFade();
	//���[�h�̎擾
	CResult::COUNT_TYPE type;
	type = CResult::GetType();
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();


	if (type == CResult::COUNT_FROG)
	{
		int nData;
		int nEnemy = 1;

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
		{
			CScore *pScore = CResult::GetScore();
			pScore->AddScore(m_nFrogNumber * 500);
			m_nFrogNumber = 0;
			int nTime = 1;

			for (int nCntTimer = 0; nCntTimer < ENEMY_DIGIT; nCntTimer++)
			{// �^�C�}�[�̌��������J��Ԃ�
				nData = m_nFrogNumber % (nEnemy * 10) / nEnemy;
				m_apNumber[nCntTimer]->SetNumber(nData);
				nEnemy *= 10;
			}
			CResult::SetType(CResult::COUNT_END);
		}

		m_nCountTimer++;
		if (m_nCountTimer % 10 == 0
			&& pFade->GetFade() == CFade::FADE_NONE)
		{// ��b�Ԃ�������
			if (m_nFrogNumber > 0)
			{
				m_nFrogNumber--;
				for (int nCntTimer = 0; nCntTimer < ENEMY_DIGIT; nCntTimer++)
				{// �^�C�}�[�̌��������J��Ԃ�
					nData = m_nFrogNumber % (nEnemy * 10) / nEnemy;
					m_apNumber[nCntTimer]->SetNumber(nData);
					nEnemy *= 10;
				}
				CSound *pSound;
				pSound = CManager::GetSound();

				CScore *pScore = CResult::GetScore();
				pScore->AddScore(500);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_COUNT);
			}
			else
			{
				CResult::SetType(CResult::COUNT_END);
			}
		}
	}
}

//=============================================================================
// �G�̐��̕`�揈��
//=============================================================================
void CFrogNumber::Draw(void)
{
	for (int nCntEnemyNumber = 0; nCntEnemyNumber < ENEMY_DIGIT; nCntEnemyNumber++)
	{
		//�����̕`�揈��
		m_apNumber[nCntEnemyNumber]->Draw();
	}
}