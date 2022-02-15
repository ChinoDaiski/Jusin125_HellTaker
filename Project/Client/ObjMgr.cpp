#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Evil.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release(); 
}

bool CObjMgr::Get_Empty(ID eID)
{
	if (m_listObject[eID].empty())
		return true;

	return false;
}

void CObjMgr::Set_EvilWhite()
{
	for (auto& iter = m_listObject[EVIL].begin(); iter != m_listObject[EVIL].end(); ++iter)
	{
		dynamic_cast<CEvil*>(*iter)->Set_White(true);
	}
}

void CObjMgr::Add_Object(ID eID, CObj * pObject)
{
	if (nullptr == pObject || END <= eID)
		return; 

	m_listObject[eID].emplace_back(pObject); 
}

void CObjMgr::Delete_ID(ID eID)
{
	for (auto& iter : m_listObject[eID])
		Safe_Delete<CObj*>(iter);
	m_listObject[eID].clear();
}

CObj* CObjMgr::Get_IndexObject(int _index)
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& iter = m_listObject[i].begin(); iter != m_listObject[i].end(); ++iter)
		{
			if (_index == (*iter)->Get_ObjIndex())
				return (*iter);
		}
	}

	return nullptr;
}

void CObjMgr::Update()
{
	for (int i = 0 ; i < END; ++i)
	{
		for (auto& iter = m_listObject[i].begin() ; iter != m_listObject[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listObject[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (int i = 0 ; i < END ; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Late_Update();
	}
}

void CObjMgr::Render()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Render();
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			Safe_Delete(pObject); 

		m_listObject[i].clear();
	}
}
