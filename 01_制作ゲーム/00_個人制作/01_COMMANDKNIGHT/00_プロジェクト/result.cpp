//=============================================================================
//
// ���U���g���� [manager.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "result.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "fade.h"
#include "score.h"
#include "number.h"
#include "timer.h"
#include "map.h"
#include "meshfield.h"
#include "logo.h"
#include "enemynumber.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CResult::RESULT CResult::m_result = RESULT_NONE;		//���U���g�̃|�C���^
CScore			*CResult::m_pScore = NULL;				//�X�R�A�̃|�C���^���
CTimer			*CResult::m_pTimer = NULL;				//�^�C�}�[�̃|�C���^���
CMap			*CResult::m_pMap = NULL;				//�}�b�v�̃|�C���^���
CBirdNumber	*CResult::m_pBirdNumber = NULL;				//�������|�C���^���
CFrogNumber	*CResult::m_pFrogNumber = NULL;				//�����鐔���|�C���^���
CResult::COUNT_TYPE CResult::m_type = COUNT_TIMER;		//

//=============================================================================
// ���U���g�̃R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_nTimer = 0;			//�^�C�}�[�̏����l
	m_pScore = NULL;		//�X�R�A��������
	m_pBirdNumber = NULL;	//�������̏�����
	m_pFrogNumber = NULL;	//�����鐔���̏�����
	m_type = COUNT_TIMER;
}

//=============================================================================
// ���U���g�̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ���U���g�̃f�X�g���N�^
//=============================================================================
CResult *CResult::Create()
{
	CResult *pResult = NULL;	//���U���g�̃|�C���^
	if (pResult == NULL)
	{
		pResult = new CResult;	//���I�m��
		if (pResult != NULL)
		{
			pResult->Init();	//����������
		}
	}
	return pResult;
}

//=============================================================================
// ���U���g�̏���������
//=============================================================================
HRESULT CResult::Init(void)
{
	//���U���g���S�̓ǂݍ���
	CResultLogo::Load();
	//���U���g�X�R�A���S�̓ǂݍ���
	CResultScoreLogo::Load();
	//�����̓ǂݍ���
	CNumber::Load();

	//���U���g���S�̐���
	CResultLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 75.0f, 0.0f), 250.0f, 75.0f);
	//���U���g�X�R�A���S�̓ǂݍ���
	CResultScoreLogo::Create(D3DXVECTOR3(300.0f, 325.0f, 0.0f), 200.0f, 200.0f);

	//�}�b�v�𐶐�
	m_pMap = CMap::Create();
	//���b�V���t�B�[���h�̐���
	CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_nTimer = 0;	//�^�C�}�[�̏���������
	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f,600.0f, 0.0f), 40.0f, 40.0f);
	//�X�R�A���擾�����Z
	m_pScore->AddScore(CManager::GetScore());
	//�^�C�}�[�̐���
	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, 200.0f, 0.0f), 40.0f, 40.0f);

	m_pBirdNumber = CBirdNumber::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, 330.0f, 0.0f), 40.0f, 40.0f);
	m_pFrogNumber = CFrogNumber::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, 450.0f, 0.0f), 40.0f, 40.0f);
	return S_OK;
}

//=============================================================================
// ���U���g�̏I������
//=============================================================================
void CResult::Uninit(void)
{
	//�����̔j��
	CNumber::Unload();
	//���U���g�X�R�A���S�̔j��
	CResultScoreLogo::Unload();
	//���U���g���S�̔j��
	CResultLogo::Unload();

	//�}�b�v�̏I������
	if (m_pMap != NULL)
	{
		m_pMap->Uninit();
		delete m_pMap;
		m_pMap = NULL;
	}

	//�S�ẴI�u�W�F�N�g�J��
	CScene::ReleaseAll();
}

//=============================================================================
// ���U���g�̍X�V����
//=============================================================================
void CResult::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();
	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();
	//�t�F�[�h�̎擾����
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
	{
		if (m_type == COUNT_END && pFade->GetFade() == CFade::FADE_NONE)
		{//Enter�L�[�����������ꍇ
			//�����L���O�֑J��
			pFade->SetFade(CManager::MODE_RANKING, pFade->FADE_OUT);
			CManager *pManager = NULL;
			pManager->SetGameScore(m_pScore->GetScore());
		}
	}

	m_nTimer++;	//�^�C�}�[�̉��Z
	if (m_nTimer >= 1500 && pFade->GetFade() == CFade::FADE_NONE)
	{//�^�C�}�[���P�T�O�O�ȏ�̏ꍇ
		//�X�R�A�̐ݒu����
		CManager *pManager = NULL;
		pManager->SetGameScore(m_pScore->GetScore());
		//�����L���O�ɉ�ʑJ��
		pFade->SetFade(CManager::MODE_RANKING, pFade->FADE_OUT);


	}
	//�f�o�b�O�\��
	CDebugProc::Print(1, "Result");
}

//=============================================================================
// ���U���g�̕`�揈��
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// ���U���g�̐ݒu����
//=============================================================================
void CResult::SetResult(RESULT result)
{
	m_result = result;
}
//=============================================================================
// ���U���g�̎擾����
//=============================================================================
CResult::RESULT CResult::GetResult(void)
{
	return m_result;
}

//=============================================================================
// ��Ԃ̐ݒu
//=============================================================================
void CResult::SetType(COUNT_TYPE type)
{
	m_type = type;
}

//=============================================================================
// ��Ԃ̎擾
//=============================================================================
CResult::COUNT_TYPE CResult::GetType(void)
{
	return m_type;
}
//=============================================================================
// �R�}���h�̎擾
//=============================================================================
CScore * CResult::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �R�}���h�̎擾
//=============================================================================
CBirdNumber * CResult::GetBirdNumber(void)
{
	return m_pBirdNumber;
}

//=============================================================================
// �R�}���h�̎擾
//=============================================================================
CFrogNumber * CResult::GetFrogNumber(void)
{
	return m_pFrogNumber;
}