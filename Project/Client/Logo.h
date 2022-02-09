#pragma once

#include "Scene.h"

class CLogo : public CScene {
public:
	CLogo();
	~CLogo();

public:
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;

public:
	static CLogo*		Create(void);
};

