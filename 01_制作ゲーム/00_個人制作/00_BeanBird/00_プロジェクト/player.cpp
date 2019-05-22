//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "barrier.h"
#include "explotion.h"
#include "stock.h"
#include "avatar.h"
#include "life.h"
#include "fade.h"
#include "skill.h"
#include "result.h"
#include "score.h"
#include "number.h"
#include "scene.h"
#include "logo.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CPlayer::STATE CPlayer::m_state = STATE_NOMAL;	//�ʏ��Ԃɂ���
CPlayer::BULLET_TYPE CPlayer::m_bulletType = BULLET_NOMAL;
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
bool					g_bDelete;

//=============================================================================
// �v���C���[�̃R���X�g���N�^
//=============================================================================
CPlayer::CPlayer() : CScene2D(5)
{
	m_nCount = 0;								//�J�E���g�̏����l
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ړ��ʂ̏����l
	m_speed = PLAYER_NOMAL_SPEED;				//�X�s�[�h�̏����l
}
//=============================================================================
// �v���C���[�̃f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
//�v���C���[�̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, float fWight, float fHeight,STATE state)
{
	CPlayer *pPlayer = NULL;
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;					//�V�[���̓��I�m��
		pPlayer->SetPos(pos);					//�ʒu�̑��
		pPlayer->SetWidth(fWight);				//���̑��
		pPlayer->SetHeight(fHeight);			//�����̑��
		pPlayer->m_state = state;				//��Ԃ̑��
		pPlayer->Init();						//����������
		pPlayer->m_speed = PLAYER_NOMAL_SPEED;
		g_bDelete = false;						//�g�p���Ă��Ȃ���Ԃɂ���
		pPlayer->BindTexture(m_pTexture);		//�e�N�X�`��
	}
	return pPlayer;					//�l��Ԃ�
}

