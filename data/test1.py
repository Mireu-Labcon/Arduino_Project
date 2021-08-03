import json,csv

a = open("./arduino_data.json",'r')
data = json.load(a)

data2 = data['test14']['온도']

f = open('./file.csv', 'w', encoding='utf-8',newline='')
wr = csv.writer(f)


for data1 in data2:
    if data1 == 'Hc':
        print('1')
        wr.writerow('1')
    else:
        print('0')
        wr.writerow('0')
