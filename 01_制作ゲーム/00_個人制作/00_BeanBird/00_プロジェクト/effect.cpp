//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "explotion.h"
#include "enemy.h"
#include "beans.h"
#include "score.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CEffect::CEffect() : CScene2D(1)
{
	m_nLife = 0;								//�̗͂̏����l
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏����l
}
//=============================================================================
// �G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
//�G�t�F�N�g�̐���
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWight, float fHeight)
{
	CEffect *pEffect = NULL;

	if (pEffect == NULL)
	{
		pEffect = new CEffect;				//�V�[���̓��I�m��
		pEffect->SetPos(pos);				//�ʒu�̑��
		pEffect->SetWidth(fWight);			//���̑��
		pEffect->SetHeight(fHeight);		//�����̑��
		pEffect->Init();					//����������
		pEffect->SetCol(col);				//�F�̑��
		pEffect->BindTexture(m_pTexture);	//�e�N�X�`��
	}
	return pEffect;						//�l��Ԃ�
}

//=============================================================================
// �G�t�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEffect::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME012,
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CEffect::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT CEffect::Init(void)
{
	//CScene2D�̏���������
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void CEffect::Uninit(void)
{
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;		//�F
	float fWidth;		//��
	float fHeight;		//����

	//�ʒu�̎擾
	pos = GetPos();
	//�F�̎擾
	col = GetCol();
	//���̎擾
	fWidth = GetWidth();
	//�����̎擾
	fHeight = GetHeight();

	//���Z����
	fWidth -= 2.5f;		//�������炷
	fHeight -= 2.5f;	//���������炷
	col.r -= 0.01f;		//�F�����炷
	col.g -= 0.01f;		//�F�����炷
	col.b -= 0.01f;		//�F�����炷
	col.a -= 0.01f;		//�����x�����炷

	//�ʒu�̐ݒu
	SetPos(pos);
	//���̐ݒu
	SetWidth(fWidth);
	//�����̐ݒu
	SetHeight(fHeight);
	//�ʒu�̐ݒu
	SetVtxPos(pos);
	//�F�̐ݒu
	SetCol(col);

	if (fWidth <= 0.0f || fHeight <= 0.0f)
	{//���܂��͍�����0�ȉ��ɂȂ����ꍇ
		//�I������
		Uninit();
	}

	//CScene2D�̍X�V����
	CScene2D::Update();
}

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//CScene2D�̕`�揈��
	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}