//=============================================================================
//
// ���f���̏��� [model.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModel
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CModel();
	~CModel();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
	void SetMesh(LPD3DXMESH mesh);
	void SetBuffMat(LPD3DXBUFFER buffmat);
	void SetNumMat(DWORD nummat);
	void BindX(LPD3DXMESH mesh, LPD3DXBUFFER buffmat, DWORD nummat);
	void SetParent(CModel *pModel);
	D3DXMATRIX &GetMtxWorld(void);
	void SetSize(D3DXVECTOR3 size);

	//�ÓI�����o�֐�
	static CModel *Create(D3DXVECTOR3 pos);

private:	//�����������A�N�Z�X�\
	//�����o�ϐ�
	LPD3DXMESH			m_pMesh = NULL;				//���b�V�����̃|�C���^
	LPD3DXBUFFER		m_pBuffMat = NULL;			//�}�e���A�����̃|�C���^
	DWORD				m_pNumMat = 0;				//�}�e���A�����̐�
	D3DXVECTOR3         m_pVtxMax;					// ���_���W�̍ő�l�̃|�C���^
	D3DXVECTOR3         m_pVtxMin;					// ���_���W�̍ŏ��l�̃|�C���^
	D3DXMATRIX			m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3			m_pos;						//�ʒu
	D3DXVECTOR3			m_rot;						//����
	int					m_nIdx;						//�C���f�b�N�X�ԍ�
	CModel				*m_pParent;					//�e�q�̃|�C���^
	D3DXVECTOR3			m_size;
};
#endif
