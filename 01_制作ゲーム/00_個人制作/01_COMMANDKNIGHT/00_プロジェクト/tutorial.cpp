//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "tutorial.h"
#include "scene.h"
#include "scene3D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "sound.h"
#include "debugproc.h"
#include "fade.h"
#include "meshfield.h"
#include "logo.h"
#include "pressenter.h"

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
	CTutorial *pTutorial = NULL;	//�`���[�g���A���̃|�C���^
	if (pTutorial == NULL)
	{
		pTutorial = new CTutorial;	//���I�m��
		if (pTutorial != NULL)
		{
			pTutorial->Init();		//����������
		}
	}
	return pTutorial;
}

//=============================================================================
// �`���[�g���A���̏���������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//�`���[�g���A�����S�̓ǂݍ���
	CTutorialLogo::Load();

	//�v���X�G���^�[�̓ǂݍ���
	//CPressEnter::Load();

	//�v���X�G���^�[�̐���
	//CPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 0.0f), 300, 75);

	//�`���[�g���A�����S�̐���
	CTutorialLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//���b�V���t�B�[���h�̐���
	CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_ntimer = 0;
	return S_OK;
}

//=============================================================================
// �`���[�g���A���̏I������
//=============================================================================
void CTutorial::Uninit(void)
{
	//�v���X�G���^�[�̔j��
	//CPressEnter::Unload();

	//�`���[�g���A���̔j��
	CTutorialLogo::Unload();
	//�S�ẴI�u�W�F�N�g�J��
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

	//�t�F�[�h�̎擾����
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
	{//Enter�L�[������
		if (pFade->GetFade() == CFade::FADE_NONE)
		{

			//�Q�[���֑J��
			pFade->SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
		}
	}
	/*m_ntimer++;
	if (m_ntimer >= 5)
	{
		pFade->SetFade(CManager::MODE_GAME, pFade->FADE_OUT);

	}*/
	//�f�o�b�O�\��
	CDebugProc::Print(1, "Tutorial");
}

//=============================================================================
// �`���[�g���A���̕`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}