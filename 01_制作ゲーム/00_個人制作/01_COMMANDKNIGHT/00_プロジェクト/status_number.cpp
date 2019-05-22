//=============================================================================
//
// �X�e�[�^�X�����̏��� [score.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "status_number.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "number.h"
#include "player.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CStatus_Number::m_nStatus_Number = 0;	//�X�e�[�^�X����

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �X�e�[�^�X�����̃R���X�g���N�^
//=============================================================================
CStatus_Number::CStatus_Number() : CScene(6, OBJTYPE_NUMBER)
{
}
//=============================================================================
// �X�e�[�^�X�����̃f�X�g���N�^
//=============================================================================
CStatus_Number::~CStatus_Number()
{

}

//=============================================================================
//�X�e�[�^�X�����̐���
//=============================================================================
CStatus_Number *CStatus_Number::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CStatus_Number *pStatus_Number = NULL;
	if (pStatus_Number == NULL)
	{
		pStatus_Number = new CStatus_Number;		//�V�[���̓��I�m��
		pStatus_Number->m_pos = pos;				//�ʒu�̐ݒu
		pStatus_Number->m_fWidth = fWidth;			//���̐ݒu
		pStatus_Number->m_fHeight = fHeight;		//�����̐ݒu
		pStatus_Number->Init();						//����������
	}
	return pStatus_Number;							//�l��Ԃ�
}

//=============================================================================
// �X�e�[�^�X�����̏���������
//=============================================================================
HRESULT CStatus_Number::Init(void)
{
	int nLife = 0;	//�̗�
	int nSkill = 0;	//�Ƃ���
	int nLifeData = 0;	//�̗͊i�[
	int nSkillData = 0;	//�Ƃ����i�[

	//�v���C���[�̎擾
	CPlayer *pPlayer = CGame::GetPlayer();
	nLife = pPlayer->GetLife();		//�̗͂̎擾
	nSkill = pPlayer->GetSkill();	//�Ƃ����̎擾

	for (int nCntStatus = 0; nCntStatus < MAX_STATUS; nCntStatus++)
	{//�X�e�[�^�X�̐������J��Ԃ�
		for (int nCntNumber = 0; nCntNumber < SCORE_DIGIT; nCntNumber++)
		{//���̐������J��Ԃ�
			m_apNumber[nCntStatus][nCntNumber] = NULL;
		}
	}

	for (int nCntStatus = 0; nCntStatus < MAX_STATUS; nCntStatus++)
	{//�X�e�[�^�X�̐������J��Ԃ�
		int nDigit = 1;
		for (int nCntNumber = 0; nCntNumber < MAX_STATUS_DIGIT; nCntNumber++)
		{//���̐������J��Ԃ�
			if (m_apNumber[nCntStatus][nCntNumber] == NULL)
			{
				//���[�h�̎擾
				CManager::MODE mode = CManager::GetMode();
				if (mode == CManager::MODE_GAME)
				{//�Q�[���̏ꍇ
					switch (nCntStatus)
					{
					case 0:
						//�����̐���
						m_apNumber[0][nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (30 * nCntNumber), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
						nLifeData = nLife % (nDigit * 10) / nDigit;
						m_apNumber[0][nCntNumber]->SetNumber(nLifeData);
						nDigit *= 10;
						break;
					case 1:
						//�����̐���
						m_apNumber[1][nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (30 * nCntNumber), m_pos.y + 50.0f, m_pos.z), m_fWidth, m_fHeight);
						nSkillData = nSkill % (nDigit * 10) / nDigit;
						m_apNumber[1][nCntNumber]->SetNumber(nSkillData);
						nDigit *= 10;
						break;
					}
				}
				m_nStatus_Number = 0;
			}
		}
	}
	return S_OK;
}

//=============================================================================
// �X�e�[�^�X�����̏I������
//=============================================================================
void CStatus_Number::Uninit(void)
{
	//�X�e�[�^�X�����̏I������
	for (int nCntStatus = 0; nCntStatus < MAX_STATUS; nCntStatus++)
	{
		for (int nCntNumber = 0; nCntNumber < SCORE_DIGIT; nCntNumber++)
		{
			if (m_apNumber[nCntStatus][nCntNumber] != NULL)
			{
				//�I������
				m_apNumber[nCntStatus][nCntNumber]->Uninit();
				//�������̊J��
				delete m_apNumber[nCntStatus][nCntNumber];
				//NULL�ɂ���
				m_apNumber[nCntStatus][nCntNumber] = NULL;
			}
		}
	}
	Release();
}

