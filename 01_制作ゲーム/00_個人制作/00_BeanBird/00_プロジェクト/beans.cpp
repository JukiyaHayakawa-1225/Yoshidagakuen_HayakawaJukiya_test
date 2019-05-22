//=============================================================================
//
// ���̏��� [player.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "beans.h"
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

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBeans::m_apTexture[MAX_BEANS_TEXTURE] = {};		//�e�N�X�`���̃|�C���^

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// ���̃R���X�g���N�^
//=============================================================================
CBeans::CBeans() : CScene2D(3)
{
	m_nCountBeans = 0;						//���̓��������񐔂������l
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ̏����l
	m_beansType = BEANS_TYPE_SCORE;			//���̎�ނ̏���
	m_beansState = BEANS_FLOATING;			//���̏�Ԃ̏���
}
//=============================================================================
// ���̃f�X�g���N�^
//=============================================================================
CBeans::~CBeans()
{

}

//=============================================================================
//���̐���
//=============================================================================
CBeans *CBeans::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CBeans *pBeans = NULL;									//���̃|�C���^
	if (pBeans == NULL)
	{//NULL�̏ꍇ
		pBeans = new CBeans;								//���̓��I�m��
		pBeans->SetPos(pos);								//�ʒu�̑��
		pBeans->SetWidth(fWight);							//���̑��
		pBeans->SetHeight(fHeight);							//�����̑��
		pBeans->Init();										//����������
		pBeans->BindTexture(m_apTexture[5]);				//�e�N�X�`��
		pBeans->m_nCountBeans = 0;							//���̏�����
		pBeans->m_move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�ړ��ʂ̏�����
	}
	return pBeans;											//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CBeans::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME007,
		&m_apTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\beans_bullet.png",
		&m_apTexture[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\beans_avatar.png",
		&m_apTexture[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\beans_barrier.png",
		&m_apTexture[3]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\beans_speed.png",
		&m_apTexture[4]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\beans_floating.png",
		&m_apTexture[5]);
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CBeans::Unload(void)
{
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_BEANS_TEXTURE; nCntEnemyTex++)
	{//�e�N�X�`���̐������J��Ԃ�
		// �e�N�X�`���̔j��
		if (m_apTexture[nCntEnemyTex] != NULL)
		{
			m_apTexture[nCntEnemyTex]->Release();
			m_apTexture[nCntEnemyTex] = NULL;
		}
	}
}

//=============================================================================
// ���̏���������
//=============================================================================
HRESULT CBeans::Init(void)
{
	//CScene2D�̏���������
	CScene2D::Init();
	//��ނ̐ݒ�
	SetObjType(OBJTYPE_BEANS);
	return S_OK;
}