//=============================================================================
// �v���C���[�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CPlayer::Load(void)
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
// �v���C���[�̃e�N�X�`���j��
//=============================================================================
void CPlayer::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�ړ��ʂ̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�e��������
	m_bulletType = BULLET_NOMAL;
	//��ނ̐ݒ�
	SetObjType(OBJTYPE_PLAYER);
	//CScene2D�̏���������
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CPlayer::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	D3DXVECTOR3 pos;								//�ʒu
	pos = GetPos();									//�ʒu�̎擾

	//���Z����
	pos += m_move;

	//��������
	m_move.x += (0.0f - m_move.x) * 0.15f;
	m_move.y += (0.0f - m_move.y) * 0.15f;

	//�ʒu�̐ݒu
	SetVtxPos(pos);

	switch (m_state)
	{
	case STATE_NOMAL:
		//�͈͊O����
		if (pos.x <= 330.0f)
		{
			pos.x = 330.0f;
		}
		else if (pos.x >= SCREEN_WIDTH - 30.0f)
		{
			pos.x = SCREEN_WIDTH - 30.0f;
		}

		if (pos.y <= 30.0f)
		{
			pos.y = 30.0f;
		}
		else if (pos.y >= SCREEN_HEIGHT - 30.0f)
		{
			pos.y = SCREEN_HEIGHT - 30.0f;
		}

		//�ʒu�̐ݒu
		SetVtxPos(pos);
		if (pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_UP) == true ||
			pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_DOWN) == true ||
			pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_LEFT) == true ||
			pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_RIGHT) == true)
		{
			//�ړ�����
			m_move.x += sinf(pInputJoypad->GetLeftAxiz()) * m_speed;
			m_move.y += cosf(pInputJoypad->GetLeftAxiz()) * m_speed;
		}

		if (pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_UP) == true ||
			pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_DOWN) == true ||
			pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LEFT) == true ||
			pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_RIGHT) == true)
		{
			//�ړ�����
			m_move.x += sinf(pInputJoypad->GetRadian()) * m_speed;
			m_move.y -= cosf(pInputJoypad->GetRadian()) * m_speed;
		}

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//W�L�[���������ꍇ
			m_move.y -= m_speed;
		}
		if (pInputKeyboard->GetPress(DIK_S) == true)
		{//S�L�[���������ꍇ
			m_move.y += m_speed;
		}
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{//A�L�[���������ꍇ
			m_move.x -= m_speed;
		}
		if (pInputKeyboard->GetPress(DIK_D) == true)
		{//D�L�[���������ꍇ
			m_move.x += m_speed;
		}
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
		{//SPACE�L�[���������ꍇ
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET);
			if (m_bulletType == BULLET_NOMAL)
			{
				//�e�̐���
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SALIVA);
			}
			else if (m_bulletType == BULLET_SKILL)
			{
				CBullet::Create(D3DXVECTOR3(pos.x - 10.0f, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SALIVA);
				CBullet::Create(D3DXVECTOR3(pos.x + 10.0f, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SALIVA);
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_K) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
		{//SPACE�L�[���������ꍇ
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHIT);
			//�^�[�Q�b�g�̐���
			CTargetLogo::Create(D3DXVECTOR3(pos.x, pos.y - 200.0f, 0.0f), 30.0f, 30.0f);
			//�e�̐���
			CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SHIT);
		}
		break;
	case STATE_FEVER:
		break;
	case STATE_REVIVAL:
		m_nCount++;					//�J�E���g
		if (m_nCount >= 50)
		{//�J�E���g���T�O�ɂȂ�����
			m_move.y -= m_speed;

			if (pos.y <= SCREEN_HEIGHT - 100)
			{//�w��̈ʒu�ɓ���������
				m_state = STATE_INVINCIBLE;	//�ʏ��Ԃɂ���
				m_nCount = 0;
			}
		}
		break;
	case STATE_INVINCIBLE:
		//�F�̎擾
		D3DXCOLOR col;
		col = GetCol();
		//�J�E���^�[�̉��Z
		m_nCount++;

		if (col.a == 0.0f)
		{//�F�������̏ꍇ
			col.a = 1.0f;
		}
		else if (col.a == 1.0f)
		{//�F�������łȂ��ꍇ
			col.a = 0.0f;
		}
		//�F�̐ݒu
		SetCol(col);

		if (m_nCount <= 300)
		{
			//�͈͊O����
			if (pos.x <= 330.0f)
			{
				pos.x = 330.0f;
			}
			else if (pos.x >= SCREEN_WIDTH - 30.0f)
			{
				pos.x = SCREEN_WIDTH - 30.0f;
			}

			if (pos.y <= 30.0f)
			{
				pos.y = 30.0f;
			}
			else if (pos.y >= SCREEN_HEIGHT - 30.0f)
			{
				pos.y = SCREEN_HEIGHT - 30.0f;
			}

			//�ʒu�̐ݒu
			SetVtxPos(pos);
			if (pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_UP) == true ||
				pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_DOWN) == true ||
				pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_LEFT) == true ||
				pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LSTICK_RIGHT) == true)
			{
				//�ړ�����
				m_move.x += sinf(pInputJoypad->GetLeftAxiz()) * m_speed;
				m_move.y += cosf(pInputJoypad->GetLeftAxiz()) * m_speed;
			}

			if (pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_UP) == true ||
				pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_DOWN) == true ||
				pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LEFT) == true ||
				pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_RIGHT) == true)
			{
				//�ړ�����
				m_move.x += sinf(pInputJoypad->GetRadian()) * m_speed;
				m_move.y -= cosf(pInputJoypad->GetRadian()) * m_speed;
			}

			if (pInputKeyboard->GetPress(DIK_W) == true)
			{//W�L�[���������ꍇ
				m_move.y -= m_speed;
			}
			if (pInputKeyboard->GetPress(DIK_S) == true)
			{//S�L�[���������ꍇ
				m_move.y += m_speed;
			}
			if (pInputKeyboard->GetPress(DIK_A) == true)
			{//A�L�[���������ꍇ
				m_move.x -= m_speed;
			}
			if (pInputKeyboard->GetPress(DIK_D) == true)
			{//D�L�[���������ꍇ
				m_move.x += m_speed;
			}
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
			{//SPACE�L�[���������ꍇ
				pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET);
				if (m_bulletType == BULLET_NOMAL)
				{
					//�e�̐���
					CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SALIVA);
				}
				else if (m_bulletType == BULLET_SKILL)
				{
					CBullet::Create(D3DXVECTOR3(pos.x - 10.0f, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SALIVA);
					CBullet::Create(D3DXVECTOR3(pos.x + 10.0f, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SALIVA);
				}
			}
			else if (pInputKeyboard->GetTrigger(DIK_K) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
			{//SPACE�L�[���������ꍇ
			 //�^�[�Q�b�g�̐���
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHIT);

				CTargetLogo::Create(D3DXVECTOR3(pos.x, pos.y - 200.0f, 0.0f), 30.0f, 30.0f);
				//�e�̐���
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0, -10.0f, 0.0f), 10.0f, 10.0f, CBullet::BULLETTYPE_PLAYER_SHIT);
			}
		}
		else if (m_nCount >= 300)
		{
			col.a = 1.0f;				//�����x��߂�
			SetCol(col);				//�F�̐ݒu
			m_state = STATE_NOMAL;		//�ʏ��Ԃɂ���
		}
		break;
	}
	CScene2D::Update();
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	//CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �����̎擾����
//=============================================================================
float CPlayer::GetRot(void)
{
	return m_rot;	//�l��Ԃ�
}

