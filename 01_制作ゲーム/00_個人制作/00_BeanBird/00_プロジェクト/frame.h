//=============================================================================
//
// �t���[���̏��� [frame.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _FRAME_H_
#define _FRAME_H_

#include "main.h"
#include "scene2D.h"

#define MAX_FRAME (FRAME_MAX)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFrame : public CScene2D
{
public:
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		FRAME_SCORE = 0,
		FRAME_STOCK,
		FRAME_LIFE,
		FRAME_SKILL,
		FRAME_MAX,
	} FRAME_TYPE;

	//�����o�֐�
	CFrame();
	~CFrame();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�ÓI�����o�֐�
	static CFrame *Create(D3DXVECTOR3 pos, float fWight, float fHeight,FRAME_TYPE type);

private:
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_FRAME];
};
#endif