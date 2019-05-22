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
#include "debugproc.h"
#include "meshfield.h"
#include "fade.h"
#include "map.h"
#include "logo.h"
#include "pressenter.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CMap			*CTitle::m_pMap = NULL;					//�}�b�v�̃|�C���^���

//=============================================================================
// �^�C�g���̃R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_pMap = NULL;			//�}�b�v��������
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
	CTitle *pTitle = NULL;	//�^�C�g���̃|�C���^

	if (pTitle == NULL)
	{
		pTitle = new CTitle;	//���I�m��
		if (pTitle != NULL)
		{
			pTitle->Init();		//����������
		}
	}
	return pTitle;
}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTitle::Init(void)
{
	//�^�C�g�����S�̓ǂݍ���
	CTitleLogo::Load();

	//�v���X�G���^�[�̓ǂݍ���
	CPressEnter::Load();

	//�}�b�v�𐶐�
	m_pMap = CMap::Create();

	//�v���X�G���^�[�̐���
	CPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 0.0f), 300, 75);

	//���b�V���t�B�[���h�̐���
	CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�^�C�g�����S�̐���
	CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 175, 0.0f), 500, 175);

	m_ntimer = 0;
	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�v���X�G���^�[�̔j��
	CPressEnter::Unload();

	//�^�C�g�����S�̔j��
	CTitleLogo::Unload();

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
// �^�C�g���̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();
	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//�t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	m_ntimer++;	//�^�C�}�[�̉��Z

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
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//�`���[�g���A���֑J��
			pFade->SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);
		}
	}
	if (m_ntimer >= 800)
	{//�^�C�}�[���W�O�O�ȏ�̏ꍇ
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_RANKING, pFade->FADE_OUT);	//�����L���O�։�ʑJ��
		}
	}
	//�f�o�b�O�\��
	CDebugProc::Print(1, "Title");
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}