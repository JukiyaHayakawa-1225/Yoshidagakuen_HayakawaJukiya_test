//=============================================================================
//
// UI�̏��� [ui.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "ui.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "score.h"
#include "player.h"
#include "game.h"
#include "debugproc.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_SIZE        (30)            // �e�N�X�`���̃T�C�Y

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// UI�R���X�g���N�^
//=============================================================================
CUI::CUI()
{
	m_pTexture = NULL;							//�e�N�X�`����NULL�ɂ���
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏����l
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F�̏����l
	m_fWidth = 10.0f;							//���̏����l
	m_fHeight = 10.0f;							//�����̏����l
}
//=============================================================================
// UI�f�X�g���N�^
//=============================================================================
CUI::~CUI()
{

}

//=============================================================================
//UI����
//=============================================================================
CUI *CUI::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CUI *pUI = NULL;
	if (pUI == NULL)
	{
		pUI = new CUI;						//�V�[���̓��I�m��
		if (pUI != NULL)
		{
			pUI->SetPos(pos);				//�ʒu�̐ݒu����
			pUI->SetWidth(fWidth);			//���̐ݒu����
			pUI->SetHeight(fHeight);		//�����̐ݒu����
			pUI->Init();					//����������
		}
	}
	return pUI;								//�l��Ԃ�
}

//=============================================================================
// UI����������
//=============================================================================
HRESULT CUI::Init(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)& pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// UI�I������
//=============================================================================
void CUI::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// UI�X�V����
//=============================================================================
void CUI::Update(void)
{

}

//=============================================================================
// UI�`�揈��
//=============================================================================
void CUI::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	//UI�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
// �I�u�W�F�N�g�̎擾����
//=============================================================================
void CUI::BindTexture(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}

//=============================================================================
// �ʒu�̐ݒu����
//=============================================================================
void CUI::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �F�̐ݒu����
//=============================================================================
void CUI::SetCol(D3DXCOLOR col)
{
	m_col= col;

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���̐ݒu����
//=============================================================================
void CUI::SetWidth(float fWidth)
{
	m_fWidth = fWidth;
}

//=============================================================================
// �����̐ݒu����
//=============================================================================
void CUI::SetHeight(float fHeight)
{
	m_fHeight = fHeight;
}

//=============================================================================
// ���_���̐ݒu����
//=============================================================================
void CUI::SetVtxPos(D3DXVECTOR3 pos)
{
	m_pos = pos;	//�ʒu�̑��

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �T�C�h�I���^���Z����
//=============================================================================
void CUI::SetSideCut(int nType)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nType == 0)
	{//�����猸�Z
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_fHeight, 0.0f);
	}
	else if (nType == 1)
	{//�E���猸�Z
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �ʒu�̎擾����
//=============================================================================
D3DXVECTOR3 CUI::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �F�̎擾����
//=============================================================================
D3DXCOLOR CUI::GetCol(void)
{
	return m_col;
}

//=============================================================================
// ���̎擾����
//=============================================================================
float CUI::GetWidth(void)
{
	return m_fWidth;
}

//=============================================================================
// �����̎擾����
//=============================================================================
float CUI::GetHeight(void)
{
	return m_fHeight;
}

//=============================================================================
//
// UI�̗̓Q�[�W�̏���
// Author : Jukiya Hayakawa
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CUI_LifeGauge::m_pTexture = NULL;
CUI	*CUI_LifeGauge::m_pUI = NULL;
//=============================================================================
// UI�̗̓Q�[�W�R���X�g���N�^
//=============================================================================
CUI_LifeGauge::CUI_LifeGauge() : CScene(5, OBJTYPE_UI)
{

}

//=============================================================================
// UI�̗̓Q�[�W�f�X�g���N�^
//=============================================================================
CUI_LifeGauge::~CUI_LifeGauge()
{

}

//=============================================================================
// UI�̗̓Q�[�W�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CUI_LifeGauge::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAUGE\\GAUGE_LIFE.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// UI�̗̓Q�[�W�̃e�N�X�`���j��
//=============================================================================
void CUI_LifeGauge::Unload(void)
{

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// �̗̓Q�[�W�̎擾����
//=============================================================================
CUI *CUI_LifeGauge::GetLifeGauge(void)
{
	return m_pUI;
}

//=============================================================================
// UI�̗̓Q�[�W����
//=============================================================================
CUI_LifeGauge *CUI_LifeGauge::Create(void)
{
	CUI_LifeGauge *pUIGauge = NULL;
	if (pUIGauge == NULL)
	{
		pUIGauge = new CUI_LifeGauge;						//�V�[���̓��I�m��
		if (pUIGauge != NULL)
		{
			pUIGauge->Init();							//����������
		}
	}
	return pUIGauge;									//�l��Ԃ�
}

//=============================================================================
// UI�̗̓Q�[�W����������
//=============================================================================
HRESULT CUI_LifeGauge::Init(void)
{
		m_pUI = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 100.0f, 0.0f),MAX_GAUGE_WIDTH,20.0f);	//UI�̐���
		m_pUI->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));																//�F�̐ݒu����
		m_pUI->SetSideCut(0);																							//�����猸�Z����
		m_pUI->BindTexture(m_pTexture);																		//�e�N�X�`���̓ǂݍ���
	return S_OK;
}

