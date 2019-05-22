//=============================================================================
//
// ���b�V���I�[�r�b�g��D���� [meshorbit.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "main.h"
#include "scene.h"

#define MAX_X (50)
#define MAX_Z (1)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeshOrbit : public CScene
{
public:
	//�����o�֐�
	CMeshOrbit(int nPriority = 2, OBJTYPE objtype = OBJTYPE_SCENE3D);
	~CMeshOrbit();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetMtxParent(D3DXMATRIX *pMtx);

	//�ÓI�����o�֐�
	static CMeshOrbit *Create(void);
private:
	//�����o�ϐ�
	int			m_nNumVertex;
	int			m_nNumPolygon;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX	m_mtxWorld;
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9			m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX					*m_pMtxParent;		//�e�̃}�g���b�N�X�ւ̃|�C���^
	D3DXVECTOR3					m_aPosVertex[(MAX_X + 1) * (MAX_Z + 1)];	//�Z�o�������_���W
	D3DXCOLOR					m_aColVertex[(MAX_X + 1) * (MAX_Z + 1)];	//�Z�o�����F���
	D3DXVECTOR2					m_aTexVertexX[(MAX_X + 1) * (MAX_Z + 1)];	//�Z�o�����e�N�X�`�����W
	D3DXVECTOR3					m_aOffset[2];		//���[�̃I�t�Z�b�g
};
#endif
