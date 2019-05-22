//=============================================================================
//
// �}�l�[�W������ [manager.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//�O���錾
class CInputKeyboard;
class CInputJoypad;
class CSound;
class CCamera;
class CLight;
class CDebugProc;
class CTitle;
class CTutorial;
class CEditor;
class CResult;
class CRanking;
class CFade;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{
public:	//�N������A�N�Z�X�\
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,		//�^�C�g��
		MODE_TUTORIAL,	//�`���[�g���A��
		MODE_GAME,		//�Q�[��
		MODE_RESULT,	//���U���g
		MODE_RANKING,	//�����L���O
		MODE_MAX,
	}MODE;

	//�����o�֐�
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CRenderer		*GetRenderer(void);
	static CInputKeyboard	*GetKeyboard(void);
	static CInputJoypad		*GetJoypad(void);
	static CSound			*GetSound(void);
	static CCamera			*GetCamera(void);
	static CLight			*GetLight(void);
	static MODE				GetMode(void);
	static void				SetMode(MODE mode);
	static CFade			*GetFade(void);

private:	//�����������A�N�Z�X�\
	//�ÓI�����o�ϐ�
	static CRenderer		*m_pRenderer;		//�����_�����O�̃|�C���^
	static CInputKeyboard	*m_pInputKeyboard;	//�L�[�{�[�g�̃|�C���^
	static CInputJoypad		*m_pInputJoypad;	//�W���C�p�b�h�̃|�C���^
	static CSound			*m_pSound;			//�T�E���h�̃|�C���^
	static CCamera			*m_pCamera;			//�J�����̃|�C���^
	static CLight			*m_pLight;			//���C�g�̃|�C���^
	static CDebugProc		*m_pDebugproc;		//�f�o�b�O�̃|�C���^
	static MODE				m_mode;				//���[�h�̏��
	static CTitle			*m_pTitle;			//�^�C�g���̃|�C���^
	static CTutorial		*m_pTutorial;		//�`���[�g���A���̃|�C���^
	static CEditor			*m_pEditor;			//�Q�[���̃|�C���^
	static CResult			*m_pResult;			//���U���g�̃|�C���^
	static CRanking			*m_pRanking;		//�����L���O�̃|�C���^
	static CFade			*m_pFade;			//�t�F�[�h�̃|�C���^

protected:	//�����Ɣh���N���X�������A�N�Z�X�\
};
#endif