//=============================================================================
//
// ���̏��� [beans.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _BEAMS_H_
#define _BEAMS_H_

#include "main.h"
#include "scene2D.h"

#define TEXTURE_NAME007 "data\\TEXTURE\\beans_score.png"			//�e�N�X�`����
#define MAX_BEANS_TEXTURE (6)										//���̃e�N�X�`���̍ő吔
#define BEANS_SIZE	(25)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBeans : public CScene2D
{
public:
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		BEANS_TYPE_NONE = 0,
		BEANS_TYPE_SCORE,		//�X�R�A��
		BEANS_TYPE_BULLET,		//�e��
		BEANS_TYPE_SPEED,		//�X�s�[�h��
		BEANS_TYPE_AVATAR,		//���g��
		BEANS_TYPE_BARRIER,		//�o���A��
		BEANS_TYPE_MAX,
	} BEANS_TYPE;
	typedef enum
	{
		BEANS_FLOATING = 0,		//���V���
		BEANS_FALL,				//�������
		BEANS_MAX,
	} BEANS_STATE;

	//�����o�֐�
	CBeans();
	~CBeans();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Collision(void);
	float GetRot(void);
	void HitBeans(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	//�ÓI�����o�֐�
	static CBeans *Create(D3DXVECTOR3 pos, float fWight, float fHeight);

private:
	int				m_nCountBeans;
	BEANS_TYPE		m_beansType;
	BEANS_STATE		m_beansState;
	D3DXVECTOR3		m_move;
	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BEANS_TEXTURE];
};
#endif