//=============================================================================
// UI�̗̓Q�[�W�I������
//=============================================================================
void CUI_LifeGauge::Uninit(void)
{
	for (int nCntUI = 0; nCntUI < MAX_GAUGE_TEXTURE; nCntUI++)
	{//�Q�[�W�̃e�N�X�`�����J��Ԃ�
		if (m_pUI != NULL)
		{
			m_pUI->Uninit();
			//�������̊J��
			delete m_pUI;
			//NULL�ɂ���
			m_pUI = NULL;
		}
	}
	Release();
}

//=============================================================================
// UI�̗̓Q�[�W�X�V����
//=============================================================================
void CUI_LifeGauge::Update(void)
{
	//�v���C���[�̎擾
	CPlayer	*pPlayer;
	pPlayer = CGame::GetPlayer();

	//UI�_���[�W�̎擾����
	CUI_DamageGauge *pUI_Damage;
	pUI_Damage = CGame::GetUI_DamageGauge();

	int nLife = 0;			//�̗�
	int nMaxLife = 0;		//�̗͂̍ő�l
	float fData;			//�f�[�^�̊i�[
	if (pPlayer != NULL)
	{//�v���C���[��񂪂���ꍇ
	 //�̗͂̎擾����
		nLife = pPlayer->GetLife();
		//�Ƃ����̎擾����
		nMaxLife = pPlayer->GetMaxLife();
	}

	float fWidth = m_pUI->GetWidth();	//��
	D3DXVECTOR3 pos = m_pUI->GetPos();	//�ʒu
	fData = MAX_GAUGE_WIDTH * nLife / nMaxLife;	//�Q�[�W�̌v�Z
	if (fWidth >= 0.0f)
	{
		m_pUI->SetWidth(fData);		//���̐ݒu����
		m_pUI->SetSideCut(0);		//�����猸�Z����
		if (fWidth <= MAX_GAUGE_WIDTH && fWidth >= (MAX_GAUGE_WIDTH / 2 + 1))
		{//�Q�[�W���ő�l�ȉ����ő�l�̔����ȏ�̏ꍇ
			m_pUI->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	//�F�̐ݒu�����i�΁j
		}
		else if (fWidth <= MAX_GAUGE_WIDTH / 2 && fWidth >= (MAX_GAUGE_WIDTH / 4 + 1))
		{//�Q�[�W���ő�l�̔����ȉ����ő�l�̂S���̂P�ȏ�̏ꍇ
			m_pUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));	//�F�̐ݒu�����i���j
		}
		else if (fWidth <= MAX_GAUGE_WIDTH / 4 && fWidth >= 0)
		{//�Q�[�W���ő�l�̔����ȉ����ő�l�̂S���̂P�ȏ�̏ꍇ
			m_pUI->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	//�F�̐ݒu�����i�ԁj
		}
	}
	else
	{
		fWidth = 0.0f;				//�l�̌Œ�
		m_pUI->SetWidth(fWidth);	//���̐ݒu����
		m_pUI->SetSideCut(0);		//�E���猸�Z����
	}
	pUI_Damage->SetDamageState(CUI_DamageGauge::STATE_MINUS);	//�Q�[�W�����炷��Ԃɂ���
}

