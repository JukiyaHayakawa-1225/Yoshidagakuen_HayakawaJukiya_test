//=============================================================================
//
// �G�̏��� [player.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "debugproc.h"
#include "scene3D.h"
#include "meshfield.h"
#include "model.h"
#include "game.h"
#include "object.h"
#include "command.h"
#include "player.h"
#include "loadfilefunction.h"
#include "particle.h"
#include "score.h"
#include "billboardgauge.h"
#include "bullet.h"

#define MOTION_TXT_NAME "data\\TEXT\\motionEnemy.txt"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH			CEnemy::m_pMesh[MAX_ENEMY_MODEL] = {};		//���b�V���̃|�C���^
LPD3DXBUFFER		CEnemy::m_pBuffMat[MAX_ENEMY_MODEL] = {};	//�}�e���A���̏��
DWORD				CEnemy::m_nNumMat[MAX_ENEMY_MODEL] = {};	//�}�e���A���̐�
int					CEnemy::m_nNumEnemy = 0;					//�G�̑���
char				CEnemy::m_aFilenameModel[MAX_ENEMY_MODEL][256] = {};		//���f���t�@�C��

//CBillboardLifeGauge *CEnemy::m_pBillboardLifeGauge = NULL;

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemy::CEnemy() : CScene(3, OBJTYPE_ENEMY)
{
	m_nNumEnemy ++;
	m_nLife = MAX_ENEMY_LIFE;
	m_nNumModel = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu�̏����l
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ߋ��̈ʒu�̏����l
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����̏����l
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ��ʏ����l
	m_bJump = false;								//�W�����v���Ă��Ȃ����
	m_bAction = false;								//�s�����Ă��Ȃ����
	m_motionType = MOTION_NEUTRAL;					//���[�V������������
	m_nCountFrame = 0;								//�t���[���̏����l
	m_nLife = 0;									//�̗͂̏����l
	m_nCounter = 0;
	m_fDestAngle = 0.0f;
	for (int nCntModel = 0; nCntModel < MAX_ENEMY_MODEL; nCntModel++)
	{//���f���̐������J��Ԃ�
		m_apModel[nCntModel] = NULL;
	}
	for (int nCntMotion = 0; nCntMotion < MAX_ENEMY_MOTION; nCntMotion++)
	{//���f���̐������J��Ԃ�
		m_aMotionAttack[nCntMotion].nAttackEndFrame = 0;
		m_aMotionAttack[nCntMotion].nAttackStartFrame = 0;
		m_aMotionAttack[nCntMotion].nNumFrame = 0;
	}
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̃e�N�X�`���j��
//=============================================================================
void CEnemy::Unload(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_ENEMY_MODEL; nCntMesh++)
	{//���f���̐������J��Ԃ�
	 // ���b�V���̊J��
		if (m_pMesh[nCntMesh] != NULL)
		{
			m_pMesh[nCntMesh]->Release();
			m_pMesh[nCntMesh] = NULL;
		}
	}

	for (int nCntMat = 0; nCntMat < MAX_ENEMY_MODEL; nCntMat++)
	{//���f���̐������J��Ԃ�
	 // �}�e���A���̊J��
		if (m_pBuffMat[nCntMat] != NULL)
		{
			m_pBuffMat[nCntMat]->Release();
			m_pBuffMat[nCntMat] = NULL;
		}
	}
}

//=============================================================================
//�G�̐���
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = NULL;					//�G�̃|�C���^
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;				//�V�[���̓��I�m��
		pEnemy->Init();						//����������
		pEnemy->m_pos = pos;				//�ʒu�̑��
	}
	return pEnemy;							//�l��Ԃ�
}

//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	//���[�V��������ǂݍ���
	//LoadMotion(MOTION_TXT_NAME);

	m_nLife = 10;								//�̗͂̏�����
	m_nMaxLife = MAX_ENEMY_LIFE;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʏ����l
	m_bJump = false;							//�W�����v���Ă��Ȃ����
	m_nKey = 0;									//���݂̃L�[��������
	m_nNumKey = 2;								//�L�[�̑�����������
	m_nCountFrame = 0;							//�J�E���g�t���[����������
	SetObjType(OBJTYPE_ENEMY);					//�I�u�W�F�N�g�̎�ނ̐ݒu
	m_nCounter = 0;								//�J�E���^�[�̏�����
	m_state = ENEMY_STATE_NOMAL;				//�ʏ��Ԃɂ���
	m_nCntDamage = 0;							//�_���[�W�J�E���^�[�̏�����
	m_nCounterAttack = 0;						//�U���J�E���^�[�̏�����
	m_bAttack = false;							//�U�����Ă��Ȃ�
	m_pBillboardLifeGauge = CBillboardLifeGauge::Create(D3DXVECTOR3(m_pos.x,m_pos.y + 60.0f,m_pos.z),m_nLife,m_nMaxLife);	//�r���{�[�h�̗̓Q�[�W�̐���

	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemy::Uninit(void)
{
	m_nNumEnemy--;		//�G�̑������Z

	for (int nCntModel = 0; nCntModel < MAX_ENEMY_MODEL; nCntModel++)
	{//���f���̐������J��Ԃ�
		if (m_apModel[nCntModel] != NULL)
		{
			//�I������
			m_apModel[nCntModel]->Uninit();
			delete m_apModel[nCntModel];
			m_apModel[nCntModel] = NULL;
		}
	}

	//�r���{�[�h�̗̓Q�[�W�̏I������
	if (m_pBillboardLifeGauge != NULL)
	{
		m_pBillboardLifeGauge->Uninit();
		m_pBillboardLifeGauge = NULL;
	}
	//�f�[�^�J��
	Release();
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemy::Update(void)
{
	//���݂̈ʒu�����ߋ��̈ʒu�ɑ��
	m_posOld = m_pos;

	//���[�V�����̍X�V����
	UpdateMotion();

	//���݂̃��[�V�������ߋ��̃��[�V�������ɑ��
	m_OldMotion = m_motionType;

	m_nCounter++;	//�J�E���^�[�̉��Z

	if (m_nCounter >= 100)
	{//�J�E���^�[��100�ȏ�̏ꍇ
		m_nCounter = 0;	//�J�E���^�[�̏�����
	}

	if (m_pBillboardLifeGauge != NULL)
	{//�r���{�[�h�̗̓Q�[�W��NULL�łȂ��ꍇ
		m_pBillboardLifeGauge->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 60.0f, m_pos.z));	//�ʒu�̐ݒu����
	}

	m_pos += m_move;	//�ʒu�̉��Z����

	//�ړI�̊p�x�܂�
	float fAngle = m_fDestAngle - m_rot.y;

	//�p�x����
	if (fAngle > D3DX_PI)
	{
		fAngle -= D3DX_PI * 2;
	}
	if (fAngle < -D3DX_PI)
	{
		fAngle += D3DX_PI * 2;
	}
	//�G�̊p�x����
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	//�p�x���
	m_rot.y += fAngle * 0.1f;

	//��ޕ���
	switch (m_state)
	{
	case ENEMY_STATE_NOMAL:	//�ʏ��Ԃ̏ꍇ
		break;
	case EMEMY_STATE_DAMAGE:	//�_���[�W��Ԃ̏ꍇ
		m_nCntDamage++;			//�_���[�W�J�E���^�[�̉��Z
		if (m_nCntDamage >= 50)
		{//�_���[�W�J�E���^�[���T�O�ȏ�̏ꍇ
			m_nCntDamage = 0;	//�_���[�W�J�E���^�[�̏�����
			m_state = ENEMY_STATE_NOMAL;	//�ʏ��Ԃɂ���
		}
		break;
	}

	if (m_bAttack == true)
	{
		m_nCounterAttack++;		//�U���J�E���^�[�̉��Z
		if (m_nCounterAttack >= 50)
		{//�U���J�E���^�[���T�O�ȏ�̏ꍇ
			m_nCounterAttack = 0;	//
			m_bAttack = false;		//�U�����Ă��Ȃ��悤�ɂ���
		}
	}
#ifdef _DEBUG
	//CDebugProc::Print(1, "�G�̈ʒu  : x[%.1f],y[%.1f],z[%.1f]\n", m_pos.x, m_pos.y, m_pos.z);
#endif
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMATRIX	mtxShadow;		//�V���h�E�}�g���b�N�X
	D3DXPLANE	planeField;		//���ʏ��
	D3DXVECTOR4 vecLight;		//���C�g���
	D3DXVECTOR3	pos, normal;	//�ʒu�A�@��

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�V���h�E�}�g���b�N�X��������
	D3DXMatrixIdentity(&mtxShadow);

	//���C�g�̐ݒ�
	vecLight = D3DXVECTOR4(0.25f, 0.87f, -0.44f, 0.0f);

	//�ʒu�̐ݒ�
	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�@���̐ݒ�
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�ʒu�Ɩ@�����畽�ʂ��쐬����
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	//���ʂ̎ˉe
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	for (int nCntModel = 0; nCntModel < MAX_ENEMY_MODEL; nCntModel++)
	{//���f���̐������J��Ԃ�
	 //�e�N�X�`������
	 //pDevice->SetTexture(0, NULL);
	 // ���f��(�p�[�c)�̕`��
	 //m_pMesh[nCntModel]->DrawSubset(0);
		if (m_apModel[nCntModel] != NULL)
		{
			//�`�揈��
			m_apModel[nCntModel]->Draw();
		}
	}

	//���̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntModel = 0; nCntModel < MAX_ENEMY_MODEL; nCntModel++)
	{//���f���̐������J��Ԃ�
		if (m_apModel[nCntModel] != NULL)
		{
			if (m_state == EMEMY_STATE_DAMAGE)
			{// ������Ă��Ȃ���Ԃ̏ꍇ
				if (m_nCounter % 5 == 0)
				{// �J�E���^�[�����̒l�ɂȂ�����
				//���f���̕`��
					m_apModel[nCntModel]->Draw();
				}
			}
			else
			{
				//���f���̕`��
				m_apModel[nCntModel]->Draw();
			}
		}
	}
}

