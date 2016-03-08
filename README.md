# mruby-mraa

## example

```ruby
gpio_led = 48 # GPIO port number of LED
gpio = Mraa::Gpio.new(gpio_led)
gpio.dir(Mraa::Gpio::OUT)
gpio.write(1)
```

## detail

### Mraa
#### class methods
| Method Name        | In                 | Out             |
|--------------------|--------------------|-----------------|
| pin_mode_test      | Integer *pin*      | Boolean         |
| adc_raw_bits       | (nil)              | Integer         |
| adc_supported_bits | (nil)              | Integer         |
| set_log_level      | Integer *level*    | mraa_result_t   |
| get_platform_name  | (nil)              | String          |
| set_priority       | Integer *priority* | Integer         |
| version            | (nil)              | String          |
| result_print       | mraa_result_t      | (nil)           |
| get_platform_type  | (nil)              | mraa_platform_t |

#### constants
| mraa_pinmodes_t |
|-----------------|
| PIN_VALID       |
| PIN_GPIO        |
| PIN_PWM         |
| PIN_FAST_GPIO   |
| PIN_SPI         |
| PIN_I2C         |
| PIN_AIO         |
| PIN_UART        |

| mraa_result_t                        |
|--------------------------------------|
| SUCCESS                              |
| ERROR_FEATURE_NOT_IMPLEMENTED        |
| ERROR_FEATURE_NOT_SUPPORTED          |
| ERROR_INVALID_VERBOSITY_LEVEL        |
| ERROR_INVALID_PARAMETER              |
| ERROR_INVALID_HANDLE                 |
| ERROR_NO_RESOURCES                   |
| ERROR_INVALID_RESOURCE               |
| ERROR_INVALID_QUEUE_TYPE             |
| ERROR_NO_DATA_AVAILABLE              |
| ERROR_INVALID_PLATFORM               |
| ERROR_PLATFORM_NOT_INITIALISED       |
| ERROR_PLATFORM_ALREADY_INITIALISED   |
| ERROR_UNSPECIFIED                    |

| mraa_platform_t       |
|-----------------------|
| INTEL_GALILEO_GEN1    |
| INTEL_GALILEO_GEN2    |
| INTEL_EDISON_FAB_C    |
| INTEL_DE3815          |
| INTEL_MINNOWBOARD_MAX |
| RASPBERRY_PI          |
| UNKNOWN_PLATFORM      |

| mraa_intel_edison_miniboard_t |
|-------------------------------|
| INTEL_EDISON_MINIBOARD_J17_1  |
| INTEL_EDISON_MINIBOARD_J17_5  |
| INTEL_EDISON_MINIBOARD_J17_7  |
| INTEL_EDISON_MINIBOARD_J17_8  |
| INTEL_EDISON_MINIBOARD_J17_9  |
| INTEL_EDISON_MINIBOARD_J17_10 |
| INTEL_EDISON_MINIBOARD_J17_11 |
| INTEL_EDISON_MINIBOARD_J17_12 |
| INTEL_EDISON_MINIBOARD_J17_14 |
| INTEL_EDISON_MINIBOARD_J18_1  |
| INTEL_EDISON_MINIBOARD_J18_2  |
| INTEL_EDISON_MINIBOARD_J18_6  |
| INTEL_EDISON_MINIBOARD_J18_7  |
| INTEL_EDISON_MINIBOARD_J18_8  |
| INTEL_EDISON_MINIBOARD_J18_10 |
| INTEL_EDISON_MINIBOARD_J18_11 |
| INTEL_EDISON_MINIBOARD_J18_12 |
| INTEL_EDISON_MINIBOARD_J18_13 |
| INTEL_EDISON_MINIBOARD_J19_4  |
| INTEL_EDISON_MINIBOARD_J19_5  |
| INTEL_EDISON_MINIBOARD_J19_6  |
| INTEL_EDISON_MINIBOARD_J19_8  |
| INTEL_EDISON_MINIBOARD_J19_9  |
| INTEL_EDISON_MINIBOARD_J19_10 |
| INTEL_EDISON_MINIBOARD_J19_11 |
| INTEL_EDISON_MINIBOARD_J19_12 |
| INTEL_EDISON_MINIBOARD_J19_13 |
| INTEL_EDISON_MINIBOARD_J19_14 |
| INTEL_EDISON_MINIBOARD_J20_3  |
| INTEL_EDISON_MINIBOARD_J20_4  |
| INTEL_EDISON_MINIBOARD_J20_5  |
| INTEL_EDISON_MINIBOARD_J20_6  |
| INTEL_EDISON_MINIBOARD_J20_7  |
| INTEL_EDISON_MINIBOARD_J20_8  |
| INTEL_EDISON_MINIBOARD_J20_9  |
| INTEL_EDISON_MINIBOARD_J20_10 |
| INTEL_EDISON_MINIBOARD_J20_11 |
| INTEL_EDISON_MINIBOARD_J20_12 |
| INTEL_EDISON_MINIBOARD_J20_13 |
| INTEL_EDISON_MINIBOARD_J20_14 |

