//=============================================================================
//
// �I�u�W�F�N�g2D���� [scene2D.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

#define BG_POS_X			(0)								// �w�i�̍���X���W
#define BG_POS_Y			(0)								// �w�i�̍���Y���W
#define BG_WIDTH			(SCREEN_WIDTH)					// �w�i�̕�
#define BG_HEIGHT			(SCREEN_HEIGHT)					// �w�i�̍���


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene2D : public CScene
{
public:
	//�����o�֐�
	CScene2D(int nPriority = 3);
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void);
	D3DXCOLOR GetCol(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetWidth(float width);
	void SetHeight(float height);
	void SetVtxPos(D3DXVECTOR3 pos);
	void SetVtxLenghtPos(D3DXVECTOR3 pos);
	void SetVtxRotPos(D3DXVECTOR3 pos);
	void SetLength(float fLength);
	float GetWidth(void);
	float GetHeight(void);
	float GetfLength(void);
	void SetCol(D3DXCOLOR col);
	void SetTex(int nAnimPattern, float texU,float texV);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DVERTEXBUFFER9 GetVtx(void);
	//�ÓI�����o�֐�
	static CScene2D *Create(D3DXVECTOR3 pos, float fWight, float fHeight);

private:
	LPDIRECT3DTEXTURE9			m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;				// �ʒu
	D3DXCOLOR					m_col;
	float						m_fWidth;
	float						m_fHeight;
	float						m_fLength;			//�g��
protected:
	//�����o�ϐ�
	float						m_rot;				//����
	float						m_fAddLength;		//���Z��
};
#endif