//=============================================================================
//
// �����L���O�̏��� [ranking.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "ranking.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "bg.h"
#include "fade.h"
#include "number.h"
#include "rankingscore.h"
#include "logo.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================


//=============================================================================
// �����L���O�̃R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
	m_nTimer = 0;
}

//=============================================================================
// �����L���O�̃f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// �����L���O�̃f�X�g���N�^
//=============================================================================
CRanking *CRanking::Create()
{
	CRanking *pRanking = NULL;
	if (pRanking == NULL)
	{
		pRanking = new CRanking;
		if (pRanking != NULL)
		{
			pRanking->Init();
		}
	}
	return pRanking;
}

//=============================================================================
// �����L���O�̏���������
//=============================================================================
HRESULT CRanking::Init(void)
{
	m_nTimer = 0;

	//�w�i�̓ǂݍ���
	CBgRanking::Load();
	//�����L���O�����N�̓ǂݎqk��
	CRankingRank::Load();
	//�����̓ǂݍ���
	CNumber::Load();
	//���S�̓ǂݍ���
	CRankingLogo::Load();

	//�����L���O�����N�̐���
	CRankingRank::Create(D3DXVECTOR3(300.0f, SCREEN_HEIGHT / 2  + 225.0f / 2, 0.0f), 125, 270.0f);
	//�X�R�A�̐���
	CRankingScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2- 100, 0.0f),50.0f, 50.0f);

	//�w�i�̐���
	CBgRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//���S�̐���
	CRankingLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f), 400.0f, 100);


	return S_OK;
}

//=============================================================================
// �����L���O�̏I������
//=============================================================================
void CRanking::Uninit(void)
{
	//���S�̔j��
	CRankingLogo::Unload();
	//�����̔j��
	CNumber::Unload();
	//�����L���O�����N�̔j��
	CRankingRank::Unload();
	//�w�i�̔j��
	CBgRanking::Unload();

	CScene::ReleaseAll();
}

//=============================================================================
// �����L���O�̍X�V����
//=============================================================================
void CRanking::Update(void)
{
	m_nTimer++;
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	if (pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_X) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_Y) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LB) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_RB) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LT) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_RT) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_BACK) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true ||
		pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{// JoyPad�̃{�^���܂���ENTER�L�[�������ꂽ�ꍇ
		CFade::Create(CManager::MODE_TITLE, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	if (m_nTimer % 600 == 0)
	{
		CFade::Create(CManager::MODE_TITLE, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

//=============================================================================
// �����L���O�̕`�揈��
//=============================================================================
void CRanking::Draw(void)
{
}