//=============================================================================
//
// �c�@�̏��� [stock.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _STOCK_H_
#define _STOCK_H_

#include "main.h"
#include "scene.h"

#define MAX_STOCK (3)	//����

class CPolygon;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CStock : public CScene
{
public:
	//�����o�֐�
	CStock();
	~CStock();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetStock(int nStock);
	int GetStock(void);
	void SetPos(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	//�ÓI�����o�֐�
	static CStock *Create(D3DXVECTOR3 pos, float fWight, float fHeight);
	void CutStock(int nStock);

private:
	D3DXVECTOR3		m_pos;								// �ʒu
														//�ÓI�����o�ϐ�
	static CPolygon			*m_apPolygon[MAX_STOCK];	// �e�N�X�`���ւ̃|�C���^
	static int				m_nStock;

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
protected:
};
#endif