//=============================================================================
// �G�̃��[�V�����X�V����
//=============================================================================
void CEnemy::UpdateMotion(void)
{
	KEY *pKey, *pKeyNext;		// �L�[�̏��
	float fRateMotion;			// ���Βl
	float fDiffMotion;			// ����
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ����

	if (m_OldMotion != m_motionType)
	{//�O��̃��[�V�������Ⴄ�ꍇ
		m_nKey = 0;			//���݂̃L�[��������
		m_nCountFrame = 0;	//�J�E���g�t���[����������
		m_nCntNumFrame = 0;
	}
	m_nCntNumFrame++;
	if (m_nCntNumFrame >= m_aMotionAttack[m_motionType].nAttackStartFrame &&
		m_nCntNumFrame <= m_aMotionAttack[m_motionType].nAttackEndFrame)
	{
		m_bAction = true;
	}
	else
	{
		m_bAction = false;

	}
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{//���f���̐������J��Ԃ�
		if (m_apModel[nCntModel] != NULL)
		{//���f��������ꍇ
			pKey = &m_apMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[nCntModel];
			pKeyNext = &m_apMotionInfo[m_motionType].aKeyInfo[(m_nKey + 1) % /*2*/m_apMotionInfo[m_motionType].nNumKey].aKey[nCntModel];

			//�ʒu���WX
			fRateMotion = (float)(m_nCountFrame) / (float)m_apMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame;	// ���Βl�̎擾
			fDiffMotion = pKeyNext->fPosX - pKey->fPosX;														// �����̎擾
			pos.x = pKey->fPosX + (fDiffMotion * fRateMotion);

			//�ʒu���WY
			fDiffMotion = pKeyNext->fPosY - pKey->fPosY;								// �����̎擾
			pos.y = pKey->fPosY + (fDiffMotion * fRateMotion);

			//�ʒu���WZ
			fDiffMotion = pKeyNext->fPosZ - pKey->fPosZ;								// �����̎擾
			pos.z = pKey->fPosZ + (fDiffMotion * fRateMotion);

			//��Βl����
			D3DXVECTOR3 rotPlus, rotMinus;
			rotPlus.x = pKeyNext->fRotX + pKey->fRotX;
			rotPlus.y = pKeyNext->fRotY + pKey->fRotY;
			rotPlus.z = pKeyNext->fRotZ + pKey->fRotZ;
			rotMinus.x = pKeyNext->fRotX - pKey->fRotX;
			rotMinus.y = pKeyNext->fRotY - pKey->fRotY;
			rotMinus.z = pKeyNext->fRotZ - pKey->fRotZ;
			rotPlus.x = abs(rotPlus.x);
			rotPlus.y = abs(rotPlus.y);
			rotPlus.z = abs(rotPlus.z);
			rotMinus.x = abs(rotMinus.x);
			rotMinus.y = abs(rotMinus.y);
			rotMinus.z = abs(rotMinus.z);

			if (nCntModel == 0)
			{
				if (rotPlus.x < rotMinus.x)
				{
					//�������WX
					fDiffMotion = pKeyNext->fRotX + pKey->fRotX;								// �����̎擾
					rot.x = pKey->fRotX + (fDiffMotion * fRateMotion);
				}
				else
				{
					//�������WX
					fDiffMotion = pKeyNext->fRotX - pKey->fRotX;								// �����̎擾
					rot.x = pKey->fRotX + (fDiffMotion * fRateMotion);
				}

				if (rotPlus.y < rotMinus.y)
				{
					//�������WY
					fDiffMotion = pKeyNext->fRotY + pKey->fRotY;								// �����̎擾
					rot.y = pKey->fRotY + (fDiffMotion * fRateMotion);

				}
				else
				{
					//�������WY
					fDiffMotion = pKeyNext->fRotY - pKey->fRotY;								// �����̎擾
					rot.y = pKey->fRotY + (fDiffMotion * fRateMotion);
				}

				if (rotPlus.z < rotMinus.z)
				{
					//�������WZ
					fDiffMotion = pKeyNext->fRotZ + pKey->fRotZ;								// �����̎擾
					rot.z = pKey->fRotZ + (fDiffMotion * fRateMotion);
				}
				else
				{
					//�������WZ
					fDiffMotion = pKeyNext->fRotZ - pKey->fRotZ;								// �����̎擾
					rot.z = pKey->fRotZ + (fDiffMotion * fRateMotion);
				}
			}
			else
			{
				//�������WX
				fDiffMotion = pKeyNext->fRotX - pKey->fRotX;								// �����̎擾
				rot.x = pKey->fRotX + (fDiffMotion * fRateMotion);

				//�������WY
				fDiffMotion = pKeyNext->fRotY - pKey->fRotY;								// �����̎擾
				rot.y = pKey->fRotY + (fDiffMotion * fRateMotion);

				//�������WZ
				fDiffMotion = pKeyNext->fRotZ - pKey->fRotZ;								// �����̎擾
				rot.z = pKey->fRotZ + (fDiffMotion * fRateMotion);

			}
			//�����̐ݒu����
			m_apModel[nCntModel]->SetRot(rot);
			m_apModel[nCntModel]->SetPos(D3DXVECTOR3(m_offsetPos[nCntModel].x + pos.x, m_offsetPos[nCntModel].y + pos.y, m_offsetPos[nCntModel].z + pos.z));
			//�ʒu�̐ݒu����
			//m_apModel[nCntModel]->SetPos(pos);

		}
	}

	if (m_nKey <= m_apMotionInfo[m_motionType].nNumKey - 1)
	{//���݂̃L�[���Ώۂ̃L�[�̑�����菬�����ꍇ�J�E���g�t���[�������Z
		m_nCountFrame++;
	}
	if (m_nCountFrame >= m_apMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame)
	{//���݂̃t���[�������Ώۂ̃L�[�t���[�����ȏ�̏ꍇ
	 //m_nKey = (m_nKey + (m_apMotionInfo[m_motionType].nNumKey - 1)) % m_apMotionInfo[m_motionType].nNumKey;
	 //���݂̃L�[�̐؂�ւ�
		m_nKey = (m_nKey + 1) % m_apMotionInfo[m_motionType].nNumKey;
		if (m_nKey == m_apMotionInfo[m_motionType].nNumKey - 1 && m_apMotionInfo[m_motionType].bLoop == false)
		{//���݂̃L�[���Ώۂ̃L�[�����ɒB�������[�v���Ȃ��ꍇ
			if (m_motionType == MOTION_JUMP && m_bJump == true)
			{//
				m_nKey = m_apMotionInfo[m_motionType].nNumKey - 1;
			}
			//if (m_motionType == MOTION_PANCH || m_motionType == MOTION_LANDING)
			else if (m_motionType != MOTION_MOVE || m_motionType != MOTION_NEUTRAL)
			{
				//���݂̃L�[��������
				m_nKey = 0;
				//�j���[�g�������[�V�����ɂ���
				m_motionType = MOTION_NEUTRAL;
				//�s�����Ă��Ȃ���Ԃɂ���
				m_bAction = false;
			}
		}
		//�J�E���g�t���[����������
		m_nCountFrame = 0;
	}
}
//=============================================================================
// �G�̍s����Ԃ��擾
//=============================================================================
bool CEnemy::GetAction(void)
{
	return m_bAction;
}

