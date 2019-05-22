//=============================================================================
//
// �X������ [icicle.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "icicle.h"
#include "sceneX.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CIcicle::m_pMesh = NULL;					//���b�V���ւ̃|�C���^
LPD3DXBUFFER CIcicle::m_pBuffMat = NULL;			//�}�e���A�����ւ̃|�C���^
DWORD CIcicle::m_nNumMat = NULL;					//�}�e���A���̐�
LPDIRECT3DTEXTURE9 CIcicle::m_pTexture = NULL;		//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CIcicle::CIcicle() : CSceneX(3,OBJTYPE_ICICLE)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CIcicle::~CIcicle()
{

}

//=============================================================================
// UI�x�[�X�Q�[�W�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CIcicle::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\icicle.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=============================================================================
// UI�x�[�X�Q�[�W�̃e�N�X�`���j��
//=============================================================================
void CIcicle::Unload(void)
{
	// ���b�V���̊J��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̊J��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

}

//=============================================================================
// �X���̐���
//=============================================================================
CIcicle *CIcicle::Create(D3DXVECTOR3 pos, CIcicle::ICICLE_TYPE Type)
{
	CIcicle *pIcicle = NULL;	//�X���̃|�C���^

	if (pIcicle == NULL)
	{
		pIcicle = new CIcicle;	//�X���̓��I�m��
		pIcicle->Init();		//����������
		pIcicle->m_type = Type;	//��ނ̑��
		
		//��ޕ���
		switch (Type)
		{
		case ICICLE_RIGIHT:		//�E�̕X���̏ꍇ
			pIcicle->SetPos(D3DXVECTOR3(pos.x - 100.0f,pos.y -80.0f, pos.z - 50.0f));	//�ʒu�̐ݒu����
			pIcicle->SetRot(D3DXVECTOR3(0.0f, 0.0f, -0.5f));							//�����̐ݒu����
			break;
		case ICICLE_LEFT:		//���̕X���̏ꍇ
			pIcicle->SetPos(D3DXVECTOR3(pos.x + 100.0f, pos.y - 80.0f, pos.z + 50.0f));	//�ʒu�̐ݒu����
			pIcicle->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.5f));								//�����̐ݒu����
			break;
		}
		pIcicle->BindX(m_pMesh, m_pBuffMat, m_nNumMat);									//���f���̐ݒu����
	}
	return pIcicle;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CIcicle::Init(void)
{
	CSceneX::Init();	//�I�u�W�F�N�gX�̏���������
	m_nCounter = 0;		//�J�E���^�[�̏�����
	SetObjType(OBJTYPE_ICICLE);	//�I�u�W�F�N�g�̎�ސݒu����
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CIcicle::Uninit(void)
{
	//�I�u�W�F�N�gX�̏I������
	CSceneX::Uninit();

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CIcicle::Update(void)
{
	m_nCounter++;	//�J�E���^�[�̉��Z

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�ʒu�̎擾����
	D3DXVECTOR3 pos; 
	pos = GetPos();

	//��ޕ���
	switch (m_type)
	{
	case ICICLE_RIGIHT:	//�E�̕X���̏ꍇ
		if (m_nCounter >= 0 && m_nCounter <= 25)
		{
		pos.x += 3;
		pos.y += 3;
		}
		break;
	case ICICLE_LEFT:	//���̕X���̏ꍇ
		if (m_nCounter >= 0 && m_nCounter <= 25)
		{
			pos.x -= 3;
			pos.y += 3;
		}
		break;
	}

	if (m_nCounter >= 140)
	{//�J�E���^�[���P�S�O�ȏ�̏ꍇ
		//�I������
		Uninit();
	}

	SetPos(pos);

}

//=============================================================================
// �`�揈��
//=============================================================================
void CIcicle::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CSceneX::Draw();

}