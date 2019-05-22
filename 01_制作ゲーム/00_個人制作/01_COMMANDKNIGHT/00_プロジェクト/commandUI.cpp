//=============================================================================
//
// �R�}���hUI�̏��� [commandUI.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "commandUI.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "scene2D.h"
#include "command.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CCommandUI::m_apTexture[MAX_COMMANDUI] = {};		//�e�N�X�`���̃|�C���^


//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CCommandUI::CCommandUI()
{
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CCommandUI::~CCommandUI()
{

}

//=============================================================================
// �^�C�g���w�i�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CCommandUI::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Command\\command_main.png",
		&m_apTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Command\\command_skill.png",
		&m_apTexture[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Command\\command_item.png",
		&m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// �^�C�g���w�i�̃e�N�X�`���j��
//=============================================================================
void CCommandUI::Unload(void)
{
	for (int nCntTexture = 0; nCntTexture < MAX_COMMANDUI; nCntTexture++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
//�R�}���hUI�̐���
//=============================================================================
CCommandUI *CCommandUI::Create(void)
{
	CCommandUI *pCommandUI = NULL;					//�v���C���[�̃|�C���^
	if (pCommandUI == NULL)
	{
		pCommandUI = new CCommandUI;				//�V�[���̓��I�m��
		pCommandUI->Init();							//����������
		pCommandUI->BindTexture(m_apTexture[0]);

	}
	return pCommandUI;					//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CCommandUI::Init(void)
{
	m_fHeight = 100.0f;
	SetPos(D3DXVECTOR3(75.0f, 620.0f, 0.0f));
	SetWidth(75.0f);
	SetHeight(m_fHeight);
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CCommandUI::Uninit(void)
{
	CScene2D::Uninit();

	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CCommandUI::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�R�}���h�̎擾
	CCommand *pCommand;
	pCommand = CGame::GetCommad();

	//�R�}���h��Ԃ̎擾
	CCommand::COMMAND_STATE state;
	state = pCommand->GetCommandState();

	//�R�}���h��ނ̎擾
	CCommand::COMMAND_TYPE type;
	type = pCommand->GetCommandType();

	if (pCommand->GetUseSkill() == true)
	{
		m_fHeight = 0;				//�����̏�����
		SetHeight(m_fHeight);		//�����̐ݒu����
		SetVtxPos(D3DXVECTOR3(200.0f, 580.0f, 0.0f));
	}
	//��ޕʏ���
	switch (type)
	{
	case CCommand::COMMAND_MAIN:	//���C����ʂ̏ꍇ
		SetWidth(75.0f);			//��
		SetVtxPos(D3DXVECTOR3(150.0f, 580.0f, 0.0f));	//�ʒu�̐ݒu����
		BindTexture(m_apTexture[0]);					//�e�N�X�`���̓\��t��
		break;
	case CCommand::COMMAND_ITEM:	//�A�C�e����ʂ̏ꍇ
		SetWidth(175.0f);								//��
		SetVtxPos(D3DXVECTOR3(250.0f, 580.0f, 0.0f));	//�ʒu�̐ݒu����
		BindTexture(m_apTexture[2]);					//�e�N�X�`���̓\��t��
		break;
	}

	//��ԕʏ���
	switch (state)
	{
	case CCommand::COMMAND_NONE:	//�ʏ��Ԃ̏ꍇ

		break;
	case CCommand::COMMAND_PROCESS:	//���s��Ԃ̏ꍇ
		m_fHeight = 0;				//�����̏�����
		SetHeight(m_fHeight);		//�����̐ݒu����
		SetVtxPos(D3DXVECTOR3(200.0f, 580.0f, 0.0f));
		break;
	case CCommand::COMMAND_SKILL:	//���s��Ԃ̏ꍇ
		m_fHeight = 0;				//�����̏�����
		SetHeight(m_fHeight);		//�����̐ݒu����
		SetVtxPos(D3DXVECTOR3(200.0f, 580.0f, 0.0f));
		break;

	case CCommand::COMMAND_END:		//�I����Ԃ̏ꍇ
		if (pCommand->GetUseSkill() == false)
		{
			m_fHeight += 2.0f;			//�����̉��Z
			if (m_fHeight >= 100.0f)
			{//�������P�O�O�ȏ�̏ꍇ
				m_fHeight = 100.0f;		//�����̌Œ�
				pCommand->SetCommandState(CCommand::COMMAND_NONE);	//�ʏ��Ԃɂ���
			}
			SetHeight(m_fHeight);							//�����̐ݒu����
			SetVtxPos(D3DXVECTOR3(150.0f, 580.0f, 0.0f));	//�ʒu�̐ݒu����
			BindTexture(m_apTexture[0]);					//�e�N�X�`���̓\��t��
		}
		break;
	}
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CCommandUI::Draw(void)
{
	CScene2D::Draw();	//�`�揈��
}

//=============================================================================
// �R�}���h��Ԏ擾����
//=============================================================================
CCommandUI::COMMAND CCommandUI::GetCommandState(void)
{
	return m_state;
}

//=============================================================================
// �R�}���h�̍�����Ԏ擾����
//=============================================================================
CCommandUI::COMMAND_HEIGHT CCommandUI::GetCommandHeightState(void)
{
	return m_heightState;
}

//=============================================================================
// �R�}���h��Ԑݒu����
//=============================================================================
void CCommandUI::SetCommandState(CCommandUI::COMMAND state)
{
	m_state = state;
}

//=============================================================================
// �R�}���h�̍�����Ԑݒu����
//=============================================================================
void CCommandUI::SetCommandHeightState(COMMAND_HEIGHT heightState)
{
	m_heightState = heightState;
}
