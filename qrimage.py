import numpy
from PIL import Image
import pyzbar.pyzbar as pyzbar
import random
import os
import sys
import io

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
sys.stderr = io.TextIOWrapper(sys.stderr.buffer, encoding='utf-8')



def to_image(str):
    """
    输入一个使用换行符分隔的二维码01矩阵字符串，将输入的二维码字符串存储为图片文件qrcode.png。
    """
    qr_matrix = []
    str_split = str.split('\n')
    for i in range(0,10):
        qr_matrix.append([0] * (5*len(str_split[0]) + 20))
    for i in str_split:
        if len(i) == 0:
            continue
        i = "00" + i + "00"
        qr_row = []
        for j in i:
            qr_row.append(int(j))
            qr_row.append(int(j))
            qr_row.append(int(j))
            qr_row.append(int(j))
            qr_row.append(int(j))
        qr_matrix.append(qr_row)
        qr_matrix.append(qr_row)
        qr_matrix.append(qr_row)
        qr_matrix.append(qr_row)
        qr_matrix.append(qr_row)
    for i in range(0,10):
        qr_matrix.append([0] * (5*len(str_split[0]) + 20))
    qr_matrix_np = 255 - (numpy.array(qr_matrix, dtype=numpy.uint8) * 255)
    qr_img = Image.fromarray(qr_matrix_np)
    qr_img.save("qrcode.png")

def randomString(len):
    return ''.join(random.choices('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789', k=len))

print("这个Python脚本可以用C++二维码生成器生成二维码图片。")
print("请输入二维码版本号（1-40）：")
version = int(input())
if version < 1 or version > 40:
    raise ValueError("版本号错误！")
print("请输入掩码模式（0-7）：")
mask = int(input())
if mask < 0 or mask > 7:
    raise ValueError("掩码模式错误！")
print("请输入要生成的二维码内容：")
content = input()
testfile = open("test.txt","w")
testfile.write("2\n")
testfile.write(str(version) + "\n")
testfile.write(str(mask) + "\n")
testfile.write(content.replace(" ","\x02") + "\n")
testfile.close()
return_value = 1
if os.name == "nt":
    return_value = os.system("type test.txt | qrgen.exe >nul")
else:
    return_value = os.system("cat test.txt | ./qrgen.bin >/dev/null")
if return_value != 0:
    raise ValueError("二维码生成时出现错误，可能是因为找不到qrgen.exe或qrgen.bin，或者生成的二维码内容太长，超出版本限制。")
to_image(open("qrcode.txt").read())
