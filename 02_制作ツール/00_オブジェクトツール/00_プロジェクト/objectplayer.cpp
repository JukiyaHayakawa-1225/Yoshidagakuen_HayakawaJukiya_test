//=============================================================================
//
// �I�u�W�F�N�g�v���C���[�̏��� [objectplayer.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "objectplayer.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "debugproc.h"
#include "scene3D.h"
#include "meshfield.h"
#include "model.h"
#include "editor.h"
#include "object.h"
#include "loadfilefunction.h"
#include "map.h"
#include "modelcreate.h"
#include "object.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CObject *CObjectPlayer::m_pObject = NULL;	//�I�u�W�F�N�g�̃|�C���^���

//=============================================================================
// �v���C���[�̃R���X�g���N�^
//=============================================================================
CObjectPlayer::CObjectPlayer() : CObject(3,OBJTYPE_OBJECT)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu�̏����l
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����̏����l
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		//�傫��
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ��ʂ̏����l
	m_pObject = NULL;								//�I�u�W�F�N�g�̃|�C���^��������
	m_pCreateObject = NULL;
	m_nSeletObject = 0;
	m_fSpeed = 50.0f;
}
//=============================================================================
// �v���C���[�̃f�X�g���N�^
//=============================================================================
CObjectPlayer::~CObjectPlayer()
{

}