//=============================================================================
// UI�̗̓Q�[�W�`�揈��
//=============================================================================
void CUI_LifeGauge::Draw(void)
{
	for (int nCntUI = 0; nCntUI < MAX_GAUGE_TEXTURE; nCntUI++)
	{//�Q�[�W�̃e�N�X�`�����J��Ԃ�
		if (m_pUI != NULL)
		{//��񂪂���ꍇ
			m_pUI->Draw();		//�`�揈��
		}
	}
}

//=============================================================================
// UI�̗̓Q�[�W���Z����
//=============================================================================
void CUI_LifeGauge::CutLifeGauge(int nCut)
{

}


//=============================================================================
// UI�̗̓Q�[�W���Z����
//=============================================================================
void CUI_LifeGauge::ResetLifeGauge(int nLifeno)
{
	//�v���C���[�̎擾
	CPlayer	*pPlayer;
	pPlayer = CGame::GetPlayer();

	int nLife = 0;			//�̗�
	int nMaxLife = 0;		//�̗͂̍ő�l
	float fData;			//�f�[�^�̊i�[

	if (pPlayer != NULL)
	{//�v���C���[��񂪂���ꍇ
	 //�̗͂̎擾����
		nLife = pPlayer->GetLife();
		//�Ƃ����̎擾����
		nMaxLife = pPlayer->GetMaxLife();
	}

	D3DXVECTOR3 pos = m_pUI->GetPos();				//�ʒu
	fData = MAX_GAUGE_WIDTH * nLife / nMaxLife;		//�Q�[�W�̌v�Z
	m_pUI->SetWidth(fData);		//���̐ݒu����
	m_pUI->SetSideCut(0);		//�����猸�Z����
}

//=============================================================================
//
// UI�Ƃ����Q�[�W�̏���
// Author : Jukiya Hayakawa
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CUI_SkillGauge::m_apTexture[MAX_GAUGE_TEXTURE] = {};	//�e�N�X�`���̃|�C���^
CUI	*CUI_SkillGauge::m_apUI[MAX_GAUGE_TEXTURE] = {};					//UI�̃|�C���^
//=============================================================================
// UI�Ƃ����Q�[�W�R���X�g���N�^
//=============================================================================
CUI_SkillGauge::CUI_SkillGauge() : CScene(5, OBJTYPE_UI)
{

}

//=============================================================================
// UI�Ƃ����Q�[�W�f�X�g���N�^
//=============================================================================
CUI_SkillGauge::~CUI_SkillGauge()
{

}

//=============================================================================
// UI�Ƃ����Q�[�W�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CUI_SkillGauge::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAUGE\\GAUGE_BASE.png",
		&m_apTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAUGE\\GAUGE_LIFE.png",
		&m_apTexture[1]);

	return S_OK;
}

