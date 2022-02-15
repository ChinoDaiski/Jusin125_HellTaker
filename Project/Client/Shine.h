#pragma once
#include "Effect.h"

class CShine : public CEffect
{
public:
	CShine();
	virtual ~CShine();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;

public:
	void	Set_Pink(bool _pink) { m_bPink = _pink; }

private:
	void	Move();				// 움직임 관리 함수
	void	PinkMove();			// 핑크 상태일 때 움직임

private:
	bool	m_bPink = false;

	// 난수값 저장
	float	m_fRandom;
	float	m_fDeadCount;
};

