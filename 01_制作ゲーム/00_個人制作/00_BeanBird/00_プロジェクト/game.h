//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

class CScore;
class CPlayer;
class CEnemy;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame
{
public:
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		STATE_START = 0,
		STATE_END,
		STATE_MAX,
	}GAME_STATE;
	//�����o�֐�
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Spawn(void);
	void SetEnemyPattern(int pattern);
	//�ÓI�����o�֐�
	static void		SetState(GAME_STATE state);
	static CGame	*Create(void);
	static CScore	*GetScore(void);
	static CPlayer	*GetPlayer(void);
	static CEnemy	*GetEnemy(void);
private:
	int				m_nSpawnCloud;
	int				m_nMainTimer;
	int				m_nSpawnHuman;
	static GAME_STATE		m_state;
	static CScore	*m_pScore;
	static CPlayer	*m_pPlayer;
	static CEnemy	*m_pEnemy;

};
#endif