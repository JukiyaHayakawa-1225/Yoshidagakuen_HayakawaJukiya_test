//=============================================================================
//
// �r���{�[�h�̏��� [billboard.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBillboard : public CScene
{
public:	//�N������A�N�Z�X�\
	//�����o�֐�
	CBillboard(int nPriority = 5, OBJTYPE objtype = OBJTYPE_BILLBOARD);
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetCol(D3DXCOLOR col);
	void SetWidth(float fWidth);
	void SetHeight(float fHeight);
	void SetLength(float fLength);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
	D3DXCOLOR GetCol(void);
	float GetWidth(void);
	float GetHeight(void);
	float GetLength(void);
	void SetLengthPos(void);
	void CutSide(int nType);
	void SetMove(D3DXVECTOR3 move);
	D3DXVECTOR3 GetMove(void);

	//�ÓI�����o�֐�
	static CBillboard *Create(void);
private:	//�����������A�N�Z�X�\
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXCOLOR	m_col;			//�F
	float		m_fWidth;		//��
	float		m_fHeight;		//����
	float		m_fLength;		//����
	D3DXVECTOR3 m_rot;			//����
	D3DXMATRIX	m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_move;			//�ړ���
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9			m_pTexture = NULL;					// �e�N�X�`���ւ̃|�C���^
};
#endif