//=============================================================================
// ���̏I������
//=============================================================================
void CBeans::Uninit(void)
{
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// ���̍X�V����
//=============================================================================
void CBeans::Update(void)
{
	//���̓����蔻�菈��
	Collision();
	//CScene2D�̍X�V����
	CScene2D::Update();

}

//=============================================================================
// ���̕`�揈��
//=============================================================================
void CBeans::Draw(void)
{
	//CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// ���̓����蔻�菈��
//=============================================================================
void CBeans::Collision(void)
{
	D3DXVECTOR3 pos;	//�ʒu
	pos = GetPos();		//�ʒu�̎擾

	m_rot -= 0.05f;	//�����̉�]����

	if (m_rot > D3DX_PI)
	{
		m_rot -= D3DX_PI * 2.0f;
	}
	else if (m_rot < -D3DX_PI)
	{
		m_rot += D3DX_PI * 2.0f;
	}

	if (m_beansState == BEANS_FLOATING)
	{//�������V��Ԃ̏ꍇ
	 //���̈ړ�
		D3DXVECTOR3 SetVtxPos(0.0f, -2.0f, 0.0f);
		m_move = SetVtxPos;
		//���𗎉���Ԃɂ���
		m_beansState = BEANS_FALL;
	}
	else if (m_beansState == BEANS_FALL)
	{//�����������Ԃ̏ꍇ
		m_move.y += 0.03f;	//�ړ��ʂ̉��Z
	}
	pos += m_move;			//�ړ��ʂ̉��Z

	//�ʒu�̐ݒu
	CScene2D::SetVtxRotPos(pos);

	for (int nCntPrioty = 0; nCntPrioty < 6; nCntPrioty++)
	{//�D��x��5�Ԃ܂ŌJ��Ԃ�
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{//Scene�̐������J��Ԃ�
			CScene2D *pScene;												//�V�[���̃|�C���^
			pScene = (CScene2D*)CScene::GetScene(nCntPrioty, nCntScene);	//�V�[���̎擾
			if (pScene != NULL)
			{//Scene��NULL�łȂ��ꍇ
				CScene::OBJTYPE objType;					//���
				objType = pScene->GetObjType();				//��ނ̎擾

				if (objType == OBJTYPE_PLAYER)
				{//�v���C���[�̏ꍇ
					D3DXVECTOR3 PlayerPos;					//�G�̈ʒu
					CPlayer *pPlayer = (CPlayer*)pScene;	//���̓��I�m��
					PlayerPos = pPlayer->GetPos();			//�ʒu�̎擾
					CSkill *pSkill = NULL;					//�X�L���̃|�C���^
					CScore *pScore = CGame::GetScore();		//�X�R�A�̎擾

					if (pPlayer != NULL)
					{//�v���C���[��NULL�łȂ��ꍇ
						if (pos.x > PlayerPos.x - PLAYER_SIZE
							&& pos.x < PlayerPos.x + PLAYER_SIZE
							&& pos.y <  PlayerPos.y + PLAYER_SIZE
							&& pos.y > PlayerPos.y - PLAYER_SIZE)
						{//�v���C���[�����͈͓̔��̏ꍇ
							switch (m_beansType)
							{
							case BEANS_TYPE_SCORE:		//�X�R�A��
								pScore->AddScore(1000);	//�X�R�A�̉��Z
								break;
							case BEANS_TYPE_BULLET:		//�e��
														//�e���QWay�ɂ���
								pPlayer->SetBullet(pPlayer->BULLET_SKILL);
								//�e���g�p���Ă����Ԃɂ���
								pSkill->SetSkill(pSkill->SKILL_2WAY, pSkill->SKILL_STATE_USE);
								break;
							case BEANS_TYPE_SPEED:		//�X�s�[�h��
														//�v���C���[�̃X�s�[�h���グ��
								pPlayer->SetSpeed(CPlayer::SPEED_SKILL);
								//�X�s�[�h���g�p���Ă����Ԃɂ���
								pSkill->SetSkill(pSkill->SKILL_SPEED, pSkill->SKILL_STATE_USE);
								break;
							case BEANS_TYPE_AVATAR:		//���g��
								CAvatar::AVATAR_STATE pAvatarState;				//���g���
								pAvatarState = CAvatar::GetAvatar();			//���g�̏�Ԏ擾
								if (pAvatarState == CAvatar::AVATAR_NONE)
								{//���g���g�p���Ă��Ȃ���Ԃɂ���
									CAvatar::Create(PlayerPos, 40.0f, 40.0f);	//���g�̐���
																				//���g���g�p���Ă����Ԃɂ���
									pSkill->SetSkill(pSkill->SKILL_AVATAR, pSkill->SKILL_STATE_USE);
								}
								break;
							case BEANS_TYPE_BARRIER:	//�o���A��
								CBarrier::BARRIER_STATE pBarrierState;	//�o���A�̏��
								pBarrierState = CBarrier::GetState();	//�o���A�̎擾
								if (pBarrierState == CBarrier::STATE_NONE)
								{//�o���A���g�p����Ă��Ȃ����
								 //�o���A�̐���
									CBarrier::Create(D3DXVECTOR3(PlayerPos.x, PlayerPos.y, PlayerPos.z), D3DXVECTOR3(0, 0.0, 0.0f), BARRIER_SIZE, BARRIER_SIZE);
									//�o���A���g�p���Ă����Ԃɂ���
									pSkill->SetSkill(pSkill->SKILL_BARRIER, pSkill->SKILL_STATE_USE);
								}
								break;
							}
							//���̏I������
							CBeans::Uninit();
						}
					}
				}
			}
		}
	}
	if (m_beansState == BEANS_FLOATING)
	{//�������V��Ԃ̏ꍇ
		BindTexture(m_apTexture[5]);
	}
	else if (m_beansState == BEANS_FALL)
	{//����������Ԃ̏ꍇ
		switch (m_beansType)
		{
		case BEANS_TYPE_SCORE:			//�X�R�A��
			BindTexture(m_apTexture[0]);
			break;
		case BEANS_TYPE_BULLET:			//�e��
			BindTexture(m_apTexture[1]);
			break;
		case BEANS_TYPE_AVATAR:			//���g��
			BindTexture(m_apTexture[2]);
			break;
		case BEANS_TYPE_BARRIER:		//�o���A��
			BindTexture(m_apTexture[3]);
			break;
		case BEANS_TYPE_SPEED:			//�X�s�[�h��
			BindTexture(m_apTexture[4]);
			break;
		}
	}
	if (pos.y >= SCREEN_HEIGHT + 50 || pos.x <= 250.0f || pos.x >= SCREEN_WIDTH)
	{//��ʊO�ɂ������ꍇ
		//���̏I������
		CBeans::Uninit();
	}
}

//=============================================================================
// �����̎擾����
//=============================================================================
float CBeans::GetRot(void)
{
	return m_rot;		//�l��Ԃ�
}

//=============================================================================
// ���̃_���[�W����
//=============================================================================
void CBeans::HitBeans(D3DXVECTOR3 pos)
{
	int nType;					//���
	if (m_beansState == BEANS_FALL)
	{//����������Ԃ̏ꍇ
		m_nCountBeans++;		//���̃J�E���g���Z
		D3DXVECTOR3 BeansPos;	//�ʒu
		BeansPos = GetPos();	//�ʒu�̎擾
		if (m_nCountBeans == 3)
		{//���ɂR�񂠂����ꍇ
			//�����_���Ő؂�ւ��
			nType = rand() % 4 + 2;
			switch (nType)
			{
			case BEANS_TYPE_BULLET:
				//�e���ɂ���
				m_beansType = BEANS_TYPE_BULLET;
				break;
			case BEANS_TYPE_SPEED:
				//�X�s�[�h���ɂ���
				m_beansType = BEANS_TYPE_SPEED;
				break;
			case BEANS_TYPE_AVATAR:
				//���g���ɂ���
				m_beansType = BEANS_TYPE_AVATAR;
				break;
			case BEANS_TYPE_BARRIER:
				//�o���A���ɂ���
				m_beansType = BEANS_TYPE_BARRIER;
				break;
			}
		}
		else if (m_nCountBeans == 4)
		{//4��ڂ̏ꍇ
			m_beansType = BEANS_TYPE_SCORE;	//�X�R�A���ɂ���
			m_nCountBeans = 0;				//���̃J�E���g������
		}
		////�p�x�̐ݒ�
		//float fAngle = atan2f(pos.x - BeansPos.x, pos.y - BeansPos.y);
		////�ʒu�ݒu
		//D3DXVECTOR3 SetVtxPos(sinf(fAngle) * -0.5f, cosf(fAngle) * -3.0f, 0.0f);
		if (pos.x >= 790)
		{
			D3DXVECTOR3 leftPos = D3DXVECTOR3(-0.5f, -2.0f, 0.0f);
			m_move = leftPos;
		}
		else if (pos.x <= 790)
		{
			D3DXVECTOR3 rightPos = D3DXVECTOR3(0.5f, -2.0f, 0.0f);
			m_move = rightPos;
		}
	}
}

//=============================================================================
// �ړ��ʂ̐ݒu����
//=============================================================================
void CBeans::SetMove(D3DXVECTOR3 move)
{
	D3DXVECTOR3 pos;	//�ʒu

	pos = GetPos();		//�ʒu�̎擾
	m_move = move;		//�ړ��ʑ��
	m_move.y += 0.5;	//
	pos += m_move;		//

}