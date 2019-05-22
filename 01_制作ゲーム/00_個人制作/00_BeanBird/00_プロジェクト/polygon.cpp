//=============================================================================
//
// �|���S���̏��� [polygon.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "polygon.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "score.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================


//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_SIZE        (30)                            // �e�N�X�`���̃T�C�Y

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �|���S���̃R���X�g���N�^
//=============================================================================
CPolygon::CPolygon()
{
	m_pTexture = NULL;

}
//=============================================================================
// �|���S���̃f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{

}

//=============================================================================
//�|���S���̐���
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CPolygon *pPolygon = NULL;
	if (pPolygon == NULL)
	{
		pPolygon = new CPolygon;			//�V�[���̓��I�m��
		pPolygon->m_pos = pos;				//�ʒu�̑��
		pPolygon->m_fWight = fWight;		//���̑��
		pPolygon->m_fHeight = fHeight;		//�����̑��
		pPolygon->Init();					//����������
	}
	return pPolygon;						//�l��Ԃ�
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CPolygon::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)& pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWight, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWight, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWight, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWight, m_pos.y + m_fHeight, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CPolygon::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//// �e�N�X�`���̔j��
	//if (m_apTexture != NULL)
	//{
	//	m_apTexture->Release();
	//	m_apTexture = NULL;
	//}

	//�I�u�W�F�N�g�̔j��
	//Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CPolygon::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
// �I�u�W�F�N�g�̎擾����
//=============================================================================
void CPolygon::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}
