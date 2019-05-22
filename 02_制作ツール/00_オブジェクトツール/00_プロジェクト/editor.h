//=============================================================================
//
// �G�f�B�^�[�̏��� [editor.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "main.h"

//�O���錾
class CMeshField;
class CCommand;
class CMap;
class CObjectPlayer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEditor
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CEditor();
	~CEditor();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CEditor			*Create(void);
	static CMeshField		*GetMeshField(void);
	static CObjectPlayer	*GetObjectPlayer(void);
	static CMap				*GetMap(void);

private:	//�����������A�N�Z�X�\
	//�ÓI�����o�ϐ�
	static CMeshField		*m_pMeshField;		//���b�V���t�B�[���h�̃|�C���^
	static CMap				*m_pMap;			//�}�b�v�̃|�C���^
	static CObjectPlayer	*m_pObjectPlayer;	//�I�u�W�F�N�g�v���C���[�̃|�C���^
};
#endif