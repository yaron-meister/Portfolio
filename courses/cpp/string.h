/*****************************************************************************
 * File name:   string.h
 * Developer:   HRD7
 * Version: 	5
 * Date:        2019-02-24 10:32:31
 * Description: String class header
 *****************************************************************************/

#ifndef __STRING_H__
#define __STRING_H__

#include <cstddef>      /* size_t	 	    */
#include <iostream>     /* ostream, istream */

namespace ilrd
{
    class String;

    std::ostream& operator<<(std::ostream& os, const String& str);
    std::istream& operator>>(std::istream& is, String& str);
    bool operator>(const String& str1, const String& str2);
    bool operator<(const String& str1, const String& str2);
    bool operator==(const String& str1, const String& str2);    
    bool operator!=(const String& str1, const String& str2);
    
    class String
    {
        public:            
            String(const char *u_str = "");         // default (u_str = "")
            String(const String& other);
            ~String();

            String& operator=(const String& str);   // for s1 = s2;

            char& operator[](std::size_t index);    // for (char&) s1[i] = 'a';
            const char& operator[](std::size_t index) const;    // for 'a' == s1[i];
            String& operator+=(const String& str);  // s1+=s2 (strcat() style)
            
            std::size_t Length(void) const;               
            const char* ToString(void) const;       // transfer String to C-string (char *)
        private:
            char *m_str;
            void InitString(const char *str); // initializes m_str
            void Destroy(); // destroys m_str
    };

}
 
#endif     /* __STRING_H__ */

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
