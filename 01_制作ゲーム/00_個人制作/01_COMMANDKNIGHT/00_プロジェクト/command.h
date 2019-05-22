//=============================================================================
//
// �R�}���h���� [command.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "main.h"
#include "scene.h"

#define MAX_COMMAND_TYPE     (COMMAND_MAX - 1)		//�R�}���h�̍ő吔
#define MAX_COMMAND_SELECT	 (COMMAND_MAX)			//�R�}���h�̑I���ő吔
#define MAX_COMMAND_TEXTURE	 (3)					//�R�}���h�̃e�N�X�`���ő吔
#define MAX_ENEMY_NAME		 (3)					//�G�̖��O��\���ł��鑍��
#define MAX_COMMANDSKILL_TEXTURE (2)				//�Ƃ����R�}���h�̃e�N�X�`���ő吔
class CScene2D;
class CSkill_Quantity_Number;
class CItem_Quantity_Number;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCommand : public CScene
{
public:
	//*****************************************************************************
	// �\���̂̒�`
	//*****************************************************************************
	typedef enum
	{
		COMMAND_NONE,			// �R�}���h���s���Ă��Ȃ����
		COMMAND_PROCESS,		// �R�}���h���s��
		COMMAND_ATTACK_PROCESS, // �R�}���h�U����
		COMMAND_SKILL,			// �Ƃ����R�}���h���s��
		COMMAND_END,			// �R�}���h���s�I��
		COMMAND_SELECT_MAX
	}COMMAND_STATE;
	typedef enum
	{
		COMMAND_NOCOUNT = 0,
		COMMAND_COUNT,
		COMMAND_COUNT_MAX,
	}COMMAND_COUNT_STATE;
	typedef enum
	{
		COMMAND_MAIN = 0,		//���C��
		COMMAND_ITEM,			//����
		//COMMAND_SKILL,
		COMMAND_MAX,
	}COMMAND_TYPE;

	//�����o�֐�
	CCommand();
	~CCommand();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetCommandState(COMMAND_STATE state);
	void SetCommandType(COMMAND_TYPE type);
	COMMAND_STATE GetCommandState(void);
	COMMAND_TYPE GetCommandType(void);
	bool GetUseSkill(void);
	//�ÓI�����o�֐�
	static CCommand *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//�����o�֐�
	void SwitchCommnad(void);

	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_apTexture[MAX_COMMAND_TEXTURE];				// �e�N�X�`���ւ̃|�C���^
	COMMAND_TYPE				m_commandType;									//
	CScene2D					*m_pCommandSelect;								// �R�}���h�̉�ʎ�ނƉ�ʂ̐�
	CScene2D					*m_apUI_CommandSkill[MAX_COMMANDSKILL_TEXTURE];	// �Ƃ����R�}���h��UI
	int							m_nCommandSelect;								//
	COMMAND_STATE				m_CommandState;									//
	int							m_nCntAttack;									//
	int							m_nCntInterval;									//
	bool						m_bUseSkill;										//�X�L���g�p��Ԃ��ǂ���
	COMMAND_COUNT_STATE			m_CommandCountState;							//
	static CSkill_Quantity_Number		*m_pSkillQuantity;						//
	static CItem_Quantity_Number		*m_pItemQuantity;						//

};
#endif