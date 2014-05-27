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

#include <ObjFileTest.hpp>
#include <Bit/Graphics/ObjFile.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
ObjFileTest::ObjFileTest( ) :
	Test( )
{
}

// Virtual functions
void ObjFileTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Obj File test." << std::endl;

	// Load obj file from file
	Bit::ObjFile obj;
	TestAssert( obj.LoadFromFile( /*"../../Sponza/sponza.obj"*/"input/objModel.obj" ) == true );

	// Save the model file
	TestAssert( obj.SaveToFile( "output/objModel.obj" ) == true );

	// Print the finish text
	std::cout << "Finished Obj File Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}