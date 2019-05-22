//=============================================================================
//
// �G�̖h�q�̏��� [defense.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "defense.h"
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CDefense::m_pTexture = NULL;

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �G�̖h�q�̃R���X�g���N�^
//=============================================================================
CDefense::CDefense() : CScene2D(2)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ̏����l
}
//=============================================================================
// �G�̖h�q�̃f�X�g���N�^
//=============================================================================
CDefense::~CDefense()
{

}

//=============================================================================
//�G�̖h�q�̐���
//=============================================================================
CDefense *CDefense::Create(D3DXVECTOR3 pos, float fWight, float fHeight)
{
	CDefense *pDefense = NULL;
	if (pDefense == NULL)
	{
		pDefense = new CDefense;			//�V�[���̓��I�m��
		pDefense->SetPos(pos);				//�ʒu�̑��
		pDefense->SetWidth(fWight);			//���̑��
		pDefense->SetHeight(fHeight);		//�����̑��
		pDefense->Init();					//����������
		pDefense->BindTexture(m_pTexture);	//�e�N�X�`���̓\��t��
	}
	return pDefense;						//�l��Ԃ�
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CDefense::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\barrier.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CDefense::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �G�̖h�q�̏���������
//=============================================================================
HRESULT CDefense::Init(void)
{
	//�ړ��ʂ̏���������
	m_move = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	//�J�E���^�|�̏���������
	m_nCounter = 0;
	//CScene2D�̏���������
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �G�̖h�q�̏I������
//=============================================================================
void CDefense::Uninit(void)
{
	//CScene2D�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �G�̖h�q�̍X�V����
//=============================================================================
void CDefense::Update(void)
{
	//�v���C���[�̒ǔ�����
	FollowPlayer();
	//�X�V����
	CScene2D::Update();
}

//=============================================================================
// �G�̖h�q�̕`�揈��
//=============================================================================
void CDefense::Draw(void)
{
	//CScene2D�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �v���C���[�̒ǔ�����
//=============================================================================
void CDefense::FollowPlayer(void)
{
	D3DXVECTOR3 pos;	//�ʒu
	float fAngle;		//�p�x
	m_nCounter++;
	pos = GetPos();		//�ʒu�̎擾

	for (int nCntPrioty = 0; nCntPrioty < NUM_PRIORITY; nCntPrioty++)
	{//�D��x�̐������J��Ԃ�
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{//Scene�̐������J��Ԃ�
			CScene2D *pScene;															//�V�[���̃|�C���^
			pScene = (CScene2D*)CScene::GetScene(nCntPrioty, nCntScene);				//�V�[���̎擾
			if (pScene != NULL)
			{//Scene��NULL�łȂ��ꍇ
				CScene::OBJTYPE objType;												//���
				objType = pScene->GetObjType();											//��ނ̎擾
				if (objType == OBJTYPE_BOSS)
				{//�I�u�W�F�N�g���v���C���[�̏ꍇ
					D3DXVECTOR3 BossPos;												//�v���C���[�̈ʒu
					CEnemyBoss *pBoss = (CEnemyBoss*)pScene;							//�v���C���[�̓��I�m��
					BossPos = pBoss->GetPos();											//�ʒu�̎擾
					fAngle = atan2f(BossPos.x - pos.x, BossPos.y - pos.y);				//�����̎擾
					D3DXVECTOR3 SetPos(sinf(fAngle) * 2.5f, cosf(fAngle) * 2.5f, 0.0f);	//�ʒu�̏��
					m_move = SetPos;													//�v���C���[�̒ǔ�
					if (m_nCounter > 200)
					{
						m_move = D3DXVECTOR3(sinf(D3DX_PI*(m_nCounter - 200) / 160.0f)*3.0f, sinf(D3DX_PI*(m_nCounter - 120) / 160.0f)*3.0f, 0.0f);
					}
					pos += m_move;		//�ړ��ʂ̑��

					//�ʒu�̐ݒu
					SetVtxPos(pos);
				}
			}
		}
	}
}