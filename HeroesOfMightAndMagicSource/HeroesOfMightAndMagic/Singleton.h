//Singleton.h
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template<typename Type>
class Singleton
{
	static Type* s_pInstance;

public:
	static Type* GetInstance()
	{
		if (!s_pInstance)
			s_pInstance = new Type;
		return s_pInstance;
	}

	static void DestroySingleton()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	virtual ~Singleton() { }
};

template <typename Type>
Type* Singleton<Type>::s_pInstance = nullptr;

#endif
