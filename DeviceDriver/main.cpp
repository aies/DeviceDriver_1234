#include "gmock/gmock.h"
#include "device_driver.h"
#include <vector>

using namespace testing;

class Flash_Mock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public Test {
public:
	Flash_Mock mockFlash;
	DeviceDriver driver{ &mockFlash };
	long testAddr = 0x8;
	int  testData = 0x8;
};

TEST_F(DeviceDriverFixture, ReadFromHW) {
	EXPECT_CALL(mockFlash, read(testAddr))
		.Times(5)
		.WillRepeatedly(Return(testAddr));

	DeviceDriver driver{ &mockFlash };
	int data = driver.read((long)testAddr);
}


TEST_F(DeviceDriverFixture, WriteFromHW) {
	EXPECT_CALL(mockFlash, read(testAddr))
		.WillRepeatedly(Return(0xff));

	EXPECT_CALL(mockFlash, write(testAddr, testData))
		.Times(1);

	driver.write(testAddr, testData);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}