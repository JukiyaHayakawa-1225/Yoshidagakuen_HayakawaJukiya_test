//=============================================================================
//
// �X�L���̏��� [skill.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "skill.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2D.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CSkill::m_pTexture[MAX_SKILL] = {};
CSkill::SKILL_STATE CSkill::m_state[MAX_SKILL] = {};

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �X�L���̃R���X�g���N�^
//=============================================================================
CSkill::CSkill() :CScene(6)
{
}
//=============================================================================
// �X�L���̃f�X�g���N�^
//=============================================================================
CSkill::~CSkill()
{
}
//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CSkill::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\skill_2way.png",
		&m_pTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\skill_speed.png",
		&m_pTexture[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\skill_barrier.png",
		&m_pTexture[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\skill_avatar.png",
		&m_pTexture[3]);
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CSkill::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
//�X�L���̐���
//=============================================================================
CSkill *CSkill::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CSkill *pPause = NULL;

	if (pPause == NULL)
	{
		pPause = new CSkill;		//�V�[���̓��I�m��
		if (pPause != NULL)
		{
			for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
			{
				pPause->m_pos = pos;			//�ʒu�̑��
				pPause->m_fWidth = fWidth;		//���̑��
				pPause->m_fHeight = fHeight;	//�����̑��
				pPause->Init();					//����������
			}
		}
	}
	return pPause;					//�l��Ԃ�
}

//=============================================================================
// �X�L���̏���������
//=============================================================================
HRESULT CSkill::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		m_aCol[nCnt] = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);			//�F��������
		m_state[nCnt] = SKILL_STATE_NONE;
	}

	float Pos = 0.0f;
	m_pVtxBuff = NULL;									//���_����������

														//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SKILL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)& pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth + Pos, m_pos.y - m_fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth + Pos, m_pos.y - m_fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth + Pos, m_pos.y + m_fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth + Pos, m_pos.y + m_fHeight, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = m_aCol[nCnt];
		pVtx[1].col = m_aCol[nCnt];
		pVtx[2].col = m_aCol[nCnt];
		pVtx[3].col = m_aCol[nCnt];

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		Pos += 63.5f;
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �X�L���̏I������
//=============================================================================
void CSkill::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�L���̍X�V����
//=============================================================================
void CSkill::Update(void)
{
	for (int nCntSkill = 0; nCntSkill < MAX_SKILL; nCntSkill++)
	{
		if (m_state[nCntSkill] == SKILL_STATE_NONE)
		{//�X�L�����g�p����Ă��Ȃ��ꍇ
			m_aCol[nCntSkill] = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		}
		else if(m_state[nCntSkill] == SKILL_STATE_USE)
		{//�X�L�����g�p����Ă���ꍇ
			m_aCol[nCntSkill] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

	}
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)& pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = m_aCol[nCnt];
		pVtx[1].col = m_aCol[nCnt];
		pVtx[2].col = m_aCol[nCnt];
		pVtx[3].col = m_aCol[nCnt];
		pVtx += 4;
	}
		//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
// �X�L���̕`�揈��
//=============================================================================
void CSkill::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_SKILL; nCntPauseSelect++)
	{// ���ڂ̐������J��Ԃ�
	 // �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCntPauseSelect]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPauseSelect * 4, 2);
	}
}

//=============================================================================
// �X�L���̏I������
//=============================================================================
void CSkill::SetSkill(CSkill::SKILL skill, SKILL_STATE state)
{
	m_state[skill] = state;
}
