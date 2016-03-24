#pragma once

#include <assert.h>

class RefCounted{
public:
	RefCounted(){
		m_refCount = 0;
	}
private:
	template <class T> friend class SmartPtr;
	int m_refCount;
};

template <class T>
class SmartPtr{
public:
	SmartPtr(T* ptr = nullptr){
		//m_ptr = nullptr;
		m_ptr = ptr;
		if (m_ptr){
			m_ptr->m_refCount++;
		}
	}

	SmartPtr(const SmartPtr& s){//copy contructor
		m_ptr = s.m_ptr;
		if (m_ptr){
			m_ptr->m_refCount++;
		}
	}

	SmartPtr& operator=(const SmartPtr& s){//assignment operator
		SmartPtr temp(s);
		std::swap(m_ptr, temp.m_ptr);

		return *this;
	}

	~SmartPtr(){
		if (m_ptr){
			m_ptr->m_refCount--;
			assert(m_ptr->m_refCount >= 0);

			if (m_ptr->m_refCount == 0){
				delete m_ptr;
			}
		}
	}

	T* operator->(){
		return m_ptr;
	}

	operator T*()const{
		return m_ptr;
	}

	bool isNull(){
		if (m_ptr == nullptr) return true;
		else return false;
	}

	int getRefCount(){
		return m_ptr->m_refCount;
	}
private:
	T* m_ptr;
};