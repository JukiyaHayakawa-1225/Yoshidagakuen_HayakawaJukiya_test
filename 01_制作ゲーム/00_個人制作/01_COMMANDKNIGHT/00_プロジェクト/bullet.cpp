//=============================================================================
//
// �e�̏��� [billboardgauge.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �e�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet() : CBillboard()
{
	m_nLife = 0;			//�̗͂̏����l
}
//=============================================================================
// �e�̃f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}
//=============================================================================
// �e�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�̃e�N�X�`���j��
//=============================================================================
void CBullet::Unload(void)
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
CBullet *CBullet::Create(D3DXVECTOR3 pos, int nLife,D3DXVECTOR3 move)
{
	CBullet *pBullet = NULL;
	if (pBullet == NULL)
	{
		pBullet = new CBullet;						//�V�[���̓��I�m��
		if (pBullet != NULL)
		{
			pBullet->SetPos(pos);					//�ʒu�̐ݒu����
			pBullet->m_nLife = nLife;				//�̗͂̐ݒu����
			pBullet->SetMove(move);					//�ړ��ʂ̐ݒu����
			pBullet->SetWidth(15.0f);				//���̐ݒu����
			pBullet->SetHeight(15.0f);				//�����̐ݒu����
			pBullet->Init();						//����������
			pBullet->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�F�̐ݒu����
			pBullet->BindTexture(m_pTexture);		//�e�N�X�`���̓\��t��
		}
	}
	return pBullet;									//�l��Ԃ�
}

//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CBullet::Init(void)
{
	//�r���{�[�h�̏���������
	CBillboard::Init();
	//�F�̐ݒu����
	SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));;
	return S_OK;
}

//=============================================================================
// �e�̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	//�r���{�[�h�̏I������
	CBillboard::Uninit();
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	//�v���C���[�̎擾����
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 pos = GetPos();					//�ʒu�̎擾����
	D3DXVECTOR3 move = GetMove();				//�ړ��ʂ̎擾����
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();	//�v���C���[�̎擾����
	pos += move;								//�ʒu�̑��

	//�����蔻��̌v�Z����
	float fLength = powf((PlayerPos.x - pos.x)*(PlayerPos.x - pos.x) + (PlayerPos.z - pos.z)*(PlayerPos.z - pos.z), 0.5f);	//�v���C���[�Ƃ̋���
	float fHit = powf(3.0f, 2.0f);	//���a
	if (fHit > fLength)
	{//�v���C���[�̋������͈͓��̏ꍇ
		//�_���[�W����
		int nDamade = rand() % 5 + 3;
		pPlayer->HitDamage(nDamade);	//�v���C���[�̃_���[�W����
		//�I������
		Uninit();
	}

	//�̗͂̌��Z����
	m_nLife--;

	if (m_nLife <= 0)
	{//�̗͂��O�ȉ��̏ꍇ
		//�I������
		Uninit();
	}
	//�ʒu�̐ݒu����
	SetPos(pos);
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	//�r���{�[�h�̕`�揈��
	CBillboard::Draw();
}