//=============================================================================
// �X�e�[�^�X�����̍X�V����
//=============================================================================
void CStatus_Number::Update(void)
{
	int nLife = 0;	//�̗�
	int nSkill = 0;	//�Ƃ���
	int nLifeData = 0;	//�̗͊i�[
	int nSkillData = 0;	//�Ƃ����i�[

	//�v���C���[�̎擾
	CPlayer *pPlayer = CGame::GetPlayer();
	nLife = pPlayer->GetLife();		//�̗͂̎擾
	nSkill = pPlayer->GetSkill();	//�Ƃ����̎擾


	for (int nCntStatus = 0; nCntStatus < MAX_STATUS; nCntStatus++)
	{
		int nDigit = 1;

		for (int nCntNumber = 0; nCntNumber < MAX_STATUS_DIGIT; nCntNumber++)
		{
				//��ޕʏ���
				switch (nCntStatus)
				{
				case 0:
					nLifeData = nLife % (nDigit * 10) / nDigit;			//�̗͂̌v�Z
					m_apNumber[0][nCntNumber]->SetNumber(nLifeData);	//�����̐ݒu����
					nDigit *= 10;
					break;
				case 1:
					nSkillData = nSkill % (nDigit * 10) / nDigit;		//�Ƃ����̌v�Z
					m_apNumber[1][nCntNumber]->SetNumber(nSkillData);	//�����̐ݒu����
					nDigit *= 10;
					break;
				}
				m_nStatus_Number = 0;
		}
	}
}

//=============================================================================
// �X�e�[�^�X�����̕`�揈��
//=============================================================================
void CStatus_Number::Draw(void)
{
	for (int nCntStatus = 0; nCntStatus < MAX_STATUS; nCntStatus++)
	{
		for (int nCntStatus_Number = 0; nCntStatus_Number < SCORE_DIGIT; nCntStatus_Number++)
		{
			if (m_apNumber[nCntStatus][nCntStatus_Number] != NULL)
			{
				//�����̕`�揈��
				m_apNumber[nCntStatus][nCntStatus_Number]->Draw();
			}
		}
	}
}

//=============================================================================
// �X�e�[�^�X�����̐ݒu����
//=============================================================================
void CStatus_Number::SetStatus_Number(int nStatus_Number)
{
	//�X�e�[�^�X�����̉��Z
	m_nStatus_Number += nStatus_Number;
}

//=============================================================================
// �X�e�[�^�X�����̉��Z
//=============================================================================
void CStatus_Number::AddStatus_Number(int nValue,int nType)
{
	int nAnswer = 1;
	int nStatus_Number;

	m_nStatus_Number = nValue;	//

	for (int nCntNumber = 0; nCntNumber < MAX_STATUS_DIGIT; nCntNumber++)
	{
		nStatus_Number = m_nStatus_Number % (nAnswer * 10) / nAnswer;
		//�����̐ݒu
		m_apNumber[nType][nCntNumber]->SetNumber(nStatus_Number);
		nAnswer *= 10;
	}
}


//=============================================================================
// �X�e�[�^�X�����̎擾
//=============================================================================
int CStatus_Number::GetStatus_Number(void)
{
	//�l��Ԃ�
	return m_nStatus_Number;
}

//=============================================================================
// �X�e�[�^�X�����̎擾
//=============================================================================
void CStatus_Number::SetCol(D3DXCOLOR col)
{
	for (int nCntNumber = 0; nCntNumber < SCORE_DIGIT; nCntNumber++)
	{
		//m_apNumber[nCntNumber]->SetCol(col);
	}
}

//=============================================================================
//
// �Ƃ����ʂ̐�������
//
//=============================================================================
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CSkill_Quantity_Number::m_nNumber = 0;	//����

//=============================================================================
// �X�e�[�^�X�����̃R���X�g���N�^
//=============================================================================
CSkill_Quantity_Number::CSkill_Quantity_Number() : CScene(6, OBJTYPE_NUMBER)
{
}
//=============================================================================
// �X�e�[�^�X�����̃f�X�g���N�^
//=============================================================================
CSkill_Quantity_Number::~CSkill_Quantity_Number()
{

}

//=============================================================================
//�X�e�[�^�X�����̐���
//=============================================================================
CSkill_Quantity_Number *CSkill_Quantity_Number::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CSkill_Quantity_Number *pSkill_Quantity_Number = NULL;
	if (pSkill_Quantity_Number == NULL)
	{
		pSkill_Quantity_Number = new CSkill_Quantity_Number;		//�V�[���̓��I�m��
		pSkill_Quantity_Number->m_pos = pos;						//�ʒu�̐ݒu
		pSkill_Quantity_Number->m_fWidth = fWidth;					//���̐ݒu
		pSkill_Quantity_Number->m_fHeight = fHeight;				//�����̐ݒu
		pSkill_Quantity_Number->Init();								//����������
	}
	return pSkill_Quantity_Number;									//�l��Ԃ�
}

