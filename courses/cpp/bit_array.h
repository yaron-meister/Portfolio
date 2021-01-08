/*****************************************************************************
 * File name:   bit_array.h
 * Developer:   HRD7
 * Version: 	1
 * Date:        2019-03-07 10:53:18
 * Description: Bit Array header
 *****************************************************************************/

#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <cstddef>      /* 	   	  size_t          */
#include <iostream>     /* 		  ostream         */
#include <limits>       /* 	numeric_limit, digits */
#include <vector>       /* 		  vector          */
#include <algorithm>	/*		 transform		  */
#include <cassert>		/*		  assert		  */


namespace ilrd
{
	// Kind of Macro
    const size_t BITS = std::numeric_limits <size_t>::digits;

    template <size_t SIZE>
    class BitArray
    {
    private:
        class BitProxy;

    public:
        BitArray() : m_bit_array(num_of_chunks){}

        BitArray& operator&=(const BitArray& other);
        BitArray& operator|=(const BitArray& other);
        BitArray& operator^=(const BitArray& other);
        BitArray& operator<<=(size_t offset);
        bool operator==(const BitArray& other) const;
        
        BitProxy operator[](size_t pos);  
        bool operator[](size_t pos) const; // for const obj.
        
        size_t CountTrueBits() const;
        
        template<size_t T>
        friend std::ostream& operator<<
        					   (std::ostream& os, const BitArray<T>& bit_array);
    
    private:
    	// Members
        static const size_t num_of_chunks = SIZE / (BITS) + !!(SIZE % BITS);
        std::vector<size_t> m_bit_array;
        // Internal functions
        void SetBit(size_t pos, bool val);
        bool GetBit(size_t pos) const;
        // A function that counts the number of bits that are 'ON' in 'chunk'
		size_t SizeTCountTrue(size_t chunk) const; 

        /* Functors */
        class And 
        {
        public:
			And(){}
  			size_t operator()(size_t x, size_t y) const 
  			{ 
				return (x & y);
		    }
		};
		/***********/
		class Or 
        {
        public:
			Or(){}
  			size_t operator()(size_t x, size_t y) const 
  			{ 
				return (x | y);
		    }
		};
		/***********/
		class Xor 
        {
        public:
			Xor(){}
  			size_t operator()(size_t x, size_t y) const 
  			{ 
				return (x ^ y);
		    }
		};
    };// End of class BitArray

    template<size_t SIZE>
    class BitArray<SIZE>::BitProxy
    {
    public:
        BitProxy(BitArray& bit_arr, size_t pos);

        // Invoked when proxy is used to modify the value.
        BitProxy& operator=(bool value); // b1[1] = true;

        // Invoked when proxy is used to read the value.
        operator bool() const; // if (b1[1])...

