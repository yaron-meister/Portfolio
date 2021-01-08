/*******************************************************************************
 * File name:   serializer.h
 * Developer:   HRD07	
 * Version:		0 
 * Date:        2019-04-08 13:09:47
 * Description: Serializer header
 ******************************************************************************/
/*
Client interface sample:

class Base
{
public:
    virtual void Serialize(std::ostream& os) const;
};

namespace ilrd
{
template<>
template<>
std::unique_ptr<Base> Serializer<Base>::Creator<Derived>(std::istream& is)
{
    ...
}
} // namespace ilrd

*/

#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <memory>       	/* std::unique_ptr								*/
#include <iostream>    		/* std::istream, std::ostream					*/
#include <string>    		/* std::string									*/

#include "factory.h"    

namespace ilrd
{
	template <typename Base>
	class Serializer final
	{
	public:
		Serializer() = default;

		/* Should allow calling on objects of types that were not registered
		 * with Add<Type>();
		 */
		void Serialize(std::ostream& stream, const Base& obj);

		/* throws BadKey when an unregistered class appears in the stream
		 * throws BadCreate when Creator<Type> fails for some reason
		 */
		std::unique_ptr<Base> Deserialize(std::istream& stream);

		template <typename Derived>
		void Add();

		// Un-copyable
    	Serializer(const Serializer&) = delete;
	    Serializer& operator=(const Serializer&) = delete;

	private:
        // Used by Deserialize
		Factory<Base, std::string, std::istream&> m_factory; 

		template<typename Derived>
		static std::unique_ptr<Base> Creator(std::istream&);
	};


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/
/******************************************************************************/
template <typename Base>
void Serializer<Base>::Serialize(std::ostream& stream, const Base& obj)
{
    obj.Serialize(stream);
}

/******************************************************************************/
template <typename Base>
std::unique_ptr<Base> Serializer<Base>::Deserialize(std::istream& stream)
{
    std::string str;
    std::getline(stream, str);

	try
	{
		return (m_factory.Create(str, stream)); 
	}
	catch(const typename Factory<Base, std::string, std::istream&>::BadKey& e)
	{
		return (nullptr);
	}
	catch(const typename Factory<Base, std::string, std::istream&>::BadCreate& e)
	{
		return (nullptr);
	}
}

/******************************************************************************/
template <typename Base>
template <typename Derived>
void Serializer<Base>::Add()
{
	try
	{
		m_factory.Add(typeid(Derived).name(), Creator<Derived>);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

} // namespace ilrd

#endif     /* __SERIALIZER_H__ */



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
