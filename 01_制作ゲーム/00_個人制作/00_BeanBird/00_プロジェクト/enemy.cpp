//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "enemy.h"
#include "game.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explotion.h"
#include "score.h"
#include "fade.h"
#include "result.h"
#include "player.h"
#include "barrier.h"
#include "defense.h"
#include "particle.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
int CEnemy::m_nNumEnemy = 0;

//=============================================================================
// �}�N����`
//=============================================================================
#define DAMAGE_TIME (5)	//�_���[�W�̎���

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene2D(nPriority)
{
	m_fSpin = 1.0f;
	m_nLife = 1;							//�̗͂̏����l
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�̏����l
	m_nNumEnemy++;							//�������Z
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	//CScene2D�̏���������
	CScene2D::Init();
	//��ނ̐ݒ�
	SetObjType(OBJTYPE_ENEMY);
	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemy::Uninit(void)
{
	//�G�̑��������炷
	m_nNumEnemy--;

	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemy::Update(void)
{
	D3DXVECTOR3 pos;	//�ʒu
	pos = GetPos();		//�ʒu�̎擾

	switch (m_enemyState)
	{
	case ENEMYSTATE_NORMAL:	//�ʏ���
		break;
	case ENEMYSTATE_DAMEGE:	//�_���[�W���
		m_nCountState--;	//���Z����
		if (m_nCountState <= 0)
		{
			m_enemyState = ENEMYSTATE_NORMAL;

			//�F�̎擾
			D3DXCOLOR col;
			col = GetCol();

			//�F�̎w��
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�F�̐ݒu
			SetCol(col);

		}
	}
	if (pos.y >= SCREEN_HEIGHT + 50 || pos.y <= -500 || pos.x <= 250.0f || pos.x >= SCREEN_WIDTH)
	{//�͈͊O�̏ꍇ
		//�I������
		CEnemy::Uninit();
	}
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	//CScene2D�̕`�揈��
	CScene2D::Draw();
}
//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void CEnemy::HitDamage(int nDamage,CEnemy::ENEMY_TYPE type)
{
	CScore *pScore = CGame::GetScore();

	m_nLife -= nDamage;

	if (m_nLife <= 0)
	{// �G�̃��C�t��0�ɂȂ����Ƃ�
		//�ʒu�̎擾
		D3DXVECTOR3 pos;
		pos = GetPos();

		switch (type)
		{
		case ENEMY_TYPE_NOMAL:
			//�X�R�A�̉��Z
			pScore->AddScore(500);

			//�����̐���
			//CExplotion::Create(pos, 50.0f,50);

			for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
			{
				m_fSpin += 0.05f;
				D3DXVECTOR3 movePar(0.0f, 0.0f, 0.0f);
				movePar.x = sinf(D3DX_PI * m_fSpin) * (rand() % 10 * 0.3f);
				movePar.y = cosf(D3DX_PI * m_fSpin) * (rand() % 10 * 0.3f);
				CParticle::Create(pos, movePar, D3DXCOLOR(rand() % 10 * 0.15f, rand() % 10 * 0.15f, rand() % 10 * 0.15f, 1.0f), rand() % 10 + 30.0f);
			}

			//�I������
			Uninit();
			break;
		case ENEMY_TYPE_BOSS:
			//�X�R�A�̉��Z
			pScore->AddScore(10000);

			for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
			{
				m_fSpin += 0.05f;
				D3DXVECTOR3 movePar(0.0f, 0.0f, 0.0f);
				movePar.x = sinf(D3DX_PI * m_fSpin) * (rand() % 10 * 0.3f);
				movePar.y = cosf(D3DX_PI * m_fSpin) * (rand() % 10 * 0.3f);
				CParticle::Create(pos, movePar, D3DXCOLOR(rand() % 10 * 0.15f, rand() % 10 * 0.15f, rand() % 10 * 0.15f, 1.0f), rand() % 30 + 30.0f);
			}
			CGame::SetState(CGame::STATE_END);
			//�I������
			Uninit();
			break;
		}

	}
	else
	{
		m_enemyState = ENEMYSTATE_DAMEGE;	//�_���[�W��Ԃɂ���
		m_nCountState = DAMAGE_TIME;		//�_���[�W�̎���

		//�F�̎擾
		D3DXCOLOR col;
		col = GetCol();

		//�F�̎w��
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//�F�̐ݒu
		SetCol(col);
	}
}

//=============================================================================
// �G�̓����蔻�菈��
//=============================================================================
void CEnemy::Collision(void)
{
	D3DXVECTOR3 pos;	//�ʒu
	pos = GetPos();		//�ʒu�̎擾

	CBarrier::BARRIER_STATE pBarrierState;	//�o���A�̏��
	pBarrierState = CBarrier::GetState();	//�o���A�̎擾

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

				if (objType == OBJTYPE_PLAYER)
				{//�v���C���[�̏ꍇ
					D3DXVECTOR3 PlayerPos;					//�G�̈ʒu
					PlayerPos = pScene->GetPos();			//�ʒu�̎擾
					CPlayer *pPlayer = (CPlayer*)pScene;
					if (pos.x > PlayerPos.x - PLAYER_SIZE
						&& pos.x < PlayerPos.x + PLAYER_SIZE
						&& pos.y <  PlayerPos.y + PLAYER_SIZE
						&& pos.y > PlayerPos.y - PLAYER_SIZE)
					{
						if (pBarrierState == CBarrier::STATE_NONE && objType == OBJTYPE_PLAYER)
						{//�o���A���g�p���Ă��Ȃ��ꍇ
						 //�_���[�W����
							pPlayer->HitDamage(3);
						}
					}
				}
				else if (objType == OBJTYPE_BARRIER)
				{//�o���A�̏ꍇ
					D3DXVECTOR3 BarrierPos;					//�G�̈ʒu
					BarrierPos = pScene->GetPos();			//�ʒu�̎擾
					CBarrier::BARRIER_STATE pBarrierState;
					pBarrierState = CBarrier::GetState();

					if (pos.x + 30.0f > BarrierPos.x - BARRIER_SIZE
						&& pos.x - 30.0f < BarrierPos.x + BARRIER_SIZE
						&& pos.y - 30.0f <  BarrierPos.y + BARRIER_SIZE
						&& pos.y + 30.0f > BarrierPos.y - BARRIER_SIZE)
					{

						if (pBarrierState == CBarrier::STATE_USE)
						{//�o���A���g�p����Ă���ꍇ
						 //�I������
							CScore *pScore = CGame::GetScore();
							pScore->AddScore(250);
							for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
							{
								m_fSpin += 0.05f;
								D3DXVECTOR3 movePar(0.0f, 0.0f, 0.0f);
								movePar.x = sinf(D3DX_PI * m_fSpin) * (rand() % 10 * 0.3f);
								movePar.y = cosf(D3DX_PI * m_fSpin) * (rand() % 10 * 0.3f);
								CParticle::Create(pos, movePar, D3DXCOLOR(rand() % 10 * 0.15f, rand() % 10 * 0.15f, rand() % 10 * 0.15f, 1.0f), rand() % 10 + 30.0f);
							}
							//�I������
							CEnemy::Uninit();
						}
					}
				}
			}
		}
	}
}

