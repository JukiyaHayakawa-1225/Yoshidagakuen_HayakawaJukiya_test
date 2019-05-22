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
#include "meshfield.h"
#include "debugproc.h"
#include "fade.h"
#include "object.h"
#include "command.h"
#include "enemy.h"
#include "map.h"
#include "CommandUI.h"
#include "number.h"
#include "timer.h"
#include "pause.h"
#include "score.h"
#include "ui.h"
#include "status_number.h"
#include "particle.h"
#include "billboardgauge.h"
#include "logo.h"
#include "bullet.h"
#include "icecircle.h"
#include "icicle.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPlayer			*CGame::m_pPlayer = NULL;				//�v���C���[�̃|�C���^���
CEnemy			*CGame::m_pEnemy = NULL;				//�G�̃|�C���^���
CMeshField		*CGame::m_pMeshField = NULL;			//���b�V���t�B�[���h�̃|�C���^���
CCommand		*CGame::m_pCommand = NULL;				//�R�}���h�̃|�C���^���
CMap			*CGame::m_pMap = NULL;					//�}�b�v�̃|�C���^���
CTimer			*CGame::m_pTimer = NULL;				//�^�C�}�[�̃|�C���^���
CScore			*CGame::m_pScore = NULL;				//�X�R�A�̃|�C���^���
CStatus_Number	*CGame::m_pStatuNumber = NULL;			//�X�e�[�^�X�����̃|�C���^���
CUI_LifeGauge	*CGame::m_pUI_LifeGauge = NULL;			//UI�̃|�C���^���
CUI_SkillGauge	*CGame::m_pUI_SkillGauge = NULL;			//UI�̃|�C���^���
CUI_DamageGauge	*CGame::m_pUI_DamageGauge = NULL;			//UI�̃|�C���^���
CBillboardNumber	*CGame::m_pBillboard_Number = NULL;

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
	m_pPlayer = NULL;		//�v���C���[��������
	m_pMeshField = NULL;	//���b�V���t�B�[���h��������
	m_pMap = NULL;			//�}�b�v��������
	m_pTimer = NULL;		//�^�C�}�[��������
	m_pScore = NULL;		//�X�R�A��������
	m_nTimer = 0;
}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CGame *CGame::Create()
{
	CGame *pGame = NULL;	//�Q�[���̃|�C���^
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
	//�}�b�v�𐶐�
	m_pMap = CMap::Create();

	//�����̓ǂݍ���
	CNumber::Load();

	//�R�}���h�̓ǂݍ���
	CCommand::Load();

	//�R�}���hUI�̓ǂݍ���
	CCommandUI::Load();

	//�Q�[�W�̗�UI�̓ǂݍ���
	CUI_LifeGauge::Load();

	//�Q�[�W�Ƃ���UI�̓ǂݍ���
	CUI_SkillGauge::Load();

	//�Q�[�W�_���[�WUI�̓ǂݍ���
	CUI_DamageGauge::Load();

	//�Q�[�W�x�[�XUI�̓ǂݍ���
	CUI_BaseGauge::Load();

	//�p�[�e�B�N���̓ǂݍ���
	CParticle::Load();

	//�|�[�Y�̓ǂݍ���
	CPause::Load();

	//�r���{�[�h�̗̓Q�[�W�̓ǂݍ���
	CBillboardLifeGauge::Load();

	//�p�[�e�B�N���X�L���Q�̓ǂݍ���
	CSkill2Particle::Load();

	//�p�[�e�B�N���_���[�W�̓ǂݍ���
	CDamageParticle::Load();

	//��̓ǂݍ���
	CSnowParticle::Load();

	//�����̓ǂݍ���
	CFountainParticle::Load();
	//HP���S�̓ǂݍ���
	CHPLogo::Load();

	//MP���S�̓ǂݍ���
	CMPLogo::Load();

	//�e�̓ǂݍ���
	CBullet::Load();

	//�~�̕X�̓ǂݍ���
	CIceCircle::Load();

	//�X���̓ǂݍ���
	CIcicle::Load();

	//HP���S�̐���
	CHPLogo::Create(D3DXVECTOR3(SCREEN_WIDTH - 350.0f, 600.0f, 0.0f), 20.0f, 20.0f);

	//MP���S�̐���
	CMPLogo::Create(D3DXVECTOR3(SCREEN_WIDTH - 350.0f, 650.0f, 0.0f), 20.0f, 20.0f);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(600.0f, 0.0f, -1000.0f));

	//�^�C�}�[�̐���
	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50.0f, 75.0f, 0.0f), 40.0f, 40.0f);

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 50.0f, 75.0f, 0.0f), 40.0f, 40.0f);

	//�X�e�[�^�X�����̐���
	m_pStatuNumber = CStatus_Number::Create(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 120.0f, 0.0f), 15.0f, 15.0f);

	//�R�}���h�̐���
	m_pCommand = CCommand::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//�R�}���hUI�̐���
	CCommandUI::Create();

	//�Q�[�W�̗�UI�̐���
	m_pUI_LifeGauge = CUI_LifeGauge::Create();

	//�Q�[�W�Ƃ���UI�̐���
	m_pUI_SkillGauge = CUI_SkillGauge::Create();

	//�Q�[�W�_���[�WUI�̐���
	m_pUI_DamageGauge = CUI_DamageGauge::Create();

	//�Q�[�W�x�[�XUI�̐���
	CUI_BaseGauge::Create();

	CEnemyBird::Create(D3DXVECTOR3(600.0f, 0.0f, -600.0f));
	CEnemyBird::Create(D3DXVECTOR3(650.0f, 0.0f, -600.0f));
	CEnemyBird::Create(D3DXVECTOR3(550.0f, 0.0f, -600.0f));
	//CEnemyBird::Create(D3DXVECTOR3(600.0f, 0.0f, -650.0f));
	//CEnemyBird::Create(D3DXVECTOR3(100.0f, 0.0f, -650.0f));

	CEnemyBird::Create(D3DXVECTOR3(100.0f, 0.0f, -900.0f));
	CEnemyBird::Create(D3DXVECTOR3(200.0f, 0.0f, -1000.0f));
	CEnemyBird::Create(D3DXVECTOR3(1100.0f, 0.0f, -900.0f));
	CEnemyBird::Create(D3DXVECTOR3(900.0f, 0.0f, -1000.0f));

	CEnemyBird::Create(D3DXVECTOR3(100.0f, 0.0f, -400.0f));
	CEnemyBird::Create(D3DXVECTOR3(1000.0f, 0.0f, -700.0f));
	//CEnemyBird::Create(D3DXVECTOR3(600.0f, 0.0f, -100.0f));
	//CEnemyBird::Create(D3DXVECTOR3(100.0f, 0.0f, -100.0f));
	CEnemyBird::Create(D3DXVECTOR3(1000.0f, 0.0f, -500.0f));

	CEnemyFrog::Create(D3DXVECTOR3(100.0f, 0.0f, -1000.0f));
	CEnemyFrog::Create(D3DXVECTOR3(100.0f, 0.0f, -200.0f));
	CEnemyFrog::Create(D3DXVECTOR3(1000.0f, 0.0f, -1000.0f));
	CEnemyFrog::Create(D3DXVECTOR3(1000.0f, 0.0f, -200.0f));
	//CEnemyFrog::Create(D3DXVECTOR3(550.0f, 0.0f, -100.0f));
	//CEnemyFrog::Create(D3DXVECTOR3(650.0f, 0.0f, -100.0f));


	//���b�V���t�B�[���h�̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_nTimer = 0;

	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	//�X���̔j��
	CIcicle::Unload();

	//�~�̕X�̔j��
	CIceCircle::Unload();

	//�e�̔j��
	CBullet::Unload();

	//MP���S�̔j��
	CMPLogo::Unload();

	//HP���S�̔j��
	CHPLogo::Unload();

	//�����̔j��
	CFountainParticle::Unload();

	//��̔j��
	CSnowParticle::Unload();

	//�p�[�e�B�N���_���[�W�̔j��
	CDamageParticle::Unload();

	//�p�[�e�B�N���Ƃ����Q�̔j��
	CSkill2Particle::Unload();

	//�r���{�[�h�̗̓Q�[�W�̔j��
	CBillboardLifeGauge::Unload();

	//�|�[�Y�̔j��
	CPause::Unload();

	//�p�[�e�B�N���̔j��
	CParticle::Unload();

	//�Q�[�W�x�[�XUI�̔j��
	CUI_BaseGauge::Unload();

	//�Q�[�W�_���[�WUI�̔j��
	CUI_DamageGauge::Unload();

	//�Q�[�W�Ƃ���UI�̔j��
	CUI_SkillGauge::Unload();

	//�Q�[�W�̗�UI�̔j��
	CUI_LifeGauge::Unload();

	//�R�}���hUI�̔j��
	CCommandUI::Unload();

	//�R�}���h�̔j��
	CCommand::Unload();

	//�����̔j��
	CNumber::Unload();

	//�}�b�v�̏I������
	if (m_pMap != NULL)
	{
		m_pMap->Uninit();
		delete m_pMap;
		m_pMap = NULL;
	}

	//�S�ẴI�u�W�F�N�g�J��
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

	//�t�F�[�h�̎擾����
	CFade *pFade = CManager::GetFade();

	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && pFade->GetFade() == CFade::FADE_NONE)
	//{//Enter�L�[�����������ꍇ
	//	CEnemy *pEnemy = NULL;

	//	////���U���g�֑J��
	//	//pFade->SetFade(CManager::MODE_RESULT, pFade->FADE_OUT);
	//	//CManager *pManager = NULL;
	//	////pManager->SetGameScore(m_pScore->GetScore());
	//	//pManager->SetScore(m_pScore->GetScore());
	//	CManager *pManager = NULL;
	//	//pManager->SetGameScore(m_pScore->GetScore());
	//	pManager->SetScore(m_pScore->GetScore());
	///*	pManager->SetBird();
	//	pManager->SetFrog();*/
	//	pFade->SetFade(CManager::MODE_RESULT, pFade->FADE_OUT);


	//}
	//else if (pInputKeyboard->GetTrigger(DIK_6) == true)
	//{
	//	m_pScore->AddScore(100);
	//}

	if (CEnemy::GetNumEnemy() <= 0 || m_pTimer->GetTimer() <= 0||m_pPlayer->GetState() == CPlayer::PLAYER_STATE_DEATH)
	{
		CManager *pManager = NULL;
		CEnemy *pEnemy = NULL;

			//pManager->SetGameScore(m_pScore->GetScore());
		pManager->SetScore(m_pScore->GetScore());
		pManager->SetBird(m_pPlayer->GetDeathBird());
		pManager->SetFrog(m_pPlayer->GetDeathFrog());
		pFade->SetFade(CManager::MODE_RESULT, pFade->FADE_OUT);

	}
	//m_nTimer++;
	//if (m_nTimer > 5)
	//{
	//	CManager *pManager = NULL;
	//	CEnemy *pEnemy = NULL;

	//	//pManager->SetGameScore(m_pScore->GetScore());
	//	pManager->SetScore(m_pScore->GetScore());
	///*	pManager->SetBird(m_pEnemy->GetNumBird());
	//	pManager->SetFrog(m_pEnemy->GetNumFrog());*/
	//	pFade->SetFade(CManager::MODE_RESULT, pFade->FADE_OUT);

	//}
	//�f�o�b�O�\��
	CDebugProc::Print(1, "Game");
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;				//�l��Ԃ�
}

