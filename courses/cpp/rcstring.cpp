/*****************************************************************************
 * File name:   rcstring.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Alon
 * Date:        2019-03-03 23:38:26
 * Description: Reference counter String implementation
 *****************************************************************************/


#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*     new, delete      */
#include <cstring>		/*	  strlen, strcmp	*/
#include <cstddef>      /* 		 size_t		    */

#include "rcstring.h"   /* Forward declarations */


using namespace ilrd;


/***************************** Global variables *******************************/
const int BUFFER_SIZE = 100;

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/ 
/******************************************************************************/
/* RCString functions */
/******************************************************************************/
RCString::RCString(const char* u_str) : m_data(u_str)
{}

/******************************************************************************/
RCString::RCString(const RCString& other) : m_data(other.m_data)
{}

/******************************************************************************/
RCString::~RCString()
{}

/******************************************************************************/
RCString& RCString::operator=(const RCString& other)
{
	m_data = other.m_data;

	return (*this);
}

/******************************************************************************/
RCString::CharProxy RCString::operator[](size_t index)
{
	// 'char_proxy' is a variable
	RCString::CharProxy char_proxy(this, index);

	return (char_proxy); 
}

/******************************************************************************/
char RCString::operator[](size_t index) const
{
	return (GetChar(index));
}

/******************************************************************************/
RCString& RCString::operator+=(const RCString& str)
{
	RCString::RCData temp(ToString(), str.ToString());

	m_data = temp;

	return (*this);
}

/******************************************************************************/
size_t RCString::Length(void) const
{
	return (strlen(ToString()));
} 

/******************************************************************************/
const char* RCString::ToString(void) const
{
	return (m_data.GetData());
}

/******************************************************************************/
char RCString::GetChar(size_t index) const
{
	return (m_data.GetChar(index));
}

/******************************************************************************/
void RCString::SetChar(size_t index, char c)
{
	m_data.SetChar(index, c);
}


/* CharProxy functions */
/******************************************************************************/
RCString::CharProxy::CharProxy(RCString* str, size_t pos) :
														 m_str(*str), m_pos(pos)
{}

/******************************************************************************/
RCString::CharProxy& RCString::CharProxy::operator=(char rhs)
{
	m_str.SetChar(m_pos, rhs);

	return (*this);
}

/******************************************************************************/
RCString::CharProxy::operator char () const
{
	return (m_str.GetChar(m_pos));
}

/******************************************************************************/
RCString::CharProxy& RCString::CharProxy::operator=
												(const RCString::CharProxy& rhs)
{
	// For s[i] = r[j] case (CharProxy = CharProxy)
	m_str.SetChar(m_pos, rhs.m_str.GetChar(rhs.m_pos));

	return (*this);
}



/* RCData functions */
/******************************************************************************/
RCString::RCData::RCData(const char* str, const char* concatenated)
{
	size_t str_len 	  = strlen(str);
	size_t concat_len = strlen(concatenated);

	// According to 'The many faces...' article
	m_data = static_cast<RCSharedData*>
	(::operator new(sizeof(RCSharedData) + str_len + concat_len + 1));

	// Initialize RCSharedData struct of new RCData
	m_data->m_ref_count = 1;
	strcpy(m_data->m_str, str);
	strcat(m_data->m_str, concatenated);
}

/******************************************************************************/
RCString::RCData::RCData(const RCData& other) : m_data(other.m_data)
{
	++m_data->m_ref_count;
}

/******************************************************************************/
RCString::RCData::~RCData()
{
	--m_data->m_ref_count;

	Destroy();
}

/******************************************************************************/
RCString::RCData& RCString::RCData::operator=(const RCData& str)
{
	if (m_data != str.m_data)
	{
		--m_data->m_ref_count;
		Destroy();
		m_data = str.m_data;
		++m_data->m_ref_count;
	}
	
	return (*this);
}

/******************************************************************************/
const char* RCString::RCData::GetData(void) const
{
	return (m_data->m_str);
}

/******************************************************************************/
char RCString::RCData::GetChar(size_t index) const
{
	return (m_data->m_str[index]);
}

/******************************************************************************/
void RCString::RCData::SetChar(size_t index, char c)
{
	RCData new_m_data(GetData());

	new_m_data.m_data->m_str[index] = c;

	//Depending on '=' operator of RCData
	*this = new_m_data;
}

/******************************************************************************/
/* An internal function for destroying 'm_data' of RCData */
void RCString::RCData::Destroy(void)
{
	if (0 == m_data->m_ref_count)
	{
		::operator delete(m_data);
	}
	
	m_data = 0;
}


/* Free operators */
/******************************************************************************/ 
std::ostream& ilrd::operator<<(std::ostream& os, const RCString& str)
{
	os << str.ToString();

	return (os);
}

/******************************************************************************/
std::istream& ilrd::operator>>(std::istream& is, RCString& str)
{
	char buffer[BUFFER_SIZE] = "";															

	str = buffer;

	do 
	{
		is.clear();
		is.getline(buffer, BUFFER_SIZE);
		str += buffer;
	}
	while (is.eof() != is.rdstate());

	return (is);
}

/******************************************************************************/
bool ilrd::operator>(const RCString& str1, const RCString& str2)
{
	return (strcmp(str1.ToString(), str2.ToString()) > 0);
}

/******************************************************************************/
bool ilrd::operator<(const RCString& str1, const RCString& str2)
{
	return (! (str1 == str2 || str1 > str2));
}

/******************************************************************************/
bool ilrd::operator==(const RCString& str1, const RCString& str2)
{
	return (0 == strcmp(str1.ToString(), str2.ToString()));
}

/******************************************************************************/
bool ilrd::operator!=(const RCString& str1, const RCString& str2)
{
	return (! (str1 == str2));
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