| mraa_intel_edison_t |
|---------------------|
| INTEL_EDISON_GP182  |
| INTEL_EDISON_GP135  |
| INTEL_EDISON_GP27   |
| INTEL_EDISON_GP20   |
| INTEL_EDISON_GP28   |
| INTEL_EDISON_GP111  |
| INTEL_EDISON_GP109  |
| INTEL_EDISON_GP115  |
| INTEL_EDISON_GP128  |
| INTEL_EDISON_GP13   |
| INTEL_EDISON_GP165  |
| INTEL_EDISON_GP19   |
| INTEL_EDISON_GP12   |
| INTEL_EDISON_GP183  |
| INTEL_EDISON_GP110  |
| INTEL_EDISON_GP114  |
| INTEL_EDISON_GP129  |
| INTEL_EDISON_GP130  |
| INTEL_EDISON_GP44   |
| INTEL_EDISON_GP46   |
| INTEL_EDISON_GP48   |
| INTEL_EDISON_GP131  |
| INTEL_EDISON_GP14   |
| INTEL_EDISON_GP40   |
| INTEL_EDISON_GP43   |
| INTEL_EDISON_GP77   |
| INTEL_EDISON_GP82   |
| INTEL_EDISON_GP83   |
| INTEL_EDISON_GP134  |
| INTEL_EDISON_GP45   |
| INTEL_EDISON_GP47   |
| INTEL_EDISON_GP49   |
| INTEL_EDISON_GP15   |
| INTEL_EDISON_GP84   |
| INTEL_EDISON_GP42   |
| INTEL_EDISON_GP41   |
| INTEL_EDISON_GP78   |
| INTEL_EDISON_GP79   |
| INTEL_EDISON_GP80   |
| INTEL_EDISON_GP81   |

### Mraa::Pwm
#### class methods
| Method Name | In                                 | Out       |
|-------------|------------------------------------|-----------|
| new         | Integer *pin* [, Integer *chipid*] | Mraa::Pwm |

#### instance methods
| Method Name    | In                             | Out           |
|----------------|--------------------------------|---------------|
| write          | Float *duty*                   | mraa_result_t |
| read           | (nil)                          | Float         |
| period         | Float *period*                 | mraa_result_t |
| period_ms      | Integer *period*               | mraa_result_t | 
| period_us      | Integer *period*               | mraa_result_t |
| pulsewidth     | Float *pulsewidth*             | mraa_result_t |
| pulsewidth_ms  | Integer *pulsewidth*           | mraa_result_t |
| pulsewidth_us  | Integer *pulsewidth*           | mraa_result_t |
| enable         | Boolean *pwmen*                | mraa_result_t |
| owner          | Boolean *owner*                | mraa_result_t |
| config_ms      | Integer *period*, Float *duty* | mraa_result_t |
| config_percent | Integer *period*, Float *duty* | mraa_result_t |

### Mraa::Aio
#### class methods
| Method Name | In            | Out       |
|-------------|---------------|-----------|
| new         | Integer *pin* | Mraa::Aio |

#### instance methods
| Method Name | In             | Out           |
|-------------|----------------|---------------|
| read        | (nil)          | Integer       |
| set_bit     | Integer *bits* | mraa_result_t |
| get_bit     | (nil)          | Integer       |

