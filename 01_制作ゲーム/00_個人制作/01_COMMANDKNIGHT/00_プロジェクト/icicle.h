//=============================================================================
//
// �X���̏��� [icicle.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _ICICLE_H_
#define _ICICLE_H_

#include "main.h"
#include "scene.h"
#include "sceneX.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CIcicle : public CSceneX
{
public:	//�N������A�N�Z�X�\
	typedef enum
	{
		ICICLE_RIGIHT = 0,
		ICICLE_LEFT,
		ICICLE_MAX,
	}ICICLE_TYPE;
	CIcicle();
	~CIcicle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CIcicle *Create(D3DXVECTOR3 pos, ICICLE_TYPE Type);
	static HRESULT Load(void);
	static void Unload(void);

private:	//�����������A�N�Z�X�\
	static LPD3DXMESH			m_pMesh;					//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat;					//�}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat;					//�}�e���A�����̐�
	static LPDIRECT3DTEXTURE9	m_pTexture;				//�e�N�X�`���̃|�C���^
	int m_nCounter;
	ICICLE_TYPE m_type;
};
#endif
