#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int ret = (int)(m_hardware->read(address));

    for (int i = 0; i < 4;  i++) {
        if (ret != (int)(m_hardware->read(address))) {
            throw ReadFailException();
        }
    }

    return ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if (m_hardware->read(address) == 0xff)
        m_hardware->write(address, (unsigned char)data);
    else
        throw WriteFailException();
}