//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene.h"

#define MAX_ENEMY_MODEL (16)	//�G���f���̑���
#define MAX_ENEMY_PARTS (16)	//�G�p�[�c�̑���
#define MAX_ENEMY_MOTION (10)	//�G���[�V�����̑���
#define MAX_KEY			 (10)	//�L�[�̑���
#define MAX_ENEMY_LIFE	(10)	//�G�̗̑�

//�O���錾
class CModel;
class CBillboardNumber;
class CBillboardLifeGauge;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy : public CScene
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
		KEY aKey[MAX_ENEMY_MODEL];
	}KEY_INFO;

	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[MAX_KEY];
	}MOTION_INFO;

	typedef enum
	{
		MOTION_NEUTRAL = 0,		//�j���[�g�������[�V����
		MOTION_MOVE,			//�ړ����[�V����
		MOTION_PANCH,			//�p���`���[�V����
		MOTION_JUMP,			//�W�����v���[�V����
		MOTION_LANDING,			//���n���[�V����
		MOTION_MAX,
	}MOTION_TYPE;

	typedef enum
	{
		ENEMY_STATE_NOMAL = 0,
		ENEMY_STATE_ATTACK,
		EMEMY_STATE_DAMAGE,
		ENEMY_STATE_MAX,
	}ENEMY_STATE;

	typedef struct
	{
		int nNumFrame;
		int nAttackStartFrame;
		int nAttackEndFrame;
	}MOTION_ATTACK;

	//�����o�֐�
	CEnemy();
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UpdateMotion(void);
	void LoadMotion(char *textName);
	void SetLife(int nLife);
	void SetMaxLife(int nMaxLife);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetMove(D3DXVECTOR3 move);
	void SetMotion(MOTION_TYPE type);
	void SetAction(bool action);
	bool GetAction(void);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetMove(void);
	void HitDamage(int damage);
	int GetMaxLife(void);
	int GetLife(void);
	void SetDestAngle(float fDestAngle);
	ENEMY_STATE GetEnemyState(void);
	void SetEnemyState(ENEMY_STATE state);
	void Attack(void);

	//�ÓI�����o�֐�
	static CEnemy *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	static int GetNumEnemy(void);
	int GetNumBird(void);
	int GetNumFrog(void);

private:	//�����������A�N�Z�X�\
	//�����o�ϐ�
	static int			m_nNumEnemy;							//�G�̑���
	int			m_nLife;										//�̗�
	int			m_nMaxLife;										//�̗͍ő�l
	D3DXVECTOR3 m_pos;											//�ʒu
	D3DXVECTOR3 m_posOld;										//�ߋ��̈ʒu
	D3DXVECTOR3 m_rot;											//����
	D3DXVECTOR3	m_move;											//�ړ���
	D3DXMATRIX	m_mtxWorld;										//���[���h�}�g���b�N�X
	D3DXVECTOR3	m_VtxMin[MAX_ENEMY_MODEL];						//�ŏ��l
	D3DXVECTOR3	m_VtxMax[MAX_ENEMY_MODEL];						//�ő�l
	D3DXVECTOR3	m_offsetPos[MAX_ENEMY_MODEL];					//�I�t�Z�b�g
	MOTION_ATTACK	m_aMotionAttack[MAX_ENEMY_MOTION];			//���[�V�����̍U�����
	bool		m_bJump;										//�W�����v���Ă��邩�ǂ���
	bool		m_bAction;										//�s�����Ă��邩�ǂ���
	int			m_nNumKey;										//�L�[�̑���
	KEY_INFO	*m_pKeyInfo;									//�L�[���̃|�C���^
	int			m_nKey;											//���݂̃L�[No.
	int			m_nCountFrame;									//�t���[���J�E���^�[
	int			m_nNumParts;									//�p�[�c�̑���
	int			m_nIndexParent[MAX_ENEMY_PARTS];				//�v���C���[�̃p�[�c�ԍ�
	KEY			m_aKeyOffset[MAX_ENEMY_PARTS];					//�v���C���[�̃I�t�Z�b�g
	MOTION_INFO	m_apMotionInfo[MAX_KEY];						//���[�V�����̏��
	MOTION_TYPE	m_motionType;									//���[�V�����̎��
	D3DXVECTOR3	 m_scale;										//�傫��
	int m_OldMotion;											//�ߋ��̃��[�V����
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	CModel						*m_apModel[MAX_ENEMY_MODEL];	//���f���̃|�C���^
	static char	m_aFilenameModel[MAX_ENEMY_MODEL][256];			//���f���t�@�C��
	int			m_nNumModel;									//���f���̑���
	CBillboardNumber		*m_apNumber[2];						// �|�C���^
	ENEMY_STATE				m_state;
	float					m_fDestAngle;
	int	m_nCntDamage;
	int m_nCounter;
	int	m_nCntNumFrame;
	int m_nCounterAttack;
	bool m_bAttack;
	//�ÓI�����o�ϐ�
	static LPD3DXMESH			m_pMesh[MAX_ENEMY_MODEL];		//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[MAX_ENEMY_MODEL];	//�}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat[MAX_ENEMY_MODEL];	//�}�e���A�����̐�
	CBillboardLifeGauge			*m_pBillboardLifeGauge;
protected:	//�����Ɣh���N���X�̂�
	int m_nNumBird;
	int m_nNumFrog;
};


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyBird : public CEnemy
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CEnemyBird();
	~CEnemyBird();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�ϐ�
	static CEnemyBird *Create(D3DXVECTOR3 pos);


private:	//�����������A�N�Z�X�\
			//�����o�ϐ�

};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyFrog : public CEnemy
{
public:	//�N������A�N�Z�X�\
		//�����o�֐�
	CEnemyFrog();
	~CEnemyFrog();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�ϐ�
	static CEnemyFrog *Create(D3DXVECTOR3 pos);


private:	//�����������A�N�Z�X�\
			//�����o�ϐ�
	int m_nCntInterval;
};

#endif