//=============================================================================
//
// �o���A�̏��� [barrier.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "barrier.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "skill.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CBarrier::m_pTexture = NULL;			//�e�N�X�`���̃|�C���^
CBarrier::BARRIER_STATE CBarrier::m_state = STATE_NONE;	//�o���A�̏��

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CBarrier::CBarrier() : CScene2D(6)
{
	m_timer = 0;		//�^�C�}�[�̏����l
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CBarrier::~CBarrier()
{
}

//=============================================================================
//�I�u�W�F�N�g�̐���
//=============================================================================
CBarrier *CBarrier::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWight, float fHeight)
{
	CBarrier *pBarrier = NULL;										//�o���A�̃|�C���^
	if (pBarrier == NULL)
	{//NULL�̏ꍇ
		pBarrier = new CBarrier;									//�o���A�̓��I�m��
		if (pBarrier != NULL)
		{//NULL�łȂ��ꍇ
			pBarrier->SetPos(pos);									//�ʒu�̐ݒu
			pBarrier->SetWidth(fWight);								//���̐ݒu
			pBarrier->SetHeight(fHeight);							//�����̐ݒu
			pBarrier->Init();										//����������
			pBarrier->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));	//�F�̐ݒu
			pBarrier->BindTexture(m_pTexture);						//�e�N�X�`��
		}
	}
	return pBarrier;						//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CBarrier::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME015,
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CBarrier::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CBarrier::Init(void)
{
	if (m_state == STATE_NONE)
	{//�o���A���g���ĂȂ��ꍇ
		//CScene2D�̏���������
		CScene2D::Init();
		//��ނ̐ݒ�
		SetObjType(OBJTYPE_BARRIER);
		//�g�p���Ă����Ԃɂ���
		m_state = STATE_USE;
		//�^�C�}�[�̏�����
		m_timer = 0;
	}
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CBarrier::Uninit(void)
{
	//�o���A���g�p���Ă��Ȃ���Ԃɂ���
	m_state = STATE_NONE;
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CBarrier::Update(void)
{
	//�v���C���[�̒ǔ�����
	FollowPlayer();

	//CScene2D�̍X�V����
	CScene2D::Update();
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CBarrier::Draw(void)
{
	//CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �v���C���[�̒ǔ�����
//=============================================================================
void CBarrier::FollowPlayer(void)
{
	if (m_state == STATE_USE)
	{//�o���A���g�p���Ă���ꍇ
	 //�^�C�}�[�̉��Z
		m_timer++;
		for (int nCntPrioty = 0; nCntPrioty < NUM_PRIORITY; nCntPrioty++)
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
						CSkill *pSkill = NULL;					//�X�L���̃|�C���^
						D3DXVECTOR3 PlayerPos;					//�v���C���[�̈ʒu
						CPlayer *pPlayer = (CPlayer*)pScene;	//�v���C���[�̓��I�m��
						PlayerPos = pPlayer->GetPos();			//�ʒu�̎擾
						if (pPlayer != NULL)
						{//�v���C���[��NULL�łȂ��ꍇ
						 //�ʒu�̐ݒu
							SetVtxPos(PlayerPos);
							if (m_timer == 1500)
							{//�^�C�}�[��1500�ɒB�����ꍇ
								m_state = STATE_NONE;			//�o���A���g�p���Ă��Ȃ���Ԃɂ���
								Uninit();						//�I������
								//�X�L�����g�p���Ă��Ȃ���Ԃɂ���
								pSkill->SetSkill(pSkill->SKILL_BARRIER, pSkill->SKILL_STATE_NONE);
							}
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
CBarrier::BARRIER_STATE CBarrier::GetState(void)
{
	return m_state;
}

//=============================================================================
// ��Ԃ̐ݒu����
//=============================================================================
void CBarrier::SetState(CBarrier::BARRIER_STATE state)
{
	m_state = state;
}