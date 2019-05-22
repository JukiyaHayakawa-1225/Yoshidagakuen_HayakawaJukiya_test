//=============================================================================
//
// �v���X�G���^�[�̏��� [pressenter.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _PRESSENTER_H_
#define _PRESSENTER_H_

#include "main.h"
#include "scene2D.h"

#define TEXTURE_NAME014 "data\\TEXTURE\\pressenter.png"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPressEnter : public CScene2D
{
public:
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		PRESSENTERSTATE_NONE = 0,
		PRESSENTERSTATE_PUSH,
		PRESSENTERSTATE_MAX
	}PRESSENTERSTATE;

	//�����o�֐�
	CPressEnter();
	~CPressEnter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	PRESSENTERSTATE GetPressEnter(void);

	//�ÓI�����o�֐�
	static CPressEnter *Create(D3DXVECTOR3 pos, float fWight, float fHeight);
	static HRESULT Load(void);
	static void Unload(void);

private:
	int m_nCounter;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture;
	static PRESSENTERSTATE      m_pressEnterState;                 // ���
};
#endif