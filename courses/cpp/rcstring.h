/*****************************************************************************
 * File name:   rcstring.h
 * Developer:   HRD7
 * Version: 	3
 * Date:        2019-03-03 23:38:26
 * Description: Reference counter string header
 *****************************************************************************/

#ifndef __RCString_H__
#define __RCString_H__

#include <cstddef>      /* 		size_t	    */
#include <iostream>     /* ostream, istream */

namespace ilrd
{
    class RCString;

    std::ostream& operator<<(std::ostream& os, const RCString& str);
    std::istream& operator>>(std::istream& is, RCString& str);
    bool operator>(const RCString& str1, const RCString& str2);
    bool operator<(const RCString& str1, const RCString& str2);
    bool operator==(const RCString& str1, const RCString& str2);    
    bool operator!=(const RCString& str1, const RCString& str2);

    class RCString
    {
        class CharProxy;

        public:            
            RCString(const char* u_str = "");         // default (u_str = "")
            RCString(const RCString& other); 
            ~RCString();

            RCString& operator=(const RCString& other);    // for s1 = s2 || s1 = 'Hello';

            // May create a new instance of RCString
            CharProxy operator[](size_t index);    // for (char&) s1[i] = 'a';
            char operator[](size_t index) const;    // for 'a' == s1[i];
            
            // May create a new instance of RCString
            RCString& operator+=(const RCString& str);   // s1+=s2 (strcat() style)
            
            std::size_t Length(void) const;               
            const char* ToString(void) const;        // transfer RCString to C-String (char *)
        private:
            class RCData
            {
            public:
                RCData(const char* str, const char* concatenated = "");
                RCData(const RCData& other);
                RCData& operator=(const RCData& str);
                ~RCData();

                const char* GetData(void) const; 
                char GetChar(size_t pos) const;
                void SetChar(size_t pos, char c);

            private:
                struct RCSharedData
                {
                	size_t m_ref_count;
                	char m_str[1];
                };

                RCSharedData* m_data;
                /* An internal function for destroying 'm_data' of RCData */
                void Destroy(void);
            }; 

            class CharProxy
            {
            public:
                CharProxy(RCString* str, size_t pos);

                // Invoked when proxy is used to modify the value.
                CharProxy& operator=(char rhs); // s[1] = 'a';

                // Invoked when proxy is used to read the value.
                operator char () const;

                CharProxy& operator=(const CharProxy& rhs); // for s1[2] = s1[5]
            private:
                RCString& m_str;
                size_t m_pos;
            };
            
            RCData m_data; 
            inline char GetChar(size_t pos) const;
            inline void SetChar(size_t pos, char c);
    };
}

#endif     /* __RCString_H__ */



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
