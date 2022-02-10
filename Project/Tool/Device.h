#pragma once

#include "Include.h"

class CDevice
{
	DECLARE_SINGLETON(CDevice)

private:
	CDevice();
	~CDevice();

public:
	LPDIRECT3DDEVICE9		Get_Device() { return m_pDevice; }
	LPD3DXSPRITE			Get_Sprite(void) { return m_pSprite; }
	LPD3DXFONT				Get_Font(void) { return m_pFont; }
public:
	HRESULT		InitDevice(void);

	void		Render_Begin(void);
	void		Render_End(HWND hWnd = nullptr);

	void		Release(void);

private:
	void		SetParameters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9				m_p3D;			// com 객체 : 이 녀석은 설치된 sdk 버전을 검색하고 그 버전 안에 있는 객체 생성을 담당하는 모체에 해당
	LPDIRECT3DDEVICE9		m_pDevice;		// 그리기와 관련된 각종 기능을 탑재한 객체
	LPD3DXSPRITE			m_pSprite;		// dx 상에서 2d이미지를 출력해주는 com객체
	LPD3DXFONT				m_pFont;
};

