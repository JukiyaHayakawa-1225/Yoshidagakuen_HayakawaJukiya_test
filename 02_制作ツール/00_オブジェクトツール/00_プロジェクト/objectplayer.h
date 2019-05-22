//=============================================================================
//
// �I�u�W�F�N�g�v���C���[���� [objectplayer.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _OBJECTPLAYER_H_
#define _OBJECTPLAYER_H_

#include "main.h"
#include "scene.h"
#include "object.h"

//�O���錾
class CModel;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObjectPlayer : public CObject
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CObjectPlayer();
	~CObjectPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetSelectObject(void);
	float GetSpeed(void);
	void SetSelectObject(int nSelect);
	void SetSpeed(float fSpeed);

	//�ÓI�����o�֐�
	static CObjectPlayer *Create(D3DXVECTOR3 pos);
	static CObject *GetObjectPointer(void);

private:	//�����������A�N�Z�X�\
	//�����o�֐�
	void Move(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;											//�ʒu
	D3DXVECTOR3 m_rot;											//����
	D3DXVECTOR3 m_move;											//�ړ���
	float		m_fSpeed;										//�ړ��̑���
	D3DXMATRIX	m_mtxWorld;										//���[���h�}�g���b�N�X
	int			m_nNumModel;									//���f������
	D3DXVECTOR3	m_scale;										//�傫��
	static CObject		*m_pObject;								//�I�u�W�F�N�g�̃|�C���^
	CObject		*m_pCreateObject;								//�I�u�W�F�N�g�̐����|�C���^
	int			m_nSeletObject;									//�I�u�W�F�N�g�̑I��

};
#endif