### Mraa::Gpio
#### class methods
| Method Name | In                              | Out        |
|-------------|---------------------------------|------------|
| new         | Integer *pin* [, Boolean *raw*] | Mraa::Gpio |

#### instance methods
| Method Name | In                              | Out           |
|-------------|---------------------------------|---------------|
| edge_mode   | gpio_edge_t *edge_mode*         | mraa_result_t |
| mode        | gpio_mode_t *mode*              | mraa_result_t |
| dir         | gpio_dir_t *dir*                | mraa_result_t |
| read        | (nil)                           | Integer       |
| write       | Integer *val*                   | mraa_result_t |
| owner       | Boolean *owner*                 | mraa_result_t |
| use_mmaped  | Boolean *use_mmaped*            | mraa_result_t |
| get_pin     | [Boolean *raw*]                 | Integer       |
| enable_irq  | gpio_edge_t *edge_mode*         | mraa_result_t |
| disable_irq | (nil)                           | mraa_result_t |

#### instance variables
| Variable Name | Type    | Description                          |
|---------------|---------|--------------------------------------|
| irq           | Boolean | Indicate the existance of GPIO event |

Mraa::Gpio#irq is read-only. Furthermore, it's read-clear.
It means when you read the value, it will be cleared automatically.

#### constants
| gpio_mode_t |
|-------------|
| STRONG      |
| PULLUP      |
| PULLDOWN    |

| gpio_dir_t |
|------------|
| HIZ        |
| OUT        |
| IN         |
| OUT_HIGH   |
| OUT_LOW    |

| gpio_edge_t  |
|--------------|
| EDGE_NONE    |
| EDGE_BOTH    |
| EDGE_RISING  |
| EDGE_FALLING |

### Mraa::Spi
#### class methods
| Method Name | In                             | Out       |
|-------------|--------------------------------|-----------|
| new         | Integer *bus* [, Boolean *cs*] | Mraa::Spi |

#### instance methods
| Method Name   | In                                     | Out                  |
|---------------|----------------------------------------|----------------------|
| mode          | spi_mode_t *mode*                      | mraa_result_t        |
| frequency     | Integer *freq*                         | mraa_result_t        |
| transfer      | Array<Byte> *txdata*, Integer *length* | Array<Byte>, Integer |
| transfer_byte | Byte *txbyte*                          | Byte                 |
| lsbmode       | Boolean *lsbmode*                      | mraa_result_t        |
| bit_per_word  | Integer *bit_per_word*                 | mraa_result_t        |

#### constants
| spi_mode_t |
|------------|
| MODE0      |
| MODE1      |
| MODE2      |
| MODE3 |

### Mraa::I2c
#### class methods
| Method Name | In                              | Out       |
|-------------|---------------------------------|-----------|
| new         | Integer *bus* [, Boolean *raw*] | Mraa::I2c |

#### instance methods
| Method Name    | In                                       | Out                 |
|----------------|------------------------------------------|---------------------|
| frequency      | i2c_mode_t *freq*                        | mraa_result_t       |
| read           | Integer *length*                         | Arra<Byte>, Integer |
| read_byte      |                                          | Byte                |
| read_reg       | Integer *reg*                            | Byte                |
| read_word_reg  | Integer *reg*                            | Word                |
| write          | Array<Byte> *wdata* [, Integer *length*] | mraa_result_t       |
| write_byte     | Byte *wbyte*                             | mraa_result_t       |
| write_reg      | Byte *wbyte*, Integer *reg*              | mraa_result_t       |
| write_word_reg | Byte *wword*, Integer *reg*              | mraa_result_t       |
| address        | Byte *addr*                              | mraa_result_t       |

#### constants
| i2c_mode_t |
|------------|
| STD        |
| FAST       |
| HIGH       |

### Mraa::Uart
#### class methods
| Method Name | In            | Out        |
|-------------|---------------|------------|
| new         | Integer *dev* | Mraa::Uart |

#### instance methods
| Method Name | In    | Out    |
|-------------|-------|--------|
|get_dev_path | (nil) | String |