        BitProxy& operator=(const BitProxy& other); // b1[1] = b2[5]
    private:
        BitArray& m_bit_arr;
        size_t m_pos;
    };


/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/* Class BitArray */
/******************************************************************************/ 
template<size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator&=(const BitArray& other)
{
	// transform(in1.begin, in1.end, in2.begin, out, functor)
	transform(m_bit_array.begin(), m_bit_array.end(), other.m_bit_array.begin(),
			  m_bit_array.begin(), And());

	return (*this);
}

/******************************************************************************/
template<size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator|=(const BitArray& other)
{
	// transform(in1.begin, in1.end, in2.begin, out, functor)
	transform(m_bit_array.begin(), m_bit_array.end(), other.m_bit_array.begin(),
			  m_bit_array.begin(), Or());

	return (*this);
}

/******************************************************************************/
template<size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator^=(const BitArray& other)
{
	// transform(in1.begin, in1.end, in2.begin, out, functor)
	transform(m_bit_array.begin(), m_bit_array.end(), other.m_bit_array.begin(),
			  m_bit_array.begin(), Xor());

	return (*this);
}

/******************************************************************************/
template<size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator<<=(size_t offset)
{
	size_t whole_chunks = offset / BITS;
	size_t remainder 	= offset % BITS;
	size_t i 			= 0;

	// Moving chunks
	if (0 != whole_chunks)
	{
		for (i = num_of_chunks - 1; i >= whole_chunks; --i)
		{
			m_bit_array[i] = m_bit_array[i - whole_chunks];
		}

		for (i = 0; i < whole_chunks; ++i)
		{
			m_bit_array[i] = 0;
		}
	}

	// Moving remainder bits
	if (0 != remainder)
	{
		for (i = num_of_chunks - 1; i > 0; --i)
		{
			m_bit_array[i] <<= remainder;
			m_bit_array[i] |= (m_bit_array[i - 1] >> (BITS - remainder));
		}

		m_bit_array[0] <<= remainder;
	}

	return (*this);
}

/******************************************************************************/
template<size_t SIZE>
bool BitArray<SIZE>::operator==(const BitArray& other) const
{
	return (m_bit_array == other.m_bit_array);
}

/******************************************************************************/
template<size_t SIZE>
typename BitArray<SIZE>::BitProxy BitArray<SIZE>::operator[](size_t pos)
{
	return (BitProxy(*this, pos));
}

/******************************************************************************/
template<size_t SIZE>
bool BitArray<SIZE>::operator[](size_t pos) const
{
	return (GetBit(pos));
}

/******************************************************************************/
template<size_t SIZE>
size_t BitArray<SIZE>::CountTrueBits() const
{
	size_t count = 0;

	for (size_t i = 0; i < num_of_chunks; ++i)
	{
		count += SizeTCountTrue(m_bit_array[i]);
	}

	return (count);
}

/******************************************************************************/
// A function that counts the number of bits that are 'ON' in 'chunk'
template<size_t SIZE>
size_t BitArray<SIZE>::SizeTCountTrue(size_t chunk) const
{
	size_t count = 0;

	while (chunk > 0)
    {
        chunk &= (chunk - 1);
        ++count;
    }
    
    return (count);
}

/******************************************************************************/
template<size_t SIZE>
void BitArray<SIZE>::SetBit(size_t pos, bool val)
{																				
	assert(pos < SIZE);
																					
	size_t mask = (1ul << (pos % BITS));

	if (val)
	{
		// '|' with 0 does nothing
		m_bit_array[pos / BITS] |= mask;
	}
	else
	{
		// '&' with 1 does nothing
		m_bit_array[pos / BITS] &= ~mask;
	}
}

/******************************************************************************/
template<size_t SIZE>
bool BitArray<SIZE>::GetBit(size_t pos) const
{
	size_t mask = (1ul << (pos % BITS));

	return (0 != (m_bit_array[pos / BITS] & mask)); 
}


/* Class BitProxy */
/******************************************************************************/
// Ctor
template<size_t SIZE>
BitArray<SIZE>::BitProxy::BitProxy(BitArray<SIZE>& bit_arr, size_t pos) : 
m_bit_arr(bit_arr), m_pos(pos)
{}

/******************************************************************************/
// operator '='
template<size_t SIZE>
typename BitArray<SIZE>::BitProxy& BitArray<SIZE>::BitProxy::operator=
																	(bool value)
{
	m_bit_arr.SetBit(m_pos, value);

	return (*this);
}

/******************************************************************************/
// operator '()'
template<size_t SIZE>
BitArray<SIZE>::BitProxy::operator bool() const
{
	return (m_bit_arr.GetBit(m_pos));
}

/******************************************************************************/
template<size_t SIZE>
typename BitArray<SIZE>::BitProxy& 
					  BitArray<SIZE>::BitProxy::operator=(const BitProxy& other)
{
	m_bit_arr.SetBit(m_pos, other.m_bit_arr.GetBit(other.m_pos));							

	return (*this);
}

/******************************************************************************/
template<size_t T>
std::ostream& operator<<(std::ostream& os, const BitArray<T>& bit_array)
{
	for (size_t i = 0; i < T; ++i)
	{
		os << bit_array[i] << " ";													
	}

	return (os);
}



}// namespace ilrd;
 
#endif     /* __BIT_ARRAY_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
