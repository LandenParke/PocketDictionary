examples/calibration_data_acc_gyro
^^^^^^^^^^^^^^

  This is a simple example of an accelerometer sensor and gyro sensor device 
  using a Sensor Control Unit. nsh built-in command. 
  This example uses a timer to acquire sensing data at regular intervals (10 ms), 
  displays the number of samples when 100 data have accumulated, 
  and writes the data to an SD card.

  Supported sensors are:

  - Bosch BMI160 sensor

  Configuration Pre-requisites:

    CONFIG_EXAMPLES_ACCEL
    CONFIG_EXAMPLES_GYRO
    CONFIG_CXD56_SCU - CXD56xx Sensor Control Unit
    CONFIG_SENSORS_BMI160_SCU - BMI160 adn SCU

  Example Configuration:

    CONFIG_EXAMPLES_CALIB_DATA_ACC_GYRO - Enable accelerometer sensor example
    CONFIG_EXAMPLES_CALIB_DATA_ACC_GYRO_PROGNAME - Program name.
    CONFIG_EXAMPLES_CALIB_DATA_ACC_GYRO_PRIORITY - Example priority. Default: 100
    CONFIG_EXAMPLES_CALIB_DATA_ACC_GYRO_STACKSIZE - Example stack size. Default: 2048

  Operation:

    Run this application from nsh. This takes data from the accelerometer and gyro sensor 
    10 times and writes it to the SD card.
