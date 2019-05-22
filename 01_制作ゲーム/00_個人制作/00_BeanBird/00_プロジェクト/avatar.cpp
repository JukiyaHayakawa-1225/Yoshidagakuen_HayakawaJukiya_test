//=============================================================================
//
// ���g�̏��� [avatar.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "avatar.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CAvatar::m_pTexture = NULL;			//�e�N�X�`���̃|�C���^
CAvatar::AVATAR_STATE CAvatar::m_state = AVATAR_NONE;	//���g�̏��

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// ���g�̃R���X�g���N�^
//=============================================================================
CAvatar::CAvatar() : CScene2D(3)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ̏����l
}
//=============================================================================
// ���g�̃f�X�g���N�^
//=============================================================================
CAvatar::~CAvatar()
{

}

//=============================================================================
//���g�̐���
//=============================================================================
CAvatar *CAvatar::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CAvatar *pAvatar = NULL;
	if (pAvatar == NULL)
	{
		pAvatar = new CAvatar;				//�V�[���̓��I�m��
		pAvatar->SetPos(pos);				//�ʒu�̑��
		pAvatar->SetWidth(fWight);			//���̑��
		pAvatar->SetHeight(fHeight);		//�����̑��
		pAvatar->Init();					//����������
		pAvatar->m_state = AVATAR_USE;		//�g�p���Ă����Ԃɂ���
		pAvatar->BindTexture(m_pTexture);	//�e�N�X�`���̓\��t��
	}
	return pAvatar;						//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CAvatar::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME000,
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CAvatar::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���g�̏���������
//=============================================================================
HRESULT CAvatar::Init(void)
{
	//�ړ��ʂ̏���������
	m_move = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	//CScene2D�̏���������
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// ���g�̏I������
//=============================================================================
void CAvatar::Uninit(void)
{
	m_state = AVATAR_NONE;

	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// ���g�̍X�V����
//=============================================================================
void CAvatar::Update(void)
{
	//�v���C���[�̒ǔ�����
	FollowPlayer();
	//�X�V����
	CScene2D::Update();
}

//=============================================================================
// ���g�̕`�揈��
//=============================================================================
void CAvatar::Draw(void)
{
	//CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �v���C���[�̒ǔ�����
//=============================================================================
void CAvatar::FollowPlayer(void)
{
	D3DXVECTOR3 pos;	//�ʒu
	float fAngle;		//�p�x

	pos = GetPos();		//�ʒu�̎擾

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	if (m_state == AVATAR_USE)
	{//���g���g�p���Ă���ꍇ
		for (int nCntPrioty = 0; nCntPrioty < NUM_PRIORITY; nCntPrioty++)
		{//�D��x�̐������J��Ԃ�
			for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
			{//Scene�̐������J��Ԃ�
				CScene2D *pScene;												//�V�[���̃|�C���^
				pScene = (CScene2D*)CScene::GetScene(nCntPrioty, nCntScene);	//�V�[���̎擾
				if (pScene != NULL)
				{//Scene��NULL�łȂ��ꍇ
					CScene::OBJTYPE objType;					//���
					objType = pScene->GetObjType();				//��ނ̎擾
					if (objType == OBJTYPE_PLAYER)
					{//�I�u�W�F�N�g���v���C���[�̏ꍇ
						D3DXVECTOR3 PlayerPos;					//�v���C���[�̈ʒu
						float speed;							//�X�s�[�h
						CPlayer *pPlayer = (CPlayer*)pScene;	//�v���C���[�̓��I�m��
						speed = pPlayer->GetSpeed();			//�X�s�[�h�̎擾
						PlayerPos = pPlayer->GetPos();			//�ʒu�̎擾
						fAngle = atan2f(PlayerPos.x - pos.x, PlayerPos.y - pos.y);								//�����̎擾
						D3DXVECTOR3 SetPos(sinf(fAngle) * (2.5f + speed), cosf(fAngle) * (2.5f + speed), 0.0f);	//�ʒu�̏��
						if (pPlayer != NULL)
						{
							m_move = SetPos;	//�v���C���[�̒ǔ�
							pos += m_move;		//�ړ��ʂ̑��
						}
						if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
						{//SPACE�L�[���������ꍇ
							if (pPlayer->GetBullet() == pPlayer->BULLET_NOMAL)
							{//�v���C���[�̒e���ʏ��Ԃ̏ꍇ
							 //�e�̐���
								CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SALIVA);
							}
							else if (pPlayer->GetBullet() == pPlayer->BULLET_SKILL)
							{//�v���C���[�̒e���X�L����Ԃ̏ꍇ
							 //�e�̐���
								CBullet::Create(D3DXVECTOR3(pos.x - 10.0f, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SALIVA);
								CBullet::Create(D3DXVECTOR3(pos.x + 10.0f, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SALIVA);
							}
						}

						//�ʒu�̐ݒu
						SetVtxPos(pos);

						if (pPlayer->GetState() == pPlayer->STATE_REVIVAL)
						{//�v���C���[�����񂾏ꍇ
						 //���g���g�p���Ă��Ȃ���Ԃɂ���
							m_state = AVATAR_NONE;
							//���g�̏I������
							CAvatar::Uninit();
						}
					}
				}
			}
		}
	}
}
//=============================================================================
// ���g�̎擾����
//=============================================================================
CAvatar::AVATAR_STATE CAvatar::GetAvatar(void)
{
	return m_state;
}

//=============================================================================
// ���g�̐ݒu����
//=============================================================================
void CAvatar::SetAvatar(AVATAR_STATE state)
{
	m_state = state;
}