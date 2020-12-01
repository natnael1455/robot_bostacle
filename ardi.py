import serial
import time
import random
from numpy import save ,load
import numpy as np

data = load('data.npy')
postions= np.array([0,0,3,0,6,3,2,1,12,6,16,6,4,2,14,7,0,12,3,12,15,6,2,13,8,4,11,4,6,14,5,10])
postion_m=np.reshape(postions,(16,2))
s = serial.Serial('COM8',9600)
time.sleep(1)
count = 1
n= int(input('Enter a number: '))# % of exploring
while count <= 100:
    count = count +1
    s.write('s'.encode())# sensor data read
    da = s.read(2)
    postion = int(da.decode('utf-8'))
    next_position =0
    x = random.uniform(0,1)
    rd = 0
    # checing for explore or expret
    if x <= n:
        result = np.where(data[postion] == np.amax(data[postion]))
        rd = result[0][0]
    else:
        rd =random.randint(0,3)
    #print(rd)
    re1=0
    re2=0
    # sending movement command
    if rd == 0 :
        s.write('f'.encode())
        re1=100 #reword for going forward 
        next_position=postion
    elif rd == 1:
        s.write('b'.encode())
    elif rd == 2:
        s.write('r'.encode())
        next_position=postion_m[postion][0]
    elif rd == 3:
        s.write('l'.encode())
        re1= -150 # panshiment for going backword
        next_position=postion_m[postion][1]
    s.write('c'.encode()) 
    dc = s.read(1) 
    dd=dc.decode('utf-8')
    if dd == "y":
        re2=-300
        next_position=0
    re=re1+re2
    a = 0.9*np.max(data[next_position]) 
    b= data[postion][rd]
    data[postion][rd] = b + 0.1 * (re + a-b )
    print(data)
    if dd == 'y':
        break
save('data.npy', data)
s.close()
    
