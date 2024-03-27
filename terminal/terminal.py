import os
import sys
import tkinter as tk
import serial

port = sys.argv[1]
baudrate = 1500000
ser = serial.Serial(port, baudrate, timeout=1)

MOVE_LEFT_CODE = b'\x34'
MOVE_RIGHT_CODE = b'\x36'
ROTATE_180_CODE = b'\x71'
ROTATE_90_CODE = b'\x38'
ROTATE_270_CODE = b'\x77'
SOFT_DROP_CODE = b'\x35'
HARD_DROP_CODE = b'\x64'
HOLD_CODE = b'\x09'
RESET_CODE = b'\x72'
QUIT_CODE = b'\x70'

def get_key_byte(event: tk.Event):
    if event.keysym == "Left": # ARROW LEFT
        return MOVE_LEFT_CODE
    elif event.keysym == "Right": # ARROW RIGHT
        return MOVE_RIGHT_CODE
    elif event.keysym == "Up":
        return ROTATE_90_CODE
    elif event.keysym == "d":
        return HARD_DROP_CODE
    elif event.keysym == "r":
        return RESET_CODE
    elif event.keysym == "w":
        return ROTATE_270_CODE
    elif event.keysym == "q":
        return ROTATE_180_CODE
    elif event.keysym == "Tab":
        return HOLD_CODE
    elif event.keysym == "Down":
        return SOFT_DROP_CODE
    elif event.keysym == "p":
        return QUIT_CODE
    return 0x00

def on_key_press(event: tk.Event):
    key = get_key_byte(event)
    print("SENDING: ", key)
    ser.write(key)
    
def on_key_released(event):
    
    key = get_key_byte(event)
    
    code = int.from_bytes(key, 'little')
    code += 128

    print("SENDING RELEASE: ", key)
    ser.write(code.to_bytes(1, 'little'))


root = tk.Tk()
root.title("Keyboard Event Example")

def readBytes():
    
    try:
        sys.stdout.buffer.write(ser.read(293))
    except serial.SerialException as e:
        print("Error: Unable to open the serial port:", e)
    except Exception as e:
        print("An error occurred:", e)
    #root.after(1, readBytes)

# Bind the key press event to the root window
root.bind("<KeyPress>", on_key_press)
root.bind("<KeyRelease>", on_key_released)
# Start the GUI event loop

os.system('xset r off')
root.after(1, readBytes)
root.mainloop()

