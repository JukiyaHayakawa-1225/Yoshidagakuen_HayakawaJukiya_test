//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "scene.h"

//=============================================================================
//	�ÓI�����o�ϐ��錾
//=============================================================================
int CScene::m_nNumAll = 0;					//�I�u�W�F�N�g�̑���
CScene *CScene::m_apScene[NUM_PRIORITY][MAX_SCENE] = {};	//�I�u�W�F�N�g�̃|�C���^

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nNumAll++;	//���������Z
			m_nID = nCntScene;
			m_nPriority = nPriority;
			break;
		}
	}
	m_objType = OBJTYPE_NONE;
}
//=============================================================================
// �I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̊J������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{//�ő吔���J��Ԃ�
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{//NULL�łȂ��ꍇ
				if (m_apScene[nCntPriority][nCntScene]->GetObjType() != OBJTYPE_FADE)
				{
					//�I������
					m_apScene[nCntPriority][nCntScene]->Uninit();
					delete m_apScene[nCntPriority][nCntScene];			//�f�[�^�̊J��
					m_apScene[nCntPriority][nCntScene] = NULL;			//NULL�ɂ���
				}
			}
		}
	}
	m_nNumAll = 0;		//�G�̑�����������
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{//�ő吔���J��Ԃ�
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{//NULL�łȂ��ꍇ
				//�X�V����
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{//�ő吔���J��Ԃ�
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{//NULL�łȂ��ꍇ
				//�`�揈��
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̔j��
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID;							//�ԍ��̕ۊ�
		nID = m_nID;						//delete���s���Ɣԍ��������Ă��܂�����nID�ɕۊǂ���
		int nPriority;						//�ԍ��̕ۊ�
		nPriority = m_nPriority;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;						//���������炷
	}
}
//=============================================================================
// �ԍ��̎擾
//=============================================================================
CScene *CScene::GetScene(int nPriority,int nIdx)
{
	return m_apScene[nPriority][nIdx];
}


//=============================================================================
// ��ނ̐ݒu
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// ��ނ̎擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}