//=============================================================================
// ��Ԃ̎擾����
//=============================================================================
CPlayer::STATE CPlayer::GetState(void)
{
	return m_state;	//�l��Ԃ�
}

//=============================================================================
// ��Ԃ̐ݒu����
//=============================================================================
void CPlayer::SetState(CPlayer::STATE state)
{
	m_state = state;
}
//=============================================================================
// �e�̎擾����
//=============================================================================
CPlayer::BULLET_TYPE CPlayer::GetBullet(void)
{
	return m_bulletType;
}
//=============================================================================
// �e�̐ݒu����
//=============================================================================
void CPlayer::SetBullet(CPlayer::BULLET_TYPE type)
{
	m_bulletType = type;
}
//=============================================================================
// �X�s�[�h�̎擾����
//=============================================================================
void CPlayer::SetSpeed(CPlayer::PLAYER_SPEED speed)
{
	switch (speed)
	{
	case CPlayer::SPEED_NOMAL:
		m_speed = PLAYER_NOMAL_SPEED;
		break;
	case CPlayer::SPEED_SKILL:
		m_speed = PLAYER_SKILL_SPEED;
		break;
	}
}

//=============================================================================
// �ړ��ʂ̐ݒu����
//=============================================================================
void CPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �X�s�[�h�̐ݒu����
//=============================================================================
float CPlayer::GetSpeed(void)
{
	return m_speed;
}

//=============================================================================
// �_���[�W����
//=============================================================================
void CPlayer::HitDamage(int nDamage)
{
	CLife *pLife = NULL;
	CStock *pStock = NULL;
	CSkill *pSkill = NULL;

	D3DXVECTOR3 pos;			//�ʒu
	pos = GetPos();				//�ʒu�̎擾

	if (pLife == NULL)
	{
		if (pStock == NULL)
		{
			if (m_state == STATE_NOMAL)
			{//�ʏ��Ԃ̏ꍇ
				pLife->SetLife(-nDamage);	//�_���[�W����
				if (pLife->GetLife() <= 0)
				{
					//�����̐���
					CExplotion::Create(pos, 50.0f, 50.0f);
					//�I������
					Uninit();
					if (pStock->GetStock() >= 1)
					{//�c�@���܂�����ꍇ
						//�v���C���[�̐���
						CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 50, 0.0f), PLAYER_SIZE, PLAYER_SIZE, STATE_REVIVAL);
						//�c�@���Z
						pStock->SetStock(-1);
						//���C�t��߂�
						pLife->SetLife(3);
						//�X�L����߂�
						pSkill->SetSkill(pSkill->SKILL_2WAY, pSkill->SKILL_STATE_NONE);
						pSkill->SetSkill(pSkill->SKILL_SPEED, pSkill->SKILL_STATE_NONE);
						pSkill->SetSkill(pSkill->SKILL_AVATAR, pSkill->SKILL_STATE_NONE);
					}
					else
					{
						//�I������
						SetState(STATE_END);
					}
				}
			}
		}
	}
}

