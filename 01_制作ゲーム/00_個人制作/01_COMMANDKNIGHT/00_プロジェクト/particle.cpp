//=============================================================================
//
// �p�[�e�B�N���̏��� [effect.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "particle.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "enemy.h"
#include "score.h"
#include "billboard.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CParticle::CParticle() : CBillboard()
{
	m_nLife = 30;								//�̗͂̏����l
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CParticle::~CParticle()
{

}

//=============================================================================
//�I�u�W�F�N�g�̐���
//=============================================================================
CParticle *CParticle::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col,float fLength)
{
	CParticle *pParticle = NULL;

	if (pParticle == NULL)
	{
		pParticle = new CParticle;				//�V�[���̓��I�m��
		pParticle->SetPos(pos);					//�ʒu�̑��
		pParticle->SetLength(fLength);			//�g��̑��
		pParticle->SetMove(move);				//�ړ��ʂ̐ݒu����
		pParticle->Init();						//����������
		pParticle->SetCol(col);					//�F�̑��
		pParticle->BindTexture(m_pTexture);		//�e�N�X�`��
	}
	return pParticle;							//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CParticle::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CParticle::Unload(void)
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
HRESULT CParticle::Init(void)
{
	CBillboard::Init();
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CParticle::Uninit(void)
{
	//�I������
	CBillboard::Uninit(); 
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CParticle::Update(void)
{
	float		length;		//�g��
	int			nLife;		//�̗�

	//�g��̎擾
	length = GetLength();
	//�̗͂̎擾
	nLife = GetLife();

	if (length <= 0.0f || nLife <= 0)
	{//�g�吔�܂��͍�����0�ȉ��܂��̗͑͂�0�ȉ��ɂȂ����ꍇ
		//�I������
		Uninit();
	}

	//CScene2D�̍X�V����
	CBillboard::Update();
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CParticle::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//CScene2D�̕`�揈��
	CBillboard::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �̗͂̐ݒu����
//=============================================================================
void CParticle::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// �̗͂̐ݒu����
//=============================================================================
int CParticle::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// �Ƃ���2�p�[�e�B�N���̏���
//=============================================================================
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CSkill2Particle::m_pTexture = NULL;

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CSkill2Particle::CSkill2Particle() : CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏����l
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CSkill2Particle::~CSkill2Particle()
{

}

//=============================================================================
//�I�u�W�F�N�g�̐���
//=============================================================================
CSkill2Particle *CSkill2Particle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fLength,int nLife)
{
	CSkill2Particle *pSkill2Particle = NULL;

	if (pSkill2Particle == NULL)
	{
		pSkill2Particle = new CSkill2Particle;			//�V�[���̓��I�m��
		pSkill2Particle->SetPos(pos);					//�ʒu�̑��
		pSkill2Particle->SetLength(fLength);			//�g��̑��
		pSkill2Particle->SetMove(move);					//�ړ��ʂ̂�����
		pSkill2Particle->SetLife(nLife);				//�̗͂̐ݒu����
		pSkill2Particle->Init();						//����������
		pSkill2Particle->SetCol(col);					//�F�̑��
		pSkill2Particle->BindTexture(m_pTexture);		//�e�N�X�`��
	}
	return pSkill2Particle;							//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CSkill2Particle::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\particle_skill0.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CSkill2Particle::Unload(void)
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
HRESULT CSkill2Particle::Init(void)
{
	//����������
	CParticle::Init();
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CSkill2Particle::Uninit(void)
{
	//�I������
	CParticle::Uninit();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CSkill2Particle::Update(void)
{
	D3DXVECTOR3	pos,move;		//�ʒu
	D3DXCOLOR	col;		//�F
	float		length;		//�g��
	int			nLife;		//�̗�

	//�ʒu�̎擾
	pos = GetPos();
	//�F�̎擾
	col = GetCol();
	//�g��̎擾
	length = GetLength();
	//�̗͂̎擾
	nLife = GetLife();
	//�ړ��ʂ̎擾
	move = GetMove();

	//�ړ��ʉ��Z
	pos += move;
	pos.y += 1.0f;

	//�̗͂̌��Z
	nLife--;

	//�ʒu�̐ݒu
	SetPos(pos);
	//�g��̐ݒu
	SetLength(length);
	//�ʒu�̐ݒu
	SetLengthPos();
	//�F�̐ݒu
	SetCol(col);
	//�̗͂̐ݒu
	SetLife(nLife);

	//�p�[�e�B�N���X�V����
	CParticle::Update();
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CSkill2Particle::Draw(void)
{
	CParticle::Draw();
	//CBillboard::Draw();
}

//=============================================================================
// �_���[�W�p�[�e�B�N���̏���
//=============================================================================
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CDamageParticle::m_pTexture = NULL;

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CDamageParticle::CDamageParticle() : CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏����l
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CDamageParticle::~CDamageParticle()
{

}

//=============================================================================
//�I�u�W�F�N�g�̐���
//=============================================================================
CDamageParticle *CDamageParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fLength, int nLife)
{
	CDamageParticle *pDamageParticle = NULL;

	if (pDamageParticle == NULL)
	{
		pDamageParticle = new CDamageParticle;			//�V�[���̓��I�m��
		pDamageParticle->SetPos(pos);					//�ʒu�̑��
		pDamageParticle->SetLength(fLength);			//�g��̑��
		pDamageParticle->SetMove(move);					//�ړ��ʂ̐ݒu����
		pDamageParticle->SetLife(nLife);				//�̗͂̐ݒu����
		pDamageParticle->Init();						//����������
		pDamageParticle->SetCol(col);					//�F�̑��
		pDamageParticle->BindTexture(m_pTexture);		//�e�N�X�`��
	}
	return pDamageParticle;							//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CDamageParticle::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CDamageParticle::Unload(void)
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
HRESULT CDamageParticle::Init(void)
{
	//����������
	CParticle::Init();
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CDamageParticle::Uninit(void)
{
	//�I������
	CParticle::Uninit();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CDamageParticle::Update(void)
{
	D3DXVECTOR3	pos,move;	//�ʒu
	D3DXCOLOR	col;		//�F
	float		length;		//�g��
	int			nLife;		//�̗�

	//�ʒu�̎擾
	pos = GetPos();
	//�F�̎擾
	col = GetCol();
	//�g��̎擾
	length = GetLength();
	//�̗͂̎擾
	nLife = GetLife();
	//�ړ��ʂ̎擾
	move = GetMove();

	//�ړ��ʉ��Z
	pos += m_move;
	//pos.y += 1.0f;

	length -= 1.0f;
	//�̗͂̌��Z
	nLife--;
	pos += move;

	//�ʒu�̐ݒu
	SetPos(pos);
	//�g��̐ݒu
	SetLength(length);
	//�ʒu�̐ݒu
	SetLengthPos();
	//�F�̐ݒu
	SetCol(col);
	//�̗͂̐ݒu
	SetLife(nLife);

	//�p�[�e�B�N���X�V����
	CParticle::Update();
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CDamageParticle::Draw(void)
{
	CParticle::Draw();
	//CBillboard::Draw();
}
//=============================================================================
// ��p�[�e�B�N���̏���
//=============================================================================
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CSnowParticle::m_pTexture = NULL;

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CSnowParticle::CSnowParticle() : CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏����l
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CSnowParticle::~CSnowParticle()
{

}

//=============================================================================
//�I�u�W�F�N�g�̐���
//=============================================================================
CSnowParticle *CSnowParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fLength, int nLife)
{
	CSnowParticle *pSnowParticle = NULL;

	if (pSnowParticle == NULL)
	{
		pSnowParticle = new CSnowParticle;			//�V�[���̓��I�m��
		pSnowParticle->SetPos(pos);					//�ʒu�̑��
		pSnowParticle->SetLength(fLength);			//�g��̑��
		pSnowParticle->SetMove(move);				//�ړ��ʂ̐ݒu����
		pSnowParticle->SetLife(nLife);				//�̗͂̐ݒu����
		pSnowParticle->Init();						//����������
		pSnowParticle->SetCol(col);					//�F�̑��
		pSnowParticle->BindTexture(m_pTexture);		//�e�N�X�`��
	}
	return pSnowParticle;							//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CSnowParticle::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\particle_skill0.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CSnowParticle::Unload(void)
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
HRESULT CSnowParticle::Init(void)
{
	//����������
	CParticle::Init();
	m_nTimer = 0;
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CSnowParticle::Uninit(void)
{
	//�I������
	CParticle::Uninit();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CSnowParticle::Update(void)
{
	D3DXVECTOR3	pos, move;		//�ʒu
	D3DXCOLOR	col;		//�F
	float		length;		//�g��
	int			nLife;		//�̗�

	//�ʒu�̎擾
	pos = GetPos();
	//�F�̎擾
	col = GetCol();
	//�g��̎擾
	length = GetLength();
	//�̗͂̎擾
	nLife = GetLife();
	//�ړ��ʂ̎擾
	move = GetMove();

	//�ړ��ʉ��Z
	//pos += m_move;
	//pos.y += 1.0f;
	pos.y -= 1.0f;
	m_nTimer++;

	if (m_nTimer >= 20)
	{

		int nData = rand() % 4 + 1;
		if (nData == 1 || nData == 2)
		{
			pos.x -= 1.0f;
		}
		else if (nData == 3 || nData == 4)
		{
			pos.x += 1.0f;

		}
		m_nTimer = 0;
	}
	//length -= 1.0f;
	//�̗͂̌��Z
	nLife--;
	//pos += move;

	//�ʒu�̐ݒu
	SetPos(pos);
	//�g��̐ݒu
	SetLength(length);
	//�ʒu�̐ݒu
	SetLengthPos();
	//�F�̐ݒu
	SetCol(col);
	//�̗͂̐ݒu
	SetLife(nLife);

	//�p�[�e�B�N���X�V����
	CParticle::Update();
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CSnowParticle::Draw(void)
{
	CParticle::Draw();
	//CBillboard::Draw();
}


//=============================================================================
// �����p�[�e�B�N���̏���
//=============================================================================
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CFountainParticle::m_pTexture = NULL;

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CFountainParticle::CFountainParticle() : CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏����l
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CFountainParticle::~CFountainParticle()
{

}

//=============================================================================
//�I�u�W�F�N�g�̐���
//=============================================================================
CFountainParticle *CFountainParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fLength, int nLife)
{
	CFountainParticle *pFountainParticle = NULL;

	if (pFountainParticle == NULL)
	{
		pFountainParticle = new CFountainParticle;		//�V�[���̓��I�m��
		pFountainParticle->SetPos(pos);					//�ʒu�̑��
		pFountainParticle->SetLength(fLength);			//�g��̑��
		pFountainParticle->SetMove(move);				//�ړ��ʂ̐ݒu����
		pFountainParticle->SetLife(nLife);				//�̗͂̐ݒu����
		pFountainParticle->Init();						//����������
		pFountainParticle->SetCol(col);					//�F�̑��
		pFountainParticle->BindTexture(m_pTexture);		//�e�N�X�`��
	}
	return pFountainParticle;							//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CFountainParticle::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\particle_skill0.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CFountainParticle::Unload(void)
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
HRESULT CFountainParticle::Init(void)
{
	//����������
	CParticle::Init();
	m_nTimer = 0;
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CFountainParticle::Uninit(void)
{
	//�I������
	CParticle::Uninit();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CFountainParticle::Update(void)
{
	D3DXVECTOR3	pos, move;		//�ʒu
	D3DXCOLOR	col;		//�F
	float		length;		//�g��
	int			nLife;		//�̗�

	//�ʒu�̎擾
	pos = GetPos();
	//�F�̎擾
	col = GetCol();
	//�g��̎擾
	length = GetLength();
	//�̗͂̎擾
	nLife = GetLife();
	//�ړ��ʂ̎擾
	move = GetMove();

	//�ړ��ʉ��Z
	pos += move;
	//pos.y += 1.0f;
	pos.y -= 5.0f;

	//length -= 1.0f;
	//�̗͂̌��Z
	nLife--;
	//pos += move;

	//�ʒu�̐ݒu
	SetPos(pos);
	//�g��̐ݒu
	SetLength(length);
	//�ʒu�̐ݒu
	SetLengthPos();
	//�F�̐ݒu
	SetCol(col);
	//�̗͂̐ݒu
	SetLife(nLife);

	//�p�[�e�B�N���X�V����
	CParticle::Update();
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CFountainParticle::Draw(void)
{
	CParticle::Draw();
	//CBillboard::Draw();
}
