import sys
import select
import time
import serial

current_state = {}
button_state = { "remote_fill_valve": 0, "remote_vent_valve": 0, "run_tank_valve": 0, "linear_actuator": 0, "ignition_power": 0, "ignition_select": 0}
current_daq = {}

state = None
temp_str = ""
def fsm(c):
    global temp_str
    global state
    global last_tower_daq_time
    global last_tower_state_time
    global current_state
    global current_daq
    #print "fsm(%c), temp_str = %s" % (c, temp_str)
    if c == '[':
        #about to receive an ACK request
        temp_str = ""
        state = "ACK"
    elif c == '{':
        #about to receive a state update
        temp_str = ""
        state = "STATE"
    elif c == '}':
        #about to receive a daq update
        temp_str = ""
        state = "DAQ"
    elif validBase64(c):
        temp_str += c
        if state == "ACK" and len(temp_str) == 1:
            #handle the ack request
            print "got an ack request"
            print str(decode_state(temp_str))
            if decode_state(temp_str) == button_state:
                output('[') #ACK
            else:
                output(']') #NACK

        elif state == "STATE" and len(temp_str) == 1:
            #handle the state update
            print "got a state update"
            current_state = decode_state(temp_str)
            last_tower_state_time = time.time()

        elif state == "DAQ" and len(temp_str) == 17:
            #handle the daq update
            print "got a daq update"
            current_daq = decode_daq(temp_str)
            last_tower_daq_time = time.time()

base64_string =  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
def validBase64(c):
    return c in base64_string

def decode_daq(s):
   x = [ base64_string.index(i) for i in s ]
   return {
       "pressure1": ''.join(s[0:3]),
       "pressure2": ''.join(s[3:6]),
       "rocket_mass": ''.join(s[6:9]),
       "ign_pri_current": ''.join(s[9:12]),
       "ign_sec_current": ''.join(s[12:15]),
       "rfill_current_open":  bool(x[15] & 32),
       "rfill_current_close": bool(x[15] & 16),
       "rvent_current_open":  bool(x[15] & 8),
       "rvent_current_close": bool(x[15] & 4),
       "linac_current_open":  bool(x[15] & 2),
       "linac_current_close": bool(x[15] & 1),
       "rfill_lsw_open":      bool(x[16] & 32),
       "rfill_lsw_close":     bool(x[16] & 16),
       "rvent_lsw_open":      bool(x[16] & 8),
       "rvent_lsw_close":     bool(x[16] & 4),
       "linac_lsw_extend":    bool(x[16] & 2),
       "linac_lsw_retract":   bool(x[16] & 1)
       }

def decode_state(c):
    x = base64_string.index(c)
    return {
        "remote_fill_valve": int(bool(x & 1)),
        "remote_vent_valve": int(bool(x & 2)),
        "run_tank_valve": int(bool(x & 4)),
        "linear_actuator": int(bool(x & 8)),
        "ignition_power": int(bool(x & 16)),
        "ignition_select": int(bool(x & 32))}

def encode_state(s):
    x = s['remote_fill_valve'] * 1 + \
        s['remote_vent_valve'] * 2 + \
        s['run_tank_valve'] * 4 + \
        s['linear_actuator'] * 8 + \
        s['ignition_power'] * 16 + \
        s['ignition_select'] * 32
    return base64_string[x]



def handle_input(line):
    if line.strip().startswith("printall"):
        print "current state: " + str(current_state)
        print "button state: " + str(button_state)
        print "current daq: " + str(current_daq)
        print "in waiting: " + str(ser.in_waiting)
    elif line.strip().startswith("open"):
        if line.strip().endswith("remote fill"):
            #open remote fill
            print("opening remote fill")
            button_state['remote_fill_valve'] = 1
        elif line.endswith("remote vent"):
            #open remote vent
            button_state['remote_vent_valve'] = 1
            print("opening remote fill")
    elif line.startswith("close"):
        if line.endswith("remote fill"):
            print "closing remote fill"
            button_state['remote_fill_valve'] = 0
        elif line.endswith("remote vent"):
            print "closing remote vent"
            button_state['remote_vent_valve'] = 0
    else:
        print "I don't understand"

last_tower_state_time = 0
last_tower_daq_time = 0
time_last_requested_state = 0
time_last_requested_daq = 0
time_last_state_command = 0
def main_loop():
    global time_last_requested_state
    global time_last_requested_daq
    global time_last_state_command
    if(current_state != button_state):
        if time.time() - time_last_state_command > 1:
            output(';')
            output(encode_state(button_state))
            time_last_state_command = time.time()
    if(time.time() - last_tower_state_time > 5 or current_state != button_state):
        if(time.time() - time_last_requested_state > 1):
            time_last_requested_state = time.time()
            output('{')
    if(time.time() - last_tower_daq_time > 5):
        if(time.time() - time_last_requested_daq > 1):
            time_last_requested_daq = time.time()
            output('}')
    
ser = serial.Serial('/dev/cu.usbmodem411', 9600)
def output(c):
    print "outputting " + c
    ser.write(c)

while True:
    if select.select([sys.stdin], [], [], 0) == ([sys.stdin], [], []):
        x = sys.stdin.readline().strip()
        handle_input(x)
        #print "you enterred " + x
    while ser.in_waiting != 0:
        x = ser.read()
        fsm(x)
    main_loop()
    
    time.sleep(0.1)
