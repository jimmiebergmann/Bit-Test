///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2013 Jimmie Bergmann - jimmiebergmann@gmail.com
//
// This software is provided 'as-is', without any express or
// implied warranty. In no event will the authors be held
// liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute
// it freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but
//    is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any
//    source distribution.
// ///////////////////////////////////////////////////////////////////////////

#ifndef BIT_TEST_HPP
#define BIT_TEST_HPP

#include <iostream>
#include <ostream>
#include <string>

// Assert function
#define TestAssert(condition) \
	{ \
		if( !(condition) ) \
		{ \
			std::cerr << "Error(" << m_ErrorCount << "): " << #condition << std::endl; \
			std::cerr << " File: "__FILE__ << " (" << __LINE__ << ")" << std::endl; m_ErrorCount++; m_Succeeded = false; \
		} \
	}

class Test
{

public:

	// Virul functions
	Test( ) : m_Succeeded( true ), m_ErrorCount( 0 ) { }
	virtual ~Test( ) { }
	virtual void Run( std::ostream & p_Trace ) = 0;

	// Get functions
	bool GetStatus( ) const { return m_Succeeded; }

protected:

	bool m_Succeeded;
	unsigned int m_ErrorCount;

};

#endif