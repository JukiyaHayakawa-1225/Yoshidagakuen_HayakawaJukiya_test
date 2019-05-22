//=============================================================================
//
// �w�i�̏��� [bg.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"
#include "result.h"

#define MAX_BG (3)											//�w�i�̍ő吔

#define TEXTURE_NAME003 "data\\TEXTURE\\BG000.png"			//�e�N�X�`����
#define TEXTURE_NAME004 "data\\TEXTURE\\bg101.png"			//�e�N�X�`����
#define TEXTURE_NAME005 "data\\TEXTURE\\bg102.png"			//�e�N�X�`����

class CScene2D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBg : public CScene
{
public:
	//�����o�֐�
	CBg(int nPriority = 1);
	~CBg();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	void SetPos(D3DXVECTOR3 pos);
	void SetVtxPos(D3DXVECTOR3 pos);
	void SetTexMove(int move);
	void SetCol(D3DXCOLOR col);
	void SetWidth(float fWidth);
	void SetHeight(float fHeight);
	D3DXVECTOR3 GetPos(void);
private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu
	int m_move;			//�ړ���
	D3DXCOLOR	m_col;	//�F
	float		m_fWidth;
	float		m_fHeight;
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

//*****************************************************************************
// �^�C�g���w�i
//*****************************************************************************
class CBgTitle : public CBg
{
public:
	//�����o�֐�
	CBgTitle();
	~CBgTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CBgTitle *Create(D3DXVECTOR3 pos, float fWight, float fHeight);
	static HRESULT Load(void);
	static void Unload(void);
private:
	//�����o�ϐ�
	D3DXVECTOR3 m_move;	//�ړ���
	int m_nMoveSpeed;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
//*****************************************************************************
// �`���[�g���A���w�i
//*****************************************************************************
class CBgTutorial : public CBg
{
public:
	typedef enum
	{
		BG_0 = 0,
		BG_1,
		BG_MAX,
	}BG_TYPE;
	typedef enum
	{
		STATE_NOMAL = 0,
		STATE_MOVE,
		STATE_REMOVE,
		STATE_MAX,
	}TUTORIAL_STATE;
	//�����o�֐�
	CBgTutorial();
	~CBgTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static void SetTutorialState(TUTORIAL_STATE state);
	static TUTORIAL_STATE GetTutorialState(void);
	static CBgTutorial *Create(D3DXVECTOR3 pos, float fWight, float fHeight,BG_TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
private:
	int						  m_moveTimer;
	CScene2D *m_apScene2D[2];
	//�ÓI�����o�ϐ�
	static TUTORIAL_STATE	  m_state;
	static LPDIRECT3DTEXTURE9 m_apTexture[2];
};

//*****************************************************************************
// �Q�[���w�i
//*****************************************************************************
class CBgGame : public CBg
{
public:
	//�����o�֐�
	CBgGame();
	~CBgGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CBgGame *Create(D3DXVECTOR3 pos, float fWight, float fHeight);
	static HRESULT Load(void);
	static void Unload(void);
private:
	//�����o�ϐ�
	D3DXVECTOR3 m_move;	//�ړ���
	int m_nMoveSpeed;
	CScene2D *m_pScene2D;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
//*****************************************************************************
// ���U���g�w�i
//*****************************************************************************
class CBgResult : public CBg
{
public:
	//�����o�֐�
	CBgResult();
	~CBgResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CBgResult *Create(D3DXVECTOR3 pos, float fWight, float fHeight,CResult::RESULT result);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_RESULT];
};

//*****************************************************************************
// �����L���O�w�i
//*****************************************************************************
class CBgRanking : public CBg
{
public:
	//�����o�֐�
	CBgRanking();
	~CBgRanking();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CBgRanking *Create(D3DXVECTOR3 pos , float fWight, float fHeight);
	static HRESULT Load(void);
	static void Unload(void);
private:
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

//*****************************************************************************
// UI�w�i
//*****************************************************************************
class CBgUI : public CBg
{
public:
	//�����o�֐�
	CBgUI();
	~CBgUI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CBgUI *Create(D3DXVECTOR3 pos, float fWight, float fHeight);
	static HRESULT Load(void);
	static void Unload(void);
private:
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif