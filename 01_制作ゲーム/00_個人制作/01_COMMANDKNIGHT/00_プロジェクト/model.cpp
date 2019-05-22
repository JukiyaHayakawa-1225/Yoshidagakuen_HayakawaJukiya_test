//=============================================================================
//
// ���f������ [model.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	// �ʒu�E�����̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏����ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		//�傫���̏����ݒ�
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{

}
//=============================================================================
// �I�u�W�F�N�gX�̐���
//=============================================================================
CModel *CModel::Create(D3DXVECTOR3 pos)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{
		pModel = new CModel;		//���I�m��
		if (pModel != NULL)
		{
			pModel->Init();			//����������
			pModel->m_pos = pos;	//�ʒu�̑��8
		}
	}
	return pModel;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CModel::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	BindX(m_pMesh, m_pBuffMat, m_pNumMat);
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModel::Uninit(void)
{
	////�o�b�t�@�̊J��
	//if (m_pBuffMat != NULL)
	//{
	//	m_pBuffMat->Release();
	//	m_pBuffMat = NULL;
	//}
	//// ���b�V���̊J��
	//if (m_pMesh != NULL)
	//{
	//	m_pMesh->Release();
	//	m_pMesh = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void CModel::Update(void)
{
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModel::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;					//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;							//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �傫���̔��f
	D3DXMatrixScaling(&mtxScale,
		m_size.x, m_size.y, m_size.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != NULL)
	{//�e������ꍇ
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//�e�����Ȃ��ꍇ
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//�e���f���̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`������
		pDevice->SetTexture(0, NULL);

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}


	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�̐ݒu����
//=============================================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �ʒu�̐ݒu����
//=============================================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
//    ���f���̃��b�V������ݒ肷��
//=============================================================================
void CModel::SetMesh(LPD3DXMESH pMesh)
{
	m_pMesh = pMesh;

	if (m_pMesh != NULL)
	{// ���f�����ǂݍ��߂�
	 // �ŏ��l�ƍő�l��������
		m_pVtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		m_pVtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

		int nNumVtx;     // ���_��
		DWORD sizeFVF;   // ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C���^

		 // ���_�����l��
		nNumVtx = m_pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		// ���_�o�b�t�@�����b�N
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{//
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;   // ���_���W�̑��

			if (vtx.x < m_pVtxMin.x)
			{
				m_pVtxMin.x = vtx.x;  // �ŏ��l�X�V
			}
			if (vtx.y < m_pVtxMin.y)
			{
				m_pVtxMin.y = vtx.y;  // �ŏ��l�X�V
			}
			if (vtx.z < m_pVtxMin.z)
			{
				m_pVtxMin.z = vtx.z;  // �ŏ��l�X�V
			}
			if (vtx.x > m_pVtxMax.x)
			{
				m_pVtxMax.x = vtx.x;  // �ő�l�X�V
			}
			if (vtx.y > m_pVtxMax.y)
			{
				m_pVtxMax.y = vtx.y;  // �ő�l�X�V
			}
			if (vtx.z > m_pVtxMax.z)
			{
				m_pVtxMax.z = vtx.z;  // �ő�l�X�V
			}

			pVtxBuff += sizeFVF;  // �T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@���A�����b�N
		m_pMesh->UnlockVertexBuffer();
	}
}

//=============================================================================
//    ���f���̃}�e���A������ݒ肷��
//=============================================================================
void CModel::SetBuffMat(LPD3DXBUFFER buffMat)
{
	m_pBuffMat = buffMat;
}

//=============================================================================
//    ���f���̃}�e���A���̐�����ݒ肷��
//=============================================================================
void CModel::SetNumMat(DWORD nNumMat)
{
	m_pNumMat = nNumMat;
}

//=============================================================================
// �ʒu�̎擾����
//=============================================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �����̎擾����
//=============================================================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// X�t�@�C���̎擾����
//=============================================================================
void CModel::BindX(LPD3DXMESH mesh, LPD3DXBUFFER buffmat, DWORD nummat)
{
	SetMesh(mesh);
	SetBuffMat(buffmat);
	SetNumMat(nummat);
	/*m_pMesh = mesh;
	m_pBuffMat = buffmat;
	m_pNumMat = nummat;*/
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//=============================================================================
// ���[���h�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX &CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
// �傫���̐ݒu�擾
//=============================================================================
void CModel::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}