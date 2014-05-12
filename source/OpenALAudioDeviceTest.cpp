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

#include <OpenALAudioDeviceTest.hpp>
#include <Bit/Audio/OpenAL/OpenALAudioDevice.hpp>
#include <Bit/Audio/Sound.hpp>
//#include <Bit/Audio/SoundBuffer.hpp>
#include <Bit/System/Sleep.hpp>
#include <Bit/System/MemoryLeak.hpp>

// Constructor
OpenALAudioDeviceTest::OpenALAudioDeviceTest( ) :
	Test( )
{
}

// Virtual functions
void OpenALAudioDeviceTest::Run( std::ostream & p_Trace )
{
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Starting OpenAL Audio Device test." << std::endl;

	// Run the test here
	Bit::AudioDevice * pAudioDevice = new Bit::OpenALAudioDevice;

	// Assert the open function
	TestAssert( pAudioDevice->IsOpen( ) == false );
	TestAssert( pAudioDevice->Open( ) == true );
	TestAssert( pAudioDevice->IsOpen( ) == true );
	pAudioDevice->SetListenerPosition( Bit::Vector3f32( 0.0f, 0.0f, 0.0f ) );
	pAudioDevice->SetListenerTarget( Bit::Vector3f32( 0.0f, 0.0f, -1.0f ) );

	if( pAudioDevice->IsOpen( ) == true )
	{
		// Assert the sound creation
		Bit::Sound * pSound = pAudioDevice->CreateSound( );
		TestAssert( pSound != NULL );
		if( pSound != NULL )
		{
			// Create a buffer
			Bit::SoundBuffer * pBuffer = pAudioDevice->CreateSoundBuffer( );

			TestAssert( pBuffer != NULL );
			if( pBuffer != NULL )
			{
				// Assert the buffer loading
				TestAssert( pBuffer->LoadFromFile( "input/waveTest.wav", true ) == true );

				// Assert the sound loading for file.
				std::cout << "Load sound from file test:" << std::endl;
				TestAssert( pSound->LoadFromBuffer( *pBuffer ) == true );

				// Test sound in right speaker.
				pSound->SetPosition( Bit::Vector3f32( 1.0f, 0.0f, 0.0f ) );
				std::cout << "Playing sound in right speaker." << std::endl;
				pSound->Play( );
				Bit::Sleep( Bit::Seconds( 2 ) );
				std::cout << "Pausing sound for 1 second." << std::endl;
				pSound->Pause( );
				// Test sound in left speaker.
				pSound->SetPosition( Bit::Vector3f32( -1.0f, 0.0f, 0.0f ) );
				Bit::Sleep( Bit::Seconds( 1 ) );
				std::cout << "Playing sound in left speaker." << std::endl;
				pSound->Play( );
				Bit::Sleep( Bit::Seconds( 3 ) );
				pSound->Stop( );

				// Delete the sound buffer
				delete pBuffer;
			}

			// Delete the sound
			delete pSound;
		}
	}


	delete pAudioDevice;

	// Print the finish text
	std::cout << "Finished OpenAL Audio Device Test." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	
}