//=============================================================================
// �G�̎擾
//=============================================================================
CEnemy * CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//=============================================================================
// �R�}���h�̎擾
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �R�}���h�̎擾
//=============================================================================
CCommand * CGame::GetCommad(void)
{
	return m_pCommand;
}

//=============================================================================
// �I�u�W�F�N�g3D�̎擾
//=============================================================================
CMeshField *CGame::GetMeshField(void)
{
	return m_pMeshField;				//�l��Ԃ�
}

//=============================================================================
// �X�e�[�^�X�����̂̎擾
//=============================================================================
CStatus_Number *CGame::GetStatusNumber(void)
{
	return m_pStatuNumber;				//�l��Ԃ�
}

//=============================================================================
// �X�e�[�^�X�����̂̎擾
//=============================================================================
CUI_LifeGauge *CGame::GetUI_LifeGauge(void)
{
	return m_pUI_LifeGauge;				//�l��Ԃ�
}

//=============================================================================
// �X�e�[�^�X�����̂̎擾
//=============================================================================
CUI_SkillGauge *CGame::GetUI_SkillGauge(void)
{
	return m_pUI_SkillGauge;				//�l��Ԃ�
}

//=============================================================================
// �X�e�[�^�X�����̂̎擾
//=============================================================================
CUI_DamageGauge *CGame::GetUI_DamageGauge(void)
{
	return m_pUI_DamageGauge;				//�l��Ԃ�
}

//=============================================================================
// �r���{�[�h�����̂̎擾
//=============================================================================
CBillboardNumber *CGame::GetBillborad_Number(void)
{
	return m_pBillboard_Number;				//�l��Ԃ�
}