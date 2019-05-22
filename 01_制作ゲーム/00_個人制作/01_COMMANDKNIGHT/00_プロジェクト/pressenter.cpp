//=============================================================================
//
// �v���X�G���^�[�̏��� [player.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "pressenter.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPressEnter::m_pTexture = NULL;
CPressEnter::PRESSENTERSTATE CPressEnter::m_pressEnterState = PRESSENTERSTATE_NONE;

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
//=============================================================================
// �v���X�G���^�[�̃R���X�g���N�^
//=============================================================================
CPressEnter::CPressEnter() : CScene2D(7)
{
	m_nCounter = 0;
}
//=============================================================================
// �v���X�G���^�[�̃f�X�g���N�^
//=============================================================================
CPressEnter::~CPressEnter()
{

}

//=============================================================================
//�v���X�G���^�[�̐���
//=============================================================================
CPressEnter *CPressEnter::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CPressEnter *pPressEnter = NULL;
	if (pPressEnter == NULL)
	{
		pPressEnter = new CPressEnter;				//�V�[���̓��I�m��
		if (pPressEnter != NULL)
		{
			pPressEnter->SetPos(pos);				//�ʒu�̑��
			pPressEnter->SetWidth(fWight);			//���̑��
			pPressEnter->SetHeight(fHeight);		//�����̑��
			pPressEnter->Init();					//����������
			pPressEnter->BindTexture(m_pTexture);
		}
	}
	return pPressEnter;								//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CPressEnter::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME014,
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CPressEnter::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �v���X�G���^�[�̏���������
//=============================================================================
HRESULT CPressEnter::Init(void)
{
	//��Ԃ̏�����
	m_pressEnterState = PRESSENTERSTATE_NONE;

	//CScene2D�̏���������
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �v���X�G���^�[�̏I������
//=============================================================================
void CPressEnter::Uninit(void)
{
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �v���X�G���^�[�̍X�V����
//=============================================================================
void CPressEnter::Update(void)
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

	//�t�F�[�h�̎擾
	CFade::FADE fade;
	CFade *pFade = NULL;
	fade = pFade->GetFade();

	m_nCounter++;

	if (m_nCounter >= 100)
	{
		m_nCounter = 0;
	}

	if (pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_X) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_Y) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LB) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_RB) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LT) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_RT) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_BACK) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true ||
		pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{// JoyPad�̃{�^���܂���ENTER�L�[�������ꂽ�ꍇ
		if (m_pressEnterState == PRESSENTERSTATE_NONE&& fade == CFade::FADE_NONE)
		{//������Ă��Ȃ���Ԃ��t�F�[�h���Ă��Ȃ���Ԃ̏ꍇ
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PRESS);
			m_pressEnterState = PRESSENTERSTATE_PUSH;  // ������Ă����Ԃɂ���
		}
	}

	//CScene2D�̍X�V����
	CScene2D::Update();
}

//=============================================================================
// �v���X�G���^�[�̕`�揈��
//=============================================================================
void CPressEnter::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	pVtxBuff = CScene2D::GetVtx();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	if (m_pressEnterState == PRESSENTERSTATE_NONE)
	{// ������Ă��Ȃ���Ԃ̏ꍇ
		if (m_nCounter / 50 == 0)
		{// �J�E���^�[�����̒l�ɂȂ�����
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	else if (m_pressEnterState == PRESSENTERSTATE_PUSH)
	{// ������Ă��Ȃ���Ԃ̏ꍇ
		if (m_nCounter % 5 == 0)
		{// �J�E���^�[�����̒l�ɂȂ�����
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	//CScene2D�̕`�揈��
	//CScene2D::Draw();
}

//=============================================================================
// �v���X�G���^�[�̏�Ԏ擾
//=============================================================================
CPressEnter::PRESSENTERSTATE CPressEnter::GetPressEnter(void)
{
	return m_pressEnterState;
}