//=============================================================================
// UI�Ƃ����Q�[�W�̃e�N�X�`���j��
//=============================================================================
void CUI_SkillGauge::Unload(void)
{
	for (int nCntTexture = 0; nCntTexture < MAX_GAUGE_TEXTURE; nCntTexture++)
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
// UI�Ƃ����Q�[�W����
//=============================================================================
CUI_SkillGauge *CUI_SkillGauge::Create(void)
{
	CUI_SkillGauge *pUIGauge = NULL;
	if (pUIGauge == NULL)
	{
		pUIGauge = new CUI_SkillGauge;						//�V�[���̓��I�m��
		if (pUIGauge != NULL)
		{
			pUIGauge->Init();								//����������
		}
	}
	return pUIGauge;										//�l��Ԃ�
}

//=============================================================================
// UI�Ƃ����Q�[�W����������
//=============================================================================
HRESULT CUI_SkillGauge::Init(void)
{
	for (int nCntUI = 0; nCntUI < MAX_GAUGE_TEXTURE; nCntUI++)
	{//�Q�[�W�̃e�N�X�`�����J��Ԃ�
		m_apUI[nCntUI] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 50.0f, 0.0f), 300.0f, 20.0f);	//UI�̐���
		m_apUI[nCntUI]->SetCol(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));														//�F�̐ݒu����
		m_apUI[nCntUI]->SetSideCut(0);																					//�����猸�Z����
		m_apUI[nCntUI]->BindTexture(m_apTexture[nCntUI]);																//�e�N�X�`���̓ǂݍ���
	}
	return S_OK;
}

//=============================================================================
// UI�Ƃ����Q�[�W�I������
//=============================================================================
void CUI_SkillGauge::Uninit(void)
{
	for (int nCntUI = 0; nCntUI < MAX_GAUGE_TEXTURE; nCntUI++)
	{//�Q�[�W�̃e�N�X�`�����J��Ԃ�
		if (m_apUI[nCntUI] != NULL)
		{
			m_apUI[nCntUI]->Uninit();
			//�������̊J��
			delete m_apUI[nCntUI];
			//NULL�ɂ���
			m_apUI[nCntUI] = NULL;
		}
	}
	Release();
}

//=============================================================================
// UI�Ƃ����Q�[�W�X�V����
//=============================================================================
void CUI_SkillGauge::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�v���C���[�̎擾
	CPlayer	*pPlayer;
	pPlayer = CGame::GetPlayer();

	int nSkill = 0;			//�̗�
	int nMaxSkill = 0;		//�̗͂̍ő�l
	float fData;			//�f�[�^�̊i�[
	if (pPlayer != NULL)
	{//�v���C���[��񂪂���ꍇ
	 //�̗͂̎擾����
		nSkill = pPlayer->GetSkill();
		//�Ƃ����̎擾����
		nMaxSkill = pPlayer->GetMaxSkill();
	}

	float fWidth = m_apUI[1]->GetWidth();
	D3DXVECTOR3 pos = m_apUI[1]->GetPos();
	fData = MAX_GAUGE_WIDTH * nSkill / nMaxSkill;
	if (fWidth >= 0.0f)
	{
		m_apUI[1]->SetWidth(fData);	//���̐ݒu����
		m_apUI[1]->SetSideCut(0);		//�����猸�Z����
	}
	else
	{
		fWidth = 0.0f;	//�l�̌Œ�
		m_apUI[1]->SetWidth(fWidth);	//���̐ݒu����
		m_apUI[1]->SetSideCut(0);		//�E���猸�Z����
	}
}

//=============================================================================
// UI�Ƃ����Q�[�W�`�揈��
//=============================================================================
void CUI_SkillGauge::Draw(void)
{
	for (int nCntUI = 0; nCntUI < MAX_GAUGE_TEXTURE; nCntUI++)
	{//�Q�[�W�̃e�N�X�`�����J��Ԃ�
		if (m_apUI[nCntUI] != NULL)
		{//��񂪂���ꍇ
			m_apUI[nCntUI]->Draw();		//�`�揈��
		}
	}
}

