//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "result.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "bg.h"
#include "logo.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CResult::RESULT CResult::m_result = RESULT_NONE;

//=============================================================================
// ���U���g�̃R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_nTimer = 0;
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
	CResult *pResult = NULL;
	if (pResult == NULL)
	{
		pResult = new CResult;
		if (pResult != NULL)
		{
			pResult->Init();
		}
	}
	return pResult;
}

//=============================================================================
// ���U���g�̏���������
//=============================================================================
HRESULT CResult::Init(void)
{
	m_nTimer = 0;

	//�w�i�̓ǂݍ���
	CBgResult::Load();

	//���U���g���S�̓ǂݍ���
	CResultLogo::Load();

	//�w�i�̐���
	CBgResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ,m_result);

	//���U���g���S�̓ǂݍ���
	CResultLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200, 0.0f), 350, 150,m_result);
	return S_OK;
}

//=============================================================================
// ���U���g�̏I������
//=============================================================================
void CResult::Uninit(void)
{
	//�w�i�̔j��
	CBgResult::Unload();

	//���U���g���S�̔j��
	CResultLogo::Unload();

	CScene::ReleaseAll();
}

//=============================================================================
// ���U���g�̍X�V����
//=============================================================================
void CResult::Update(void)
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
		CFade::Create(CManager::MODE_RANKING, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	if (m_nTimer % 600 == 0)
	{
		CFade::Create(CManager::MODE_RANKING, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	}
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