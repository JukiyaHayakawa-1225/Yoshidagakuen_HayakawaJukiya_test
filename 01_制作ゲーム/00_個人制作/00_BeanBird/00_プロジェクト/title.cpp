//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "title.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "bg.h"
#include "fade.h"
#include "pressenter.h"
#include "logo.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================


//=============================================================================
// �^�C�g���̃R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_nTimer = 0;
}

//=============================================================================
// �^�C�g���̃f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// �^�C�g���̃f�X�g���N�^
//=============================================================================
CTitle *CTitle::Create()
{
	CTitle *pTitle = NULL;
	if (pTitle == NULL)
	{
		pTitle = new CTitle;
		if (pTitle != NULL)
		{
			pTitle->Init();
		}
	}
	return pTitle;
}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTitle::Init(void)
{
	//�^�C�}�[������
	m_nTimer = 0;

	//�w�i�̓ǂݍ���
	CBgTitle::Load();

	//�v���X�G���^�[�̓ǂݍ���
	CPressEnter::Load();

	//�^�C�g�����S�̓ǂݍ���
	CTitleLogo::Load();

	//�v���X�G���^�[�̐���
	CPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 0.0f), 300, 75);
	//�w�i�̐���
	CBgTitle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//�^�C�g�����S�̐���
	CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 175, 0.0f), 500, 175);

	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�^�C�g�����S�̔j��
	CTitleLogo::Unload();

	//�w�i�̔j��
	CBgTitle::Unload();

	//�v���X�G���^�[�̔j��
	CPressEnter::Unload();

	CScene::ReleaseAll();
}

//=============================================================================
// �^�C�g���̍X�V����
//=============================================================================
void CTitle::Update(void)
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
		CFade::Create(CManager::MODE_TUTORIAL, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	if (m_nTimer % 800 == 0)
	{
		CFade::Create(CManager::MODE_RANKING, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}