#pragma once

#include "Include.h"

class CToolView;
class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	void			Initialize(void);
	void			Update(void);
	void			Render(void);
	void			Mini_Render(void);
	void			Release(void);

public:
	void		SetMainView(CToolView* pMainView) { m_pMainView = pMainView; }

	int			GetTileIndex(const D3DXVECTOR3& vPos);
	//bool		Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool		Picking(const D3DXVECTOR3& vPos, const int& iIndex);

	void		TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID);

private:
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

private:
	vector<TILE*>			m_vecTile;
	CToolView*				m_pMainView = nullptr;

};

