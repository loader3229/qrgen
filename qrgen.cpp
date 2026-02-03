// 这是由loader3229编写的C++二维码（QR）生成器。支持版本1-40，掩码格式0-7。生成的二维码固定为L级纠错等级。

#include <iostream>
#include <fstream>
#include <cstring>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif
#include <cstdlib>
using namespace std;
char c[10000],d[1000000];
#ifdef _WIN32
HANDLE handle;
#endif
int b[1000][1000];
unsigned int charlimit[41] = {0,
    17,32,53,78,106,134,154,192, // Versions 1-8
    230,271,321,367,425,458,520,586, // Versions 9-16
    644,718,792,858,929,1003,1091,1171, // Versions 17-24
    1273,1367,1465,1528,1628,1732,1840,1952, // Versions 25-32
    2068,2188,2303,2431,2563,2699,2809,2953, // Versions 33-40
};
int datasizes[41] = {0,
    19*8,34*8,55*8,80*8,108*8,136*8,156*8,194*8, // Versions 1-8
    232*8,274*8,324*8,370*8,428*8,461*8,523*8,589*8, // Versions 9-16
    647*8,721*8,795*8,861*8,932*8,1006*8,1094*8,1174*8, // Versions 17-24
    1276*8,1370*8,1468*8,1531*8,1631*8,1735*8,1843*8,1955*8, // Versions 25-32
    2071*8,2191*8,2306*8,2434*8,2566*8,2702*8,2812*8,2956*8, // Versions 33-40
};
int polylengths[41] = {0,
    7,10,15,20,26,18,20,24, // Versions 1-8
    30,18,20,24,26,30,22,24, // Versions 9-16
    28,30,28,28,28,28,30,30, // Versions 17-24
    26,28,30,30,30,30,30,30, // Versions 25-32
    30,30,30,30,30,30,30,30, // Versions 33-40
};
int ecBlocks[41]={0,
    1,1,1,1,1,2,2,2, // Versions 1-8
    2,4,4,4,4,4,6,6, // Versions 9-16
    6,6,7,8,8,9,9,10, // Versions 17-24
    12,12,12,13,14,15,16,17, // Versions 25-32
    18,19,19,20,21,22,24,25, // Versions 33-40
};
int maskFormatInformation[8][15] = {
    {1,1,1, 0,1,1,1, 1,1,0,0, 0,1,0,0}, // Mask 0
    {1,1,1, 0,0,1,0, 1,1,1,1, 0,0,1,1}, // Mask 1
    {1,1,1, 1,1,0,1, 1,0,1,0, 1,0,1,0}, // Mask 2
    {1,1,1, 1,0,0,0, 1,0,0,1, 1,1,0,1}, // Mask 3
    {1,1,0, 0,1,1,0, 0,0,1,0, 1,1,1,1}, // Mask 4
    {1,1,0, 0,0,1,1, 0,0,0,1, 1,0,0,0}, // Mask 5
    {1,1,0, 1,1,0,0, 0,1,0,0, 0,0,0,1}, // Mask 6
    {1,1,0, 1,0,0,1, 0,1,1,1, 0,1,1,0}, // Mask 7
};
int versionInformation[41][18] = {{},{},{},{},{},{},{},
    {0,0,0,1,1,1,1,1,0,0,1,0,0,1,0,1,0,0}, // Version 7
    {0,0,1,0,0,0,0,1,0,1,1,0,1,1,1,1,0,0}, // Version 8
    {0,0,1,0,0,1,1,0,1,0,1,0,0,1,1,0,0,1}, // Version 9
    {0,0,1,0,1,0,0,1,0,0,1,1,0,1,0,0,1,1}, // Version 10
    {0,0,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1,0}, // Version 11
    {0,0,1,1,0,0,0,1,1,1,0,1,1,0,0,0,1,0}, // Version 12
    {0,0,1,1,0,1,1,0,0,0,0,1,0,0,0,1,1,1}, // Version 13
    {0,0,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,1}, // Version 14
    {0,0,1,1,1,1,1,0,0,1,0,0,1,0,1,0,0,0}, // Version 15
    {0,1,0,0,0,0,1,0,1,1,0,1,1,1,1,0,0,0}, // Version 16
    {0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,1}, // Version 17
    {0,1,0,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1}, // Version 18
    {0,1,0,0,1,1,0,1,0,1,0,0,1,1,0,0,1,0}, // Version 19
    {0,1,0,1,0,0,1,0,0,1,1,0,1,0,0,1,1,0}, // Version 20
    {0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,1,1}, // Version 21
    {0,1,0,1,1,0,1,0,0,0,1,1,0,0,1,0,0,1}, // Version 22
    {0,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1,0,0}, // Version 23
    {0,1,1,0,0,0,1,1,1,0,1,1,0,0,0,1,0,0}, // Version 24
    {0,1,1,0,0,1,0,0,0,1,1,1,1,0,0,0,0,1}, // Version 25
    {0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1}, // Version 26
    {0,1,1,0,1,1,0,0,0,0,1,0,0,0,1,1,1,0}, // Version 27
    {0,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,1,0}, // Version 28
    {0,1,1,1,0,1,0,0,1,1,0,0,1,1,1,1,1,1}, // Version 29
    {0,1,1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,1}, // Version 30
    {0,1,1,1,1,1,0,0,1,0,0,1,0,1,0,0,0,0}, // Version 31
    {1,0,0,0,0,0,1,0,0,1,1,1,0,1,0,1,0,1}, // Version 32
    {1,0,0,0,0,1,0,1,1,0,1,1,1,1,0,0,0,0}, // Version 33
    {1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,1,0}, // Version 34
    {1,0,0,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1}, // Version 35
    {1,0,0,1,0,0,1,0,1,1,0,0,0,0,1,0,1,1}, // Version 36
    {1,0,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,0}, // Version 37
    {1,0,0,1,1,0,1,0,1,0,0,1,1,0,0,1,0,0}, // Version 38
    {1,0,0,1,1,1,0,1,0,1,0,1,0,0,0,0,0,1}, // Version 39
    {1,0,1,0,0,0,1,1,0,0,0,1,1,0,1,0,0,1}, // Version 40
};
int poly[100][10000]={{1}};
int blocklengths[10000];
int poly2[100][10000];
int blockdata[100][10000];
int alignmentPos[100];
int m(int x,int y){
    int r=0;
    while(y){
        if(y&1){
            r=r^x;
        }
        y=y>>1;
        x=x<<1;
        if(x&256){
            x=x^285;
        }
    }
    return r;
}

