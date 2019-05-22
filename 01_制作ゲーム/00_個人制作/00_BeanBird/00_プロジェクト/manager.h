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
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CRanking;
class CSound;
class CScore;

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
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetGameScore(int score);
	static int  GetGameScore(int nIdx);
	static int  GetUpdateScore(void);

	//�ÓI�����o�֐�
	static CRenderer		*GetRenderer(void);
	static CInputKeyboard	*GetKeyboard(void);
	static CInputJoypad		*GetJoypad(void);
	static CSound			*GetSound(void);
	static MODE				GetMode(void);
	static void				SetMode(MODE mode);

private:	//�����������A�N�Z�X�\
	//�ÓI�����o�ϐ�
	static CRenderer		*m_pRenderer;
	static CInputKeyboard	*m_pInputKeyboard;
	static CInputJoypad		*m_pInputJoypad;
	static MODE				m_mode;
	static CTitle			*m_pTitle;
	static CTutorial		*m_pTutorial;
	static CGame			*m_pGame;
	static CResult			*m_pResult;
	static CRanking			*m_pRanking;
	static CSound			*m_pSound;
	static CScore			*m_pScore;
	static int				m_aRankingScore[5];
	static int				m_nUpdateSocre;
protected:	//�����Ɣh���N���X�������A�N�Z�X�\
};
#endif