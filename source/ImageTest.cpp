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

#include <ImageTest.hpp>
#include <Bit/Graphics/Image.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
ImageTest::ImageTest( ) :
	Test( )
{
}

// Virtual functions
void ImageTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Image test." << std::endl;

	// Assert the load image from file function
	Bit::Image image1;
	TestAssert( image1.LoadFromFile( "ImageTest.tga" ) == true );

	// Assert the size
	TestAssert( image1.GetSize( ) == Bit::Vector2u32( 4, 4 ) );

	// Assert the values with GetPixel( index )
	TestAssert( image1.GetPixel( 0 ) == Bit::Pixel( 255, 0, 0, 255 ) );
	TestAssert( image1.GetPixel( 1 ) == Bit::Pixel( 0, 255, 0, 255 ) );
	TestAssert( image1.GetPixel( 2 ) == Bit::Pixel( 0, 0, 255, 255 ) );
	TestAssert( image1.GetPixel( 3 ) == Bit::Pixel( 0, 0, 0, 255 ) );
	for( Bit::SizeType i = 4; i < 12; i++ )
	{
		TestAssert( image1.GetPixel( i ) == Bit::Pixel( 255, 0, 255, 255 ) );
	}
	TestAssert( image1.GetPixel( 12 ) == Bit::Pixel( 255, 255, 255, 255 ) );
	TestAssert( image1.GetPixel( 13 ) == Bit::Pixel( 255, 0, 255, 255 ) );
	TestAssert( image1.GetPixel( 14 ) == Bit::Pixel( 255, 0, 255, 255 ) );
	TestAssert( image1.GetPixel( 15 ) == Bit::Pixel( 0, 0, 0, 255 ) );

	// Assert the values with GetPixel( position )
	TestAssert( image1.GetPixel( Bit::Vector2u32( 0, 0 ) ) == Bit::Pixel( 255, 0, 0, 255 ) );
	TestAssert( image1.GetPixel( Bit::Vector2u32( 1, 0 ) ) == Bit::Pixel( 0, 255, 0, 255 ) );
	TestAssert( image1.GetPixel( Bit::Vector2u32( 2, 0 ) ) == Bit::Pixel( 0, 0, 255, 255 ) );
	TestAssert( image1.GetPixel( Bit::Vector2u32( 3, 0 ) ) == Bit::Pixel( 0, 0, 0, 255 ) );
	for( Bit::SizeType y = 1; y < 3; y++ )
	{
		for( Bit::SizeType x = 0; x < 4; x++ )
		{
			TestAssert( image1.GetPixel( Bit::Vector2u32( x, y ) ) == Bit::Pixel( 255, 0, 255, 255 ) );
		}
	}
	TestAssert( image1.GetPixel( Bit::Vector2u32( 0, 3 ) ) == Bit::Pixel( 255, 255, 255, 255 ) );
	TestAssert( image1.GetPixel( Bit::Vector2u32( 1, 3 ) ) == Bit::Pixel( 255, 0, 255, 255 ) );
	TestAssert( image1.GetPixel( Bit::Vector2u32( 2, 3 ) ) == Bit::Pixel( 255, 0, 255, 255 ) );
	TestAssert( image1.GetPixel( Bit::Vector2u32( 3, 3 ) ) == Bit::Pixel( 0, 0, 0, 255 ) );


	// Assert the load from memory function
	static const Bit::Uint8 imageData[ 9 * 4 ] =
	{
		1, 0, 0, 255,		0, 2, 0, 5,		0, 0, 3, 255,
		0, 5, 6, 5,			0, 66, 25, 0,	0, 2, 0, 255,
		0, 13, 0, 255,		1, 33, 0, 2,	0, 0, 0, 255
	};
	TestAssert( image1.LoadFromMemory( imageData, 4, Bit::Vector2u32( 3, 3 ) ) == true );

	// Assert the size
	TestAssert( image1.GetSize( ) == Bit::Vector2u32( 3, 3 ) );

	// Assert the image data
	TestAssert( image1.GetPixel( 0 ) == Bit::Pixel( 1, 0, 0, 255 ) );
	TestAssert( image1.GetPixel( 1 ) == Bit::Pixel( 0, 2, 0, 5 ) );
	TestAssert( image1.GetPixel( 2 ) == Bit::Pixel( 0, 0, 3, 255 ) );
	TestAssert( image1.GetPixel( 3 ) == Bit::Pixel( 0, 5, 6, 5 ) );
	TestAssert( image1.GetPixel( 4 ) == Bit::Pixel( 0, 66, 25, 0 ) );
	TestAssert( image1.GetPixel( 5 ) == Bit::Pixel( 0, 2, 0, 255 ) );
	TestAssert( image1.GetPixel( 6 ) == Bit::Pixel( 0, 13, 0, 255 ) );
	TestAssert( image1.GetPixel( 7 ) == Bit::Pixel( 1, 33, 0, 2 ) );
	TestAssert( image1.GetPixel( 8 ) == Bit::Pixel( 0, 0, 0, 255 ) );

	// Assert the set pixel function
	image1.SetPixel( 5, Bit::Pixel( 1, 2, 3, 4 ) );
	TestAssert( image1.GetPixel( 5 ) == Bit::Pixel( 1, 2, 3, 4 ) );
	image1.SetPixel( 7, Bit::Pixel( 5, 6, 7, 8 ) );
	TestAssert( image1.GetPixel( 7 ) == Bit::Pixel( 5, 6, 7, 8 ) );
	image1.SetPixel( Bit::Vector2u32( 1, 1 ), Bit::Pixel( 1, 3, 6, 7 ) );
	TestAssert( image1.GetPixel( Bit::Vector2u32( 1, 1 ) ) == Bit::Pixel( 1, 3, 6, 7 ) );

	// Print the finish text
	std::cout << "Finished Image Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}