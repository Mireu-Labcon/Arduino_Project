import serial
from myemail import *
useremail = "alfmalfm1214@gmail.com"
s = serial.Serial("/dev/ttyACM0", 9600)

if "001": #온습도 센서 에어컨 실행
    email(user=useremail, name_main="현제 온도가 높습니다 에어컨을 켜주세요", name_tit="에어컨을 켜주세요")

elif "002": #온습도 센서 히터 실행
    email(user=useremail, name_main="현제 온도가 낮습니다 히터을 켜주세요", name_tit="히터을 켜주세요")

elif "003": #가스센서 화제 발생
    a = 1
    while a <= 5:
        email(user=useremail, name_main="현제 화제가 발생되었습니다", name_tit="화제가 발생되었습니다")
        a += 1

elif "004": #가스센서 환기 요청
        email(user=useremail, name_main="현제 집내부에 가스농도가 높습니다 환기을 진행해주세요", name_tit="환기을 해주세요")

elif "005": #미세먼지센서 미 실행
    email(user=useremail, name_main="현제 집내부에 미세먼지가 기존보다 많습니다 공기청정기을 켜주세요", name_tit="공기청정기을 약하게 켜주세요")

elif "006": #미세먼지센서 중 실행
    email(user=useremail, name_main="현제 집내부에 미세먼지가 기존보다 매우 많습니다 공기청정기을 켜주세요", name_tit="공기청정기을 조금 강하게 켜주세요")

elif "007": #미세먼지센서 강 실행
    email(user=useremail, name_main="현제 집내부에 미세먼지가 매우 많습니다 공기청정기을 켜주세요", name_tit="공기청정기을 강하게 켜주세요")

while True:
    print("help!")