//=============================================================================
//�v���C���[�̐���
//=============================================================================
CObjectPlayer *CObjectPlayer::Create(D3DXVECTOR3 pos)
{
	CObjectPlayer *pObjectPlayer = NULL;					//�v���C���[�̃|�C���^
	if (pObjectPlayer == NULL)
	{
		pObjectPlayer = new CObjectPlayer;					//�V�[���̓��I�m��
		pObjectPlayer->m_pos = pos;							//�ʒu�̐ݒu����
		pObjectPlayer->Init();								//����������
	}
	return pObjectPlayer;									//�l��Ԃ�
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CObjectPlayer::Init(void)
{
	m_nSeletObject = 0;

	if (m_pObject == NULL)
	{
		CMap *pMap = NULL;
		if (pMap == NULL)
		{
			m_pObject = CObject::Create(m_pos,m_rot,m_scale,true,true);
			if (m_pObject != NULL)
			{
				m_pObject->BindX(pMap->GetCModelCreate()->GetMesh(m_nSeletObject), pMap->GetCModelCreate()->GetBuffMat(m_nSeletObject), pMap->GetCModelCreate()->GetNumMat(m_nSeletObject));
				m_pObject->SetObjType(OBJTYPE_PLAYER);
			}
		}
	}
	SetObjType(OBJTYPE_PLAYER);
	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CObjectPlayer::Uninit(void)
{
	//for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	//{//���f���̐������J��Ԃ�
	//	if (m_apModel[nCntModel] != NULL)
	//	{
	//		//�I������
	//		m_apModel[nCntModel]->Uninit();
	//		delete m_apModel[nCntModel];
	//		m_apModel[nCntModel] = NULL;
	//	}
	//}

	//if (m_pObject != NULL)
	//{
	//	m_pObject->Uninit();
	//	delete m_pObject;
	//	m_pObject = NULL;
	//}


	Release();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CObjectPlayer::Update(void)
{
	//�ړ�����
	Move();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

#ifdef _DEBUG
	CDebugProc::Print(1, "���f���̈ʒu  : x[%.1f],y[%.1f],z[%.1f]\n", m_pos.x, m_pos.y, m_pos.z);
#endif
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CObjectPlayer::Draw(void)
{
	////�����_�����O�̎擾
	//CRenderer *pRenderer;
	//pRenderer = CManager::GetRenderer();

	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice;
	//pDevice = pRenderer->GetDevice();

	//D3DXMATRIX mtxRot, mtxTrans, mtxScale;					//�v�Z�p�}�g���b�N�X

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&m_mtxWorld);

	//// ��]�𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot,
	//	m_rot.y, m_rot.x, m_rot.z);

	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//// �傫���̔��f
	//D3DXMatrixScaling(&mtxScale,
	//	m_scale.x, m_scale.y, m_scale.z);

	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//// ��]�𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
	//	m_rot.x,
	//	m_rot.z);

	//D3DXMatrixMultiply(&m_mtxWorld,
	//	&m_mtxWorld,
	//	&mtxRot);

	//// �ړ��𔽉f
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//D3DXMATRIX	mtxShadow;		//�V���h�E�}�g���b�N�X
	//D3DXPLANE	planeField;		//���ʏ��
	//D3DXVECTOR4 vecLight;		//���C�g���
	//D3DXVECTOR3	pos, normal;	//�ʒu�A�@��

	////���Z�����̐ݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP,
	//	D3DBLENDOP_REVSUBTRACT);
	//pDevice->SetRenderState(D3DRS_SRCBLEND,
	//	D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND,
	//	D3DBLEND_ONE);

	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////�V���h�E�}�g���b�N�X��������
	//D3DXMatrixIdentity(&mtxShadow);

	////���C�g�̐ݒ�
	//vecLight = D3DXVECTOR4(0.25f, 0.87f, -0.44f, 0.0f);

	////�ʒu�̐ݒ�
	//pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	////�@���̐ݒ�
	//normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	////�ʒu�Ɩ@�����畽�ʂ��쐬����
	//D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	////���ʂ̎ˉe
	//D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	////���[���h�}�g���b�N�X�Ɗ|�����킹��
	//D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	////���̐ݒ�ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP,
	//	D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND,
	//	D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND,
	//	D3DBLEND_INVSRCALPHA);
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//// �}�e���A���f�[�^�ւ̃|�C���^���擾
	//CMap *pMap = NULL;
	//if (pMap == NULL)
	//{
	//	D3DXMATERIAL *pMat = (D3DXMATERIAL*)pMap->GetCModelCreate()->GetBuffMat(m_nSeletObject)->GetBufferPointer();
	//	pMat->MatD3D.Diffuse.a = 0.4f;
	//}
	if (m_pObject != NULL)
	{
		m_pObject->Draw();
	}
	if (m_pCreateObject != NULL)
	{
		m_pCreateObject->Draw();
	}
}

//=============================================================================
// �I�u�W�F�N�g�̑I���擾
//=============================================================================
int CObjectPlayer::GetSelectObject(void)
{
	return m_nSeletObject;
}

//=============================================================================
// �I�u�W�F�N�g�̈ړ��X�s�[�h�擾
//=============================================================================
float CObjectPlayer::GetSpeed(void)
{
	return m_fSpeed;
}

//=============================================================================
// �I�u�W�F�N�g�̈ړ��X�s�[�h�ݒu����
//=============================================================================
void CObjectPlayer::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

//=============================================================================
// �I�u�W�F�N�g�̑I��ݒu����
//=============================================================================
void CObjectPlayer::SetSelectObject(int nSelect)
{
	//m_nSeletObject = nSelect;

	CMap *pMap = NULL;	//�}�b�v�̃|�C���^
	if (pMap == NULL)
	{
		m_nNumModel = pMap->GetCModelCreate()->GetNumModel();
		//m_nSeletObject = (m_nSeletObject + nSelect) % m_nNumModel;
		if (nSelect < m_nNumModel && nSelect >= 0)
		{
			m_nSeletObject = nSelect;
			m_pObject->BindX(pMap->GetCModelCreate()->GetMesh(m_nSeletObject), pMap->GetCModelCreate()->GetBuffMat(m_nSeletObject), pMap->GetCModelCreate()->GetNumMat(m_nSeletObject));
		}
	}

}

//=============================================================================
// �I�u�W�F�N�g�̏��擾
//=============================================================================
CObject *CObjectPlayer::GetObjectPointer(void)
{
	return m_pObject;
}
//=============================================================================
// �v���C���[�̈ړ�����
//=============================================================================
void CObjectPlayer::Move(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//�J�����̎擾
	CCamera *pCamera;
	pCamera = CManager::GetCamera();
	//�J�����̌����擾
	D3DXVECTOR3 cameraRot = pCamera->GetRot();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	D3DXVECTOR3 pos = m_pObject->GetPos();
	D3DXVECTOR3 rot = m_pObject->GetRot();
	D3DXVECTOR3 size = m_pObject->GetSize();
	bool bHit = m_pObject->GetHit();
	bool bDestroy = m_pObject->GetDestroy();

	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		CMap *pMap = NULL;	//�}�b�v�̃|�C���^
		if (pMap == NULL)
		{
			m_nNumModel = pMap->GetCModelCreate()->GetNumModel();
			m_nSeletObject = (m_nSeletObject + (m_nNumModel - 1)) % m_nNumModel;
			m_pObject->BindX(pMap->GetCModelCreate()->GetMesh(m_nSeletObject), pMap->GetCModelCreate()->GetBuffMat(m_nSeletObject), pMap->GetCModelCreate()->GetNumMat(m_nSeletObject));
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{
		CMap *pMap = NULL;	//�}�b�v�̃|�C���^
		if (pMap == NULL)
		{
			m_nNumModel = pMap->GetCModelCreate()->GetNumModel();
			m_nSeletObject = (m_nSeletObject + 1) % m_nNumModel;
			m_pObject->BindX(pMap->GetCModelCreate()->GetMesh(m_nSeletObject), pMap->GetCModelCreate()->GetBuffMat(m_nSeletObject), pMap->GetCModelCreate()->GetNumMat(m_nSeletObject));
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		CMap *pMap = NULL;
		if (pMap == NULL)
		{
			m_pCreateObject = CObject::Create(pos, rot, size,bHit,bDestroy);
			m_pCreateObject->BindX(pMap->GetCModelCreate()->GetMesh(m_nSeletObject), pMap->GetCModelCreate()->GetBuffMat(m_nSeletObject), pMap->GetCModelCreate()->GetNumMat(m_nSeletObject));
			m_pCreateObject->SetType(m_nSeletObject);
		}
	}

	//if (pInputKeyboard->GetTrigger(DIK_A) == true)
	//{// �L�[�{�[�h��[A]�L�[�������ꂽ�i���ړ��j
	//	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	//	{// �L�[�{�[�h��[W]�L�[�������ꂽ�i����ړ��j
	//		m_pos.x += -sinf(cameraRot.y + D3DX_PI * 0.75f) * 50.0f;
	//		m_pos.z += -cosf(cameraRot.y + D3DX_PI * 0.75f) * 50.0f;
	//	}
	//	else if (pInputKeyboard->GetTrigger(DIK_S) == true)
	//	{// �L�[�{�[�h��[S]�L�[�������ꂽ�i�����ړ��j
	//		m_pos.x += -sinf(cameraRot.y + D3DX_PI * 0.25f) * 50.0f;
	//		m_pos.z += -cosf(cameraRot.y + D3DX_PI * 0.25f) * 50.0f;
	//	}
	//	else
	//	{// �L�[�{�[�h��[A]�L�[�������ꂽ�i���ړ��j
	//		m_pos.x += -sinf(cameraRot.y + D3DX_PI / 2) * 50.0f;
	//		m_pos.z += -cosf(cameraRot.y + D3DX_PI / 2) * 50.0f;
	//	}
	//}
	//else if (pInputKeyboard->GetTrigger(DIK_D) == true)
	//{// �L�[�{�[�h��[D]�L�[�������ꂽ�i�E�ړ��j
	//	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	//	{// �L�[�{�[�h��[W]�L�[�������ꂽ�i�E��ړ��j
	//		m_pos.x += -sinf(cameraRot.y + D3DX_PI * -0.75f) * 50.0f;
	//		m_pos.z += -cosf(cameraRot.y + D3DX_PI * -0.75f) * 50.0f;
	//	}
	//	else if (pInputKeyboard->GetTrigger(DIK_S) == true)
	//	{// �L�[�{�[�h��[S]�L�[�������ꂽ�i�E���ړ��j
	//		m_pos.x += -sinf(cameraRot.y + D3DX_PI * -0.25f) * 50.0f;
	//		m_pos.z += -cosf(cameraRot.y + D3DX_PI * -0.25f) * 50.0f;
	//	}
	//	else
	//	{// �L�[�{�[�h��[D]�L�[�������ꂽ�i�E�ړ��j
	//		m_pos.x += -sinf(cameraRot.y + D3DX_PI / -2) * 50.0f;
	//		m_pos.z += -cosf(cameraRot.y + D3DX_PI / -2) * 50.0f;
	//	}
	//}
	//else if (pInputKeyboard->GetTrigger(DIK_W) == true)
	//{//�L�[�{�[�h��[W]�L�[�������ꂽ�i�O�ړ��j
	//	m_pos.x -= sinf(cameraRot.y + D3DX_PI * 1)*50.0f;
	//	m_pos.z -= cosf(cameraRot.y + D3DX_PI * 1)*50.0f;
	//}
	//else if (pInputKeyboard->GetTrigger(DIK_S) == true)
	//{//�L�[�{�[�h��[S]�L�[�������ꂽ�i��ړ��j
	//	m_pos.x += -sinf(cameraRot.y + D3DX_PI * 0)*50.0f;
	//	m_pos.z += -cosf(cameraRot.y + D3DX_PI * 0)*50.0f;
	//}

	if (pInputKeyboard->GetTrigger(DIK_F) == true)
	{//
		rot.y += 0.785f;
	}
	if (pInputKeyboard->GetTrigger(DIK_G) == true)
	{//
		rot.y -= 0.785f;
	}
	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	{
		pos.z += m_fSpeed;
	}
	else if (pInputKeyboard->GetTrigger(DIK_S) == true)
	{
		pos.z -= m_fSpeed;
	}
	else if (pInputKeyboard->GetTrigger(DIK_A) == true)
	{
		pos.x -= m_fSpeed;
	}
	else if(pInputKeyboard->GetTrigger(DIK_D) == true)
	{
		pos.x += m_fSpeed;
	}
	//�ʒu�̐ݒu����
	m_pObject->SetPos(pos);
	m_pObject->SetRot(rot);
	//m_pObject->SetRot(m_rot);
	//�d��
	//m_move.y -= cosf(D3DX_PI * 0) * 0.5f;

	//�ړ����Z����
	//m_pos.y += m_move.y;

#ifdef _DEBUG
	CDebugProc::Print(1,"%d\n", m_nSeletObject);
	CDebugProc::Print(1, "%f\n", rot.y);
	CDebugProc::Print(1, "��ނ̐؂�ւ�[1,2] ���f���̐ݒu[3] ���f���̕ۑ�[F2]\n");
#endif
}