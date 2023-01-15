//
// Test program for the CC1200 morse code example
//

#include <mbed.h>

#include <CC1200.h>
#include <CC1200Morse.h>

#include "CC1200DemoPins.h"

#include <cinttypes>


CC1200 radio(PIN_SPI_MOSI, PIN_SPI_MISO, PIN_SPI_SCLK, PIN_TX_CS, PIN_TX_RST, stdout);

void testMorseCodeConversion()
{
	radio.begin();
	CC1200Morse morseConverter(radio);

	const size_t bufferLen = 64;
	uint8_t outputBuffer[bufferLen];

	char const * testString = "eternal silence@54!";

	CC1200Morse::EncodedMorse morse = morseConverter.convertToMorse(testString, outputBuffer, bufferLen);

	if(!morse.valid)
	{
		printf("Morse is invalid\n");
	}
	else
	{
		printf("Output %zu bytes:", morse.totalLength);
		for(size_t index = 0; index < morse.totalLength; ++index)
		{
			printf(" %" PRIx8, outputBuffer[index]);
		}
		printf("\n");
	}
}

/**
 * Test sending some arbitrary bytes as OOK modulated data.
 */
void testMorseByteTransmission()
{
	const auto timeUnit = 100ms;

	radio.begin();
	CC1200Morse morseConverter(radio);
	morseConverter.configure(CC1200::Band::BAND_820_960MHz, 915e6f, timeUnit, 14.5);

	const char testString[] = "\xFF\x0E\xFF";
	const size_t testStringLength = 3;

	// manually create morse code data
	CC1200Morse::EncodedMorse morse;
	morse.valid = true;
	morse.buffer = reinterpret_cast<uint8_t const *>(testString);
	morse.byteLen = testStringLength;
	morse.bitLen = 0;
	morse.totalLength = testStringLength;

	morseConverter.transmit(morse);

	Timer messageTimer;
	messageTimer.start();

	radio.setOnTransmitState(CC1200::State::IDLE);
	radio.startTX();

	// wait until all bytes have been transmitted.
	// Note: the FIFO length is 0 when the last byte is being sent, so we can't just check the FIFO length
	while(radio.getTXFIFOLen() > 0 || radio.getState() != CC1200::State::IDLE)
	{
		printf("TX FIFO size: %zu\n", radio.getTXFIFOLen());
		ThisThread::sleep_for(timeUnit * 100);
	}

	float timeSeconds = std::chrono::duration_cast<std::chrono::duration<float>>(messageTimer.elapsed_time()).count();
	size_t numBits = ((morse.byteLen * 8) + morse.bitLen);
	float effectiveBitrate = numBits / timeSeconds;

	printf("Sent %zu bits in %.03f s, effective bitrate = %.03f sps\n", numBits, timeSeconds, effectiveBitrate);

}

void testMorseCodeTransmission()
{
	const auto timeUnit = 100ms;

	radio.begin();
	CC1200Morse morseConverter(radio);
	morseConverter.configure(CC1200::Band::BAND_820_960MHz, 915e6f, timeUnit, 0);

	const size_t bufferLen = 64;
	uint8_t outputBuffer[bufferLen];

	char const * testString = "eternal silence@54!";

	CC1200Morse::EncodedMorse morse = morseConverter.convertToMorse(testString, outputBuffer, bufferLen);

	if(!morse.valid)
	{
		printf("Morse is invalid\n");
	}

	morseConverter.transmit(morse);

	radio.setOnTransmitState(CC1200::State::IDLE);
	radio.startTX();

	// wait until all bytes have been transmitted.
	// Note: the FIFO length is 0 when the last byte is being sent, so we can't just check the FIFO length
	while(radio.getTXFIFOLen() > 0 || radio.getState() != CC1200::State::IDLE)
	{
		printf("TX FIFO size: %zu\n", radio.getTXFIFOLen());
		ThisThread::sleep_for(timeUnit * 100);
	}
}

int main()
{
	printf("\nCC1200 Morse Demo:\n");

	while(1){
		int test=-1;
		//MENU. ADD AN OPTION FOR EACH TEST.
		printf("Select a test: \n");
		printf("1.  Test converting to Morse code\n");
		printf("2.  Test transmitting bytes as Morse\n");
		printf("3.  Test transmitting string of Morse\n");

		scanf("%d", &test);
		printf("Running test %d:\n\n", test);
		//SWITCH. ADD A CASE FOR EACH TEST.
		switch(test) {
			case 1:			testMorseCodeConversion();			break;
			case 2:			testMorseByteTransmission();		break;
			case 3:			testMorseCodeTransmission();		break;
			default:        printf("Invalid test number. Please run again.\n"); continue;
		}
		printf("done.\r\n");
	}

	return 0;

}