//=============================================================================
//
// �|���S������ [number.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

#define MAX_POLYGON_TEXTURE (2)
#define TEXTURE_NAME011 "data\\TEXTURE\\life.png"
#define TEXTURE_NAME013 "data\\TEXTURE\\stock.png"
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPolygon
{
public:
	//=========================================================================
	// �\���̂̒�`
	//=========================================================================
	typedef enum
	{
		POLYGON_TYPE_NONE = 0,
		POLYGON_TYPE_LIFE,		//�̗�
		POLYGON_TYPE_STOCK,		//�c�@
	} POLYGON_TYPE;
	//�����o�֐�
	CPolygon();
	~CPolygon();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 texture);
	//�ÓI�����o�֐�
	static CPolygon *Create(D3DXVECTOR3 pos, float fWight, float fHeight);

private:
	LPDIRECT3DTEXTURE9					m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3							m_pos;				// �ʒu
	float								m_fWight;
	float								m_fHeight;

protected:
};
#endif