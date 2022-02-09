#pragma once

#include "Obj.h"
#include "Texture.h"
#include "SceneMgr.h"

class CBackground : public CObj {
public:
	CBackground();
	virtual ~CBackground();

public:
	virtual HRESULT		Initialize(void) override;
	virtual int			Update(void) override;
	virtual void		Late_Update(void) override;
	virtual void		Render(void) override;
	virtual void		Release(void) override;

public:
	void Set_SceneID(CSceneMgr::ID _eID) { m_eID = _eID; }

private:
	CSceneMgr::ID		m_eID;
	float				m_fEnlarge;

};

