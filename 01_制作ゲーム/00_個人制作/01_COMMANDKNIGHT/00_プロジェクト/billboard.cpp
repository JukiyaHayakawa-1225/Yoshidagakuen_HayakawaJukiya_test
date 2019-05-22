//=============================================================================
//
// �r���{�[�h�̏��� [billboard.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "billboard.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard(int nPriority, OBJTYPE objtype) : CScene(nPriority, objtype)
{
	m_pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);		//�ʒu�̏����l
	m_fWidth = 10.0f;							//���̏����l
	m_fHeight = 10.0f;							//�����̏����l
	m_fLength = 10.0f;							//�����̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ�������
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{

}

//=============================================================================
// �r���{�[�h�̐���
//=============================================================================
CBillboard *CBillboard::Create(void)
{
	CBillboard *pBillboard = NULL;	//�r���{�[�h�̃|�C���^

	if (pBillboard == NULL)
	{//NULL�̏ꍇ
		pBillboard = new CBillboard;	//���I�m��
		if (pBillboard != NULL)
		{//NULL�łȂ��ꍇ
			pBillboard->Init();			//����������
		}
	}
	return pBillboard;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CBillboard::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

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
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, 0.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBillboard::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�f�[�^�̊J��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBillboard::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CBillboard::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxView;	//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW,
		&mtxView);

	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	//�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						//��l
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�����_�[�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// �r���{�[�h�̃e�N�X�`���̎擾����
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// �r���{�[�h�̈ʒu�̐ݒu����
//=============================================================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �r���{�[�h�̕��̐ݒu����
//=============================================================================
void CBillboard::SetWidth(float fWidth)
{
	m_fWidth = fWidth;
}

//=============================================================================
// �r���{�[�h�̍����̐ݒu����
//=============================================================================
void CBillboard::SetHeight(float fHeight)
{
	m_fHeight = fHeight;
}

//=============================================================================
// �r���{�[�h�̌����̎擾����
//=============================================================================
void CBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �r���{�[�h�̐F�̐ݒu����
//=============================================================================
void CBillboard::SetCol(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �r���{�[�h�̒����̐ݒu����
//=============================================================================
void CBillboard::SetLength(float fLength)
{
	m_fLength = fLength;
}

//=============================================================================
// �r���{�[�h�̈ʒu�̎擾����
//=============================================================================
D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �r���{�[�h�̌����̎擾����
//=============================================================================
D3DXVECTOR3 CBillboard::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �r���{�[�h�̒����̎擾����
//=============================================================================
float CBillboard::GetLength(void)
{
	return m_fLength;
}

//=============================================================================
// �r���{�[�h�̐F�̎擾����
//=============================================================================
D3DXCOLOR CBillboard::GetCol(void)
{
	return m_col;
}

//=============================================================================
// �r���{�[�h�̕��̎擾����
//=============================================================================
float CBillboard::GetWidth(void)
{
	return m_fWidth;
}

//=============================================================================
// �r���{�[�h�̍����̎擾����
//=============================================================================
float CBillboard::GetHeight(void)
{
	return m_fHeight;
}

//=============================================================================
// �r���{�[�h�̒����̐ݒu����
//=============================================================================
void CBillboard::SetLengthPos(void)
{
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fLength, m_fLength, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fLength, m_fLength, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fLength, -m_fLength, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fLength, -m_fLength, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
// �T�C�h�I���^���Z����
//=============================================================================
void CBillboard::CutSide(int nType)
{
	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nType == 0)
	{//�����猸�Z
	 // ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, 0.0f);
	}
	else if (nType == 1)
	{//�E���猸�Z
	 // ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �r���{�[�h�̈ړ��ʐݒu����
//=============================================================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �r���{�[�h�̈ړ��ʎ擾����
//=============================================================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return m_move;
}