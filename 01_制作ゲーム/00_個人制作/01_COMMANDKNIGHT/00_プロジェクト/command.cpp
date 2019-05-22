//=============================================================================
//
// �R�}���h���� [command.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "command.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "scene2D.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "debugproc.h"
#include "loadfilefunction.h"
#include "status_number.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CCommand::m_apTexture[MAX_COMMAND_TEXTURE] = {};					//�e�N�X�`���̃|�C���^
CSkill_Quantity_Number *CCommand::m_pSkillQuantity = NULL;							//�Ƃ����̍��ڃ|�C���^
CItem_Quantity_Number	*CCommand::m_pItemQuantity = NULL;							//�A�C�e���̍��ڃ|�C���^

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CCommand::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Command\\cursor.png",
		&m_apTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Command\\command_skill_cicle.png",
		&m_apTexture[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Command\\command_skill_icon.png",
		&m_apTexture[2]);
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CCommand::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTexture = 0 ; nCntTexture < MAX_COMMAND_TEXTURE; nCntTexture++)
	{
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CCommand::CCommand() : CScene(4,OBJTYPE_SCENE2D)
{
	m_commandType = COMMAND_MAIN;		//�R�}���h��Ԃ�������

	m_pCommandSelect = NULL;			//�I���R�}���h��NULL�ɂ���

	for (int nCntTexture = 0; nCntTexture < MAX_COMMANDSKILL_TEXTURE; nCntTexture++)
	{
		m_apUI_CommandSkill[nCntTexture] = NULL;			//�Ƃ����R�}���h��UI��NULL�ɂ���
	}

	m_CommandState = COMMAND_NONE;		//���s���Ă��Ȃ���Ԃɂ���

	m_nCommandSelect = 0;				//�I��ԍ���������

	m_nCntAttack = 0;					//�U���̃J�E���^�[��������

	m_nCntInterval = 0;					//�Ԋu�J�E���^�[��������

	m_CommandCountState = COMMAND_NOCOUNT;	//�R�}���h

}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CCommand::~CCommand()
{

}

//=============================================================================
//�I�u�W�F�N�g�̐���
//=============================================================================
CCommand *CCommand::Create(D3DXVECTOR3 pos)
{
	CCommand *pCommand = NULL;	//CCommand�̃|�C���^

	if (pCommand == NULL)
	{//NULL�̏ꍇ
		pCommand = new CCommand;	//�V�[���̓��I�m��
		if (pCommand != NULL)
		{
			pCommand->Init();		//����������
		}
	}
	return pCommand;				//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CCommand::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	m_commandType = COMMAND_MAIN;	//�R�}���h��Ԃ�������

	//�R�}���h�I���̏�����
	if (m_pCommandSelect == NULL)
	{
		m_pCommandSelect = new CScene2D(7);										//���I�m��
		if (m_pCommandSelect != NULL)
		{
			m_pCommandSelect->SetPos(D3DXVECTOR3(15.0f, 595.0f, 0.0f));			//�ʒu�̐ݒu����
			m_pCommandSelect->SetWidth(10.0f);									//���̐ݒu����
			m_pCommandSelect->SetHeight(10.0f);									//�����̐ݒu����
			m_pCommandSelect->Init();											//����������
			m_pCommandSelect->BindTexture(m_apTexture[0]);						//�e�N�X�`���̓ǂݍ���
		}
	}

	//�Ƃ����R�}���h��UI�̏�����
	for (int nCntSkill = 0; nCntSkill < MAX_COMMANDSKILL_TEXTURE; nCntSkill++)
	{
		if (m_apUI_CommandSkill[nCntSkill] == NULL)
		{
			m_apUI_CommandSkill[nCntSkill] = new CScene2D(6);										//���I�m��
			if (m_apUI_CommandSkill[nCntSkill] != NULL)
			{
				m_apUI_CommandSkill[nCntSkill]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2, 0.0f));			//�ʒu�̐ݒu����
				m_apUI_CommandSkill[nCntSkill]->SetWidth(300.0f);															//���̐ݒu����
				m_apUI_CommandSkill[nCntSkill]->SetHeight(300.0f);															//�����̐ݒu����
				m_apUI_CommandSkill[nCntSkill]->Init();																		//����������
				m_apUI_CommandSkill[nCntSkill]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
				if (nCntSkill == 0)
				{
					m_apUI_CommandSkill[nCntSkill]->SetLength(250.0f);															//�����̐ݒu����
					m_apUI_CommandSkill[nCntSkill]->SetVtxLenghtPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));	//�����̐ݒu����
				}
				else
				{
					m_apUI_CommandSkill[nCntSkill]->SetLength(350.0f);															//�����̐ݒu����
					m_apUI_CommandSkill[nCntSkill]->SetVtxLenghtPos(D3DXVECTOR3(SCREEN_WIDTH / 2 - 10.0f, SCREEN_HEIGHT / 2 - 25.0f, 0.0f));	//�����̐ݒu����
				}
				m_apUI_CommandSkill[nCntSkill]->BindTexture(m_apTexture[1 + nCntSkill]);												//�e�N�X�`���̓ǂݍ���
			}
		}
	}
	m_nCommandSelect = 0;	//�R�}���h�I��������
	m_bUseSkill = false;
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CCommand::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CCommand::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�W���C�p�b�h�̎擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetJoypad();

	//�v���C���[�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	if (m_bUseSkill == false)
	{
		for (int nCntSkill = 0; nCntSkill < MAX_COMMANDSKILL_TEXTURE; nCntSkill++)
		{
			m_apUI_CommandSkill[nCntSkill]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}

	}
	else
	{
		//if (m_CommandState == COMMAND_SKILL)
		{
			for (int nCntSkill = 0; nCntSkill < MAX_COMMANDSKILL_TEXTURE; nCntSkill++)
			{
				m_apUI_CommandSkill[nCntSkill]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}

	if (m_bUseSkill == false)
	{
		if (m_CommandState == COMMAND_NONE /*&& m_commandType != COMMAND_SKILL*/)
		{//�R�}���h���s�����Ă��Ȃ��ꍇ
			m_pCommandSelect->SetHeight(10.0f);
			// �I�����ڈړ�����
			if (pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
				pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_DOWN) == true)
			{// ���L�[�܂��͏\�����܂��͍��X�e�B�b�N���������ꂽ
				m_nCommandSelect = (m_nCommandSelect + 1) % MAX_COMMAND_SELECT;								//�R�}���h�I��ԍ������Z
			}
			if (pInputKeyboard->GetTrigger(DIK_UP) == true ||
				pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_UP) == true)
			{// ��L�[�܂��͏\����܂��͍��X�e�B�b�N�オ�����ꂽ
				m_nCommandSelect = (m_nCommandSelect + (MAX_COMMAND_SELECT - 1)) % MAX_COMMAND_SELECT;		//�R�}���h�I��ԍ������Z
			}

			// ��ʑJ��
			if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true ||
				pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
			{// ENTER�L�[�܂���B�{�^���������ꂽ
				SwitchCommnad();	//�R�}���h�̐؂�ւ�����
			}
			if (pInputKeyboard->GetTrigger(DIK_LEFT) == true ||
				pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
			{//���L�[�܂���A�{�^���������ꂽ
				m_nCommandSelect = 0;				//�R�}���h�I��ԍ���������
				m_commandType = COMMAND_MAIN;		//���C���R�}���h��ʂɂ���

				//�Ƃ������ڂ̏I������
				if (m_pSkillQuantity != NULL)
				{
					m_pSkillQuantity->Uninit();
					m_pSkillQuantity = NULL;
				}
				//�ǂ������ڂ̏I������
				if (m_pItemQuantity != NULL)
				{
					m_pItemQuantity->Uninit();
					m_pItemQuantity = NULL;
				}
			}
			//for (int nCntSkill = 0; nCntSkill < MAX_COMMANDSKILL_TEXTURE; nCntSkill++)
			//{
			//	m_apUI_CommandSkill[nCntSkill]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			//}
		}
		else if (m_CommandState == COMMAND_PROCESS)
		{//���s��Ԃ̏ꍇ

			m_nCommandSelect = 0;					//�R�}���h�I��ԍ���������
			m_commandType = COMMAND_MAIN;			//���C���R�}���h��ʂɂ���
			m_pCommandSelect->SetHeight(0.0f);		//�R�}���h�̍������O�ɂ���
		}
	}
	else
	{
		//else if (m_CommandState == COMMAND_SKILL)
		//{
		m_nCommandSelect = 0;					//�R�}���h�I��ԍ���������
		m_pCommandSelect->SetHeight(0.0f);		//�R�}���h�̍������O�ɂ���

		//for (int nCntSkill = 0; nCntSkill < MAX_COMMANDSKILL_TEXTURE; nCntSkill++)
		//{
		//	m_apUI_CommandSkill[nCntSkill]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		//}

		//if (pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
		//	pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_DOWN) == true)
		//{// ���L�[�܂��͏\�����܂��͍��X�e�B�b�N���������ꂽ
		//	m_commandType = COMMAND_MAIN;			//���C���R�}���h��ʂɂ���
		//	m_CommandState = COMMAND_END;		//�R�}���h�����s���Ă����Ԃɂ���

		//}

		 if (pInputKeyboard->GetTrigger(DIK_LEFT) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LEFT) == true)
		{// ��L�[�܂��͏\����܂��͍��X�e�B�b�N�オ�����ꂽ
			if (m_nCommandSelect == 0 && pPlayer->GetSkill() >= pPlayer->GetCutSkill(0))
			{//�R�}���h�I�����O����MP���g�p����ʈȏ゠��ꍇ
				pPlayer->SetMotion(pPlayer->MOTION_SKILL0);							//�Ƃ����O���[�V�����ɂ���
				pPlayer->SetSkill(pPlayer->GetSkill() - pPlayer->GetCutSkill(0));	//MP�̐ݒu����
				m_CommandState = COMMAND_PROCESS;									//�R�}���h�����s���Ă����Ԃɂ���
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SKILL0);
				//�Ƃ������ڂ̏I������
				if (m_pSkillQuantity != NULL)
				{
					m_pSkillQuantity->Uninit();
					m_pSkillQuantity = NULL;
				}
				m_bUseSkill = false;
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_UP) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_UP) == true)
		{// ��L�[�܂��͏\����܂��͍��X�e�B�b�N�オ�����ꂽ
			if (m_nCommandSelect == 0 && pPlayer->GetSkill() >= pPlayer->GetCutSkill(1))
			{//�R�}���h�I�����O����MP���g�p����ʈȏ゠��ꍇ
				pPlayer->SetMotion(pPlayer->MOTION_SKILL1);							//�Ƃ����P���[�V�����ɂ���
				pPlayer->SetSkill(pPlayer->GetSkill() - pPlayer->GetCutSkill(1));	//MP�̐ݒu����
				m_CommandState = COMMAND_PROCESS;									//�R�}���h�����s���Ă����Ԃɂ���
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SKILL1);
				//�Ƃ������ڂ̏I������
				if (m_pSkillQuantity != NULL)
				{
					m_pSkillQuantity->Uninit();
					m_pSkillQuantity = NULL;
				}
				m_bUseSkill = false;
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_RIGHT) == true)
		{// ��L�[�܂��͏\����܂��͍��X�e�B�b�N�オ�����ꂽ
			if (m_nCommandSelect == 0 && pPlayer->GetSkill() >= pPlayer->GetCutSkill(2))
			{//�R�}���h�I�����O����MP���g�p����ʈȏ゠��ꍇ
				pPlayer->SetMotion(pPlayer->MOTION_SKILL2);							//�Ƃ����Q���[�V�����ɂ���
				pPlayer->SetSkill(pPlayer->GetSkill() - pPlayer->GetCutSkill(2));	//MP�̐ݒu����
				m_CommandState = COMMAND_PROCESS;									//�R�}���h�����s���Ă����Ԃɂ���
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SKILL2);
																					//�Ƃ������ڂ̏I������
				if (m_pSkillQuantity != NULL)
				{
					m_pSkillQuantity->Uninit();
					m_pSkillQuantity = NULL;
				}
				m_bUseSkill = false;
			}
		}


	}


	//�R�}���h�J�[�\���ʏ���
	switch (m_nCommandSelect)
	{
	case 0:
		m_pCommandSelect->SetPos(D3DXVECTOR3(95.0f, 575.0f, 0.0f));			//�ʒu�̐ݒu����
		break;
	case 1:
		m_pCommandSelect->SetPos(D3DXVECTOR3(95.0f, 650.0f, 0.0f));			//�ʒu�̐ݒu����
		break;
	}

	//�R�}���h��ԕʏ���
	switch (m_CommandCountState)
	{
	case COMMAND_NOCOUNT:	//�J�E���g���Ă��Ȃ��ꍇ
		m_nCntInterval = 0;	//�Ԋu�J�E���^�[��������
		m_nCntAttack = 0;	//�U���J�E���^�[�̏�����
		break;

	case COMMAND_COUNT:			//�J�E���g���Ă���ꍇ
		m_nCntInterval++;		//�Ԋu�J�E���^�[��������

		if (m_nCntInterval >= 120)
		{//�Ԋu�J�E���^�[���P�Q�O�ȏ�̏ꍇ
			m_CommandCountState = COMMAND_NOCOUNT;	//�J�E���g���Ă��Ȃ���Ԃɂ���
		}
		break;
	}
		m_pCommandSelect->SetVtxPos(m_pCommandSelect->GetPos());	//�ʒu�̐ݒu����

