//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�O���錾
class CMeshField;
class CPlayer;
class CEnemy;
class CCommand;
class CMap;
class CTimer;
class CScore;
class CStatus_Number;
class CUI_LifeGauge;
class CUI_SkillGauge;
class CUI_DamageGauge;
class CBillboardNumber;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CGame			*Create(void);
	static CMeshField		*GetMeshField(void);
	static CPlayer			*GetPlayer(void);
	static CEnemy			*GetEnemy(void);
	static CCommand			*GetCommad(void);
	static CTimer			*GetTimer(void);
	static CScore			*GetScore(void);
	static CStatus_Number	*GetStatusNumber(void);
	static CUI_LifeGauge	*GetUI_LifeGauge(void);
	static CUI_SkillGauge	*GetUI_SkillGauge(void);
	static CUI_DamageGauge	*GetUI_DamageGauge(void);
	static CBillboardNumber *GetBillborad_Number(void);

private:	//�����������A�N�Z�X�\

	int m_nTimer;
	//�ÓI�����o�ϐ�
	static CMeshField		*m_pMeshField;	//���b�V���t�B�[���h�̃|�C���^
	static CPlayer			*m_pPlayer;		//�v���C���[�̃|�C���^
	static CEnemy			*m_pEnemy;		//�G�̃|�C���^
	static CCommand			*m_pCommand;
	static CMap				*m_pMap;		//�}�b�v�̃|�C���^
	static CTimer			*m_pTimer;		//�^�C�}�[�̃|�C���^
	static CScore			*m_pScore;		//�X�R�A�̃|�C���^
	static CStatus_Number	*m_pStatuNumber;//�X�e�[�^�X�����̃|�C���^
	static CUI_LifeGauge	*m_pUI_LifeGauge;
	static CUI_SkillGauge	*m_pUI_SkillGauge;
	static CUI_DamageGauge	*m_pUI_DamageGauge;
	static CBillboardNumber *m_pBillboard_Number;
};
#endif