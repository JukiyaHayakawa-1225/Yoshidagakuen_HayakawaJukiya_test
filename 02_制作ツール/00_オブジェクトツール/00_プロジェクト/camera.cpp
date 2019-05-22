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
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_MOVE (3.0f);

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
	CCamera *pCamera = NULL;

	if (pCamera == NULL)
	{
		pCamera = new CCamera;
		pCamera->Init();
	}
	return pCamera;
}

//=============================================================================
// �J�����̏���������
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -150.0f);						//���_
	m_posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);								//�����_
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
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{// �L�[�{�[�h��[A]�L�[�������ꂽ
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{// �L�[�{�[�h��[W]�L�[�������ꂽ(����)
			m_posV.x += -sinf(m_rot.y + D3DX_PI * 0.75f) * CAMERA_MOVE;
			m_posV.z += -cosf(m_rot.y + D3DX_PI * 0.75f) * CAMERA_MOVE;
			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
		}
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{// �L�[�{�[�h��[S]�L�[�������ꂽ(����)
			m_posV.x += -sinf(m_rot.y + D3DX_PI * 0.25f) * CAMERA_MOVE;
			m_posV.z += -cosf(m_rot.y + D3DX_PI * 0.25f) * CAMERA_MOVE;
			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
		}
		else
		{// �L�[�{�[�h��[A]�L�[�������ꂽ(��)
			m_posV.x += -sinf(m_rot.y + D3DX_PI / 2) * CAMERA_MOVE;
			m_posV.z += -cosf(m_rot.y + D3DX_PI / 2) * CAMERA_MOVE;
			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{// �L�[�{�[�h��[D]�L�[�������ꂽ(��)
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{// �L�[�{�[�h��[W]�L�[�������ꂽ(����)
			m_posV.x += -sinf(m_rot.y + D3DX_PI * -0.75f) * CAMERA_MOVE;
			m_posV.z += -cosf(m_rot.y + D3DX_PI * -0.75f) * CAMERA_MOVE;
			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
		}
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{// �L�[�{�[�h��[S]�L�[�������ꂽ(����)
			m_posV.x += -sinf(m_rot.y + D3DX_PI * -0.25f) * CAMERA_MOVE;
			m_posV.z += -cosf(m_rot.y + D3DX_PI * -0.25f) * CAMERA_MOVE;
			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
		}
		else
		{// �L�[�{�[�h��[D]�L�[�������ꂽ(��)
			m_posV.x += sinf(m_rot.y + D3DX_PI / 2) * CAMERA_MOVE;
			m_posV.z += cosf(m_rot.y + D3DX_PI / 2) * CAMERA_MOVE;
			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_UP) == true)
	{// �L�[�{�[�h��[W]�L�[�������ꂽ(�O)
		m_posV.x += sinf(m_rot.y + D3DX_PI * 0.0f) * CAMERA_MOVE;
		m_posV.z += cosf(m_rot.y + D3DX_PI * 0.0f) * CAMERA_MOVE;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
	}
	else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{// �L�[�{�[�h��[S]�L�[�������ꂽ(���)
		m_posV.x += sinf(m_rot.y + D3DX_PI * 1.0f) * CAMERA_MOVE;
		m_posV.z += cosf(m_rot.y + D3DX_PI * 1.0f) * CAMERA_MOVE;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
	}
	//===================================================
	//�@�J�����̒����_����
	//===================================================
	if (pInputKeyboard->GetPress(DIK_T) == true)
	{// �L�[�{�[�h��[T]�L�[�������ꂽ
		m_posR.y += 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_B) == true)
	{// �L�[�{�[�h��[B]�L�[�������ꂽ
		m_posR.y -= 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_Q) == true)
	{// �L�[�{�[�h��[Q]�L�[�������ꂽ�i�����ɐ���j
		m_rot.y -= 0.025f;
		if (m_rot.y <= -D3DX_PI)
		{
			m_rot.y = D3DX_PI;
		}
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
	}
	if (pInputKeyboard->GetPress(DIK_E) == true)
	{// �L�[�{�[�h��[E]�L�[�������ꂽ
		m_rot.y += 0.025f;
		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posR.x = m_posV.x + sinf( m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
	}

	//===================================================
	//�@�J�����̎��_����
	//===================================================
	if (pInputKeyboard->GetPress(DIK_Y) == true)
	{// �L�[�{�[�h��[Y]�L�[�������ꂽ
		m_posV.y += 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_N) == true)
	{// �L�[�{�[�h��[N]�L�[�������ꂽ
		m_posV.y -= 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_Z) == true)
	{// �L�[�{�[�h��[Z]�L�[�������ꂽ
		m_rot.y += 0.025f;
		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
		m_posV.z = m_posR.z - cosf(m_rot.y) *m_fLength;
	}
	if (pInputKeyboard->GetPress(DIK_C) == true)
	{// �L�[�{�[�h��[C]�L�[�������ꂽ
		m_rot.y -= 0.025f;
		if (m_rot.y <= -D3DX_PI)
		{
			m_rot.y = D3DX_PI;
		}
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}

#ifdef _DEBUG
	//�����_�̕\��
	CDebugProc::Print(1, "���_�̈ړ�    : x[%.1f],y[%.1f],z[%.1f]\n", m_posV.x, m_posV.y, m_posV.z);
	//���_�̕\��
	CDebugProc::Print(1, "�����_�̈ړ�  : x[%.1f],y[%.1f],z[%.1f]\n", m_posR.x, m_posR.y, m_posR.z);
#endif
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
		1000.0f);									//���s��	�ύX����1000

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
// �J�����̎��_�擾
//=============================================================================
D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}

//=============================================================================
// �J�����̒����_�擾
//=============================================================================
D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}

//=============================================================================
// �J�����̌����擾
//=============================================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �J�����̎��_�ݒu����
//=============================================================================
void CCamera::SetPosV(D3DXVECTOR3 posV)
{
	m_posV = posV;
}

//=============================================================================
// �J�����̒����_�ݒu����
//=============================================================================
void CCamera::SetPosR(D3DXVECTOR3 posR)
{
	m_posR = posR;
}
