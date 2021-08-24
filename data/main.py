import json,csv

a = open("./arduino_data.json",'r')
data = json.load(a)

data2 = data['test14']['온도']

f = open('./file.csv', 'w', encoding='utf-8',newline='')
wr = csv.writer(f)


for data1 in data2:
    #온도 정상인 데이터
    if data1 == 'Hc':
        print('2')
        wr.writerow('2')

    #온도 매우 낮은 데이터
    elif data1 == 'Ha':
        print('1')
        wr.writerow('1')

    #온도 매우 높은 데이터
    elif data1 == 'Hb':
        print('3')
        wr.writerow('3')
    
    #없는 데이터(공백) from Json
    else:
        print('0')
        wr.writerow('0')

import matplotlib.pyplot as plt

f = open('file.csv', 'r', encoding='utf-8')
wr = csv.reader(f)
data4 = []
for data in wr:
  data4 = data

plt.plot(data)
plt.show()