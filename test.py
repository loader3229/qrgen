import numpy
from PIL import Image
import pyzbar.pyzbar as pyzbar
import random
import os
import sys



def decode_qr(str):
    """
    输入一个使用换行符分隔的二维码01矩阵字符串，对输入的二维码字符串进行解码。
    """
    qr_matrix = []
    str_split = str.split('\n')
    qr_matrix.append([0] * (2*len(str_split[0]) + 8))
    qr_matrix.append([0] * (2*len(str_split[0]) + 8))
    qr_matrix.append([0] * (2*len(str_split[0]) + 8))
    qr_matrix.append([0] * (2*len(str_split[0]) + 8))
    for i in str_split:
        if len(i) == 0:
            continue
        i = "00" + i + "00"
        qr_row = []
        for j in i:
            qr_row.append(int(j))
            qr_row.append(int(j))
        qr_matrix.append(qr_row)
        qr_matrix.append(qr_row)
    qr_matrix.append([0] * (2*len(str_split[0]) + 8))
    qr_matrix.append([0] * (2*len(str_split[0]) + 8))
    qr_matrix.append([0] * (2*len(str_split[0]) + 8))
    qr_matrix.append([0] * (2*len(str_split[0]) + 8))
    qr_matrix_np = 255 - (numpy.array(qr_matrix, dtype=numpy.uint8) * 255)
    qr_img = Image.fromarray(qr_matrix_np)
    decoded = pyzbar.decode(qr_img)
    result = None
    for obj in decoded:
        if obj.type == "QRCODE":
            result = obj.data.decode("utf-8")
            break
    return result

def randomString(len):
    return ''.join(random.choices('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789', k=len))

for version in range(1,41):
    for mask in range(0,8):
        for i in range(0,3+version//10):
            test_str = randomString((2*version-1)*(4*i+2))
            print("正在测试版本", version, "掩码", mask, "字符串长度", len(test_str))
            testfile = open("test.txt","w")
            testfile.write("2\n")
            testfile.write(str(version) + "\n")
            testfile.write(str(mask) + "\n")
            testfile.write(test_str + "\n")
            testfile.close()
            if os.name == "nt":
                os.system("type test.txt | qrgen.exe >nul")
            else:
                os.system("cat test.txt | ./qrgen.bin >nul")
            result = decode_qr(open("qrcode.txt").read())
            if result != test_str:
                print("测试时出错，实际结果为", result, "，预期结果为", test_str)
                sys.exit(1)
