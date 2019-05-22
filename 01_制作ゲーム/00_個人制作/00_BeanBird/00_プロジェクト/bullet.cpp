//=============================================================================
//
// �e�̏��� [bullte.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "bullet.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "explotion.h"
#include "enemy.h"
#include "beans.h"
#include "score.h"
#include "effect.h"
#include "life.h"
#include "barrier.h"
#include "player.h"
#include "cloud.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_BULLET] = {};

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �e�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet() : CScene2D()
{
	m_nLife = 0;								//�̗͏����l
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʏ����l
	m_bulletType = BULLETTYPE_NONE;				//��ޏ���
}
//=============================================================================
// �e�̃f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
//�e�̐���
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, float fWight, float fHeight,BULLETTYPE type)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{
		pBullet = new CBullet;				//�V�[���̓��I�m��
		pBullet->SetPos(pos);				//�ʒu�̑��
		pBullet->SetWidth(fWight);			//���̑��
		pBullet->SetHeight(fHeight);		//�����̑��
		pBullet->Init();					//����������
		pBullet->m_move = move;				//�ړ��ʂ���
		pBullet->m_bulletType = type;		//��ނ̑��
		switch (type)
		{
		case BULLETTYPE_PLAYER_SALIVA:
			pBullet->BindTexture(m_pTexture[0]);	//�e�N�X�`��
			break;
		case BULLETTYPE_PLAYER_SHIT:
			pBullet->BindTexture(m_pTexture[1]);	//�e�N�X�`��
			break;
		case BULLETTYPE_ENEMY:
			pBullet->BindTexture(m_pTexture[2]);	//�e�N�X�`��
			break;
		}
	}
	return pBullet;							//�l��Ԃ�
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
		TEXTURE_NAME001,
		&m_pTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\egg.png",
		&m_pTexture[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\humanbullet.png",
		&m_pTexture[2]);
	return S_OK;
}

//=============================================================================
// �e�̃e�N�X�`���j��
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCntTexture = 0; nCntTexture < MAX_BULLET; nCntTexture++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture]= NULL;
		}
	}
}
//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CBullet::Init(void)
{
	//CScene2D�̏���������
	CScene2D::Init();
	//��ނ̐ݒ�
	SetObjType(OBJTYPE_BULLET);
	return S_OK;
}