//=============================================================================
// �X�e�[�^�X�����̏���������
//=============================================================================
HRESULT CSkill_Quantity_Number::Init(void)
{
	//�v���C���[�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	for (int nCntSkill_Quantity = 0; nCntSkill_Quantity < MAX_SKILL; nCntSkill_Quantity++)
	{//�Ƃ����̐������J��Ԃ�
		for (int nCntNumber = 0; nCntNumber < MAX_QUANTITY_DIGIT; nCntNumber++)
		{//���̐������J��Ԃ�
			m_apNumber[nCntSkill_Quantity][nCntNumber] = NULL;
		}
	}

	m_apNumber[0][0] = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 - 60.0f , m_pos.z), m_fWidth, m_fHeight);
	m_apNumber[0][1] = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 125.0f, SCREEN_HEIGHT / 2 - 60.0f, m_pos.z), m_fWidth, m_fHeight);
	m_apNumber[1][0] = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 260.0f, SCREEN_HEIGHT / 2 - 170.0f, m_pos.z), m_fWidth, m_fHeight);
	m_apNumber[1][1] = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 235.0f, SCREEN_HEIGHT / 2 - 170.0f, m_pos.z), m_fWidth, m_fHeight);
	m_apNumber[2][0] = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 320.0f, SCREEN_HEIGHT / 2 + 45.0f, m_pos.z), m_fWidth, m_fHeight);
	m_apNumber[2][1] = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 295.0f, SCREEN_HEIGHT / 2 + 45.0f, m_pos.z), m_fWidth, m_fHeight);

	for (int nCntSkill_Quantity = 0; nCntSkill_Quantity < MAX_SKILL; nCntSkill_Quantity++)
	{//�Ƃ����̐������J��Ԃ�
		int nDigit = 1;

		for (int nCntNumber = 0; nCntNumber < MAX_QUANTITY_DIGIT; nCntNumber++)
		{//���̐������J��Ԃ�
			if (m_apNumber[nCntSkill_Quantity][nCntNumber] != NULL)
			{
				//�����̐���
				int nSkillData = pPlayer->GetSkillLevel(nCntSkill_Quantity) % (nDigit * 10) / nDigit;
				m_apNumber[nCntSkill_Quantity][nCntNumber]->SetNumber(nSkillData);
				nDigit *= 10;
				m_nNumber = 0;
			}
		}
	}
	return S_OK;
}

//=============================================================================
// �X�e�[�^�X�����̏I������
//=============================================================================
void CSkill_Quantity_Number::Uninit(void)
{
	//�X�e�[�^�X�����̏I������
	for (int nCntSkill_Quantity = 0; nCntSkill_Quantity < MAX_SKILL; nCntSkill_Quantity++)
	{
		for (int nCntNumber = 0; nCntNumber < MAX_QUANTITY_DIGIT; nCntNumber++)
		{
			if (m_apNumber[nCntSkill_Quantity][nCntNumber] != NULL)
			{
				//�I������
				m_apNumber[nCntSkill_Quantity][nCntNumber]->Uninit();
				//�������̊J��
				delete m_apNumber[nCntSkill_Quantity][nCntNumber];
				//NULL�ɂ���
				m_apNumber[nCntSkill_Quantity][nCntNumber] = NULL;
			}
		}
	}
	Release();
}

//=============================================================================
// �X�e�[�^�X�����̍X�V����
//=============================================================================
void CSkill_Quantity_Number::Update(void)
{

}

//=============================================================================
// �X�e�[�^�X�����̕`�揈��
//=============================================================================
void CSkill_Quantity_Number::Draw(void)
{
	for (int nCntSkill_Quantity = 0; nCntSkill_Quantity < MAX_SKILL; nCntSkill_Quantity++)
	{
		for (int nCntSkill_Quantity_Number = 0; nCntSkill_Quantity_Number < MAX_QUANTITY_DIGIT; nCntSkill_Quantity_Number++)
		{
			if (m_apNumber[nCntSkill_Quantity][nCntSkill_Quantity_Number] != NULL)
			{
				//�����̕`�揈��
				m_apNumber[nCntSkill_Quantity][nCntSkill_Quantity_Number]->Draw();
			}
		}
	}
}

//=============================================================================
//
// �ǂ����ʂ̐�������
//
//=============================================================================
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CItem_Quantity_Number::m_nNumber = 0;		//����

//=============================================================================
// �X�e�[�^�X�����̃R���X�g���N�^
//=============================================================================
CItem_Quantity_Number::CItem_Quantity_Number() : CScene(6, OBJTYPE_NUMBER)
{
}
//=============================================================================
// �X�e�[�^�X�����̃f�X�g���N�^
//=============================================================================
CItem_Quantity_Number::~CItem_Quantity_Number()
{

}

//=============================================================================
//�X�e�[�^�X�����̐���
//=============================================================================
CItem_Quantity_Number *CItem_Quantity_Number::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CItem_Quantity_Number *pItem_Quantity_Number = NULL;
	if (pItem_Quantity_Number == NULL)
	{
		pItem_Quantity_Number = new CItem_Quantity_Number;		//�V�[���̓��I�m��
		pItem_Quantity_Number->m_pos = pos;						//�ʒu�̐ݒu
		pItem_Quantity_Number->m_fWidth = fWidth;				//���̐ݒu
		pItem_Quantity_Number->m_fHeight = fHeight;				//�����̐ݒu
		pItem_Quantity_Number->Init();							//����������
	}
	return pItem_Quantity_Number;								//�l��Ԃ�
}

//=============================================================================
// �X�e�[�^�X�����̏���������
//=============================================================================
HRESULT CItem_Quantity_Number::Init(void)
{
	//�v���C���[�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	for (int nCntItem_Quantity = 0; nCntItem_Quantity < MAX_ITEM; nCntItem_Quantity++)
	{//�ǂ����̐������J��Ԃ�
		for (int nCntNumber = 0; nCntNumber < MAX_QUANTITY_DIGIT; nCntNumber++)
		{//���̐������J��Ԃ�
			m_apNumber[nCntItem_Quantity][nCntNumber] = NULL;
		}
	}

	for (int nCntItem_Quantity = 0; nCntItem_Quantity < MAX_ITEM; nCntItem_Quantity++)
	{//�ǂ����̐������J��Ԃ�
		int nDigit = 1;
		for (int nCntNumber = 0; nCntNumber < MAX_QUANTITY_DIGIT; nCntNumber++)
		{//���̐������J��Ԃ�
			if (m_apNumber[nCntItem_Quantity][nCntNumber] == NULL)
			{
				//�����̐���
				m_apNumber[nCntItem_Quantity][nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (25 * nCntNumber), m_pos.y + (62 * nCntItem_Quantity), m_pos.z), m_fWidth, m_fHeight);
				int nItemData = pPlayer->GetItemQuantity(nCntItem_Quantity) % (nDigit * 10) / nDigit;
				m_apNumber[nCntItem_Quantity][nCntNumber]->SetNumber(nItemData);
				nDigit *= 10;
				m_nNumber = 0;
			}
		}
	}
	return S_OK;
}

//=============================================================================
// �X�e�[�^�X�����̏I������
//=============================================================================
void CItem_Quantity_Number::Uninit(void)
{
	//�X�e�[�^�X�����̏I������
	for (int nCntItem_Quantity = 0; nCntItem_Quantity < MAX_ITEM; nCntItem_Quantity++)
	{
		for (int nCntNumber = 0; nCntNumber < MAX_QUANTITY_DIGIT; nCntNumber++)
		{
			if (m_apNumber[nCntItem_Quantity][nCntNumber] != NULL)
			{
				//�I������
				m_apNumber[nCntItem_Quantity][nCntNumber]->Uninit();
				//�������̊J��
				delete m_apNumber[nCntItem_Quantity][nCntNumber];
				//NULL�ɂ���
				m_apNumber[nCntItem_Quantity][nCntNumber] = NULL;
			}
		}
	}
	Release();
}

//=============================================================================
// �X�e�[�^�X�����̍X�V����
//=============================================================================
void CItem_Quantity_Number::Update(void)
{

}

//=============================================================================
// �X�e�[�^�X�����̕`�揈��
//=============================================================================
void CItem_Quantity_Number::Draw(void)
{
	for (int nCntItem_Quantity = 0; nCntItem_Quantity < MAX_ITEM; nCntItem_Quantity++)
	{
		for (int nCntItem_Quantity_Number = 0; nCntItem_Quantity_Number < MAX_QUANTITY_DIGIT; nCntItem_Quantity_Number++)
		{
			if (m_apNumber[nCntItem_Quantity][nCntItem_Quantity_Number] != NULL)
			{
				//�����̕`�揈��
				m_apNumber[nCntItem_Quantity][nCntItem_Quantity_Number]->Draw();
			}
		}
	}
}