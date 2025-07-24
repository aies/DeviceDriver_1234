#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class Flash_Mock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	Flash_Mock mockFlash;

	EXPECT_CALL(mockFlash, read(0x8))
		.Times(5)
		.WillRepeatedly(Return(0x8));

	DeviceDriver driver{ &mockFlash };
	int data = driver.read((long)0x8);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}