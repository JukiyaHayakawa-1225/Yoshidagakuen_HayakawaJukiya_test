//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "tutorial.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "bg.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================


//=============================================================================
// �`���[�g���A���̃R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{

}

//=============================================================================
// �`���[�g���A���̃f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// �`���[�g���A���̐���
//=============================================================================
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;
	if (pTutorial == NULL)
	{
		pTutorial = new CTutorial;
		if (pTutorial != NULL)
		{
			pTutorial->Init();
		}
	}
	return pTutorial;
}

//=============================================================================
// �`���[�g���A���̏���������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	m_counter = 0;
	//�w�i�̓ǂݍ���
	CBgTutorial::Load();

	//�w�i�̐���
	CBgTutorial::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,CBgTutorial::BG_0);
	//CBgTutorial::Create(D3DXVECTOR3(SCREEN_WIDTH + 640, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CBgTutorial::BG_1);

	return S_OK;
}

//=============================================================================
// �`���[�g���A���̏I������
//=============================================================================
void CTutorial::Uninit(void)
{
	//�w�i�̔j��
	CBgTutorial::Unload();

	CScene::ReleaseAll();
}

//=============================================================================
// �`���[�g���A���̍X�V����
//=============================================================================
void CTutorial::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	CBgTutorial *pTutorial = NULL;

	if (pTutorial->GetTutorialState() == CBgTutorial::STATE_NOMAL &&
		m_counter == 0)
	{
		if (pInputKeyboard->GetTrigger(DIK_D) == true||
			pInputKeyboard->GetTrigger(DIK_RIGHT) == true||
			pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LSTICK_RIGHT) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_RIGHT) == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SLIDE);
			m_counter++;
			CBgTutorial::SetTutorialState(CBgTutorial::STATE_MOVE);
		}
	}
	else if (pTutorial->GetTutorialState() == CBgTutorial::STATE_NOMAL &&
		m_counter == 1)
	{
		if (pInputKeyboard->GetTrigger(DIK_A) == true ||
			pInputKeyboard->GetTrigger(DIK_LEFT) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LSTICK_LEFT) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LEFT) == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SLIDE);

			m_counter--;
			CBgTutorial::SetTutorialState(CBgTutorial::STATE_REMOVE);
		}
	}
	if (m_counter == 1)
	{
		if (pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true ||
			pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{// JoyPad�̃{�^���܂���ENTER�L�[�������ꂽ�ꍇ]
			pSound->PlaySound(CSound::SOUND_LABEL_SE_KETTEI);

			CFade::Create(CManager::MODE_GAME, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
		}
	}
}

//=============================================================================
// �`���[�g���A���̕`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}