#if _DEBUG
		CDebugProc::Print(1, "�R�}���h�I�� [I : ��ړ�][K : ���ړ�][L : �R�}���h���s][J : �R�}���h��߂�]\n");
		CDebugProc::Print(1, "�R�}���h���s���[0 : ���Ă��Ȃ�][1 : ���Ă���][2 : �I��]  %d\n", m_CommandState);
		CDebugProc::Print(1, "�I��ԍ�[%d/%d]\n", m_nCommandSelect, MAX_COMMAND_SELECT);
		CDebugProc::Print(1, "�J�E���^�[%d\n", m_nCntInterval);
		CDebugProc::Print(1, "�A�^�b�N%d\n", m_nCntAttack);

#endif
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CCommand::Draw(void)
{
}

//=============================================================================
// �R�}���h�̏�Ԑݒu����
//=============================================================================
void CCommand::SetCommandState(COMMAND_STATE state)
{
	m_CommandState = state;
}

//=============================================================================
// �R�}���h�̎�ސݒu����
//=============================================================================
void CCommand::SetCommandType(COMMAND_TYPE type)
{
	m_commandType = type;
}

//=============================================================================
// �R�}���h�̏�Ԏ擾����
//=============================================================================
CCommand::COMMAND_STATE CCommand::GetCommandState(void)
{
	return m_CommandState;
}

