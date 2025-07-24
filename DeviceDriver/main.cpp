#include "gmock/gmock.h"
#include "device_driver.h"
#include <vector>

using namespace testing;

class Flash_Mock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	Flash_Mock mockFlash;
	long testCase = 0x8;

	EXPECT_CALL(mockFlash, read(testCase))
		.Times(5)
		.WillRepeatedly(Return(testCase));

	DeviceDriver driver{ &mockFlash };
	int data = driver.read((long)testCase);
}


TEST(DeviceDriver, WriteFromHW) {
	Flash_Mock mockFlash;
	long testCase = 0x8;
	int  testCase2 = 0x8;

	EXPECT_CALL(mockFlash, read(testCase))
		.WillRepeatedly(Return(0xff));

	DeviceDriver driver{ &mockFlash };
	driver.write(testCase, testCase2);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}