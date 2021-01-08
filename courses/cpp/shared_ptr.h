/*****************************************************************************
 * File name:   shared_ptr.h
 * Developer:   HRD7
 * Version:     1
 * Date:        2019-03-10 14:43:34
 * Description: Shared pointer header
 *****************************************************************************/

#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

#include <cstddef>      /* size_t */

namespace ilrd
{
    template<typename T>
    class SharedPtr
    {
    public:
        explicit SharedPtr(T* ptr = 0);

        template<typename Derived>
        friend class SharedPtr;
        
        template<typename Derived>
        SharedPtr(const SharedPtr<Derived>& other);
        template<typename Derived>
        SharedPtr& operator=(const SharedPtr<Derived>& other);

		~SharedPtr();
        SharedPtr(const SharedPtr& other);

        SharedPtr& operator=(const SharedPtr& other);

        T& operator*();              // for *ptr = val
        T* operator->();             // for ptr->x = val

        T* GetPtr() const;

    private:
        size_t* m_ref_count;
        T* m_data;
        void Init(const SharedPtr<T>& other);
        void Destroy();
        
    };


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
template<typename T>
SharedPtr<T>::SharedPtr(T* ptr) : m_ref_count(new size_t(1)), m_data(ptr)
{}

/******************************************************************************/ 
template<typename T>
SharedPtr<T>::~SharedPtr()
{
	Destroy(); 
}

/******************************************************************************/ 
template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) : 
							m_ref_count(other.m_ref_count), m_data(other.m_data)
{
	++(*m_ref_count);
}

/******************************************************************************/
template<typename T>
template<typename Derived>
SharedPtr<T>::SharedPtr(const SharedPtr<Derived>& other) : 
							m_ref_count(other.m_ref_count), m_data(other.m_data)
{
	++(*m_ref_count);
}

/******************************************************************************/
template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	if (m_data != other.m_data)
	{
		Destroy();
		Init(other);
	}

	return (*this);
}

/******************************************************************************/
template<typename T>
template<typename Derived>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<Derived>& other)
{
	if (m_data != other.m_data)
	{
		Destroy();
		Init(other);
	}

	return (*this);
}

/******************************************************************************/
template<typename T>
T& SharedPtr<T>::operator*()
{
	return (*m_data);
}

/******************************************************************************/
template<typename T>
T* SharedPtr<T>::operator->()
{
	return (m_data);
}

/******************************************************************************/
template<typename T>
T* SharedPtr<T>::GetPtr() const
{
	return (m_data);
}

/******************************************************************************/
template<typename T>
void SharedPtr<T>::Init(const SharedPtr<T>& other)
{
	m_ref_count = other.m_ref_count;
	m_data = other.m_data;
	++(*m_ref_count);
}

/******************************************************************************/
template<typename T>
void SharedPtr<T>::Destroy()
{
	--(*m_ref_count);

    if (0 == *m_ref_count)
    {
        delete (m_data);
        delete (m_ref_count);
        
        m_data = 0;
        m_ref_count = 0;
    }
}



} // ilrd.
 

 
#endif     /* __SHARED_PTR_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