void drawFinder(int x,int y){
    for(int i=0;i<=6;i++){
        for(int j=0;j<=6;j++){
            b[x+i][y+j]=1;
        }
    }
    for(int i=1;i<=5;i++){
        b[x+i][y+1]=b[x+1][y+i]=0;
        b[x+i][y+5]=b[x+5][y+i]=0;
    }
    for(int i=y-1;i<=y+7;i++){
        if(i>=0){
            if(x>0)b[x-1][i]=0;
            b[x+7][i]=0;
        }
    }
    for(int i=x-1;i<=x+7;i++){
        if(i>=0){
            if(y>0)b[i][y-1]=0;
            b[i][y+7]=0;
        }
    }
}
void drawAlignment(int x,int y){
    for(int i=0;i<=4;i++){
        for(int j=0;j<=4;j++){
            b[x+i][y+j]=1;
        }
    }
    for(int i=1;i<=3;i++){
        b[x+i][y+1]=b[x+1][y+i]=0;
        b[x+i][y+3]=b[x+3][y+i]=0;
    }
}
void errorCorrection(int version){
    if(version<=5){
        int l=datasizes[version],l2=0;
        for(int i=0;i<datasizes[version]/8+polylengths[version];i++){
            poly2[0][i]=0;
        }
        for(int i=0;i<datasizes[version]/8;i++){
            for(int j=0;j<8;j++){
                poly2[0][i]=poly2[0][i]*2+d[l2++];
            }
        }
        for(int i=0;i<datasizes[version]/8;i++){
            int coeff=poly2[0][i];
            if(coeff){
                for(int j=1;j<=polylengths[version];j++){
                    poly2[0][i+j] ^= m(poly[polylengths[version]][j],coeff);
                }
            }
        }
        for(int i=0;i<polylengths[version];i++){
            for(int j=7;j>=0;j--){
                if(poly2[0][i+datasizes[version]/8]&(1<<j)){
                    d[l++]=1;
                }else{
                    d[l++]=0;
                }
            }
        }
        return;
    }
    int blocklength=datasizes[version]/8/ecBlocks[version];
    int remaining_data=datasizes[version]/8;
    for(int i=0;i<ecBlocks[version];i++){
        blocklengths[i]=blocklength;
        remaining_data-=blocklength;
        if(remaining_data/(blocklength+1)>=(ecBlocks[version]-i-1))blocklength++;
        cout<<blocklengths[i]<<" ";
    }
    cout<<endl;
    int l=0,l2=0;
    for(int block=0;block<ecBlocks[version];block++){
        for(int i=0;i<blocklengths[block]+polylengths[version];i++){
            poly2[block][i]=0;
        }
        for(int i=0;i<blocklengths[block];i++){
            for(int j=0;j<8;j++){
                poly2[block][i]=poly2[block][i]*2+d[l2++];
            }
            blockdata[block][i]=poly2[block][i];
        }
        for(int i=0;i<blocklengths[block];i++){
            int coeff=poly2[block][i];
            if(coeff){
                for(int j=1;j<=polylengths[version];j++){
                    poly2[block][i+j] ^= m(poly[polylengths[version]][j],coeff);
                }
            }
        }
    }
    for(int i=0;i<blocklength;i++){
        for(int block=0;block<ecBlocks[version];block++){
            if(i<blocklengths[block]){
                for(int j=7;j>=0;j--){
                    if(blockdata[block][i]&(1<<j)){
                        d[l++]=1;
                    }else{
                        d[l++]=0;
                    }
                }
            }
        }
    }
    for(int i=0;i<polylengths[version];i++){
        for(int block=0;block<ecBlocks[version];block++){
            for(int j=7;j>=0;j--){
                if(poly2[block][i+blocklengths[block]]&(1<<j)){
                    d[l++]=1;
                }else{
                    d[l++]=0;
                }
            }
        }
    }
}
int maskPattern(int x,int y,int mask){
    switch(mask){
        case 0: return (x+y)%2==0;
        case 1: return x%2==0;
        case 2: return y%3==0;
        case 3: return (x+y)%3==0;
        case 4: return (x/2+y/3)%2==0;
        case 5: return (x*y)%2+(x*y)%3==0;
        case 6: return ((x*y)%2+(x*y)%3)%2==0;
        case 7: return ((x+y)%2+(x*y)%3)%2==0;
    }
    return 0;
}
int main(){
    int tmp=1;
    for(int i=0;i<50;i++){
        for(int j=0;j<=i;j++){
            poly[i+1][j]=poly[i+1][j]^poly[i][j];
            poly[i+1][j+1]=poly[i+1][j+1]^m(tmp,poly[i][j]);
        }
        tmp=tmp<<1;
        if(tmp&256){
            tmp=tmp^285;
        }
    }
    int output_mode=0;
    #ifdef _WIN32
    system("chcp 65001");
    system("color f0");
    system("cls");
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cout<<"C++ 二维码生成器 by loader3229"<<endl;
    cout<<"现在正在Windows系统下，可以直接在Windows控制台输出黑白二维码。您也可以用01矩阵的形式输出二维码。"<<endl;
    cout<<"请输入输出模式（0：Windows控制台直接输出，1：01矩阵输出到控制台，2：01矩阵输出到qrcode.txt）：";
    cin>>output_mode;
    if(output_mode<0||output_mode>2){
        cout<<"输出模式错误！"<<endl;
        return 1;
    }
    #else
    cout<<"C++ 二维码生成器 by loader3229"<<endl;
    cout<<"现在不在Windows系统下，只能用01矩阵的形式输出二维码。"<<endl;
    cout<<"请输入输出模式（1：01矩阵输出到控制台，2：01矩阵输出到qrcode.txt）：";
    cin>>output_mode;
    if(output_mode<1||output_mode>2){
        cout<<"输出模式错误！"<<endl;
        return 1;
    }
    #endif
    cout<<"请输入二维码版本号（1-40）：";
    int version;
    cin>>version;
    if(version<1||version>40){
        cout<<"版本号错误！"<<endl;
        return 1;
    }
    // Init Matrix
    int size=version*4+17;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            b[i][j]=-1;
        }
    }
    // Finder Pattern
    drawFinder(0,0);
    drawFinder(0,size-7);
    drawFinder(size-7,0);
    // Timing Pattern
    for(int i=8;i<size-8;i++){
        b[6][i]=b[i][6]=(i%2==0);
    }
    // Alignment Pattern
    if(version>=2){
        alignmentPos[0]=4;
        alignmentPos[1]=size-9;
        if(version>=7 && version<=13){
            alignmentPos[2]=(size-4)/2;
        }
        if(version>=14 && version<=20){
            alignmentPos[2]=((version-2)/3)*4+8;
            alignmentPos[3]=((version-2)/3)*2+version*2+8;
        }
        if(version>=21 && version<=27){
            int j = (version/2)*2+2;
            for(int i=1;i<4;i++){
                alignmentPos[i+1]=alignmentPos[i]-j;
            }
        }
        if(version>=28 && version<=34){
            int j = (version/3)*2+6;
            for(int i=1;i<5;i++){
                alignmentPos[i+1]=alignmentPos[i]-j;
            }
        }
        if(version>=35){
            int j = (version/3)*2+2;
            for(int i=1;i<6;i++){
                alignmentPos[i+1]=alignmentPos[i]-j;
            }
        }
        for(int i=0;alignmentPos[i];i++){
            for(int j=0;alignmentPos[j];j++){
                if(i+j>=2)drawAlignment(alignmentPos[i],alignmentPos[j]);
            }
        }
    }
    
    // Version Information
    if(version>=7){
        b[size-9][5]=b[5][size-9]=versionInformation[version][0];
        b[size-10][5]=b[5][size-10]=versionInformation[version][1];
        b[size-11][5]=b[5][size-11]=versionInformation[version][2];
        b[size-9][4]=b[4][size-9]=versionInformation[version][3];
        b[size-10][4]=b[4][size-10]=versionInformation[version][4];
        b[size-11][4]=b[4][size-11]=versionInformation[version][5];
        b[size-9][3]=b[3][size-9]=versionInformation[version][6];
        b[size-10][3]=b[3][size-10]=versionInformation[version][7];
        b[size-11][3]=b[3][size-11]=versionInformation[version][8];
        b[size-9][2]=b[2][size-9]=versionInformation[version][9];
        b[size-10][2]=b[2][size-10]=versionInformation[version][10];
        b[size-11][2]=b[2][size-11]=versionInformation[version][11];
        b[size-9][1]=b[1][size-9]=versionInformation[version][12];
        b[size-10][1]=b[1][size-10]=versionInformation[version][13];
        b[size-11][1]=b[1][size-11]=versionInformation[version][14];
        b[size-9][0]=b[0][size-9]=versionInformation[version][15];
        b[size-10][0]=b[0][size-10]=versionInformation[version][16];
        b[size-11][0]=b[0][size-11]=versionInformation[version][17];
    }

    cout<<"请输入掩码模式（0-7）：";
    int mask;
    cin>>mask;
    if(mask<0||mask>7){
        cout<<"掩码模式错误！"<<endl;
        return 1;
    }

    // Format Information
    for(int i=0;i<=5;i++){
        b[8][i]=maskFormatInformation[mask][i];
        b[i][8]=maskFormatInformation[mask][14-i];
    }
    for(int i=0;i<=7;i++){
        b[8][size-i-1]=maskFormatInformation[mask][14-i];
        b[size-i-1][8]=maskFormatInformation[mask][i];
    }
    b[size-8][8]=1;
    b[8][7]=maskFormatInformation[mask][6];
    b[8][8]=maskFormatInformation[mask][7];
    b[7][8]=maskFormatInformation[mask][8];
    
    cout<<"请输入内容，不超过"<<charlimit[version]<<"个字符，请用Ctrl+B代表空格：";
    cin>>c;
    if(strlen(c)>charlimit[version]){
        cout<<"字符的数量超限"<<endl; 
        return 1;
    }
    // Data Codewords
    int l=0;
    d[l++]=0;
    d[l++]=1;
    d[l++]=0;
    d[l++]=0;
    int len=strlen(c);
    for(int i=(version>=10?15:7);i>=0;i--){
        if(len&(1<<i)){
            d[l++]=1;
        }else{
            d[l++]=0;
        }
    }
    for(int i=0;i<len;i++){
        if(c[i]==2)c[i]=' ';
        for(int j=7;j>=0;j--){
            if(c[i]&(1<<j)){
                d[l++]=1;
            }else{
                d[l++]=0;
            }
        }
    }
    d[l++]=0;
    d[l++]=0;
    d[l++]=0;
    d[l++]=0;
    while(l<datasizes[version]){
        d[l++]=1;
        d[l++]=1;
        d[l++]=1;
        d[l++]=0;
        d[l++]=1;
        d[l++]=1;
        d[l++]=0;
        d[l++]=0;
        d[l++]=0;
        d[l++]=0;
        d[l++]=0;
        d[l++]=1;
        d[l++]=0;
        d[l++]=0;
        d[l++]=0;
        d[l++]=1;
    }
    errorCorrection(version);
    int fillType=1;
    int index=0;
    for(int i=size-2;i>=0;i-=2){
        if(i==5)i=4;
        if(fillType){
            for(int j=size-1;j>=0;j--){
                if(b[j][i+1]==-1){
                    b[j][i+1]=d[index++]^maskPattern(j,i+1,mask);
                }
                if(b[j][i]==-1){
                    b[j][i]=d[index++]^maskPattern(j,i,mask);
                }
            }
        }else{
            for(int j=0;j<size;j++){
                if(b[j][i+1]==-1){
                    b[j][i+1]=d[index++]^maskPattern(j,i+1,mask);
                }
                if(b[j][i]==-1){
                    b[j][i]=d[index++]^maskPattern(j,i,mask);
                }
            }
        }
        fillType=1-fillType;
    }
    cout<<index<<endl;
    #ifdef _WIN32
    if(output_mode==0){
        cout<<endl<<endl;
        for(int j=0;j<size;j++){
            cout<<"    ";
            for(int k=0;k<size;k++){
                if(b[j][k]){
                    SetConsoleTextAttribute(handle,15);
                }else{
                    SetConsoleTextAttribute(handle,240);
                }
                cout<<"  ";
                SetConsoleTextAttribute(handle,240);
                if(version<5)Sleep(10-version*2);
            }
            SetConsoleTextAttribute(handle,240);
            cout<<endl;
        }
        cout<<endl<<endl;
        system("pause");
    }else
    #endif
    if(output_mode==1){
        cout<<"正在用01矩阵的形式输出二维码，0为白色，1为黑色。"<<endl;
        for(int j=0;j<size;j++){
            for(int k=0;k<size;k++){
                cout<<b[j][k];
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }else if(output_mode==2){
        cout<<"正在用01矩阵的形式输出二维码到qrcode.txt，0为白色，1为黑色。"<<endl;
        ofstream fout("qrcode.txt");
        for(int j=0;j<size;j++){
            for(int k=0;k<size;k++){
                fout<<b[j][k];
            }
            fout<<endl;
        }
        fout.close();
    }
    return 0;
}
