/**
 * \file ADS1100.h
 * \brief  ADS1100 is a class to handle an I2C ADC ADS1100.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef ADS1100_H_
#define ADS1100_H_

#include <interfaces/i2cinterface.h>
#include <I2Cdev.h>

namespace smrtobj
{
  /**
   * Class ADS1100 models the Analog-to-Digital (A/D) converter TI ADS1100.
   * The ADS1100 is a precision, continuously self-calibrating ADC with differential inputs and up to 16 bits
   * of resolution in a small SOT23-6 package. Conversions are performed ratiometrically, using the power supply
   * as the reference voltage. The ADS1100 uses an I2C-compatible serial interface and operates from a single
   * power supply ranging from 2.7V to 5.5V.
   *
   */
  class ADS1100: public I2CInterface, public Sensor
  {
    public:
      //! Device address used by default
      static const uint8_t DEVICE_ADDRESS = 0x48;

      /**
       * Default Constructor.
       *
       */
      ADS1100();

      /**
       * Constructor.
       * Sets the device address.
       *
       * \param[in] addr device address
       */
      ADS1100(uint8_t addredd);

      /**
       * Copy Constructor.
       *
       * \param[in] d i2c device object
       */
      ADS1100(const ADS1100 &d);

      /**
       * Destructor.
       */
      virtual ~ADS1100();

      /**
       * Override operator =
       *
       * \param[in] d source device object
       *
       * \return destination signal reference
       */
      ADS1100 & operator=(const ADS1100 &d);

      /**
       * Initializes the i2c device: power on and prepare for general usage.
       * Nothing is required by this device.
       *
       * \return true if no errors
       */
      virtual bool initialize();

      /**
       * Tests if the device is connected.
       * Make sure the device is connected and responds as expected.
       *
       * \return true if connection is valid, false otherwise
       */
      virtual bool isConnected();

      /**
       * Reads data from the i2c device. This function read 2 byte:
       *   - 1st byte (Byte0) is the most significant byte
       *   - 2nd byte (Byte1) is the less significant byte
       * Data is calculate as:
       *   value = (Byte0] << 8) | Byte1;
       * The value read is stored in m_value.
       *
       * \return true if no errors
       */
      virtual bool read();

      /**
       * Converts data read (saved in m_value variable) in voltage.
       * Note: To be changed!! now it use the formula of ADS1110
       *
       * \return last data read as voltage level
       */
      virtual float measure();

      /**
       * Returns last ADC value read
       *
       * \return last value read
       */
      uint16_t value() { return m_value; }

    private:
      //! Last value read
      uint16_t m_value;
};

} /* namespace smrtobj */

#endif /* ADS1100_H_ */
