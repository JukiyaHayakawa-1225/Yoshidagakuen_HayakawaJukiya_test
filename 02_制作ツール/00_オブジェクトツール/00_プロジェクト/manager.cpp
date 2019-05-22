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
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "scene3D.h"
#include "sceneX.h"
#include "debugproc.h"
#include "billboard.h"
#include "meshfield.h"
#include "editor.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CManager::MODE	CManager::m_mode = MODE::MODE_GAME;		//���[�h�̏��
CRenderer		*CManager::m_pRenderer = NULL;				//�����_�����O�|�C���^
CInputKeyboard	*CManager::m_pInputKeyboard = NULL;			//�L�[�{�[�h�|�C���^
CInputJoypad	*CManager::m_pInputJoypad = NULL;			//�W���C�p�b�h�|�C���^
CSound			*CManager::m_pSound = NULL;					//�T�E���h�̃|�C���^
CCamera			*CManager::m_pCamera = NULL;				//�J�����̃|�C���^
CLight			*CManager::m_pLight = NULL;					//���C�g�̃|�C���^
CDebugProc		*CManager::m_pDebugproc = NULL;				//�f�o�b�O�̃|�C���^
CTitle			*CManager::m_pTitle = NULL;					//�^�C�g���̃|�C���^
CTutorial		*CManager::m_pTutorial = NULL;				//�`���[�g���A���̃|�C���^
CEditor			*CManager::m_pEditor = NULL;					//�Q�[���̃|�C���^
CResult			*CManager::m_pResult = NULL;				//���U���g�̃|�C���^
CRanking		*CManager::m_pRanking = NULL;				//�����L���O�̃|�C���^
CFade			*CManager::m_pFade = NULL;					//�t�F�[�h�̃|�C���^

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
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_�����O�̓��I�m��
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;			//�����_�����O�̓��I�m��
	}

	//�L�[�{�[�h�̓��I�m��
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;	//�L�[�{�[�h�̓��I�m��
	}

	//�W���C�p�b�h�̓��I�m��
	if (m_pInputJoypad == NULL)
	{
		m_pInputJoypad = new CInputJoypad;		//�W���C�p�b�h�̓��I�m��
	}

	//�T�E���h�̓��I�m��
	//if (m_pSound == NULL)
	//{
	//	m_pSound = new CSound;					//�T�E���h�̓��I�m��
	//}

	//�J�����̓��I�m��
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
	}

	//���C�g�̓��I�m��
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
	}

	//�f�o�b�O�̓��I�m��
	if (m_pDebugproc == NULL)
	{
		m_pDebugproc = new CDebugProc;
	}

	//�����_�����O�̏���������
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, TRUE);
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
	/*if (m_pSound != NULL)
	{
		m_pSound->InitSound(hWnd);
	}*/

	//�J�����̏���������
	if (m_pCamera != NULL)
	{
		m_pCamera->Init();
	}

	//���C�g�̏���������
	if (m_pLight != NULL)
	{
		m_pLight->Init();
	}

	//�f�o�b�O�̏���������
	if (m_pDebugproc != NULL)
	{
		m_pDebugproc->Init();
	}

	//�t�F�[�h�̐���
	m_pFade = CFade::Create();
	//�t�F�[�h�̐ݒu����
	m_pFade->SetFade(m_mode, m_pFade->FADE_IN);
	//���[�h�̐ݒu
	//SetMode(m_mode);

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

	//�t�F�[�h�̏I������
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
	//�T�E���h�̏I������
	//if (m_pSound != NULL)
	//{
	//	m_pSound->UninitSound();
	//	delete m_pSound;
	//	m_pSound = NULL;
	//}

	//�J�����̏I������
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//���C�g�̏I������
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//�f�o�b�O�̏I������
	if (m_pDebugproc != NULL)
	{
		m_pDebugproc->Uninit();
		delete m_pDebugproc;
		m_pDebugproc = NULL;
	}

	if (m_pEditor != NULL)
	{
		//�Q�[���̏I������
		m_pEditor->Uninit();
		//�������̊J��
		delete m_pEditor;
		m_pEditor = NULL;
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
	//�t�F�[�h�̍X�V����
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
	//�J�����̍X�V����
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//���C�g�̍X�V����
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	switch (m_mode)
	{
	case MODE_GAME:					//�Q�[���̏ꍇ
		if (m_pEditor != NULL)
		{
			//�Q�[���̍X�V����
			m_pEditor->Update();
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

	//�J�����̐ݒu����
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// �����_�����O�̎擾
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;	//�l��Ԃ�
}

//=============================================================================
// �L�[�{�[�h�̎擾
//=============================================================================
CInputKeyboard *CManager::GetKeyboard(void)
{
	return m_pInputKeyboard;	//�l��Ԃ�
}

//=============================================================================
// �W���C�p�b�h�̎擾
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
// �J�����̎擾
//=============================================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;				//�l��Ԃ�
}

//=============================================================================
// ���C�g�̎擾
//=============================================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;				//�l��Ԃ�
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;				//�l��Ԃ�
}
//=============================================================================
// ���[�h�̎擾
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;				//�l��Ԃ�
}

//=============================================================================
// ���[�h�̐ݒu
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_GAME:					//�Q�[���̏ꍇ
		if (m_pEditor != NULL)
		{
			//�Q�[���̏I������
			m_pEditor->Uninit();
			//�������̊J��
			delete m_pEditor;
			m_pEditor = NULL;
		}
		break;
	}

	m_mode = mode;	//���

	switch (mode)
	{
	case MODE_GAME:					//�Q�[���̏ꍇ
		if (m_pEditor == NULL)
		{
			//�Q�[���̐���
			m_pEditor = CEditor::Create();
		}
		break;
	}
}