//=============================================================================
// �G�̈ʒu�擾����
//=============================================================================
D3DXVECTOR3 CEnemy::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �G�̌����擾����
//=============================================================================
D3DXVECTOR3 CEnemy::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �G�̈ړ��ʂ̎擾����
//=============================================================================
D3DXVECTOR3 CEnemy::GetMove(void)
{
	return m_move;
}
//=============================================================================
// �G�̍s����Ԃ̐ݒu����
//=============================================================================
void CEnemy::SetAction(bool action)
{
	m_bAction = action;
}

//=============================================================================
// �G�̗͎̑擾����
//=============================================================================
int CEnemy::GetLife(void)
{
	return m_nLife;
}

//=============================================================================
// �G�̌����ݒu����
//=============================================================================
void CEnemy::SetDestAngle(float fDestAngle)
{
	m_fDestAngle = fDestAngle;
}
//=============================================================================
// �G�̏�Ԏ擾����
//=============================================================================
CEnemy::ENEMY_STATE CEnemy::GetEnemyState(void)
{
	return m_state;
}
//=============================================================================
// �G�̏�Ԏ擾����
//=============================================================================
void CEnemy::SetEnemyState(ENEMY_STATE state)
{
	m_state = state;
}

//=============================================================================
// �G�̏�Ԏ擾����
//=============================================================================
void CEnemy::Attack(void)
{
	//�v���C���[�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 PlayerPos,PlayerMove;
	PlayerPos = pPlayer->GetPos();
	PlayerMove = pPlayer->GetMove();

	float fLength = powf((PlayerPos.x - m_pos.x)*(PlayerPos.x - m_pos.x) + (PlayerPos.z - m_pos.z)*(PlayerPos.z - m_pos.z), 0.5f);	//�v���C���[�Ƃ̋���

	float fFind = powf(17.0f, 2.0f);	//���a
	float fAttackFind = powf(5.0f, 2.0f);	//���a

	if (fLength < fAttackFind && pPlayer->GetState() != CPlayer::PLAYER_STATE_DAMAGE)
	{//�Ώۂ̒��_���͈͓���������
		float fAttackAngle = atan2f(PlayerPos.x - m_pos.x,PlayerPos.z - m_pos.z);// ���������p�x���v�Z
		PlayerMove.x = sinf((D3DX_PI *  fAttackAngle)) * 25.0f;
		PlayerMove.z = cosf((D3DX_PI *  fAttackAngle)) * 25.0f;
		pPlayer->HitDamage(2);
		CGame::GetPlayer()->SetMove(PlayerMove);
	}

}

