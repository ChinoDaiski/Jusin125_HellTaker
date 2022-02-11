#pragma once
#include "Obj.h"
#include "BackGround.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void		Set_GroundPtr(CObj* pObj) { m_pBackGround = pObj; };

private:
	void		Key_Input(void);				// 방향키 입력
	bool		DontMove(int _index);			// 필드의 끝에 있을 때 움직이지 않음

	void		Create_HitEffect(D3DXVECTOR3 _pos);
	void		Create_MoveEffect(D3DXVECTOR3 _pos);

	void		Moving(void);		// 움직이는 중일 때

private:
	wstring			m_wstrStateKey = L"";
	CObj*			m_pBackGround;
	DIR				m_PreDir;		// 이전 방향

	int				moveCount;		// MoveEffect 카운트 (0~3 반복)
	bool			moving;			// 움직이는 상태면 true
};