//=============================================================================
// UI�̗̓Q�[�W���Z����
//=============================================================================
void CUI_SkillGauge::CutSkillGauge(int nCut)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetKeyboard();

	//�v���C���[�̎擾
	CPlayer	*pPlayer;
	pPlayer = CGame::GetPlayer();

	int nSkill = 0;			//�̗�
	int nMaxSkill = 0;		//�̗͂̍ő�l
	float fData;			//�f�[�^�̊i�[
	if (pPlayer != NULL)
	{//�v���C���[��񂪂���ꍇ
	 //�̗͂̎擾����
		nSkill = pPlayer->GetSkill();
		//�Ƃ����̎擾����
		nMaxSkill = pPlayer->GetMaxSkill();
	}

	float fWidth = m_apUI[1]->GetWidth();
	D3DXVECTOR3 pos = m_apUI[1]->GetPos();
	fData = MAX_GAUGE_WIDTH * nSkill / nMaxSkill;
	if (fWidth >= 0.0f)
	{
		m_apUI[1]->SetWidth(fData);	//���̐ݒu����
		m_apUI[1]->SetSideCut(0);		//�����猸�Z����
	}
	else
	{
		fWidth = 0.0f;	//�l�̌Œ�
		m_apUI[1]->SetWidth(fWidth);	//���̐ݒu����
		m_apUI[1]->SetSideCut(0);		//�E���猸�Z����
	}
}

//=============================================================================
//
// �_���[�W�Q�[�W�̏���
// Author : Jukiya Hayakawa
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CUI_DamageGauge::m_pTexture = NULL;
CUI	*CUI_DamageGauge::m_pUI = NULL;

//=============================================================================
// �_���[�W�Q�[�W�R���X�g���N�^
//=============================================================================
CUI_DamageGauge::CUI_DamageGauge() : CScene(4, OBJTYPE_UI)
{

}

//=============================================================================
// �_���[�W�Q�[�W�f�X�g���N�^
//=============================================================================
CUI_DamageGauge::~CUI_DamageGauge()
{

}

//=============================================================================
// �_���[�W�Q�[�W�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CUI_DamageGauge::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAUGE\\DAMAGE_GAUGE.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �_���[�W�Q�[�W�̃e�N�X�`���j��
//=============================================================================
void CUI_DamageGauge::Unload(void)
{

		// �e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//=============================================================================
// �_���[�W�Q�[�W����
//=============================================================================
CUI_DamageGauge *CUI_DamageGauge::Create(void)
{
	CUI_DamageGauge *pUIGauge = NULL;
	if (pUIGauge == NULL)
	{
		pUIGauge = new CUI_DamageGauge;						//�V�[���̓��I�m��
		if (pUIGauge != NULL)
		{
			pUIGauge->Init();							//����������
		}
	}
	return pUIGauge;									//�l��Ԃ�
}

//=============================================================================
// �_���[�W�Q�[�W����������
//=============================================================================
HRESULT CUI_DamageGauge::Init(void)
{
	m_state = STATE_NOMAL;	//��Ԃ̏�����
	m_pUI = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 100.0f, 0.0f), 300.0f, 20.0f);	//UI�̐���
	m_pUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));														//�F�̐ݒu����
	m_pUI->SetSideCut(0);																					//�����猸�Z����
	m_pUI->BindTexture(m_pTexture);																			//�e�N�X�`���̓ǂݍ���
	return S_OK;
}

//=============================================================================
// �_���[�W�Q�[�W�I������
//=============================================================================
void CUI_DamageGauge::Uninit(void)
{
	if (m_pUI != NULL)
	{
		m_pUI->Uninit();
		//�������̊J��
		delete m_pUI;
		//NULL�ɂ���
		m_pUI = NULL;
	}
	Release();
}

