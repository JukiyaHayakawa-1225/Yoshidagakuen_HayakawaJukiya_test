//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"

#define MAX_PLAYER_MODEL (17)
#define MAX_PLAYER_PARTS (17)
#define MAX_MOTION		 (11)
#define MAX_KEY			 (10)
#define MAX_QUANTITY	 (9)
#define MAX_SELECT		 (3)
#define PLAYER_MOVE		 (2.5f)
//�O���錾
class CModel;
class CMeshOrbit;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CScene
{
public:	//�N������A�N�Z�X�\
		//*************************************************************************
		// �\���̒�`
		//*************************************************************************
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PLAYER_MODEL];
	}KEY_INFO;

	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[MAX_KEY];
	}MOTION_INFO;

	typedef struct
	{
		int nNumFrame;
		int nAttackStartFrame;
		int nAttackEndFrame;
	}MOTION_ATTACK;

	typedef enum
	{
		MOTION_NEUTRAL = 0,		//�j���[�g�������[�V����
		MOTION_MOVE,			//�ړ����[�V����
		MOTION_COMBO0,			//�p���`���[�V����
		MOTION_COMBO1,			//�p���`���[�V����
		//MOTION_COMBO2,		//�p���`���[�V����
		MOTION_JUMP,			//�W�����v���[�V����
		MOTION_LANDING,			//���n���[�V����
		MOTION_SKILL0,
		MOTION_SKILL1,
		MOTION_SKILL2,
		MOTION_ITEM,
		MOTION_DEATH,
		MOTION_MAX,
	}MOTION_TYPE;

	typedef enum
	{
		PLAYER_STATE_NOMAL = 0,
		PLAYER_STATE_DAMAGE,
		PLAYER_STATE_DEATH,
		PLAYER_STATE_MAX,
	}PLAYER_STATE;

	typedef enum
	{
		USE_ITEM0 = 0,
		USE_ITEM1,
		USE_ITEM2,
		USE_ITEM_MAX,
	}USE_ITEM;
	//�����o�֐�
	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UpdateMotion(void);
	void LoadMotion(void);
	void SetMotion(MOTION_TYPE type);
	void SetAction(bool action);
	void SetLife(int nLife);
	void SetSkill(int nSkill);
	void SetMaxLife(int nMaxLife);
	void SetState(PLAYER_STATE state);
	void SetMove(D3DXVECTOR3 move);
	void AddSkillLevel(int nSelect, int nValue);
	void AddItemQuantity(int nSelect, int nValue);
	bool GetJump(void);
	bool GetAction(void);
	int	 GetLife(void);
	int  GetSkill(void);
	int GetMaxLife(void);
	int GetMaxSkill(void);
	int GetSkillLevel(int nSelect);
	int GetItemQuantity(int nSelect);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);
	MOTION_TYPE GetMotion(void);
	PLAYER_STATE GetState(void);
	void HitDamage(int nDamage);
	void SetUseItem(USE_ITEM item);
	void UseItem(void);
	int GetCutSkill(int nSkill);
	void AddDeathBird(int nValue);
	void AddDeathFrog(int nValue);
	int GetDeathBird(void);
	int GetDeathFrog(void);
	bool HitAttack(void);

	//�ÓI�����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:	//�����������A�N�Z�X�\
	//�����o�֐�
	void Move(void);
	void Collision(void);
	void SetCountLevel(MOTION_TYPE type);
	void SwitchWeaponSize(void);
	void SwitchIceSize(void);
	void AttackSkill0(void);
	void AttackSkill1(void);
	void AttackSkill2(void);
	//�����o�ϐ�
	D3DXVECTOR3					m_pos;											//�ʒu
	D3DXVECTOR3					m_posOld;										//�ߋ��̈ʒu
	D3DXVECTOR3					m_rot;											//����
	D3DXVECTOR3					m_move;											//�ړ���
	D3DXMATRIX					m_mtxWorld;										//���[���h�}�g���b�N�X
	D3DXVECTOR3					m_VtxMin[MAX_PLAYER_MODEL];						//�ŏ��l
	D3DXVECTOR3					m_VtxMax[MAX_PLAYER_MODEL];						//�ő�l
	D3DXVECTOR3					m_offsetPos[MAX_PLAYER_MODEL];					//�I�t�Z�b�g
	bool						m_bJump;										//�W�����v���Ă��邩�ǂ���
	bool						m_bAction;										//�s�����Ă��邩�ǂ���
	int							m_nNumKey;										//�L�[�̑���
	KEY_INFO					*m_pKeyInfo;									//�L�[���̃|�C���^
	int							m_nKey;											//���݂̃L�[No.
	int							m_nCountFrame;									//�t���[���J�E���^�[
	int							m_nNumParts;									//�p�[�c�̑���
	int							m_nIndexParent[MAX_PLAYER_PARTS];				//�v���C���[�̃p�[�c�ԍ�
	KEY							m_aKeyOffset[MAX_PLAYER_PARTS];					//�v���C���[�̃I�t�Z�b�g
	MOTION_INFO					m_apMotionInfo[MAX_MOTION];						//���[�V�����̏��
	MOTION_TYPE					m_motionType;									//���[�V�����̎��
	D3DXVECTOR3					m_scale;										//�傫��
	int							m_OldMotion;									//�ߋ��̃��[�V����
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;										//���_�o�b�t�@�ւ̃|�C���^
	CModel						*m_apModel[MAX_PLAYER_MODEL];					//���f���̃|�C���^
	int							m_nLife;										//�̗�
	int							m_nMaxLife;										//�̗͂̍ő�l
	int							m_nSkill;										//�Ƃ���
	int							m_nMaxSkill;									//�Ƃ����̍ő�l
	float						m_fSpin;										//��]
	int							m_aSkillLevel[MAX_SELECT];						//�Ƃ����̃��x��
	int							m_aCntLevel[MAX_SELECT];						//�Ƃ����̃��x���J�E���^�[
	int							m_aItemQuantity[MAX_SELECT];					//����̗�
	MOTION_ATTACK				m_aMotionAttack[MAX_MOTION];
	int							m_nCntNumFrame;
	CMeshOrbit					*m_pMeshOrbit;									//���b�V���I�[�r�b�g�̃|�C���^
	PLAYER_STATE				m_state;
	int m_nCounter;
	int m_nCntDamage;
	USE_ITEM					m_useItem;
	int							m_aCutSkill[MAX_SELECT];
	int m_nNumDeathBird;
	int m_nNumDeathFrog;

	//�ÓI�����o�ϐ�
	static LPD3DXMESH			m_pMesh[MAX_PLAYER_MODEL];						//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[MAX_PLAYER_MODEL];					//�}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat[MAX_PLAYER_MODEL];					//�}�e���A�����̐�
};
#endif