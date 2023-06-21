import time
import Adafruit_ADS1x15

adc = Adafruit_ADS1x15.ADS1115()

GAIN = 1

while True:
	value = adc.read_adc(0, gain=GAIN)
	print('ADC Value: {}, Voltage: {}V'.format(value, value * 0.0001875))
	time.sleep(0.5)
