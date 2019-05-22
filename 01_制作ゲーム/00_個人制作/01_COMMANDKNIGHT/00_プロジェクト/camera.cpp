//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_MOVE (1.0f);	//�J�����̈ړ���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �J�����R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{

}

//=============================================================================
// �J�����f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// �J�����̐���
//=============================================================================
CCamera *CCamera::Create()
{
	CCamera *pCamera = NULL;	//�J�����̃|�C���^

	if (pCamera == NULL)
	{//NULL�łȂ��ꍇ
		pCamera = new CCamera;	//�J�����̓��I�m��
		pCamera->Init();		//����������
	}
	return pCamera;
}

//=============================================================================
// �J�����̏���������
//=============================================================================
HRESULT CCamera::Init(void)
{
	//���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	//���[�h���Ƃ̏���������
	switch (mode)
	{
	case CManager::MODE_TITLE:	//�^�C�g���̏ꍇ
		m_posV = D3DXVECTOR3(600.0f, 60.0f, -1200.0f);						//���_
		m_posR = D3DXVECTOR3(600.0f, 40.0f, -1000.0f);						//�����_

		break;
	case CManager::MODE_TUTORIAL:	//�^�C�g���̏ꍇ
		m_posV = D3DXVECTOR3(600.0f, 60.0f, -1200.0f);						//���_
		m_posR = D3DXVECTOR3(600.0f, 40.0f, -1000.0f);						//�����_

		break;
	case CManager::MODE_GAME:	//�Q�[���̏ꍇ
		m_posV = D3DXVECTOR3(0.0f, 100.0f, -150.0f);						//���_
		m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//�����_

		break;
	case CManager::MODE_RESULT:	//�Q�[���̏ꍇ
		m_posV = D3DXVECTOR3(600.0f, 60.0f, -1200.0f);						//���_
		m_posR = D3DXVECTOR3(600.0f, 40.0f, -1000.0f);						//�����_

		break;
	case CManager::MODE_RANKING:	//�����L���O�̏ꍇ
		m_posV = D3DXVECTOR3(600.0f, 100.0f, -900.0f);						//���_
		m_posR = D3DXVECTOR3(600.0f, 60.0f, -700.0f);								//�����_

		break;
	}

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);								//������x�N�g��
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�ړI�̎��_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�ړI�̒����_
	m_rot.y =atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z) ;			//����
	m_rotDest = m_rot;													//�ړI�̌���
	m_rotDiff = 0.0f;
	m_fLength = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));	//����

	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	//���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	if (mode == CManager::MODE_GAME)
	{//�Q�[���̏ꍇ
		//�v���C���[�̎擾
		CPlayer *pPlayer;
		pPlayer = CGame::GetPlayer();

		if (pPlayer != NULL)
		{//NULL�łȂ��ꍇ
			//�v���C���[�̈ʒu�̎擾
			D3DXVECTOR3 playerpos = pPlayer->GetPos();
			//�v���C���[�̌����̎擾
			D3DXVECTOR3 playerrot = pPlayer->GetRot();

			//�ǔ�����
			m_posVDest.x = playerpos.x + sinf(m_rot.y) * -m_fLength;
			m_posVDest.y = (playerpos.y + 100.0f) /*+ m_eyepoint*/;
			m_posVDest.z = playerpos.z + cosf(m_rot.y) * -m_fLength;

			m_posRDest.x = playerpos.x - sinf(playerrot.y) * 1.0f;
			m_posRDest.y = (playerpos.y + 50.0f);
			m_posRDest.z = playerpos.z - cosf(playerrot.y) * 1.0f;

			m_posV.x += (m_posVDest.x - m_posV.x) * 0.4f;
			m_posV.y += (m_posVDest.y - m_posV.y) * 0.4f;
			m_posV.z += (m_posVDest.z - m_posV.z) * 0.4f;

			m_posR.x += (m_posRDest.x - m_posR.x) * 0.4f;
			m_posR.y += (m_posRDest.y - m_posR.y) * 0.4f;
			m_posR.z += (m_posRDest.z - m_posR.z) * 0.4f;

		}
		//�L�[�{�[�h�̎擾
		CInputKeyboard *pInputKeyboard;
		pInputKeyboard = CManager::GetKeyboard();

		//�W���C�p�b�h�̎擾
		CInputJoypad *pInputJoypad;
		pInputJoypad = CManager::GetJoypad();

		if (pInputKeyboard->GetPress(DIK_Z) == true ||
			pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_RSTICK_LEFT) == true)
		{// �L�[�{�[�h��[Z]�L�[�������ꂽ
			m_rot.y += 0.025f;
			if (m_rot.y >= D3DX_PI)
			{
				m_rot.y = -D3DX_PI;
			}
			m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
			m_posV.z = m_posR.z - cosf(m_rot.y) *m_fLength;
		}
		if (pInputKeyboard->GetPress(DIK_C) == true||
			pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_RSTICK_RIGHT) == true)
		{// �L�[�{�[�h��[C]�L�[�������ꂽ
			m_rot.y -= 0.025f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y = D3DX_PI;
			}
			m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
			m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
		}

	}
		////�L�[�{�[�h�̎擾
		//CInputKeyboard *pInputKeyboard;
		//pInputKeyboard = CManager::GetKeyboard();

		//if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
		//{// �L�[�{�[�h��[��]�L�[�������ꂽ
		//	m_posR.x += 2.0f;
		//	m_posV.x += 2.0f;
		//}
		//if (pInputKeyboard->GetPress(DIK_LEFT) == true)
		//{// �L�[�{�[�h��[��]�L�[�������ꂽ
		//	m_posR.x -= 2.0f;
		//	m_posV.x -= 2.0f;
		//}
		//if (pInputKeyboard->GetPress(DIK_UP) == true)
		//{// �L�[�{�[�h��[��]�L�[�������ꂽ
		//	m_posR.z += 2.0f;
		//	m_posV.z += 2.0f;
		//}
		//if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		//{// �L�[�{�[�h��[��]�L�[�������ꂽ
		//	m_posR.z -= 2.0f;
		//	m_posV.z -= 2.0f;
		//}
		////===================================================
		////�@�J�����̒����_����
		////===================================================
		//if (pInputKeyboard->GetPress(DIK_T) == true)
		//{// �L�[�{�[�h��[T]�L�[�������ꂽ
		//	m_posR.y += 2.0f;
		//}
		//if (pInputKeyboard->GetPress(DIK_B) == true)
		//{// �L�[�{�[�h��[B]�L�[�������ꂽ
		//	m_posR.y -= 2.0f;
		//}
		//if (pInputKeyboard->GetPress(DIK_Q) == true)
		//{// �L�[�{�[�h��[Q]�L�[�������ꂽ�i�����ɐ���j
		//	m_rot.y -= 0.025f;
		//	if (m_rot.y <= -D3DX_PI)
		//	{
		//		m_rot.y = D3DX_PI;
		//	}
		//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
		//}
		//if (pInputKeyboard->GetPress(DIK_E) == true)
		//{// �L�[�{�[�h��[E]�L�[�������ꂽ
		//	m_rot.y += 0.025f;
		//	if (m_rot.y >= D3DX_PI)
		//	{
		//		m_rot.y = -D3DX_PI;
		//	}
		//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
		//}

		////===================================================
		////�@�J�����̎��_����
		////===================================================
		//if (pInputKeyboard->GetPress(DIK_Y) == true)
		//{// �L�[�{�[�h��[Y]�L�[�������ꂽ
		//	m_posV.y += 2.0f;
		//}
		//if (pInputKeyboard->GetPress(DIK_N) == true)
		//{// �L�[�{�[�h��[N]�L�[�������ꂽ
		//	m_posV.y -= 2.0f;
		//}
		//if (pInputKeyboard->GetPress(DIK_Z) == true)
		//{// �L�[�{�[�h��[Z]�L�[�������ꂽ
		//	m_rot.y += 0.025f;
		//	if (m_rot.y >= D3DX_PI)
		//	{
		//		m_rot.y = -D3DX_PI;
		//	}
		//	m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
		//	m_posV.z = m_posR.z - cosf(m_rot.y) *m_fLength;
		//}
		//if (pInputKeyboard->GetPress(DIK_C) == true)
		//{// �L�[�{�[�h��[C]�L�[�������ꂽ
		//	m_rot.y -= 0.025f;
		//	if (m_rot.y <= -D3DX_PI)
		//	{
		//		m_rot.y = D3DX_PI;
		//	}
		//	m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
		//	m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
		//}


	//�����_�̕\��
	CDebugProc::Print(1, "���_�̈ړ�    : x[%.1f],y[%.1f],z[%.1f]\n", m_posV.x, m_posV.y, m_posV.z);
	//���_�̕\��
	CDebugProc::Print(1, "�����_�̈ړ�  : x[%.1f],y[%.1f],z[%.1f]\n", m_posR.x, m_posR.y, m_posR.z);
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),						//��p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//��ʔ䗦
		10.0f,										//��O
		1500.0f);									//���s��	�ύX����1000

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
				       &m_posV,
					   &m_posR,
					   &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}


//=============================================================================
// �J�����̌����擾
//=============================================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}