//=============================================================================
// �G�̗͍̑ő�l�擾����
//=============================================================================
int CEnemy::GetMaxLife(void)
{
	return m_nMaxLife;
}

//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void CEnemy::HitDamage(int nDamage)
{
	//�v���C���[�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	if (m_state != EMEMY_STATE_DAMAGE)
	{//�_���[�W���
		m_nLife -= nDamage;//�̗͌��Z����
		m_pBillboardLifeGauge->CutLifeGauge(nDamage);	//�r���{�[�h�̗̓Q�[�W���Z����
		if (m_nLife <= 0)
		{//�̗͂��O�ȉ��̏ꍇ
			OBJTYPE type = GetObjType();	//�I�u�W�F�N�g�̎�ނ��擾
			switch (type)
			{
			case OBJTYPE_BIRD:	//���G�̏ꍇ
				pPlayer->AddDeathBird(1);	//���̎��S���Z����
				//m_nNumBird++;
				break;

			case OBJTYPE_FROG: //������̏ꍇ
				pPlayer->AddDeathFrog(1);	//������̎��S���Z����

				//m_nNumFrog++;
				break;
			}
			Uninit();	//�I������

			//�X�R�A�̎擾����
			CScore *pScore;
			pScore = CGame::GetScore();
			pScore->AddScore(100);	//�X�R�A���Z
		}
		else
		{
			m_state = EMEMY_STATE_DAMAGE;	//�_���[�W��Ԃɂ���
		}
		//�T�E���h�̎擾
		CSound *pSound;
		pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

		//�p�[�e�B�N���̐���
		for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
		{
			float fAngle = (rand() % 628 * 0.01f) - D3DX_PI;
			D3DXVECTOR3 movePar(0.0f, 0.0f, 0.0f);
			movePar.x = sinf(fAngle) * (rand() % 10 * 0.75f);
			movePar.y = (rand() % 10 * 0.75f);
			movePar.z = cosf(fAngle) * (rand() % 10 * 0.75f);
			CDamageParticle::Create(m_pos, movePar, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), rand() % 10 + 10.0f, 25);
		}
	}
}

//=============================================================================
// �G�̑����擾����
//=============================================================================
int CEnemy::GetNumEnemy(void)
{
	return m_nNumEnemy;
}

//=============================================================================
// ���G�̑����擾����
//=============================================================================
int CEnemy::GetNumBird(void)
{
	return m_nNumBird;
}

