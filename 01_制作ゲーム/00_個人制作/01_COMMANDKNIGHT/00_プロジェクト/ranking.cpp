//=============================================================================
//
// �����L���O�̏��� [ranking.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "ranking.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "billboard.h"
#include "fade.h"
#include "number.h"
#include "rankingscore.h"
#include "map.h"
#include "meshfield.h"
#include "logo.h"
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CMap			*CRanking::m_pMap = NULL;					//�}�b�v�̃|�C���^���

//=============================================================================
// �����L���O�̃R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
	m_nTimer = 0;	//�^�C�}�[�̏�����
}

//=============================================================================
// �����L���O�̃f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// �����L���O�̃f�X�g���N�^
//=============================================================================
CRanking *CRanking::Create()
{
	CRanking *pRanking = NULL;	//�����L���O�̃|�C���^
	if (pRanking == NULL)
	{
		pRanking = new CRanking;	//���I�m��
		if (pRanking != NULL)
		{
			pRanking->Init();		//����������
		}
	}
	return pRanking;
}

//=============================================================================
// �����L���O�̏���������
//=============================================================================
HRESULT CRanking::Init(void)
{
	//�����̓ǂݍ���
	CNumber::Load();

	//�����L���O�����N�̓ǂݎqk��
	CRankingRank::Load();

	//�����L���O���S�̓ǂݍ���
	CRankingLogo::Load();

	//�����L���O�����N�̐���
	CRankingRank::Create(D3DXVECTOR3(300.0f, SCREEN_HEIGHT / 2 + 225.0f / 2, 0.0f), 125.0f, 250.0f);

	//���S�̐���
	CRankingLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f), 400.0f, 100);

	//�X�R�A�̐���
	CRankingScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2 - 100, 0.0f), 50.0f, 50.0f);

	//���b�V���t�B�[���h�̐���
	CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�}�b�v�𐶐�
	m_pMap = CMap::Create();

	return S_OK;
}

//=============================================================================
// �����L���O�̏I������
//=============================================================================
void CRanking::Uninit(void)
{
	//�����L���O���S�̔j��
	CRankingLogo::Unload();

	//�����L���O�����N�̔j��
	CRankingRank::Unload();

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
// �����L���O�̍X�V����
//=============================================================================
void CRanking::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//�t�F�[�h�̎擾����
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
	{//Enter�L�[�����������ꍇ
		//�^�C�g���֑J��
		pFade->SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);
	}

	m_nTimer++;
	if (m_nTimer >= 500)
	{
		pFade->SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);

	}
	//�f�o�b�O�\��
	CDebugProc::Print(1, "Ranking");
}

//=============================================================================
// �����L���O�̕`�揈��
//=============================================================================
void CRanking::Draw(void)
{
}