from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.application import MIMEApplication
import smtplib  # 메일을 보내기 위한 라이브러리 모듈
import time
import string
import random
import os

def email(user,name_tit, name_main):
    sendEmail = "a33107521@gmail.com"
    recvEmail = [user]
    password = "bwgpmalglegrzfxn"

    smtpName = "smtp.gmail.com"
    smtpPort = 587

    for recvEmaila in recvEmail:
        # 여러 MIME을 넣기위한 MIMEMultipart 객체 생성
        msg = MIMEMultipart()

        msg["Subject"] = '[아두이노 플젝] '+name_tit
        msg["From"] = sendEmail
        msg["To"] = recvEmaila

        # 본문 추가
        text = (
            name_main
            + "\n\n"
            + time.strftime("%y-%m-%d")
            + "에 전송 하였습니다"
        )
        contentPart = MIMEText(text)  # MIMEText(text , _charset = "utf8")
        msg.attach(contentPart)

        s = smtplib.SMTP(smtpName, smtpPort)
        s.starttls()
        s.login(sendEmail, password)
        s.sendmail(sendEmail, recvEmaila, msg.as_string())
        s.close()
        print("전송완료 하였습니다")
