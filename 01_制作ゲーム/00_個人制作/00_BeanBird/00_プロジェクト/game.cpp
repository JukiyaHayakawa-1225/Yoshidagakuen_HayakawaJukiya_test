//=============================================================================
//
// �Q�[������ [manager.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "game.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "player.h"
#include "bullet.h"
#include "explotion.h"
#include "bg.h"
#include "enemy.h"
#include "beans.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "effect.h"
#include "stock.h"
#include "fade.h"
#include "barrier.h"
#include "avatar.h"
#include "skill.h"
#include "logo.h"
#include "pause.h"
#include "cloud.h"
#include "frame.h"
#include "defense.h"
#include "particle.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScore *CGame::m_pScore = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CGame::GAME_STATE CGame::m_state = STATE_START;

//=============================================================================
// �Q�[���̃R���X�g���N�^
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CGame *CGame::Create()
{
	CGame *pGame = NULL;
	if (pGame == NULL)
	{
		pGame = new CGame;	//���I�m��
		if (pGame != NULL)
		{
			pGame->Init();	//����������
		}
	}
	return pGame;
}

//=============================================================================
// �Q�[���̏���������
//=============================================================================
HRESULT CGame::Init(void)
{
	m_nSpawnCloud = 0;
	m_nMainTimer = 0;
	m_nSpawnHuman = 0;
	m_state = STATE_START;

	//�Q�[���w�i�̓ǂݍ���
	CBgGame::Load();
	//�����̓ǂݍ���
	CNumber::Load();
	//�v���C���[�̓ǂݍ���
	CPlayer::Load();
	//�G�̓ǂݍ���
	CEnemySlide::Load();
	CEnemyCurve::Load();
	CEnemyMeandering::Load();
	CEnemyTracking::Load();
	CEnemyHuman::Load();
	CEnemyBoss::Load();
	//�G�̖h�q�̓ǂݍ���
	CDefense::Load();

	//�e�̓ǂݍ���
	CBullet::Load();
	//�����̓ǂݍ���
	CExplotion::Load();
	//���̓ǂݍ���
	CBeans::Load();
	//���C�t�̓ǂݍ���
	CLife::Load();
	//�c�@�̓ǂݍ���
	CStock::Load();
	//�G�t�F�N�g�̓ǂݍ���
	CEffect::Load();
	//�p�[�e�B�N���̓ǂݍ���
	CParticle::Load();
	//�o���A�ǂݍ���
	CBarrier::Load();
	//���g�̓ǂݍ���
	CAvatar::Load();
	//�X�L���̓ǂݍ���
	CSkill::Load();
	//UI�w�i�̓ǂݍ���
	CBgUI::Load();
	//�|�[�Y�̓ǂݍ���
	CPause::Load();
	//�_�̓ǂݍ���
	CCloud::Load();
	//�t���[���̓ǂݍ���
	CFrame::Load();

	//�^�[�Q�b�g�̓ǂݍ���
	CTargetLogo::Load();

	//�t���[���̐���
	CFrame::Create(D3DXVECTOR3(145.0f, 90.0f ,0.0f), 145.0f, 90, CFrame::FRAME_SKILL);
	CFrame::Create(D3DXVECTOR3(145.0f, 270.0f, 0.0f), 145.0f, 90, CFrame::FRAME_STOCK);
	CFrame::Create(D3DXVECTOR3(145.0f, 450.0f, 0.0f), 145.0f, 90, CFrame::FRAME_LIFE);
	CFrame::Create(D3DXVECTOR3(145.0f, 630.0f, 0.0f), 145.0f, 90, CFrame::FRAME_SCORE);

	//�w�i�̐���
	CBgGame::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2, 0.0f), 500.0f, SCREEN_HEIGHT / 2);

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(260.0f, 665.0f, 0.0f),23.0f, 23.0f);

	//�c�@�̐���
	CStock::Create(D3DXVECTOR3(70.0f, 305.0f, 0.0f), 35.0f, 35.0f);

	//���C�t�̐���
	CLife::Create(D3DXVECTOR3(70.0f, 485.0f, 0.0f),35.0f, 35.0f);

	//�X�L���̐���
	CSkill::Create(D3DXVECTOR3(47.5f, 135.0f, 0.0f), 30.0f, 30.0f);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2,650.0f, 0.0f), PLAYER_SIZE, PLAYER_SIZE,CPlayer::STATE_NOMAL);
	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	//�^�[�Q�b�g�̔j��
	CTargetLogo::Unload();

	//�t���[���̔j��
	CFrame::Unload();
	//�_�̔j��
	CCloud::Unload();

	//�|�[�Y�̔j��
	CPause::Unload();

	//�X�L���̔j��
	CSkill::Unload();

	//���g�̔j��
	CAvatar::Unload();

	//�w�i�̔j��
	CBgGame::Unload();

	//�����̔j��
	CNumber::Unload();

	//���C�t�̔j��
	CLife::Unload();

	//�c�@�̔j��
	CStock::Unload();

	//�v���C���[�̔j��
	CPlayer::Unload();

	//�G�̖h�q�̔j��
	CDefense::Unload();

	//�G�̔j��
	CEnemySlide::Unload();
	//�G�̔j��
	CEnemyCurve::Unload();
	//�G�̔j��
	CEnemyMeandering::Unload();
	//�G�̔j��
	CEnemyHuman::Unload();
	//�G�̔j��
	CEnemyBoss::Unload();
	//�e�̔j��
	CBullet::Unload();

	//�����̔j��
	CExplotion::Unload();

	//���̔j��
	CBeans::Unload();

	//�p�[�e�B�N���̔j��
	CParticle::Unload();

	//�G�t�F�N�g�̔j��
	CEffect::Unload();

	//�o���A�̔j��
	CBarrier::Unload();

	//UI�w�i�̔j��
	CBgUI::Unload();

	m_nSpawnCloud = 0;
	m_nMainTimer = 0;
	m_nSpawnHuman = 0;

	CScene::ReleaseAll();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();
	//�t�F�[�h�̎擾
	CFade::FADE fade;
	CFade *pFade = NULL;
	fade = pFade->GetFade();
	if (CRenderer::GetPause() == false)
	{
		CEnemyBoss *pBoss = NULL;
		if (pBoss == NULL)
		{
			if (m_state == STATE_END)
			{
				CResult *pResult = NULL;
				CManager *pManager = NULL;
				if (pResult == NULL)
				{
					pResult->SetResult(pResult->RESULT_CLEAR);
				}
				CFade::Create(CManager::MODE_RESULT, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
				if (pManager == NULL && fade == CFade::FADE_NONE)
				{
					pManager->SetGameScore(m_pScore->GetScore());
				}
			}
		}
		if (m_pPlayer->GetState() == m_pPlayer->STATE_END)
		{
			CResult *pResult = NULL;
			CManager *pManager = NULL;
			if (pResult == NULL)
			{
				pResult->SetResult(pResult->RESULT_GAMEOVER);
			}
			CFade::Create(CManager::MODE_RESULT, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
			if (pManager == NULL && fade == CFade::FADE_NONE)
			{
				pManager->SetGameScore(m_pScore->GetScore());
			}
		}

		//��������
		Spawn();
	}
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{
}
//=============================================================================
// ��������
//=============================================================================
void CGame::Spawn(void)
{
	//�����Ď��Ԍo�߂��ƂɓG�o��
	m_nMainTimer ++;
	if (m_nMainTimer == 50)
	{
		SetEnemyPattern(0);
	}
	else if (m_nMainTimer == 400)
	{
		SetEnemyPattern(1);
	}
	else if (m_nMainTimer == 800)
	{
		SetEnemyPattern(2);
	}
	else if (m_nMainTimer == 1200)
	{
		SetEnemyPattern(3);
	}
	else if (m_nMainTimer == 1600)
	{
		SetEnemyPattern(0);
	}
	else if(D3DSPSM_SIGNNEG == 1800)
	{
		SetEnemyPattern(1);
	}
	else if (m_nMainTimer == 2200)
	{
		SetEnemyPattern(2);
	}
	else if (m_nMainTimer == 2400)
	{
		SetEnemyPattern(0);

	}
	else if (m_nMainTimer == 2600)
	{
		SetEnemyPattern(3);
	}
	else if (m_nMainTimer == 2600)
	{
		SetEnemyPattern(3);
	}
	else if (m_nMainTimer == 3000)
	{
		SetEnemyPattern(5);
	}
	else if (m_nMainTimer == 3400)
	{
		SetEnemyPattern(1);
	}
	else if (m_nMainTimer == 3600)
	{
		SetEnemyPattern(0);
	}
	else if (m_nMainTimer == 3800)
	{
		SetEnemyPattern(3);
	}
	else if (m_nMainTimer == 4400)
	{
		SetEnemyPattern(0);
	}
	else if (m_nMainTimer == 4600)
	{
		SetEnemyPattern(0);
	}
	else if (m_nMainTimer == 4800)
	{
		SetEnemyPattern(5);
	}
	else if (m_nMainTimer == 5000)
	{
		SetEnemyPattern(4);
	}
	if (m_nMainTimer < 5000)
	{
		float fRandPos = rand() % 900 + 400.0f;		//�ʒu�������_��
		int	  nNumber = rand() % 2 + 1;				//��ނ̃����_��
		m_nSpawnCloud++;							//�X�|�[���̃^�C�}�[
		m_nSpawnHuman++;
		//�_�̐���
		if (m_nSpawnCloud >= 250)
		{
			if (nNumber == 1)
			{
				CCloud::Create(D3DXVECTOR3(fRandPos, -30.0f, 0.0f), 50.0f, 50.0f, CCloud::CLOUD_BEANS);
			}
			else
			{
				CCloud::Create(D3DXVECTOR3(fRandPos, -30.0f, 0.0f), 50.0f, 50.0f, CCloud::CLOUD_NONE);
			}
		}
		if (m_nSpawnCloud >= 250)
		{
			m_nSpawnCloud = 0;
		}

		//�l�Ԃ̐���
		if (m_nSpawnHuman >= 1500)
		{
			CEnemyHuman::Create(D3DXVECTOR3(fRandPos, -30.0f, 0.0f), 50.0f, 50.0f);
		}
		if (m_nSpawnHuman >= 1500)
		{
			m_nSpawnHuman = 0;
		}
	}

}
//=============================================================================
// �X�R�A�̎擾����
//=============================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �v���C���[�̎擾����
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// �G�̃p�^�[���ݒu����
//=============================================================================
void CGame::SetEnemyPattern(int pattern)
{
	switch (pattern)
	{
	case 0:
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(350, -30, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_R);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(SCREEN_WIDTH - 50, -30, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_L);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(350, -180, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_R);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(SCREEN_WIDTH - 50, -180, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_L);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(350, -310, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_R);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(SCREEN_WIDTH - 50, -310, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_L);
		break;
	case 1:
		m_pEnemy = CEnemyCurve::Create(D3DXVECTOR3(840, -30, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyCurve::CURVE_R);
		m_pEnemy = CEnemyCurve::Create(D3DXVECTOR3(740, -30, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyCurve::CURVE_L);
		m_pEnemy = CEnemyCurve::Create(D3DXVECTOR3(840, -180, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyCurve::CURVE_R);
		m_pEnemy = CEnemyCurve::Create(D3DXVECTOR3(740, -180, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyCurve::CURVE_L);
		m_pEnemy = CEnemyCurve::Create(D3DXVECTOR3(840, -330, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyCurve::CURVE_R);
		m_pEnemy = CEnemyCurve::Create(D3DXVECTOR3(740, -330, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyCurve::CURVE_L);
		break;
	case 2:
		m_pEnemy = CEnemyMeandering::Create(D3DXVECTOR3(840, -30, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyMeandering::MEANDERING_R);
		m_pEnemy = CEnemyMeandering::Create(D3DXVECTOR3(740, -30, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyMeandering::MEANDERING_L);
		m_pEnemy = CEnemyMeandering::Create(D3DXVECTOR3(840, -180, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyMeandering::MEANDERING_R);
		m_pEnemy = CEnemyMeandering::Create(D3DXVECTOR3(740, -180, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyMeandering::MEANDERING_L);
		m_pEnemy = CEnemyMeandering::Create(D3DXVECTOR3(840, -330, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyMeandering::MEANDERING_R);
		m_pEnemy = CEnemyMeandering::Create(D3DXVECTOR3(740, -330, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemyMeandering::MEANDERING_L);

		break;
	case 3:
		m_pEnemy = CEnemyTracking::Create(D3DXVECTOR3(840, -30, 0), ENEMY_SIZE, ENEMY_SIZE);
		m_pEnemy = CEnemyTracking::Create(D3DXVECTOR3(740, -30, 0), ENEMY_SIZE, ENEMY_SIZE);
		m_pEnemy = CEnemyTracking::Create(D3DXVECTOR3(840, -180, 0), ENEMY_SIZE, ENEMY_SIZE);
		m_pEnemy = CEnemyTracking::Create(D3DXVECTOR3(740, -180, 0), ENEMY_SIZE, ENEMY_SIZE);
		m_pEnemy = CEnemyTracking::Create(D3DXVECTOR3(840, -330, 0), ENEMY_SIZE, ENEMY_SIZE);
		m_pEnemy = CEnemyTracking::Create(D3DXVECTOR3(740, -330, 0), ENEMY_SIZE, ENEMY_SIZE);
		break;
	case 4:
		m_pEnemy = CEnemyBoss::Create(D3DXVECTOR3(790, -30.0f, 0.0f), BOSS_SIZE, BOSS_SIZE);
		break;
	case 5:
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(840, -30, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_R);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(740, -30, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_L);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(840, -180, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_R);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(740, -180, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_L);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(840, -310, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_R);
		m_pEnemy = CEnemySlide::Create(D3DXVECTOR3(740, -310, 0), ENEMY_SIZE, ENEMY_SIZE, CEnemySlide::SLIDE_L);
		break;
	}
}

//=============================================================================
// �G�̎擾����
//=============================================================================
CEnemy *CGame::GetEnemy(void)
{
	return m_pEnemy;
}
//=============================================================================
// �Q�[���̏�Ԑݒu����
//=============================================================================
void CGame::SetState(CGame::GAME_STATE state)
{
	m_state = state;
}