//=============================================================================
// �_���[�W�Q�[�W�X�V����
//=============================================================================
void CUI_DamageGauge::Update(void)
{
	CUI *pLifeGauge = NULL;
	pLifeGauge = CUI_LifeGauge::GetLifeGauge();

	float fWidth;
	float fLifeWidth;
	fWidth = m_pUI->GetWidth();
	fLifeWidth = pLifeGauge->GetWidth();
	switch (m_state)
	{
	case STATE_NOMAL:		//�ʏ��Ԃ̏ꍇ
		break;
	case STATE_MINUS:		//���Z��Ԃ̏ꍇ
		fWidth -= 0.5f;	//���Z����
		if (fWidth <= fLifeWidth)
		{//������v�����ꍇ
			fWidth = fLifeWidth;	//���̌Œ�
		}
		break;
	}
	m_pUI->SetWidth(fWidth);
	m_pUI->SetSideCut(0);
}

//=============================================================================
// �_���[�W�Q�[�W�`�揈��
//=============================================================================
void CUI_DamageGauge::Draw(void)
{

	if (m_pUI != NULL)
	{//��񂪂���ꍇ
		m_pUI->Draw();		//�`�揈��
	}
}

//=============================================================================
// ��Ԑݒu����
//=============================================================================
void CUI_DamageGauge::SetDamageState(DAMAGE_STATE state)
{
	m_state = state;
}

//=============================================================================
//
// UI�x�[�X�Q�[�W�̏���
// Author : Jukiya Hayakawa
//
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CUI_BaseGauge::m_pTexture = NULL;
CUI	*CUI_BaseGauge::m_pUI = NULL;
//=============================================================================
// UI�x�[�X�Q�[�W�R���X�g���N�^
//=============================================================================
CUI_BaseGauge::CUI_BaseGauge() : CScene(3, OBJTYPE_UI)
{

}

//=============================================================================
// UI�x�[�X�Q�[�W�f�X�g���N�^
//=============================================================================
CUI_BaseGauge::~CUI_BaseGauge()
{

}

//=============================================================================
// UI�x�[�X�Q�[�W�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CUI_BaseGauge::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAUGE\\GAUGE_BASE.png",
		&m_pTexture);
	return S_OK;
}

//=============================================================================
// UI�x�[�X�Q�[�W�̃e�N�X�`���j��
//=============================================================================
void CUI_BaseGauge::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// UI�x�[�X�Q�[�W����
//=============================================================================
CUI_BaseGauge *CUI_BaseGauge::Create(void)
{
	CUI_BaseGauge *pUIGauge = NULL;
	if (pUIGauge == NULL)
	{
		pUIGauge = new CUI_BaseGauge;						//�V�[���̓��I�m��
		if (pUIGauge != NULL)
		{
			pUIGauge->Init();							//����������
		}
	}
	return pUIGauge;									//�l��Ԃ�
}

//=============================================================================
// UI�x�[�X�Q�[�W����������
//=============================================================================
HRESULT CUI_BaseGauge::Init(void)
{
	m_pUI = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 100.0f, 0.0f), 300.0f, 20.0f);	//UI�̐���
	m_pUI->SetCol(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));														//�F�̐ݒu����
	m_pUI->SetSideCut(0);																					//�����猸�Z����
	m_pUI->BindTexture(m_pTexture);																			//�e�N�X�`���̓ǂݍ���

	return S_OK;
}

//=============================================================================
// UI�x�[�X�Q�[�W�I������
//=============================================================================
void CUI_BaseGauge::Uninit(void)
{
	if (m_pUI != NULL)
	{
		m_pUI->Uninit();
		//�������̊J��
		delete m_pUI;
		//NULL�ɂ���
		m_pUI = NULL;
	}

	Release();
}

//=============================================================================
// UI�x�[�X�Q�[�W�X�V����
//=============================================================================
void CUI_BaseGauge::Update(void)
{
}

//=============================================================================
// UI�x�[�X�Q�[�W�`�揈��
//=============================================================================
void CUI_BaseGauge::Draw(void)
{
	if (m_pUI != NULL)
	{//��񂪂���ꍇ
		m_pUI->Draw();		//�`�揈��
	}
}

