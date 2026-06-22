examples/calibration_data_mag
^^^^^^^^^^^^^^

  This is a simple example of an magnet sensor device 
  using a Sensor Control Unit. nsh built-in command. 
  This example uses a timer to acquire sensing data at regular intervals (10 ms), 
  displays the number of samples when 100 data have accumulated, 
  and writes the data to an SD card.

  Supported sensors are:

  - ROHM BM1422AGMV sensor

  Configuration Pre-requisites:

    CONFIG_EXAMPLES_MAG
    CONFIG_CXD56_SCU - CXD56xx Sensor Control Unit
    CONFIG_SENSORS_BM1422GMV_SCU - BM1422AGMV and SCU

  Example Configuration:

    CONFIG_EXAMPLES_ACCEL - Enable accelerometer sensor example
    CONFIG_EXAMPLES_ACCEL_PROGNAME - Program name.
    CONFIG_EXAMPLES_ACCEL_PRIORITY - Example priority. Default: 100
    CONFIG_EXAMPLES_ACCEL_STACKSIZE - Example stack size. Default: 2048

  Operation:

    Run this application from nsh. This takes data from the mag sensor 
    10 times and writes it to the SD card.