//=============================================================================
// ������G�̑����擾����
//=============================================================================
int CEnemy::GetNumFrog(void)
{
	return m_nNumFrog;
}
//=============================================================================
// �G�̃��[�V�����ǂݍ���
//=============================================================================
void CEnemy::LoadMotion(char *textName)
{
	//�����_�����O�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();
	int nCntAttack = 0;
	FILE *pFile;	//�t�@�C���̃|�C���^

	pFile = fopen(textName, "r");	//�e�L�X�g�ǂݍ���
	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		char *pStrCur;						//������̐擪�ւ̃|�C���^
		char aLine[256];					//������̓ǂݍ��ݗp
		char aStr[256];						//�����񔲂��o���p
		int nIdx;

		//************************************************************************
		// ���f���̑���&�t�@�C���̓ǂݍ���
		//************************************************************************
		while (1)
		{//���f���t�@�C����ǂݍ��ނ܂ŌJ��Ԃ�
			pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
			strcpy(&aStr[0], pStrCur);				//����������o��

			if (memcmp(&aStr[0], TEXT_NUM_MODEL, strlen(TEXT_NUM_MODEL)) == 0)
			{//�e�L�X�g�����f���̑����������s�̏ꍇ
				pStrCur += strlen(TEXT_NUM_MODEL);	//���o��
				strcpy(&aStr[0], pStrCur);

				m_nNumModel = atoi(&aStr[0]);	//���f���̑����ɑ��

				for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
				{
					while (1)
					{
						pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
						strcpy(&aStr[0], pStrCur);				//����������o��
						if (memcmp(&aStr[0], TEXT_FILENAME_MODEL, strlen(TEXT_FILENAME_MODEL)) == 0)
						{//�e�L�X�g�����f���̖��O�������s�̏ꍇ
							pStrCur += strlen(TEXT_FILENAME_MODEL);					//���o��
							strcpy(&aStr[0], pStrCur);
							int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
							strcpy(&aStr[0], pStrCur);
							aStr[nNum - 1] = '\0';

							strcpy(&m_aFilenameModel[nCntModel][0], aStr);	//���f���̖��O���擾

																			// X�t�@�C���̓ǂݍ���
							D3DXLoadMeshFromX(&m_aFilenameModel[nCntModel][0],
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&m_pBuffMat[nCntModel],
								NULL,
								&m_nNumMat[nCntModel],
								&m_pMesh[nCntModel]);

							break;
						}
					}
				}
				break;		//�����o��
			}
		}

		while (1)
		{//���f���̏���ǂݎ��܂ŌJ��Ԃ�
			pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
			strcpy(&aStr[0], pStrCur);				//����������o��

													//************************************************************************
													// ���f���̏��ǂݍ���
													//************************************************************************
			if (memcmp(&aStr[0], TEXT_CHARASET, strlen(TEXT_CHARASET)) == 0)
			{//�e�L�X�g�����f���ݒu�������s�̏ꍇ
				while (1)
				{
					pStrCur = CLoadFileFunction::ReadLine(pFile, pStrCur);
					strcpy(&aStr[0], pStrCur);				//����������o��
					if (memcmp(&aStr[0], TEXT_NUM_PARTS, strlen(TEXT_NUM_PARTS)) == 0)
					{
						pStrCur += strlen(TEXT_NUM_PARTS);
						pStrCur = CLoadFileFunction::GetLineTop(pStrCur);
						strcpy(&aStr[0], pStrCur);			//����������o��
						m_nNumParts = atoi(&aStr[0]);

						for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
						{
							pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
							strcpy(&aStr[0], pStrCur);				//����������o��

							while (1)
							{
								if (memcmp(&aStr[0], TEXT_PARTSSET, strlen(TEXT_PARTSSET)) == 0)
								{//�p�[�c���̐ݒu�������s�̏ꍇ
									while (1)
									{
										pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
										strcpy(&aStr[0], pStrCur);				//����������o��

										if (memcmp(&aStr[0], TEXT_INDEX, strlen(TEXT_INDEX)) == 0)
										{//�e�L�X�g���C���f�b�N�X�������s�̏ꍇ
											pStrCur += strlen(TEXT_INDEX);
											pStrCur = CLoadFileFunction::GetLineTop(pStrCur);
											strcpy(&aStr[0], pStrCur);			//����������o��
											nIdx = atoi(&aStr[0]);
											m_nIndexParent[nIdx];
										}
										else if (memcmp(&aStr[0], TEXT_PARENT, strlen(TEXT_PARENT)) == 0)
										{//�e�L�X�g���e�q�֌W�������s�̏ꍇ
											pStrCur += strlen(TEXT_PARENT);
											pStrCur = CLoadFileFunction::GetLineTop(pStrCur);
											strcpy(&aStr[0], pStrCur);			//����������o��
											m_nIndexParent[nIdx] = atoi(&aStr[0]);
										}
										else if (memcmp(&aStr[0], TEXT_POS, strlen(TEXT_POS)) == 0)
										{//�e�L�X�g���ʒu�������s�̏ꍇ
											int nWord = 0;
											pStrCur += strlen(TEXT_POS);
											//nWord = PopString(pStrCur, &aStr[0]);
											//pStrCur += nWord;
											strcpy(&aStr[0], pStrCur);			//����������o��
											m_aKeyOffset[nCntParts].fPosX = (float)atof(&aStr[0]);

											nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
											pStrCur += nWord;
											strcpy(&aStr[0], pStrCur);			//����������o��
											m_aKeyOffset[nCntParts].fPosY = (float)atof(&aStr[0]);

											nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
											pStrCur += nWord;
											strcpy(&aStr[0], pStrCur);			//����������o��
											m_aKeyOffset[nCntParts].fPosZ = (float)atof(&aStr[0]);
										}
										else if (memcmp(&aStr[0], TEXT_ROT, strlen(TEXT_ROT)) == 0)
										{//�e�L�X�g���ʒu�������s�̏ꍇ
											int nWord = 0;
											pStrCur += strlen(TEXT_ROT);
											//nWord = PopString(pStrCur, &aStr[0]);
											//pStrCur += nWord;
											strcpy(&aStr[0], pStrCur);			//����������o��
											m_aKeyOffset[nCntParts].fRotX = (float)atof(&aStr[0]);

											nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
											pStrCur += nWord;
											strcpy(&aStr[0], pStrCur);			//����������o��
											m_aKeyOffset[nCntParts].fRotY = (float)atof(&aStr[0]);

											nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);
											pStrCur += nWord;
											strcpy(&aStr[0], pStrCur);			//����������o��
											m_aKeyOffset[nCntParts].fRotZ = (float)atof(&aStr[0]);
										}
										else if (memcmp(&aStr[0], TEXT_END_PARTSSET, strlen(TEXT_END_PARTSSET)) == 0)
										{//�e�L�X�g���p�[�c�̐ݒu�I���������s�̏ꍇ
											if (m_nIndexParent[nCntParts] == -1)
											{
												m_apModel[nIdx] = CModel::Create(D3DXVECTOR3(m_pos.x + m_aKeyOffset[nIdx].fPosX, m_pos.y + m_aKeyOffset[nIdx].fPosY, m_pos.z + m_aKeyOffset[nIdx].fPosZ));
												m_apModel[nIdx]->BindX(m_pMesh[nIdx], m_pBuffMat[nIdx], m_nNumMat[nIdx]);
												m_apModel[nIdx]->SetParent(NULL);
												//m_offsetPos[nIdx] = m_apModel[nIdx]->GetPos();
											}
											else if (m_nIndexParent[nCntParts] > -1)
											{
												m_apModel[nIdx] = CModel::Create(D3DXVECTOR3(m_pos.x + m_aKeyOffset[nIdx].fPosX, m_pos.y + m_aKeyOffset[nIdx].fPosY, m_pos.z + m_aKeyOffset[nIdx].fPosZ));
												m_apModel[nIdx]->BindX(m_pMesh[nIdx], m_pBuffMat[nIdx], m_nNumMat[nIdx]);
												m_apModel[nIdx]->SetParent(m_apModel[m_nIndexParent[nIdx]]);
												//m_offsetPos[nIdx] = m_apModel[nIdx]->GetPos();
											}
											m_offsetPos[nIdx] = m_apModel[nIdx]->GetPos();
											break;
										}
									}
									break;
								}
							}
						}
					}
					else if (memcmp(&aStr[0], TEXT_END_CHARASET, strlen(TEXT_END_CHARASET)) == 0)
					{//�e�L�X�g�����f���̐ݒu�I���������s�̏ꍇ
						break;
					}
				}
				break;
			}
		}

		//************************************************************************
		// ���[�V�����̓ǂݍ���
		//************************************************************************
		for (int nCntMotion = 0; nCntMotion < MAX_ENEMY_MOTION; nCntMotion++)
		{
			pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
			strcpy(&aStr[0], pStrCur);				//����������o��
			if (memcmp(&aStr[0], TEXT_MOTIONSET, strlen(TEXT_MOTIONSET)) == 0)
			{//���[�V�����̐ݒu�������s�̏ꍇ
				while (1)
				{
					pStrCur = CLoadFileFunction::ReadLine(pFile, pStrCur);				//�s�̓ǂݍ���
					strcpy(&aStr[0], pStrCur);						//����������o��
					if (memcmp(&aStr[0], TEXT_LOOP, strlen(TEXT_LOOP)) == 0)
					{//���[�v�������s�̏ꍇ
						pStrCur += strlen(TEXT_LOOP);				//���o��
						pStrCur = CLoadFileFunction::GetLineTop(pStrCur);				//�󔒏���
						int nNum = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������̃J�E���g
						strcpy(&aStr[0], pStrCur);
						aStr[nNum - 1] = '\0';

						if (atoi(&aStr[0]) == 0)
						{//�O���L������Ă����ꍇ���[�v���Ȃ�
							m_apMotionInfo[nCntMotion].bLoop = false;
						}
						else if (atoi(&aStr[0]) == 1)
						{//�P���L������Ă����ꍇ���[�v����
							m_apMotionInfo[nCntMotion].bLoop = true;
						}
					}
					else if (memcmp(&aStr[0], TEXT_COLLISION, strlen(TEXT_COLLISION)) == 0)
					{
						pStrCur += strlen(TEXT_COLLISION);								//���o��
						pStrCur = CLoadFileFunction::GetLineTop(pStrCur);				//�󔒏���
						strcpy(&aStr[0], pStrCur);										//����������o��
						int nWord = 0;

						m_aMotionAttack[nCntMotion].nAttackStartFrame = atoi(&aStr[0]);	//X���W�̑��

						nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);		//�������J�E���g

						pStrCur += nWord;												//�J�E���g���ꂽ�����o��
						strcpy(&aStr[0], pStrCur);										//����������o��
						m_aMotionAttack[nCntMotion].nAttackEndFrame = atoi(&aStr[0]);	//X���W�̑��
					}
					else if (memcmp(&aStr[0], TEXT_NUM_KEY, strlen(TEXT_NUM_KEY)) == 0)
					{//�L�[�̑����������s�̏ꍇ
						pStrCur += strlen(TEXT_NUM_KEY);			//���o��
						pStrCur = CLoadFileFunction::GetLineTop(pStrCur);				//�󔒏���
						strcpy(&aStr[0], pStrCur);					//����������o��

						m_apMotionInfo[nCntMotion].nNumKey = atoi(&aStr[0]);//�L�[�̑�������

						for (int nCntKey = 0; nCntKey < m_apMotionInfo[nCntMotion].nNumKey; nCntKey++)
						{//�L�[�̑������J��Ԃ�
							while (1)
							{
								pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);	//�s�̓ǂݍ���
								strcpy(&aStr[0], pStrCur);				//����������o��
								if (memcmp(&aStr[0], TEXT_KEYSET, strlen(TEXT_KEYSET)) == 0)
								{//�L�[�̐ݒu�J�n�������s�̏ꍇ
									for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
									{
										while (1)
										{
											pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);
											strcpy(&aStr[0], pStrCur);				//����������o��

											if (memcmp(&aStr[0], TEXT_FRAME, strlen(TEXT_FRAME)) == 0)
											{//�t���[�����������s�̏ꍇ
												pStrCur += strlen(TEXT_FRAME);		//���o��
												pStrCur = CLoadFileFunction::GetLineTop(pStrCur);		//�s�̓ǂݍ���
												strcpy(&aStr[0], pStrCur);			//����������o��
												m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = atoi(&aStr[0]);	//�t���[���̑��
												m_aMotionAttack[nCntMotion].nNumFrame += atoi(&aStr[0]);
											}
											else if (memcmp(&aStr[0], TEXT_KEY, strlen(TEXT_KEY)) == 0)
											{//�L�[�̊J�n�������s�̏ꍇ

												while (1)
												{
													pStrCur = CLoadFileFunction::ReadLine(pFile, &aLine[0]);	//�s�̓ǂݍ���
													strcpy(&aStr[0], pStrCur);				//����������o��

													if (memcmp(&aStr[0], TEXT_POS, strlen(TEXT_POS)) == 0)
													{//�ʒu�̏��������s�̏ꍇ
														int nWord = 0;
														pStrCur += strlen(TEXT_POS);	//���o��

														strcpy(&aStr[0], pStrCur);			//����������o��
														m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosX = (float)atof(&aStr[0]);	//X���W�̑��

														nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������J�E���g
														pStrCur += nWord;						//�J�E���g���ꂽ�����o��
														strcpy(&aStr[0], pStrCur);				//����������o��
														m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosY = (float)atof(&aStr[0]);	//Y���W�̑��

														nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������J�E���g
														pStrCur += nWord;						//�J�E���g���ꂽ�����o��
														strcpy(&aStr[0], pStrCur);				//����������o��
														m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosZ = (float)atof(&aStr[0]);	//Z���W�̑��
													}
													else if (memcmp(&aStr[0], TEXT_ROT, strlen(TEXT_ROT)) == 0)
													{//�����̏��������s�̏ꍇ
														int nWord = 0;
														pStrCur += strlen(TEXT_ROT);		//���o��

														strcpy(&aStr[0], pStrCur);			//����������o��
														m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotX = (float)atof(&aStr[0]);	//X���W�̑��

														nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������J�E���g
														pStrCur += nWord;						//�J�E���g���ꂽ�����o��
														strcpy(&aStr[0], pStrCur);				//����������o��
														m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotY = (float)atof(&aStr[0]);	//Y���W�̑��

														nWord = CLoadFileFunction::PopString(pStrCur, &aStr[0]);	//�������J�E���g
														pStrCur += nWord;						//�J�E���g���ꂽ�����o��
														strcpy(&aStr[0], pStrCur);				//����������o��
														m_apMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotZ = (float)atof(&aStr[0]);	//Z���W�̑��
													}
													else if (memcmp(&aStr[0], TEXT_END_KEY, strlen(TEXT_END_KEY)) == 0)
													{//�L�[�̏I���������s�̏ꍇ
														break;
													}
												}
												break;
											}

										}
									}
								}
								else if (memcmp(&aStr[0], TEXT_END_KEYSET, strlen(TEXT_END_KEYSET)) == 0)
								{//�L�[�̐ݒu�I���������s�̏ꍇ
									break;
								}
							}
						}
						nCntAttack++;
					}
					else if (memcmp(&aStr[0], TEXT_END_MOTIONSET, strlen(TEXT_END_MOTIONSET)) == 0)
					{//���[�V�����̐ݒu�I���������s�̏ꍇ
						break;
					}
				}
			}
		}
	}
	fclose(pFile);	//�t�@�C�������
}

