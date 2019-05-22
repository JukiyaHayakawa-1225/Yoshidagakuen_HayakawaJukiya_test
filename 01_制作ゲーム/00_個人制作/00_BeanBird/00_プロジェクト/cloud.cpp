//=============================================================================
//
// �_�̏��� [cloud.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "cloud.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "player.h"
#include "barrier.h"
#include "avatar.h"
#include "skill.h"
#include "score.h"
#include "beans.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CCloud::m_pTexture = NULL;		//�e�N�X�`���̃|�C���^
//=============================================================================
// �_�̃R���X�g���N�^
//=============================================================================
CCloud::CCloud() : CScene2D(2)
{
	m_move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//�ړ��ʂ̏����l
	m_state = CLOUD_BEANS;					//��Ԃ̏���
}
//=============================================================================
// �_�̃f�X�g���N�^
//=============================================================================
CCloud::~CCloud()
{

}

//=============================================================================
//�_�̐���
//=============================================================================
CCloud *CCloud::Create(D3DXVECTOR3 pos, float fWight, float fHeight, CLOUD_STATE state)
{
	CCloud *pCloud = NULL;									//�_�̃|�C���^
	if (pCloud == NULL)
	{//NULL�̏ꍇ
		pCloud = new CCloud;								//�_�̓��I�m��
		pCloud->SetPos(pos);								//�ʒu�̑��
		pCloud->SetWidth(fWight);							//���̑��
		pCloud->SetHeight(fHeight);							//�����̑��
		pCloud->Init();										//����������
		pCloud->BindTexture(m_pTexture);					//�e�N�X�`��
		pCloud->m_move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�ړ��ʂ̏�����
		pCloud->m_state = state;							//��Ԃ̑��
	}
	return pCloud;											//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CCloud::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cloud.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CCloud::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// �_�̏���������
//=============================================================================
HRESULT CCloud::Init(void)
{
	//CScene2D�̏���������
	CScene2D::Init();
	//��ނ̐ݒ�
	SetObjType(OBJTYPE_CLOUD);
	return S_OK;
}

//=============================================================================
// �_�̏I������
//=============================================================================
void CCloud::Uninit(void)
{
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �_�̍X�V����
//=============================================================================
void CCloud::Update(void)
{
	D3DXVECTOR3 pos;	//�ʒu
	pos = GetPos();		//�ʒu�̎擾

	//�ړ��ʑ��
	pos += m_move;

	//�ʒu�̐ݒu
	SetVtxPos(pos);

	//CScene2D�̍X�V����
	CScene2D::Update();

}

//=============================================================================
// �_�̕`�揈��
//=============================================================================
void CCloud::Draw(void)
{
	//CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �_�̓����蔻�菈��
//=============================================================================
void CCloud::HitCloud(void)
{
	D3DXVECTOR3 pos;	//�ʒu
	pos = GetPos();		//�ʒu�̎擾

	if (m_state == CLOUD_BEANS)
	{
		//���̐���
		CBeans::Create(D3DXVECTOR3(pos.x,pos.y - 20.0f,pos.z), BEANS_SIZE, BEANS_SIZE);
		//��Ԃ�ύX
		m_state = CLOUD_NONE;
	}
	if (pos.y >= SCREEN_HEIGHT + 50)
	{//��ʊO�ɂ������ꍇ
	 //�_�̏I������
		CCloud::Uninit();
	}
}

//=============================================================================
// �_�̎擾����
//=============================================================================
CCloud::CLOUD_STATE CCloud::GetCloud(void)
{
	return m_state;
}