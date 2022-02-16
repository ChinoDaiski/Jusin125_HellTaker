#pragma once

#include "Include.h"

class CObj; 
class CObjMgr final 
{
	DECLARE_SINGLETON(CObjMgr)

public:
	enum ID { TERRAIN, MONSTER, WALL, TRAP, EVENT_OBJ, EFFECT, PLAYER, EVIL, UI, END };

private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*			Get_Terrain() { return m_listObject[TERRAIN].front(); }
	CObj*			Get_Player() { return m_listObject[PLAYER].front(); }
	
	bool			Get_Empty(ID eID);

	void			Set_EvilWhite(bool _white);

public:
	void	Add_Object(ID eID, CObj* pObject); 
	void	Delete_ID(ID eID);

	CObj*	Get_IndexObject(int _index);

public:
	void Update(); 
	void Late_Update(); 
	void Render(); 
	void Release(); 

private:
	list<CObj*> m_listObject[END];
};

