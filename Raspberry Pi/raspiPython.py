#!/usr/bin/env python3

import RPi.GPIO as GPIO
from flask import Flask, Response, render_template, stream_with_context
import json
import time
from datetime import datetime

bit_pins = [3, 5, 7, 11, 13, 15, 19]
sensorValue = 0

app = Flask(__name__)

def setup_gpio():
    GPIO.setwarnings(False)  # Deaktiviere GPIO-Warnungen
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(35, GPIO.OUT)
    GPIO.setup(37, GPIO.OUT)
    # GPIO 1 bis 7 einrichten und als Pull-Down konfigurieren
    for pin in bit_pins:
        GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

def update_gpio():
    if sensorValue < 30:
        GPIO.output(35, GPIO.HIGH)
    else:
        GPIO.output(35, GPIO.LOW)

def get_sensor_value():
    global sensorValue

    bit_values = [GPIO.input(pin) for pin in bit_pins]
    sensorValue = sum(bit_values[i] * (2 ** i) for i in range(len(bit_values)))

"""
@app.route('/wetnesslevel', methods['POST'])
def wetnesslevel():

wetnesslevel= request.form['message']
 
"Lokales Wetnesslevel=wetnesslevel"
 
return 0
 
@app.route('/water', methods['POST'])
def water():
 
water= true
 
"if(water&&(data<wetnesslevel){
LED Pumpe ein
}else{LED Pumpe aus und water=false}"
 
return 0
"""
@app.route('/')
def index():
    return render_template('index.html')

@app.route("/chart-data")
def chart_data():
    def generate_data():
        while True:
            get_sensor_value()
            json_data = json.dumps(
                {'time': datetime.now().strftime('%Y-%m-%d %H:%M:%S'), 'value': sensorValue})
            yield f"data:{json_data}\n\n"
            time.sleep(1)

    response = Response(stream_with_context(generate_data()), mimetype="text/event-stream")
    response.headers["Cache-Control"] = "no-cache"
    response.headers["X-Accel-Buffering"] = "no"
    return response

def main():
    setup_gpio()
    update_gpio()
    try:
        app.run(host='0.0.0.0', debug=True, threaded=True)
    except KeyboardInterrupt:
        pass
    finally:
        GPIO.cleanup()

if __name__ == "__main__":
    main()
