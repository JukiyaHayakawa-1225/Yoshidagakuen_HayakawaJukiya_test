//=============================================================================
//
// ���b�V���I�[�r�b�g�̏��� [meshorbit.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "meshorbit.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "player.h"
#include "command.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME01 "data\\TEXTURE\\orbit.png"			//�e�N�X�`����

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �|���S���̃R���X�g���N�^
//=============================================================================
CMeshOrbit::CMeshOrbit(int nPrioriry, OBJTYPE objtype) : CScene(nPrioriry, objtype)
{
	m_pTexture = NULL;							// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
	m_pMtxParent = NULL;						// �e�}�g���b�N�X�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu

}
//=============================================================================
// �|���S���̃R���X�g���N�^
//=============================================================================
CMeshOrbit::~CMeshOrbit()
{

}
//=============================================================================
// �|���S���̐���
//=============================================================================
CMeshOrbit *CMeshOrbit::Create(void)
{
	CMeshOrbit *pMeshOrbit = NULL;		//�I�u�W�F�N�g�̃|�C���^

	if (pMeshOrbit == NULL)
	{
		pMeshOrbit = new CMeshOrbit;	//���I�m��
		if (pMeshOrbit != NULL)
		{
			pMeshOrbit->Init();		//����������
		}
	}
	return pMeshOrbit;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshOrbit::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�����v�Z
	m_nNumVertex = ((MAX_X + 1) * (MAX_Z + 1));

	//�|���S���̑������v�Z
	m_nNumPolygon = ((MAX_X + 1) * (MAX_Z + 1)
		+ (2 * (MAX_Z - 1))
		+ (MAX_X + 1) * (MAX_Z - 1)) - 2;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME01,
		&m_pTexture);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int nCntVtx = 0;
	for (int nCntX = 0; nCntX < MAX_X + 1; nCntX++)
	{
		// ���_���W�̐ݒ�
		pVtx[nCntX + nCntVtx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[(nCntX + nCntVtx) + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���̐ݒ�
		pVtx[nCntX + nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[(nCntX + nCntVtx) + 1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//�F�̐ݒ�
		pVtx[nCntX + nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[(nCntX + nCntVtx) + 1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[nCntX + nCntVtx].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[(nCntX + nCntVtx) + 1].tex = D3DXVECTOR2(0.0f, 1.0f);
		nCntVtx += MAX_Z;
	}
	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	for (int nCnt = 0; nCnt < MAX_X + 1; nCnt++)
	{
		m_aPosVertex[nCnt] = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		//m_aColVertex[nCnt] = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		//m_aTexVertexX[nCnt] = D3DXVECTOR2(0.0f, 0.0f);
	}

	nCntVtx = 0;
	for (int nCntX = 0; nCntX < MAX_X + 1; nCntX++)
	{
		//�F�̐ݒ�
		m_aColVertex[nCntX + nCntVtx] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aColVertex[(nCntX + nCntVtx) + 1] = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		m_aTexVertexX[nCntX + nCntVtx] = D3DXVECTOR2(1.0f, 1.0f);
		m_aTexVertexX[(nCntX + nCntVtx) + 1] = D3DXVECTOR2(1.0f, 0.0f);
		nCntVtx += MAX_Z;
	}
	m_aOffset[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aOffset[1] = D3DXVECTOR3(0.0f, 25.0f, 0.0f);
	//��ނ̐ݒ�
	SetObjType(OBJTYPE_SCENE3D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshOrbit::Uninit(void)
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
void CMeshOrbit::Update(void)
{
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;
	for (int nCntX = 2; nCntX < MAX_X + 1; nCntX++)
	{//�I�[�r�b�g�̐������J��Ԃ�
		//�F�̌��Z����
		m_aColVertex[nCntX + nCntVtx].a -= 0.025f;
		m_aColVertex[nCntX + nCntVtx + 1].a -= 0.025f;

		m_aColVertex[nCntX + nCntVtx].a -= 0.015f;
		m_aColVertex[nCntX + nCntVtx + 1].a -= 0.015f;

		//�e�N�X�`���̌��Z����
		m_aTexVertexX[nCntX + nCntVtx].x -= 0.02f;
		m_aTexVertexX[nCntX + nCntVtx + 1].x -= 0.02f;

		nCntVtx += MAX_Z;
	}
	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshOrbit::Draw(void)
{
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	if (pPlayer->GetMotion() != CPlayer::MOTION_ITEM &&
		pPlayer->GetMotion() != CPlayer::MOTION_JUMP &&
		pPlayer->GetMotion() != CPlayer::MOTION_NEUTRAL &&
		pPlayer->GetMotion() != CPlayer::MOTION_MOVE)
	{
		//�����_�����O�̎擾
		CRenderer *pRenderer;
		pRenderer = CManager::GetRenderer();

		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = pRenderer->GetDevice();

		D3DXVECTOR3 pos;							//�ʒu�̏��
		D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;						//�e�q�֌W�}�g���b�N�X

		// �J�����O�����Ȃ���Ԃɂ���
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		// �A���t�@�e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 200);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		 // ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntMeshOrbit = m_nNumVertex - 3; nCntMeshOrbit >= 0; nCntMeshOrbit--)
		{//���_�����J��Ԃ�
			//���݂̏����Q��ɓ���ւ�
			m_aPosVertex[nCntMeshOrbit + 2] = m_aPosVertex[nCntMeshOrbit];
			m_aColVertex[nCntMeshOrbit + 2] = m_aColVertex[nCntMeshOrbit];
			m_aTexVertexX[nCntMeshOrbit + 2] = m_aTexVertexX[nCntMeshOrbit];

			//�Q��̏��𒸓_�ɑ��
			pVtx[nCntMeshOrbit + 2].pos = m_aPosVertex[nCntMeshOrbit + 2];
			pVtx[nCntMeshOrbit + 2].col = m_aColVertex[nCntMeshOrbit + 2];
			pVtx[nCntMeshOrbit + 2].tex = m_aTexVertexX[nCntMeshOrbit + 2];
		}
		//���_�O�Ԗڂ̏�����
		//�ʒu
		D3DXVec3TransformCoord(&m_aPosVertex[0], &m_aOffset[0], m_pMtxParent);
		pVtx[0].pos = m_aPosVertex[0];
		//�F
		m_aColVertex[0].a = 1.0f;
		pVtx[0].col = m_aColVertex[0];
		//�e�N�X�`��
		m_aTexVertexX[0] = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[0].tex = m_aTexVertexX[0];

		//���_�P�Ԗڂ̏�����
		//�ʒu
		D3DXVec3TransformCoord(&m_aPosVertex[1], &m_aOffset[1], m_pMtxParent);
		pVtx[1].pos = m_aPosVertex[1];
		//�F
		m_aColVertex[1].a = 1.0f;
		pVtx[1].col = m_aColVertex[1];
		//�e�N�X�`��
		m_aTexVertexX[1] = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = m_aTexVertexX[1];

		// ���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		////�e���f���̃}�g���b�N�X���|�����킹��
		//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, m_pMtxParent);


		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumPolygon);

		// ���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// �A���t�@�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		// �J�����O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	}
}

//=============================================================================
// �}�g���b�N�X�̐ݒu����
//=============================================================================
void CMeshOrbit::SetMtxParent(D3DXMATRIX *pMtx)
{
	//�e�q�֌W�̃}�g���b�N�X�ɑ��
	m_pMtxParent = pMtx;
}