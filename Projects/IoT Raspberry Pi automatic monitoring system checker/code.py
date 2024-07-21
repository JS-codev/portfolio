import RPi.GPIO as GPIO
import time, math

R1 = 1000 # Ohms
B = 3000.0 # The thermistor constant 
R0 = 10000.0 # The resistance of the thermistor at 25C 

GPIO.setmode(GPIO.BCM)

# Pin_a charges the thermistor
# pin_b discharges the thermistor 
a_pin = 7
b_pin = 5
buzzer = 3

# Set setup buzzer
GPIO.setup(buzzer,GPIO.OUT)

# emptying…
def discharge():
    GPIO.setup(a_pin, GPIO.IN)
    GPIO.setup(b_pin, GPIO.OUT)
    GPIO.output(b_pin, False)
    time.sleep(0.1)

# return the time taken (uS) for the voltage to count as a digital input HIGH
def charge_time():
    GPIO.setup(b_pin, GPIO.IN)
    GPIO.setup(a_pin, GPIO.OUT)
    GPIO.output(a_pin, True)
    t1 = time.time()
    while not GPIO.input(b_pin):
        pass
    t2 = time.time()
    return (t2 - t1) * 1000000





# Take an analog reading as the time taken to charge after first discharge.
def analog_read():
    discharge()
    t = charge_time()
    discharge()
    return t

# Convert the time taken to charge into a value of resistance
# To reduce errors, do it 10 times and take the average.
def read_resistance():
    n = 10
    total = 0;
    for i in range(1, n):
        total = total + analog_read() 
    t = total / float(n)      #New t average value
    T = t * 0.632 * 3.3
    r = (T / C) - R1
    return r
    
def read_temp_c():
    R = read_resistance()
    t0 = 273.15     # 0 deg C in K
    t25 = t0 + 25.0 # 25 deg C in K
    # Steinhart-Hart equation - Google it
    inv_T = 1/t25 + 1/B * math.log(R/R0)
    T = (1/inv_T - t0)
    return T * 9.0 / 5.0 + 32.0 # convert C to F
    
try:
    while True:
        print(read_temp_c())
        if read_temp_c() < 120:
            print(“Temp below 120°C”)  #Molding may crack 
            GPIO.output(buzzer, GPIO.HIGH)
        if read_temp_c() > 180:
            print(“Temp above 180°C”)  #Molding materials may be damaged. 
            GPIO.output(buzzer, GPIO.HIGH)
        else:
            GPIO.output(buzzer,GPIO.LOW)  #Molding no crack / damaged 
            continue
        
        time.sleep(0.5)
finally:
    GPIO.cleanup()