//=============================================================================
// �R�}���h�̎�ގ擾����
//=============================================================================
CCommand::COMMAND_TYPE CCommand::GetCommandType(void)
{
	return m_commandType;
}

//=============================================================================
// �R�}���h�̂Ƃ������g�p���Ă��邩�擾
//=============================================================================
bool CCommand::GetUseSkill(void)
{
	return m_bUseSkill;
}

//=============================================================================
// �R�}���h�̐؂�ւ�����
//=============================================================================
void CCommand::SwitchCommnad(void)
{
	//�v���C���[�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetSound();

	switch (m_commandType)
	{
	case COMMAND_MAIN:	//���C����ʂ̏ꍇ
		if (m_nCommandSelect == 0)
		{

			if (pPlayer->GetJump() == false)
			{//�W�����v���Ă��Ȃ��ꍇ
				if (m_nCntAttack == 0)
				{

					pPlayer->SetMotion(pPlayer->MOTION_COMBO0);			//�U�����[�V�����ɂ���
					pSound->PlaySound(CSound::SOUND_LABEL_SE_SLASH);
					pPlayer->SetAction(true);							//�s�����Ă����Ԃɂ���
					m_CommandCountState = COMMAND_COUNT;				//�J�E���g�����Ă����Ԃɂ���
					m_CommandState = COMMAND_ATTACK_PROCESS;			//�R�}���h�����s���Ă����Ԃɂ���

					if (m_nCntInterval <= 120)
					{//�Ԋu�J�E���^�[���P�Q�O�ȏ�̏ꍇ
						m_nCntAttack++;		//�U���J�E���^�[���Z

					}

				}
				else if (m_nCntAttack == 1)
				{//�U���J�E���^�[���P�̏ꍇ
					pPlayer->SetMotion(pPlayer->MOTION_COMBO1);		//�U�����[�V�����ɂ���
					pSound->PlaySound(CSound::SOUND_LABEL_SE_SLASH);

					pPlayer->SetAction(true);						//�s�����Ă����Ԃɂ���
					m_CommandCountState = COMMAND_NOCOUNT;			//�J�E���g���Ă��Ȃ���Ԃɂ���
					m_CommandState = COMMAND_ATTACK_PROCESS;			//�R�}���h�����s���Ă����Ԃɂ���
					m_pSkillQuantity = CSkill_Quantity_Number::Create(D3DXVECTOR3(375.0f, SCREEN_HEIGHT - 165.0f, 0.0f), 15.0f, 23.0f);

					//m_commandType = COMMAND_SKILL;					//�Ƃ����ɂ���
					//m_CommandState = COMMAND_SKILL;			//�R�}���h�����s���Ă����Ԃɂ���
					m_bUseSkill = true;
				}
			}
		}
		else if (m_nCommandSelect == 1)
		{//�R�}���h�I�����Q�̏ꍇ
			//�ǂ������ڂ̐���
			m_pItemQuantity = CItem_Quantity_Number::Create(D3DXVECTOR3(405.0f, SCREEN_HEIGHT - 132.5f, 0.0f), 13.0f, 17.5f);

			m_commandType = COMMAND_ITEM;						//�ǂ����̃R�}���h��ʂɂ���
			m_nCommandSelect = 0;								//�R�}���h�I��ԍ���������
			m_nCntAttack = 0;									//�U���J�E���^�[�̏�����

		}
		break;
	case COMMAND_ITEM:	//�ǂ�����ʂ̏ꍇ
		if (pPlayer->GetJump() == false)
		{//�W�����v���Ă��Ȃ��ꍇ
			if (m_nCommandSelect == 0 && pPlayer->GetItemQuantity(0) > 0)
			{//�ǂ����I�����O���ǂ������O���傫���ꍇ
				pPlayer->SetMotion(pPlayer->MOTION_ITEM);	//�ǂ����g�p���[�V�����ɂ���
				pPlayer->AddItemQuantity(0, -1);			//�ǂ����O�̎c�������炷
				pPlayer->SetUseItem(CPlayer::USE_ITEM0);	//�ǂ����̐ݒu����
				m_CommandState = COMMAND_PROCESS;			//�R�}���h�����s���Ă����Ԃɂ���
				//�A�C�e�����ڂ̏I������
				if (m_pItemQuantity != NULL)
				{
					m_pItemQuantity->Uninit();
					m_pItemQuantity = NULL;
				}
			}
			else if (m_nCommandSelect == 1 && pPlayer->GetItemQuantity(1) > 0)
			{//�ǂ����I�����P���ǂ������O���傫���ꍇ
				pPlayer->SetMotion(pPlayer->MOTION_ITEM);	//�ǂ����g�p���[�V�����ɂ���
				pPlayer->AddItemQuantity(1, -1);			//�ǂ����P�̎c�������炷
				pPlayer->SetUseItem(CPlayer::USE_ITEM1);	//�ǂ����̐ݒu����
				m_CommandState = COMMAND_PROCESS;			//�R�}���h�����s���Ă����Ԃɂ���
				//�A�C�e�����ڂ̏I������
				if (m_pItemQuantity != NULL)
				{
					m_pItemQuantity->Uninit();
					m_pItemQuantity = NULL;
				}
			}
			else if (m_nCommandSelect == 2 && pPlayer->GetItemQuantity(2) > 0)
			{//�ǂ����I�����P���ǂ������O���傫���ꍇ
				pPlayer->SetMotion(pPlayer->MOTION_ITEM);	//�ǂ����g�p���[�V�����ɂ���
				pPlayer->SetUseItem(CPlayer::USE_ITEM2);	//�ǂ����P�̎c�������炷
				pPlayer->AddItemQuantity(2, -1);			//�ǂ����̐ݒu����
				m_CommandState = COMMAND_PROCESS;			//�R�}���h�����s���Ă����Ԃɂ���
				//�A�C�e�����ڂ̏I������
				if (m_pItemQuantity != NULL)
				{
					m_pItemQuantity->Uninit();
					m_pItemQuantity = NULL;
				}
			}
		}
		break;
	}
}