#pragma once

/// <summary>
/// SingletonBase : 게임 내 각종 매니저 클래스의 기반 싱글톤 클래스.
///					싱글톤 패턴을 목적으로 만들어진 클래스.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class SingletonBase
{
protected:
	static T* instance;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetSingleton();
	void ReleaseSingleton();	// 해제
};

// 싱글톤 초기화
template <typename T>
T* SingletonBase<T>::instance = 0;

template <typename T>
T* SingletonBase<T>::GetSingleton()
{
	// 생성되지 않은 경우
	if (!instance)
	{
		instance = new T;
	}

	return instance;
}

template <typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	if (instance)
	{
		delete instance;
		instance = 0;	
	}
}
