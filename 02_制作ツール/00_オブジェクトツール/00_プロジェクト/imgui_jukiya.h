//=============================================================================
//
// ImGui�̏��� [imgui_jukiya.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _IMGUI_JUKIYA_H_
#define _IMGUI_JUKIYA_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CImGui_Jukiya
{
public:	//�N������A�N�Z�X�\
		//�����o�֐�
	CImGui_Jukiya();
	~CImGui_Jukiya();
	void Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:	//�����������A�N�Z�X�\
};
#endif
