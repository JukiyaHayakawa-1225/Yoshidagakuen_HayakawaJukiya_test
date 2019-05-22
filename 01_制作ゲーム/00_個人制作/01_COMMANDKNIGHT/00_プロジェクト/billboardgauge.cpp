//=============================================================================
//
// �r���{�[�h�Q�[�W���� [billboardgauge.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "billboardgauge.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "enemy.h"
#include "score.h"
#include "billboard.h"
#include "player.h"
#include "game.h"
#include "ui.h"
#include "enemy.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBillboardLifeGauge::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CBillboardLifeGauge::CBillboardLifeGauge() : CBillboard()
{
	m_nLife = 0;								//�̗͂̏����l
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CBillboardLifeGauge::~CBillboardLifeGauge()
{

}
//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CBillboardLifeGauge::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Gauge\\GAUGE_LIFE.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CBillboardLifeGauge::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �r���{�[�h�̗̓Q�[�W����
//=============================================================================
CBillboardLifeGauge *CBillboardLifeGauge::Create(D3DXVECTOR3 pos, int nLife, int nMaxLife)
{
	CBillboardLifeGauge *pBillboardLifeGauge = NULL;
	if (pBillboardLifeGauge == NULL)
	{
		pBillboardLifeGauge = new CBillboardLifeGauge;						//�V�[���̓��I�m��
		if (pBillboardLifeGauge != NULL)
		{
			pBillboardLifeGauge->SetPos(pos);						//�ʒu�̐ݒu����
			pBillboardLifeGauge->m_nLife = nLife;					//�̗͂̐ݒu����
			pBillboardLifeGauge->m_nMaxLife = nMaxLife;				//�̗͂̍ő�l�ݒu����
			pBillboardLifeGauge->SetWidth(MAX_BILLBOARDGAGE_WIDTH);	//���̐ݒu����
			pBillboardLifeGauge->SetHeight(2.5f);					//�����̐ݒu����
			pBillboardLifeGauge->Init();							//����������
			pBillboardLifeGauge->CutSide(0);						//�����猸�Z����
			pBillboardLifeGauge->BindTexture(m_pTexture);			//�e�N�X�`���̓\��t��
		}
	}
	return pBillboardLifeGauge;									//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CBillboardLifeGauge::Init(void)
{
	//�r���{�[�h�̏���������
	CBillboard::Init();
	//�F�̐ݒu����
	SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));;
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CBillboardLifeGauge::Uninit(void)
{
	//�r���{�[�h�̏I������
	CBillboard::Uninit();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CBillboardLifeGauge::Update(void)
{

}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CBillboardLifeGauge::Draw(void)
{
	//CScene2D�̕`�揈��
	CBillboard::Draw();
}

//=============================================================================
// UI�̗̓Q�[�W���Z����
//=============================================================================
void CBillboardLifeGauge::CutLifeGauge(int nCut)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�G�̎擾
	CEnemy *pEnemy;
	pEnemy = CGame::GetEnemy();

	int nLife = 0;			//�̗�
	int nMaxLife = 0;		//�̗͂̍ő�l
	float fData;			//�f�[�^�̊i�[

	m_nLife -= nCut;		//�̗͂̌��Z

	D3DXVECTOR3 pos = GetPos();	//�ʒu�̎擾����
	float fWidth = GetWidth();	//���̎擾����

	//�Q�[�W�̊�������
	fData = MAX_BILLBOARDGAGE_WIDTH * m_nLife / m_nMaxLife;

	if (fWidth >= 0.0f)
	{//�����O�ȏ�̏ꍇ
		SetWidth(fData);		//���̐ݒu����
		CutSide(0);				//�����猸�Z����
		if (fWidth <= MAX_BILLBOARDGAGE_WIDTH && fWidth >= (MAX_BILLBOARDGAGE_WIDTH / 2 + 1))
		{//�����������傫���̏ꍇ
			SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	//�F�̐ݒu����
		}
		else if (fWidth <= MAX_BILLBOARDGAGE_WIDTH / 2 && fWidth >= (MAX_BILLBOARDGAGE_WIDTH / 4 + 1))
		{//����������菬�����ꍇ
			SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));	//�F�̐ݒu����
		}
		else if (fWidth <= MAX_BILLBOARDGAGE_WIDTH / 4 && fWidth >= 0)
		{//�����S���ȉ��̏ꍇ
			SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	//�F�̐ݒu����
		}
	}
	else
	{
		fWidth = 0.0f;		//�l�̌Œ�
		SetWidth(fWidth);	//���̐ݒu����
		CutSide(0);			//�E���猸�Z����
	}
}
