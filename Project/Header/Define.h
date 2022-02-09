#pragma once

#define WINCX		800
#define WINCY		600

#define		OBJ_NOEVENT			0
#define		OBJ_DEAD			1

#define		VK_MAX		0xff

#define		TILECX		130
#define		TILECY		68

#define		TILEX		20
#define		TILEY		30

#define		MIN_STR		64
#define		MAX_STR		256

#define		RUBY		0x01
#define		DIAMOND		0x02
#define		SAPPHIRE	0x04


#define			MSG_BOX(_message)			MessageBox(NULL, _message, L"System Message", MB_OK)

#define NO_COPY(CLASSNAME)							\
		private:										\
		CLASSNAME(const CLASSNAME&);					\
		CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)				\
		NO_COPY(CLASSNAME)								\
		private:										\
		static CLASSNAME*	m_pInstance;				\
		public:											\
		static CLASSNAME*	GetInstance( void );		\
		static void DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)				\
		CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
		CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
			if(NULL == m_pInstance) {					\
				m_pInstance = new CLASSNAME;			\
			}											\
			return m_pInstance;							\
		}												\
		void CLASSNAME::DestroyInstance( void ) {		\
			if(NULL != m_pInstance)	{					\
				delete m_pInstance;						\
				m_pInstance = NULL;						\
			}											\
		}


extern		HWND	g_hWnd;