/*****************************************************************************
 * File name:   string.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Alon
 * Date:        2019-02-24 10:32:31
 * Description: String Class implementation
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*      new, delete     */
#include <cassert>		/*		  assert		*/
#include <cstring>		/* 	  strlen, strcpy	*/

#include "string.h"     /* Forward declarations */

using namespace ilrd;
/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
String::String(const char *u_str)
{
	assert(u_str);

	InitString(u_str);	// Allocates memory and copies the string 
}

/******************************************************************************/
String::String(const String& str)
{
	InitString(str.ToString());
}

/******************************************************************************/
String::~String()
{
	Destroy();			// Deleting the object
}

/******************************************************************************/
String& String::operator=(const String& str)
{
	char* temp = new char[str.Length() + 1];
	
	strcpy(temp, str.m_str);
	Destroy();
	m_str = temp;

	return (*this);
}

/******************************************************************************/
char& String::operator[](std::size_t index)
{
	// According to item 3 of Meyers - calling const []
	return (const_cast<char&>(static_cast<const String&>(*this)[index]));
}

/******************************************************************************/
const char& String::operator[](std::size_t index) const
{
	return (const_cast<const char&>(m_str[index])); ///probably doesn't need cast. try it
}

/******************************************************************************/
String& String::operator+=(const String& str)
{
	char* old_m_str = m_str; 
	std::size_t this_length = Length() + 1;
	std::size_t str_length	= str.Length() +1;

	// Allocates memory in size of both of the strings
	char *temp = new char[this_length + str_length];

	// Copy first one
	strcpy(temp, m_str);
	// Concatenates the second one
	strcat(temp, str.m_str);

	m_str = temp;

	delete[] old_m_str; 
	old_m_str = 0;

	return (*this);
}

/******************************************************************************/
std::size_t String::Length(void) const
{
	return (strlen(m_str));
}

/******************************************************************************/
const char* String::ToString(void) const
{
	// Gets char* from String&
	return (m_str);
}

/******************************************************************************/
// Allocates memory and copies the string 
void String::InitString(const char *str)
{
	size_t length = strlen(str) + 1;
	m_str = new char[length];

	strcpy(m_str, str);
}

/******************************************************************************/
// Deleting the object
void String::Destroy()
{
	delete[] m_str;
	m_str = 0;
}

/******************************************************************************/
std::ostream& ilrd::operator<<(std::ostream& os, const String& str)
{
	os << str.ToString();

	return (os);
}

/******************************************************************************/
std::istream& ilrd::operator>>(std::istream& is, String& str)
{
	char buffer[100] = "";															

	str = buffer;

	do 
	{
		is.clear();
		is.getline(buffer, 100);
		str += buffer;
	}
	while (is.eof() != is.rdstate());

	return (is);
}

/******************************************************************************/
bool ilrd::operator>(const String& str1, const String& str2)
{
	// Look at 'man strcmp' at Bash
	return (strcmp(str1.ToString(), str2.ToString()) > 0);
}

/******************************************************************************/
bool ilrd::operator<(const String& str1, const String& str2)
{
	return (strcmp(str1.ToString(), str2.ToString()) < 0);
}

/******************************************************************************/
bool ilrd::operator==(const String& str1, const String& str2)
{
	return (0 == strcmp(str1.ToString(), str2.ToString()));
}

/******************************************************************************/
bool ilrd::operator!=(const String& str1, const String& str2)
{
	return (! (str1 == str2));
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