//=============================================================================
// �e�̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	//�e�̓����蔻��
	Collision();

	//CScene2D�̍X�V����
	CScene2D::Update();
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	//CScene2D�̕`�揈��
	CScene2D::Draw();
}
//=============================================================================
// �e�̓����蔻��
//=============================================================================
void CBullet::Collision(void)
{
	D3DXVECTOR3 pos;			//�ʒu
	bool bDisappear = false;	//���ł��Ă邩�ǂ���

	pos = GetPos();				//�ʒu�̎擾

	m_nLife++;					//�̗͂̉��Z
	pos += m_move;				//���W�̑��

	//�ʒu�̐ݒu
	CScene2D::SetVtxPos(pos);

	switch (m_bulletType)
	{
	case BULLETTYPE_PLAYER_SALIVA:
		//�G�t�F�N�g�̐���
		CEffect::Create(pos, D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f), 20.0f, 20.0f);
		break;
	case BULLETTYPE_PLAYER_SHIT:
		//�G�t�F�N�g�̐���
		CEffect::Create(pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 20.0f, 20.0f);
		break;
	case BULLETTYPE_ENEMY:
		//�G�t�F�N�g�̐���
		CEffect::Create(pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20.0f, 20.0f);
		break;
	}

	if (m_bulletType == BULLETTYPE_PLAYER_SALIVA || m_bulletType == BULLETTYPE_ENEMY)
	{
		if (pos.y < 0 || m_nLife > 40)
		{//��ʊO�̏ꍇ
		 //�I������
			bDisappear = true;

			//�̗͂̏�����
			m_nLife = 0;

			//�����̐���
			CExplotion::Create(pos, 50.0f, 50.0f);
		}
	}
	else if (m_bulletType == BULLETTYPE_PLAYER_SHIT)
	{
		if (pos.y < 0 || m_nLife > 20)
		{//��ʊO�̏ꍇ
		 //�I������
			bDisappear = true;

			//�̗͂̏�����
			m_nLife = 0;

			//�����̐���
			CExplotion::Create(pos, 50.0f, 50.0f);
		}
	}

	for (int nCntPrioty = 0; nCntPrioty < NUM_PRIORITY; nCntPrioty++)
	{//�D��x�̐������J��Ԃ�
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{//Scene�̐������J��Ԃ�
			CScene2D *pScene;												//�V�[���̃|�C���^
			pScene = (CScene2D*)CScene::GetScene(nCntPrioty, nCntScene);	//�V�[���̎擾
			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;		//���
				objType = pScene->GetObjType();	//��ނ̎擾

				//=========================================================================
				// �v���C���[���̒e����
				//=========================================================================
				if (m_bulletType == BULLETTYPE_PLAYER_SALIVA)
				{//�v���C���[�̒e�̏ꍇ
					if (objType == OBJTYPE_ENEMY)
					{//���������̂��G�̏ꍇ

						CEnemy *pEnemy = (CEnemy*)pScene;
						D3DXVECTOR3 EnemyPos;			//�G�̈ʒu
						EnemyPos = pScene->GetPos();	//�ʒu�̎擾
						if (pos.x > EnemyPos.x - ENEMY_SIZE
							&& pos.x < EnemyPos.x + ENEMY_SIZE
							&& pos.y <  EnemyPos.y + ENEMY_SIZE
							&& pos.y > EnemyPos.y - ENEMY_SIZE)
						{
							//�G�̃_���[�W����
							pEnemy->HitDamage(1, CEnemy::ENEMY_TYPE_NOMAL);

							//�e�̏I������
							bDisappear = true;
						}
					}
					else if (objType == OBJTYPE_BOSS)
					{//���������̂��{�X�̏ꍇ
						CEnemyBoss *pBoss = (CEnemyBoss*)pScene;
						D3DXVECTOR3 BossPos;			//�{�X�̈ʒu
						BossPos = pScene->GetPos();		//�ʒu�̎擾
						if (pos.x > BossPos.x - BOSS_SIZE
							&& pos.x < BossPos.x + BOSS_SIZE
							&& pos.y <  BossPos.y + BOSS_SIZE
							&& pos.y > BossPos.y - BOSS_SIZE)
						{
							//�{�X�̃_���[�W����
							pBoss->HitDamage(1,CEnemy::ENEMY_TYPE_BOSS);

							//�e�̏I������
							bDisappear = true;
						}
					}
					else if (objType == OBJTYPE_CLOUD)
					{//���������̂��_�̏ꍇ
						D3DXVECTOR3 CloudPos;				//�G�̈ʒu
						CloudPos = pScene->GetPos();		//�ʒu�̎擾
						CCloud *pCloud = (CCloud*)pScene;	//�_�̓��I�m��

						if (pCloud != NULL && pCloud->GetCloud() == pCloud->CLOUD_BEANS)
						{
							if (pos.x > CloudPos.x - CLOUD_SIZE
								&& pos.x < CloudPos.x + CLOUD_SIZE
								&& pos.y <  CloudPos.y + CLOUD_SIZE
								&& pos.y > CloudPos.y - CLOUD_SIZE)
							{
								//�_�̈ړ����菈��
								pCloud->HitCloud();

								//�e�̏I������
								bDisappear = true;

							}

						}
					}
					else if (objType == OBJTYPE_BEANS)
					{//���������̂����̏ꍇ
						D3DXVECTOR3 BeansPos;				//�G�̈ʒu
						BeansPos = pScene->GetPos();		//�ʒu�̎擾
						CBeans *pBeans = (CBeans*)pScene;	//���̓��I�m��
						CScore *pScore = CGame::GetScore();	//�X�R�A�̎擾

						if (pBeans != NULL)
						{
							if (pos.x > BeansPos.x - BEANS_SIZE
								&& pos.x < BeansPos.x + BEANS_SIZE
								&& pos.y <  BeansPos.y + BEANS_SIZE
								&& pos.y > BeansPos.y - BEANS_SIZE)
							{
								//���̈ړ����菈��
								pBeans->HitBeans(pos);

								//�X�R�A�̉��Z
								pScore->AddScore(100);

								//�e�̏I������
								bDisappear = true;

							}
						}
					}
				}
				//=========================================================================
				// �v���C���[���̒e����
				//=========================================================================

				else if (m_bulletType == BULLETTYPE_PLAYER_SHIT)
				{
					if (objType == OBJTYPE_HUMAN)
					{//���������̂��G�̏ꍇ

						CEnemy *pEnemy = (CEnemy*)pScene;
						D3DXVECTOR3 EnemyPos;			//�G�̈ʒu
						EnemyPos = pScene->GetPos();	//�ʒu�̎擾
						if (pos.x > EnemyPos.x - ENEMY_SIZE
							&& pos.x < EnemyPos.x + ENEMY_SIZE
							&& pos.y <  EnemyPos.y + ENEMY_SIZE
							&& pos.y > EnemyPos.y - ENEMY_SIZE)
						{
							//�G�̃_���[�W����
							pEnemy->HitDamage(1,CEnemy::ENEMY_TYPE_NOMAL);

							//�e�̏I������
							bDisappear = true;
						}
					}
				}
				//=========================================================================
				// �G�̒e����
				//=========================================================================
				else if (m_bulletType == BULLETTYPE_ENEMY)
				{//�G�̒e�̏ꍇ
					if (objType == OBJTYPE_PLAYER)
					{//���������̂��v���C���[�̏ꍇ
						D3DXVECTOR3 PlayerPos;					//�G�̈ʒu
						PlayerPos = pScene->GetPos();			//�ʒu�̎擾
						CLife *pLife = (CLife*)pScene;			//���C�t�̓��I�m��
						CPlayer *pPlayer = (CPlayer*)pScene;	//�v���C���[�̓��I�m��
						CBarrier::BARRIER_STATE pBarrierState;	//�o���A�̏��
						pBarrierState = CBarrier::GetState();	//�o���A�̎擾����

						if (pos.x > PlayerPos.x - PLAYER_SIZE
							&& pos.x < PlayerPos.x + PLAYER_SIZE
							&& pos.y <  PlayerPos.y + PLAYER_SIZE
							&& pos.y > PlayerPos.y - PLAYER_SIZE)
						{
							if (pBarrierState == CBarrier::STATE_NONE && pPlayer->GetState() == CPlayer::STATE_NOMAL)
							{//�o���A�g�p��Ԃł͂Ȃ��܂��̓v���C���[���ʏ��Ԃ̏ꍇ
							 //�v���C���[�̃_���[�W����
								pPlayer->HitDamage(1);
								bDisappear = true;
							}
							else if (pBarrierState == CBarrier::STATE_USE)
							{
								bDisappear = true;
							}
						}
					}
					else if (objType == OBJTYPE_BARRIER)
					{//���������̂��o���A�̏ꍇ
					 //CEffect::Create(pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 12.0f);
						D3DXVECTOR3 BarrierPos;					//�G�̈ʒu
						BarrierPos = pScene->GetPos();			//�ʒu�̎擾
						CLife *pLife = (CLife*)pScene;			//�v���C���[�̓��I�m��
						CBarrier::BARRIER_STATE pBarrierState;	//�o���A�̏��
						pBarrierState = CBarrier::GetState();	//�o���A�̎擾

						if (pos.x + 30.0f > BarrierPos.x - BARRIER_SIZE
							&& pos.x - 30.0f < BarrierPos.x + BARRIER_SIZE
							&& pos.y - 30.0f <  BarrierPos.y + BARRIER_SIZE
							&& pos.y + 30.0f > BarrierPos.y - BARRIER_SIZE)
						{
							if (pBarrierState == CBarrier::STATE_USE)
							{//�o���A���g�p����Ă����Ԃ̏ꍇ
								bDisappear = true;
							}
						}
					}
				}
			}
		}
	}
	if (bDisappear == true)
	{//�e��true�ɂȂ����ꍇ
	 //�I������
		Uninit();
	}
}