//=============================================================================
//
// �G���ړ��̏���
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemySlide::m_pTexture = NULL;
//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemySlide::CEnemySlide() : CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�̏����l
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemySlide::~CEnemySlide()
{

}

//=============================================================================
//�G�̐���
//=============================================================================
CEnemySlide *CEnemySlide::Create(D3DXVECTOR3 pos, float fWight, float fHeight,CEnemySlide::SLIDE slide)
{
	CEnemySlide *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemySlide;			//�V�[���̓��I�m��
		pEnemy->SetPos(pos);				//�ʒu�̑��
		pEnemy->SetWidth(fWight);			//���̑��
		pEnemy->SetHeight(fHeight);			//�����̑��
		pEnemy->m_slide = slide;			//��Ԃ̑��
		pEnemy->Init();						//����������
		pEnemy->BindTexture(m_pTexture);	//�e�N�X�`��
	}
	return pEnemy;							//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEnemySlide::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME006,
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CEnemySlide::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}


//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemySlide::Init(void)
{
	//CScene2D�̏���������
	CEnemy::Init();
	m_move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemySlide::Uninit(void)
{
	//CScene2D�̏I������
	CEnemy::Uninit();
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemySlide::Update(void)
{
	D3DXVECTOR3 pos;			//�ʒu
	pos = GetPos();				//�ʒu�̎擾

	for (int nCntPrioty = 0; nCntPrioty < 6; nCntPrioty++)
	{//�D��x�̐������J��Ԃ�
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{//Scene��4�Ԃ����J��Ԃ�
			CScene2D *pScene;												//�V�[���̃|�C���^
			pScene = (CScene2D*)CScene::GetScene(nCntPrioty, nCntScene);	//�V�[���̎擾
			if (pScene != NULL)
			{//Scene��NULL�łȂ��ꍇ
				CScene::OBJTYPE objType;		//���
				objType = pScene->GetObjType();	//��ނ̎擾
				if (objType == OBJTYPE_PLAYER)
				{//�v���C���[�̏ꍇ
					D3DXVECTOR3 PlayerPos;					//�v���C���[�̈ʒu
					CPlayer *pPlayer = (CPlayer*)pScene;	//�v���C���[�̓��I�m��
					PlayerPos = pPlayer->GetPos();			//�ʒu�̎擾
					if (pPlayer != NULL)
					{//�v���C���[��NULL�łȂ��ꍇ
					 	if (pos.y >= PlayerPos.y + 5)
					 	{
							switch (m_slide)
							{
							case SLIDE_R:
								m_move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);
								break;
							case SLIDE_L:
								m_move = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);
							}
					 	}
					}
				}
			}
		}
	}
	pos += m_move;
	//�ʒu�̐ݒu
	SetVtxPos(pos);
	CEnemy::Update();
	CEnemy::Collision();
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemySlide::Draw(void)
{
	//CScene2D�̕`�揈��
	CEnemy::Draw();
}

//=============================================================================
//
// �G�Ȑ��ړ��̏���
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemyCurve::m_pTexture = NULL;
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemyCurve::CEnemyCurve() : CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemyCurve::~CEnemyCurve()
{

}

//=============================================================================
//�G�̐���
//=============================================================================
CEnemyCurve *CEnemyCurve::Create(D3DXVECTOR3 pos, float fWight, float fHeight,CEnemyCurve::CURVE curve)
{
	CEnemyCurve *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemyCurve;		//�V�[���̓��I�m��
		pEnemy->SetPos(pos);			//�ʒu�̑��
		pEnemy->SetWidth(fWight);		//���̑��
		pEnemy->SetHeight(fHeight);		//�����̑��
		pEnemy->m_curve = curve;		//��Ԃ̑��
		pEnemy->Init();					//����������
		pEnemy->BindTexture(m_pTexture);
	}
	return pEnemy;					//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEnemyCurve::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy002.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CEnemyCurve::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}


//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyCurve::Init(void)
{
	//CScene2D�̏���������
	CEnemy::Init();
	m_move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_nCounter = 0;
	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemyCurve::Uninit(void)
{
	//CScene2D�̏I������
	CEnemy::Uninit();
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemyCurve::Update(void)
{
	D3DXVECTOR3 pos;			//�ʒu

	pos = GetPos();				//�ʒu�̎擾

	pos += m_move;				//�ړ��ʉ��Z
	if (pos.y >= 0)
	{
		m_nCounter++;
	}
	switch (m_curve)
	{
	case CURVE_R:
		if (m_nCounter < 200)
		{//�J�E���^���Q�O�O�ȉ��܂ňړ�
			m_move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		}
		if (m_nCounter >= 200)
		{//�Q�O�O�ȏ�ɂȂ����ꍇ
			m_move = D3DXVECTOR3(sinf(D3DX_PI*(m_nCounter - 200.0f) / 160.0f)*4.0f, sinf(D3DX_PI*(m_nCounter - 120.0f) / 160.0f)*4.0f, 0.0f);
		}
		if (m_nCounter >= 350)
		{//350�ȏ�ɂȂ����ꍇ
			m_move = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
		}
		break;

	case CURVE_L:
		if (m_nCounter < 200)
		{//200��菬�����Ȃ����ꍇ
			m_move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		}
		if (m_nCounter >= 200)
		{//200�ȏ�ɂȂ����ꍇ
			m_move = D3DXVECTOR3(sinf(-D3DX_PI*(m_nCounter - 200.0f) / 160.0f)*4.0f, sinf(D3DX_PI*(m_nCounter - 120.0f) / 160.0f)*4.0f, 0.0f);
		}
		if (m_nCounter >= 350)
		{//350�ȏ�ɂȂ����ꍇ
			m_move = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
		}
	}
	//�ʒu�̐ݒu
	SetVtxPos(pos);

	//�X�V����
	CEnemy::Update();
	//�����蔻��
	CEnemy::Collision();
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemyCurve::Draw(void)
{
	//CScene2D�̕`�揈��
	CEnemy::Draw();
}

//=============================================================================
//
// �G�֍s�ړ��̏���
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemyMeandering::m_pTexture = NULL;
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemyMeandering::CEnemyMeandering() : CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemyMeandering::~CEnemyMeandering()
{

}

//=============================================================================
//�G�̐���
//=============================================================================
CEnemyMeandering *CEnemyMeandering::Create(D3DXVECTOR3 pos, float fWight, float fHeight, CEnemyMeandering::MEANDERING meandering)
{
	CEnemyMeandering *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemyMeandering;			//�V�[���̓��I�m��
		pEnemy->SetPos(pos);					//�ʒu�̑��
		pEnemy->SetWidth(fWight);				//���̑��
		pEnemy->SetHeight(fHeight);				//�����̑��
		pEnemy->m_meandering = meandering;		//��Ԃ̑��
		pEnemy->Init();							//����������
		pEnemy->BindTexture(m_pTexture);
	}
	return pEnemy;								//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEnemyMeandering::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy004.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CEnemyMeandering::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}


//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyMeandering::Init(void)
{
	//CScene2D�̏���������
	CEnemy::Init();
	m_move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_nCounter = 0;
	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemyMeandering::Uninit(void)
{
	//CScene2D�̏I������
	CEnemy::Uninit();
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemyMeandering::Update(void)
{

	D3DXVECTOR3 pos;			//�ʒu

	pos = GetPos();				//�ʒu�̎擾
	if (pos.y >= 0)
	{
		m_nCounter++;
	}
	switch (m_meandering)
	{
	case MEANDERING_R:
		if (m_nCounter < 50)
		{
			m_move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		}
		else if (m_nCounter > 50)
		{
			m_move = D3DXVECTOR3(sinf(D3DX_PI*(m_nCounter - 50.0f) / 160.0f)*2.0f,1.0f, 0.0f);
		}
		else if (m_nCounter > 200)
		{
			//m_move = D3DXVECTOR3(sinf(-D3DX_PI*(m_nCounter) / -160.0f)*3.0f, sinf(D3DX_PI*(m_nCounter - 120) / 80.0f)*3.0f, 0.0f);
		}
		break;

	case MEANDERING_L:
		if (m_nCounter < 50)
		{
			m_move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		}
		if (m_nCounter > 50)
		{
			m_move = D3DXVECTOR3(sinf(-D3DX_PI*(m_nCounter - 50.0f) / 160.0f)*2.5f,1.0f, 0.0f);
		}
		if (m_nCounter >= 350)
		{
			//m_move = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
		}
	}
	pos += m_move;
	//�ʒu�̐ݒu
	SetVtxPos(pos);

	CEnemy::Update();
	CEnemy::Collision();
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemyMeandering::Draw(void)
{
	//CScene2D�̕`�揈��
	CEnemy::Draw();
}

//=============================================================================
//
// �G�ǔ��ړ��̏���
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemyTracking::m_pTexture = NULL;
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemyTracking::CEnemyTracking() : CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemyTracking::~CEnemyTracking()
{

}

//=============================================================================
//�G�̐���
//=============================================================================
CEnemyTracking *CEnemyTracking::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CEnemyTracking *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemyTracking;			//�V�[���̓��I�m��
		pEnemy->SetPos(pos);					//�ʒu�̑��
		pEnemy->SetWidth(fWight);				//���̑��
		pEnemy->SetHeight(fHeight);				//�����̑��
		pEnemy->Init();							//����������
		pEnemy->BindTexture(m_pTexture);
	}
	return pEnemy;								//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEnemyTracking::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy003.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CEnemyTracking::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}


//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyTracking::Init(void)
{
	//CScene2D�̏���������
	CEnemy::Init();
	m_move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_nCounter = 0;
	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemyTracking::Uninit(void)
{
	//CScene2D�̏I������
	CEnemy::Uninit();
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemyTracking::Update(void)
{
	D3DXVECTOR3 pos;			//�ʒu

	pos = GetPos();				//�ʒu�̎擾
	if (pos.y >= 0)
	{
		m_nCounter++;
	}
	for (int nCntPrioty = 0; nCntPrioty < 6; nCntPrioty++)
	{//�D��x�̐������J��Ԃ�
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{//Scene��4�Ԃ����J��Ԃ�
			CScene2D *pScene;												//�V�[���̃|�C���^
			pScene = (CScene2D*)CScene::GetScene(nCntPrioty, nCntScene);	//�V�[���̎擾
			if (pScene != NULL)
			{//Scene��NULL�łȂ��ꍇ
				CScene::OBJTYPE objType;		//���
				objType = pScene->GetObjType();	//��ނ̎擾
				if (objType == OBJTYPE_PLAYER)
				{//�v���C���[�̏ꍇ
					D3DXVECTOR3 PlayerPos;					//�v���C���[�̈ʒu
					CPlayer *pPlayer = (CPlayer*)pScene;	//�v���C���[�̓��I�m��
					PlayerPos = pPlayer->GetPos();			//�ʒu�̎擾
					if (pPlayer != NULL)
					{//�v���C���[��NULL�łȂ��ꍇ
							float fData = atan2f(PlayerPos.x - pos.x, PlayerPos.y - pos.y);
							if (m_nCounter == 200)
							{
								m_move = D3DXVECTOR3(sinf(fData) * 3.0f, cosf(fData) *3.0f, 0.0f);
							}
							//CBullet::Create(pos, D3DXVECTOR3(sinf(fData) * 7.0f, cosf(fData) *7.0f, 0.0f),10.0,10.0, CBullet::BULLETTYPE_ENEMY);
					}
				}
			}
		}
	}

	pos += m_move;
	//�ʒu�̐ݒu
	SetVtxPos(pos);

	CEnemy::Update();
	CEnemy::Collision();
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemyTracking::Draw(void)
{
	//CScene2D�̕`�揈��
	CEnemy::Draw();
}

//=============================================================================
//
// �l�Ԃ̏���
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemyHuman::m_pTexture = NULL;
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemyHuman::CEnemyHuman() : CEnemy(2)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemyHuman::~CEnemyHuman()
{

}

//=============================================================================
//�G�̐���
//=============================================================================
CEnemyHuman *CEnemyHuman::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CEnemyHuman *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemyHuman;			//�V�[���̓��I�m��
		pEnemy->SetPos(pos);				//�ʒu�̑��
		pEnemy->SetWidth(fWight);			//���̑��
		pEnemy->SetHeight(fHeight);			//�����̑��
		pEnemy->Init();						//����������
		pEnemy->BindTexture(m_pTexture);
	}
	return pEnemy;					//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEnemyHuman::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME010,
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CEnemyHuman::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}


//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyHuman::Init(void)
{
	//CScene2D�̏���������
	CEnemy::Init();
	m_move = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	m_nCounter = 0;
	SetObjType(OBJTYPE_HUMAN);
	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemyHuman::Uninit(void)
{
	//CScene2D�̏I������
	CEnemy::Uninit();
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemyHuman::Update(void)
{
	D3DXVECTOR3 pos;			//�ʒu

	pos = GetPos();				//�ʒu�̎擾

	if (pos.y >= 0)
	{
		for (int nCntPrioty = 0; nCntPrioty < 6; nCntPrioty++)
		{//�D��x�̐������J��Ԃ�
			for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
			{//Scene��4�Ԃ����J��Ԃ�
				CScene2D *pScene;												//�V�[���̃|�C���^
				pScene = (CScene2D*)CScene::GetScene(nCntPrioty, nCntScene);	//�V�[���̎擾
				if (pScene != NULL)
				{//Scene��NULL�łȂ��ꍇ
					CScene::OBJTYPE objType;		//���
					objType = pScene->GetObjType();	//��ނ̎擾
					if (objType == OBJTYPE_PLAYER)
					{//�v���C���[�̏ꍇ
						D3DXVECTOR3 PlayerPos;					//�v���C���[�̈ʒu
						CPlayer *pPlayer = (CPlayer*)pScene;	//�v���C���[�̓��I�m��
						PlayerPos = pPlayer->GetPos();			//�ʒu�̎擾
						if (pPlayer != NULL)
						{//�v���C���[��NULL�łȂ��ꍇ
							float fData = atan2f(PlayerPos.x - pos.x, PlayerPos.y - pos.y);
							//�e�̐���
							if (rand() % 100 == 0)
							{
								CBullet::Create(pos, D3DXVECTOR3(sinf(fData) * 7.0f, cosf(fData) *7.0f, 0.0f), 20.0f, 20.0f, CBullet::BULLETTYPE_ENEMY);
							}
						}
					}
				}
			}
		}
	}
	pos += m_move;
	//�ʒu�̐ݒu
	SetVtxPos(pos);
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemyHuman::Draw(void)
{
	//CScene2D�̕`�揈��
	CEnemy::Draw();
}

//=============================================================================
//
// �{�X�̏���
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemyBoss::m_pTexture = NULL;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemyBoss::CEnemyBoss() : CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemyBoss::~CEnemyBoss()
{

}

//=============================================================================
//�G�̐���
//=============================================================================
CEnemyBoss *CEnemyBoss::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CEnemyBoss *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemyBoss;			//�V�[���̓��I�m��
		pEnemy->SetPos(pos);				//�ʒu�̑��
		pEnemy->SetWidth(fWight);			//���̑��
		pEnemy->SetHeight(fHeight);			//�����̑��
		pEnemy->Init();						//����������
		pEnemy->BindTexture(m_pTexture);
	}
	return pEnemy;					//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEnemyBoss::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy005.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CEnemyBoss::Unload(void)
{
	m_pTexture->Release();
	m_pTexture = NULL;
}


//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyBoss::Init(void)
{
	//CScene2D�̏���������
	CEnemy::Init();
	m_move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_nCounter = 0;
	m_nLife = 100;
	SetObjType(OBJTYPE_BOSS);
	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemyBoss::Uninit(void)
{
	//CScene2D�̏I������
	CEnemy::Uninit();
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemyBoss::Update(void)
{
	D3DXVECTOR3 pos;			//�ʒu
	pos = GetPos();				//�ʒu�̎擾
	m_nCounter++;
	if (m_nCounter >= 250)
	{
		CBarrier::BARRIER_STATE pBarrierState;	//�o���A�̏��
		pBarrierState = CBarrier::GetState();	//�o���A�̎擾

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

					if (objType == OBJTYPE_PLAYER)
					{//�v���C���[�̏ꍇ
						D3DXVECTOR3 PlayerPos;					//�G�̈ʒu
						PlayerPos = pScene->GetPos();			//�ʒu�̎擾
						CPlayer *pPlayer = (CPlayer*)pScene;
						if (pos.x > PlayerPos.x - BULLET_HIT
							&& pos.x < PlayerPos.x + BULLET_HIT
							&& pos.y <  PlayerPos.y + BULLET_HIT
							&& pos.y > PlayerPos.y - BULLET_HIT)
						{
							if (pBarrierState == CBarrier::STATE_NONE)
							{//�o���A���g�p���Ă��Ȃ��ꍇ
							 //�_���[�W����
								pPlayer->HitDamage(3);
							}
						}
					}
					else if (objType == OBJTYPE_BARRIER)
					{//�o���A�̏ꍇ
						D3DXVECTOR3 BarrierPos;					//�G�̈ʒu
						BarrierPos = pScene->GetPos();			//�ʒu�̎擾
						CBarrier::BARRIER_STATE pBarrierState;
						pBarrierState = CBarrier::GetState();

						if (pos.x + 30.0f > BarrierPos.x - BULLET_HIT
							&& pos.x - 30.0f < BarrierPos.x + BULLET_HIT
							&& pos.y - 30.0f <  BarrierPos.y + BULLET_HIT
							&& pos.y + 30.0f > BarrierPos.y - BULLET_HIT)
						{

							if (pBarrierState == CBarrier::STATE_USE)
							{//�o���A���g�p����Ă���ꍇ
							}
						}
					}
				}
			}
		}
		//�G�̈ړ�����
		m_move = D3DXVECTOR3(sinf(D3DX_PI*(m_nCounter) / -160.0f)*5.0f, sinf(D3DX_PI*(m_nCounter - 120) / 80.0f)*3.0f, 0.0f);
		if (rand() % 50 == 0)
		{
			//�e�̐���
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 20, pos.z), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 20.0f, 20.0f, CBullet::BULLETTYPE_ENEMY);

			//CDefense::Create(D3DXVECTOR3(pos.x,pos.y,pos.z), 10.0f, 10.0f);
		}
	}

	pos += m_move;
	//�ʒu�̐ݒu
	SetVtxPos(pos);
	CEnemy::Update();
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemyBoss::Draw(void)
{
	//CScene2D�̕`�揈��
	CEnemy::Draw();
}