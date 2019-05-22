//=============================================================================
//
// �t���[���̏��� [frame.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "frame.h"
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
LPDIRECT3DTEXTURE9 CFrame::m_apTexture[MAX_FRAME] = {};		//�e�N�X�`���̃|�C���^

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �t���[���̃R���X�g���N�^
//=============================================================================
CFrame::CFrame() : CScene2D(6)
{

}
//=============================================================================
// �t���[���̃f�X�g���N�^
//=============================================================================
CFrame::~CFrame()
{

}

//=============================================================================
//�t���[���̐���
//=============================================================================
CFrame *CFrame::Create(D3DXVECTOR3 pos, float fWight, float fHeight,CFrame::FRAME_TYPE frame)
{
	CFrame *pFrame = NULL;									//�t���[���̃|�C���^
	if (pFrame == NULL)
	{//NULL�̏ꍇ
		pFrame = new CFrame;								//�t���[���̓��I�m��
		pFrame->SetPos(pos);								//�ʒu�̑��
		pFrame->SetWidth(fWight);							//���̑��
		pFrame->SetHeight(fHeight);							//�����̑��
		pFrame->Init();										//����������
		pFrame->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pFrame->BindTexture(m_apTexture[frame]);				//�e�N�X�`��
	}
	return pFrame;											//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CFrame::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ScoreUI.png",
		&m_apTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\StockUI.png",
		&m_apTexture[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LifeUI.png",
		&m_apTexture[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BeansUI.png",
		&m_apTexture[3]);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CFrame::Unload(void)
{
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_FRAME; nCntEnemyTex++)
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
// �t���[���̏���������
//=============================================================================
HRESULT CFrame::Init(void)
{
	//CScene2D�̏���������
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �t���[���̏I������
//=============================================================================
void CFrame::Uninit(void)
{
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �t���[���̍X�V����
//=============================================================================
void CFrame::Update(void)
{
	//CScene2D�̍X�V����
	CScene2D::Update();
}

//=============================================================================
// �t���[���̕`�揈��
//=============================================================================
void CFrame::Draw(void)
{
	//CScene2D�̕`�揈��
	CScene2D::Draw();
}