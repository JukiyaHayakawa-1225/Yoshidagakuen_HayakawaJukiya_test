//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

#define SCORE_DIGIT (6)	//����
#define MAX_SCENE (2000)	//�V�[���̍ő吔
#define NUM_PRIORITY (8)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene
{
public:	//�N������A�N�Z�X�\
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		//�v���C���[
		OBJTYPE_ENEMY,				//�G
		OBJTYPE_HUMAN,				//�l��
		OBJTYPE_BOSS,				//�{�X
		OBJTYPE_BULLET,				//�e
		OBJTYPE_EXPLOTION,			//����
		OBJTYPE_BG,					//�w�i
		OBJTYPE_BEANS,				//��
		OBJTYPE_CLOUD,			//�o���A
		OBJTYPE_FADE,				//�t�F�[�h
		OBJTYPE_BARRIER,			//�o���A
		OBJTYPE_MAX,
	} OBJTYPE;
	//�f�t�H���g�R���X�g���N�^
	//CScene();
	CScene(int nPriority = 3);
	//�������z�֐�
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);

	//�ÓI�����o�֐�
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static CScene *GetScene(int nPriority,int nIdx);

private:	//�����������A�N�Z�X�\
	//�ÓI�����o�ϐ�
	static CScene *m_apScene[NUM_PRIORITY][MAX_SCENE];
	static int m_nNumAll;
	int  m_nID;
	OBJTYPE m_objType;
	int m_nPriority;	//�D�揇�ʂ̔ԍ�
protected:	//�����Ɣh���N���X�������A�N�Z�X�\
	void Release(void);
};
#endif