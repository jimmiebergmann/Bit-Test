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

#include <AnimationTest.hpp>
#include <Bit/System/MemoryLeak.hpp>
#include <Bit/Graphics/Model/Skeleton.hpp>
#include <Bit/Graphics/Model/VertexAnimation.hpp>
#include <Bit/Graphics/Model/VertexAnimationTrack.hpp>
#include <Bit/Graphics/Model/VertexKeyFrame.hpp>

// Constructor
AnimationTest::AnimationTest( ) :
	Test( )
{
}

// Virtual functions
void AnimationTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting Animation test." << std::endl;

	// Create a skeleton
	Bit::Skeleton skeleton;
	TestAssert( skeleton.GetAnimationCount( ) == 0 );
	TestAssert( skeleton.GetAnimation( 0 ) == NULL );
	TestAssert( skeleton.GetAnimation( 1 ) == NULL );

	// Create a vertex animation
	Bit::Animation * pAnimation1 = skeleton.CreateVertexAnimation( );
	TestAssert( skeleton.GetAnimationCount( ) == 1 );
	TestAssert( pAnimation1 != NULL );
	if( pAnimation1 != NULL )
	{
		// Assert the animation
		TestAssert( pAnimation1->GetType( ) == Bit::Animation::PerVertex );
		TestAssert( pAnimation1->GetTrackCount( ) == 0 );
		TestAssert( pAnimation1->GetTrack( 0 ) == NULL );
		TestAssert( pAnimation1->GetTrack( 1 ) == NULL );

		// Create an animation track
		Bit::AnimationTrack * pTrack1 = pAnimation1->CreateTrack( );
		TestAssert( pAnimation1->GetTrackCount( ) == 1 );
		TestAssert( pTrack1 != NULL );
		if( pTrack1 != NULL )
		{
			// Assert the animation track
			TestAssert( pTrack1->GetKeyFrameCount( ) == 0 );
			TestAssert( pTrack1->GetKeyFrame( 0 ) == NULL );
			TestAssert( pTrack1->GetKeyFrame( 1 ) == NULL );

			// Create a key frame
			Bit::KeyFrame * pKeyFrame1 = pTrack1->CreateKeyFrame( Bit::Microseconds( 100 ) );
			TestAssert( pKeyFrame1 != NULL );
			if( pKeyFrame1 != NULL )
			{
				// Assert the newly created key frame
				TestAssert( pTrack1->GetKeyFrameCount( ) == 1 );
				TestAssert( pTrack1->GetKeyFrame( 0 ) == pKeyFrame1 );

				// Delete the key frame
				pTrack1->DeleteKeyFrame( static_cast<Bit::SizeType>( 0 ) );
				TestAssert( pTrack1->GetKeyFrameCount( ) == 0 );

				// Recreate it.
				pKeyFrame1 = pTrack1->CreateKeyFrame( Bit::Microseconds( 100 ) );
				TestAssert( pTrack1->GetKeyFrameCount( ) == 1 );
				TestAssert( pKeyFrame1->GetTime( ).AsMicroseconds( ) == 100 );

				// Add key frame
				Bit::KeyFrame * pKeyFrame2 = pTrack1->CreateKeyFrame( Bit::Microseconds( 20 ) );
				TestAssert( pKeyFrame2 != NULL );
				TestAssert( pTrack1->GetKeyFrameCount( ) == 2 );

				// Add 3 more key frames
				pTrack1->CreateKeyFrame( Bit::Microseconds( 40 ) );
				pTrack1->CreateKeyFrame( Bit::Microseconds( 120 ) );
				pTrack1->CreateKeyFrame( Bit::Microseconds( 10 ) );
				TestAssert( pTrack1->GetKeyFrameCount( ) == 5 );
				if( pTrack1->GetKeyFrameCount( ) == 5 )
				{
					// Assert the key frame time
					TestAssert( pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 0 ) )->GetTime( ).AsMicroseconds( ) == 10 );
					TestAssert( pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 1 ) )->GetTime( ).AsMicroseconds( ) == 20 );
					TestAssert( pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 2 ) )->GetTime( ).AsMicroseconds( ) == 40 );
					TestAssert( pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 3 ) )->GetTime( ).AsMicroseconds( ) == 100 );
					TestAssert( pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 4 ) )->GetTime( ).AsMicroseconds( ) == 120 );

					// Assert the get function(time param)
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 10 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 0 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 20 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 1 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 40 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 2 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 100 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 3 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 120 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 4 ) ) );

					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 5 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 0 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 16 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 1 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 33 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 2 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 99 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 3 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 110 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 4 ) ) );

					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 15 ) ) != pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 0 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 31 ) ) != pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 1 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 80 ) ) != pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 2 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 110 ) ) != pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 3 ) ) );
					TestAssert( pTrack1->GetKeyFrame( Bit::Microseconds( 200 ) ) == pTrack1->GetKeyFrame( static_cast<Bit::SizeType>( 4 ) ) );
				}

					
			}
		}

	}


	// Print the finish text
	std::cout << "Finished Animation Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}