//=============================================================================
// ���[�V�����̐ݒu����
//=============================================================================
void CEnemy::SetMotion(MOTION_TYPE type)
{
	m_motionType = type;
}

//=============================================================================
// �̗͂̐ݒu����
//=============================================================================
void CEnemy::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// �̗͂̍ő�l�ݒu����
//=============================================================================
void CEnemy::SetMaxLife(int nMaxLife)
{
	m_nMaxLife = nMaxLife;
}

//=============================================================================
// �ʒu�̐ݒu����
//=============================================================================
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//=============================================================================
// �G�̌����ݒu����
//=============================================================================
void CEnemy::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �G�̈ړ��ʐݒu����
//=============================================================================
void CEnemy::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}


//=============================================================================
//
// ���G�̏���
//
//=============================================================================

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemyBird::CEnemyBird() : CEnemy()
{
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemyBird::~CEnemyBird()
{

}

//=============================================================================
//�G�̐���
//=============================================================================
CEnemyBird *CEnemyBird::Create(D3DXVECTOR3 pos)
{
	CEnemyBird *pEnemyBird = NULL;					//�G�̃|�C���^
	if (pEnemyBird == NULL)
	{
		pEnemyBird = new CEnemyBird;				//�V�[���̓��I�m��
		pEnemyBird->Init();							//����������
		pEnemyBird->SetPos(pos);					//�ʒu�̐ݒu����
		//pEnemyBird->SetLife(20);
		//pEnemyBird->SetMaxLife(20);
	}
	return pEnemyBird;					//�l��Ԃ�
}

//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyBird::Init(void)
{
	CEnemy::Init();	//����������

	//���[�V��������ǂݍ���
	LoadMotion("data\\TEXT\\Enemy\\Bird.txt");

	SetObjType(OBJTYPE_BIRD);	//�I�u�W�F�N�g�̎�ސݒu����
	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemyBird::Uninit(void)
{
	CEnemy::Uninit();	//�G�̏I������
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemyBird::Update(void)
{
	//�v���C���[�̎擾����
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	//�G�̍X�V����
	CEnemy::Update();


	if (pPlayer != NULL)
	{//�v���C���[��NULL�łȂ��ꍇ
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���

		D3DXVECTOR3 PlayerPos, EnemyPos;					//�v���C���[�̈ʒu
		PlayerPos = pPlayer->GetPos();						//�ʒu�̎擾
		EnemyPos = GetPos();								//�G�̈ʒu�擾
		ENEMY_STATE state = GetEnemyState();				//�G�̏�Ԏ擾

		if (state != EMEMY_STATE_DAMAGE)
		{//�_���[�W��Ԃ̏ꍇ
			if (pPlayer != NULL)
			{//�v���C���[��NULL�łȂ��ꍇ
				float fLength = powf((PlayerPos.x - EnemyPos.x)*(PlayerPos.x - EnemyPos.x) + (PlayerPos.z - EnemyPos.z)*(PlayerPos.z - EnemyPos.z), 0.5f);	//�v���C���[�Ƃ̋���
				float fFind = powf(17.0f, 2.0f);			//�����锼�a
				float fAttackFind = powf(5.0f, 2.0f);		//�U�����锼�a

				if (fLength < fFind)
				{//�Ώۂ��͈͓���������
					D3DXVECTOR3 DiffPos;

					//�v���C���[�ƓG�̃x�N�g�����Z�o
					DiffPos = EnemyPos - PlayerPos;
					D3DXVec3Normalize(&DiffPos, &DiffPos);

					//�x�N�g�������Ɍ������Ĉړ�
					move.x -= DiffPos.x * 0.80f;
					move.z -= DiffPos.z * 0.80f;

					//�G�̊p�x�ݒ�
					float fDestAngle = atan2f(EnemyPos.x - PlayerPos.x, EnemyPos.z - PlayerPos.z);
					SetDestAngle(fDestAngle);
					SetMove(move);
					if (fAttackFind > fLength)
					{//�U���͈͂��v���C���[�̋�����菬�����ꍇ
						SetMotion(MOTION_PANCH);	//�U�����[�V�����ɂ���
						Attack();					//�U��
					}
					else
					{//����ȊO�̏ꍇ
						SetMotion(MOTION_MOVE);	//�ړ����[�V�����ɂ���
					}
				}
				else
				{//����ȊO�̏ꍇ
					SetMotion(MOTION_NEUTRAL);	//�j���[�g�������[�V�����ɂ���
					move.x = 0.0f;				//�ړ��ʏ�����
					move.z = 0.0f;
					SetMove(move);				//�ړ��ʐݒu����
				}

			}
		}
		else
		{
			move.x = 0.0f;	//�ړ��ʏ�����
			move.z = 0.0f;
			SetMove(move);	//�ړ��ʐݒu����
		}
	}
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemyBird::Draw(void)
{
	CEnemy::Draw();	//�`�揈��
}

//=============================================================================
//
// ������G�̏���
//
//=============================================================================

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemyFrog::CEnemyFrog() : CEnemy()
{
	m_nCntInterval = 0;	//�Ԋu�J�E���^�[�̏�����
}
//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemyFrog::~CEnemyFrog()
{

}

//=============================================================================
//�G�̐���
//=============================================================================
CEnemyFrog *CEnemyFrog::Create(D3DXVECTOR3 pos)
{
	CEnemyFrog *pEnemyFrog = NULL;					//�G�̃|�C���^
	if (pEnemyFrog == NULL)
	{
		pEnemyFrog = new CEnemyFrog;				//�V�[���̓��I�m��
		pEnemyFrog->Init();							//����������
		pEnemyFrog->SetPos(pos);					//�ʒu�̐ݒu����
	}
	return pEnemyFrog;					//�l��Ԃ�
}

//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemyFrog::Init(void)
{
	CEnemy::Init();	//����������

	//���[�V��������ǂݍ���
	LoadMotion("data\\TEXT\\Enemy\\Frog.txt");


	SetObjType(OBJTYPE_FROG);	//�I�u�W�F�N�g�̎�ސݒu����

	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemyFrog::Uninit(void)
{
	CEnemy::Uninit();	//�I������
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemyFrog::Update(void)
{
	CEnemy::Update();	//�G�̍X�V����

	//�v���C���[�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{//�v���C���[��NULL�łȂ��ꍇ
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVECTOR3 PlayerPos, EnemyPos, EnemyRot;					//�v���C���[�̈ʒu
		PlayerPos = pPlayer->GetPos();								//�ʒu�̎擾
		EnemyPos = GetPos();										//�G�̈ʒu�擾
		EnemyRot = GetRot();										//�G�̌����擾����
		ENEMY_STATE state = GetEnemyState();						//�G�̏�Ԏ擾

		if (state != EMEMY_STATE_DAMAGE)
		{
			if (pPlayer != NULL)
			{//�v���C���[��NULL�łȂ��ꍇ
				float fLength = powf((PlayerPos.x - EnemyPos.x)*(PlayerPos.x - EnemyPos.x) + (PlayerPos.z - EnemyPos.z)*(PlayerPos.z - EnemyPos.z), 0.5f);	//�v���C���[�Ƃ̋���
				float fFind = powf(17.0f, 2.0f);			//�����锼�a
				float fAttackFind = powf(15, 2.0f);			//�U�����锼�a

				if (fLength < fFind)
				{//�Ώۂ��͈͓���������
					D3DXVECTOR3 DiffPos;

					//�G�̊p�x�ݒ�
					float fDestAngle = atan2f(EnemyPos.x - PlayerPos.x, EnemyPos.z - PlayerPos.z);
					SetDestAngle(fDestAngle);	//�p�x�̐ݒu����
					if (fAttackFind > fLength && state != ENEMY_STATE_ATTACK)
					{
						SetMotion(MOTION_PANCH);	//�U�����[�V�����ɂ���
						SetEnemyState(ENEMY_STATE_ATTACK);	//�U����Ԃɂ���
						CBullet::Create(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + 30.0f, EnemyPos.z), 50, D3DXVECTOR3(sinf(EnemyRot.y) * -8.0f, 0.0f, cosf(EnemyRot.y) * -8.0f)); //�e�̐���
					}
				}
			}
		}

		//��Ԃ̐ݒ�
		switch (state)
		{
		case ENEMY_STATE_ATTACK:	//�U����Ԃ̏ꍇ
			m_nCntInterval++;	//�Ԋu�J�E���^�[�����Z
			if (m_nCntInterval >= 100)
			{//�Ԋu�J�E���^�[���P�O�O�ȏ�̏ꍇ
				SetEnemyState(ENEMY_STATE_NOMAL);	//�ʏ��Ԃɂ���
			}
			break;
		case ENEMY_STATE_NOMAL://�ʏ��Ԃ̏ꍇ
			m_nCntInterval = 0;	//�Ԋu�J�E���^�[��������
			break;
		}
	}
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemyFrog::Draw(void)
{
	CEnemy::Draw();	//�G�̕`�揈��
}