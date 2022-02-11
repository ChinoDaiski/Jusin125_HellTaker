#pragma once
#include "Obj.h"
#include "Device.h"
#include "TextureMgr.h"

class CEffect : public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

protected:
	wstring			m_wstrStateKey = L"";
};

