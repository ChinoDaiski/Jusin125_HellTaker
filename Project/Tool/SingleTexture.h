#pragma once
#include "Texture.h"
class CSingleTexture :
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

public:
	const	TEXINFO*	Get_Texture(const TCHAR* pStateKey = L"", const int& iCount = 0) {return m_pTexInfo;}

public:
	virtual HRESULT InsertTexture(const TCHAR* pFilePath, const TCHAR* pStateKey = L"", const int& iCount = 0) override;
	virtual void Release(void) override;

private:
	TEXINFO*		m_pTexInfo = nullptr;

};

