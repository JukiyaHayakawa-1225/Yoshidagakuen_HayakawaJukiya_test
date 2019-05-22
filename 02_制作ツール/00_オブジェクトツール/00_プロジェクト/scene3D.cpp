//=============================================================================
//
// �I�u�W�F�N�g3D���� [scene3D.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME01 "data\\TEXTURE\\grass.jpg"			//�e�N�X�`����
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �|���S���̃R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(int nPrioriry,OBJTYPE objtype) : CScene(nPrioriry,objtype)
{
	m_pTexture = NULL;							// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_fSizeX = 50.0f;							// X���W�̑傫��
	m_fSizeZ = 50.0f;							// Z���W�̑傫��
}
//=============================================================================
// �|���S���̃R���X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}
//=============================================================================
// �|���S���̐���
//=============================================================================
CScene3D *CScene3D::Create(void)
{
	CScene3D *pScene3D = NULL;		//�I�u�W�F�N�g�̃|�C���^

	if (pScene3D == NULL)
	{
		pScene3D = new CScene3D;	//���I�m��
		if (pScene3D != NULL)
		{
			pScene3D->Init();		//����������
		}
	}
	return pScene3D;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		NULL,/*TEXTURE_NAME01*/
		&m_pTexture);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fSizeX, 0.0f, -m_fSizeZ);
	pVtx[1].pos = D3DXVECTOR3(-m_fSizeX, 0.0f, m_fSizeZ);
	pVtx[2].pos = D3DXVECTOR3(m_fSizeX, 0.0f, -m_fSizeZ);
	pVtx[3].pos = D3DXVECTOR3(m_fSizeX, 0.0f, m_fSizeZ);

	m_vec0 = pVtx[3].pos - pVtx[2].pos;
	m_vec1 = pVtx[3].pos - pVtx[1].pos;

	m_nor0.x = ((m_vec0.y * m_vec1.z) - (m_vec0.z * m_vec1.y));
	m_nor0.y = ((m_vec0.z * m_vec1.x) - (m_vec0.x * m_vec1.z));
	m_nor0.z = ((m_vec0.x * m_vec1.y) - (m_vec0.y * m_vec1.x));

	//D3DXVec3Cross(&nor0, &m_vec0, &m_vec1);
	D3DXVec3Normalize(&m_nor0, &m_nor0);		//���K������

	m_vec0 = pVtx[0].pos - pVtx[1].pos;
	m_vec1 = pVtx[0].pos - pVtx[2].pos;

	D3DXVec3Cross(&m_nor0, &m_vec0, &m_vec1);
	D3DXVec3Normalize(&m_nor1, &m_nor1);		//���K������

	m_dData = (m_nor0 + m_nor1) / 2;

	//�@���̐ݒ�
	//pVtx[0].nor = m_nor1;
	//pVtx[1].nor = m_dData;
	//pVtx[2].nor = m_dData;
	//pVtx[3].nor = m_nor0;

	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�J���[
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//��ނ̐ݒ�
	SetObjType(OBJTYPE_SCENE3D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();


	//�ʒu�̈ړ�����
	MovePos();

	//�@���̐ݒu����
	SetNor();

	if (pInputKeyboard->GetPress(DIK_L) == true)
	{
		m_rot.y += 0.1f;
	}
	if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{
		//Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
		m_rot.x,
		m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �@���̐ݒu
//=============================================================================
void CScene3D::SetNor(void)
{
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_vec0 = pVtx[3].pos - pVtx[2].pos;
	m_vec1 = pVtx[3].pos - pVtx[1].pos;

	D3DXVec3Cross(&m_nor0, &m_vec0, &m_vec1);
	D3DXVec3Normalize(&m_nor0, &m_nor0);		//���K������

	m_vec0 = pVtx[0].pos - pVtx[1].pos;
	m_vec1 = pVtx[0].pos - pVtx[2].pos;

	D3DXVec3Cross(&m_nor1, &m_vec0, &m_vec1);
	D3DXVec3Normalize(&m_nor1, &m_nor1);		//���K������

	m_dData = (m_nor0 + m_nor1) / 2;

	//�@���̐ݒ�
	pVtx[0].nor = m_nor1;
	pVtx[1].nor = m_dData;
	pVtx[2].nor = m_dData;
	pVtx[3].nor = m_nor0;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �ʒu�̈ړ�����
//=============================================================================
void CScene3D::MovePos(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	/*if (pInputKeyboard->GetPress(DIK_F1) == true)
	{
		pVtx[0].pos.y += 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_F2) == true)
	{
		pVtx[0].pos.y -= 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_F3) == true)
	{
		pVtx[1].pos.y += 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_F4) == true)
	{
		pVtx[1].pos.y -= 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_F5) == true)
	{
		pVtx[2].pos.y += 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_F6) == true)
	{
		pVtx[2].pos.y -= 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_F7) == true)
	{
		pVtx[3].pos.y += 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_F8) == true)
	{
		pVtx[3].pos.y -= 1.0f;
	}*/

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �ʒu�̈ړ�����
//=============================================================================
D3DXVECTOR3 CScene3D::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// X�T�C�Y�̎擾����
//=============================================================================
float CScene3D::GetSizeX(void)
{
	return m_fSizeX;
}
//=============================================================================
// Z�T�C�Y�̎擾����
//=============================================================================
float CScene3D::GetSizeZ(void)
{
	return m_fSizeZ;
}
//=============================================================================
// �@���̎擾����
//=============================================================================
D3DXVECTOR3 CScene3D::GetNor(void)
{
	return m_dData;
}

//=============================================================================
// �����̎擾
//=============================================================================
float CScene3D::GetHeight(D3DXVECTOR3 pos, bool bR)
{
	D3DXVECTOR3 vecA, vecC;
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (bR == true)
	{
		pos.y = ((pVtx[0].nor.x * (pos.x - pVtx[0].pos.x) + pVtx[0].nor.z * (pos.z - pVtx[0].pos.z)) / -pVtx[0].nor.y) + pVtx[0].pos.y;
	}
	else if (bR == false)
	{
		pos.y = ((pVtx[3].nor.x * (pos.x - pVtx[3].pos.x) + pVtx[3].nor.z * (pos.z - pVtx[3].pos.z)) / -pVtx[3].nor.y) + pVtx[3].pos.y;
	}
	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
	return pos.y;
}
//=============================================================================
// �ʒu�̐ݒu����
//=============================================================================
void CScene3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`���̐ݒu����
//=============================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}
//=============================================================================
// X�T�C�Y�̐ݒu����
//=============================================================================
void CScene3D::SetSizeX(float sizeX)
{
	m_fSizeX = sizeX;
}

//=============================================================================
// Z�T�C�Y�̐ݒu����
//=============================================================================
void CScene3D::SetSizeZ(float sizeZ)
{
	m_fSizeZ = sizeZ;
}
