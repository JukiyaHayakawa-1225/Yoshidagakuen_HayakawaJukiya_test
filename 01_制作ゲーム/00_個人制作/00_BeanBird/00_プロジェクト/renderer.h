//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

class CPause;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void); //{ return m_pD3DDevice; } //��s�����̏����̏ꍇ�g�p
	void RelesePause(void);
	static bool GetPause(void);

private:
#ifdef _DEBUG
	void DrawFPS(void);
	void DrawMode(void);
#endif
	static	CPause				*m_pPause;
	static bool m_bPause;
	LPDIRECT3D9					m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9			m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT					m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
};
#endif