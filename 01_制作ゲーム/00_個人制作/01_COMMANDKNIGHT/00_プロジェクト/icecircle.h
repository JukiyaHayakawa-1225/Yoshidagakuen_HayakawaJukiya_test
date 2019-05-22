//=============================================================================
//
// �~�̕X���� [icecircle.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _ICECIRCLE_H_
#define _ICECIRCLE_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CIceCircle : public CScene3D
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CIceCircle();
	~CIceCircle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CIceCircle *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:	//�����������A�N�Z�X�\
	int m_nTimer;		//�^�C�}�[
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif
