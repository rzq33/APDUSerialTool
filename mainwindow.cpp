#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <tool.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mingwen_input_lineEdit->setMaxLength(16);//DES明文最长8字节
    ui->miwen_input_lineEdit->setMaxLength(16);//DES加密密钥最长8字节
    ui->jiemi_key_input_lineEdit->setMaxLength(16);//DES解密密钥最长8字节
    ui->tdesmingwen_input->setMaxLength(16);//3DES明文最长8字节
    ui->tdeskey_input->setMaxLength(32);//3DES加密密钥最长16字节

    //查找可用的串口
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))//读写方式打开串口
        {
            ui->PortBox->addItem(serial.portName());//添加串口号到portbox
            serial.close();//关闭串口等待人为打开           
        }

    }
    qDebug()<<"初始化查找可用串口成功";
    ui->textEdit->insertPlainText(tr("初始化成功=>>"));
    ui->textEdit->insertPlainText("\n");

    //设置波特率下拉菜单默认显示第4项，即115200
    ui->BaudBox->setCurrentIndex(4);
    ui->pushButton->setEnabled(false);
    ui->pushButton_SD->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->SendButton->setEnabled(false);
    ui->ClearButton->setEnabled(false);
    ui->huanhangButton->setEnabled(false);
    ui->APDUSendButton->setEnabled(false);
    ui->resetButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    ui->newButton->setEnabled(false);
    ui->CreditForLoad_Btn->setEnabled(false);//设置各按钮初始为不可点击
    ui->Sha1Result_2->setEnabled(false);
    QObject::connect(ui->Sha1Button, SIGNAL(clicked()), this, SLOT(Sha1Bt()));//连接SHA1按钮信号槽
}

MainWindow::~MainWindow()
{
    delete ui;
}


//打开，关闭串口函数
void MainWindow::on_OpenSerialButton_clicked()
{
    if(ui->OpenSerialButton->text() == tr("打开串口"))
    {

        //设置串口名
        serial->setPortName(ui->PortBox->currentText());
        //打开串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        switch (ui->BaudBox->currentText().toInt())
        {
        case 9600:
            serial->setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            serial->setBaudRate(QSerialPort::Baud19200);
            break;
        case 38400:
            serial->setBaudRate(QSerialPort::Baud38400);
            break;
        case 57600:
            serial->setBaudRate(QSerialPort::Baud57600);
            break;
        case 115200:
            serial->setBaudRate(QSerialPort::Baud115200);
            break;
        default:
            break;
        }
        //设置数据位数
        switch (ui->BitBox->currentText().toInt())
        {
        case 8:
            serial->setDataBits(QSerialPort::Data8);//设置数据位8
            break;
        default:
            break;
        }
        //设置校验位
        switch (ui->ParityBox->currentText().toInt())
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        default:
            break;
        }
        //设置停止位
        switch (ui->BitBox->currentText().toInt())
        {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);//停止位设置为1
            break;
        default:
            break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制

        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->SearchSerialButton->setEnabled(false);
        ui->pushButton->setEnabled(true);
        ui->pushButton_SD->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->SendButton->setEnabled(true);
        ui->ClearButton->setEnabled(true);
        ui->huanhangButton->setEnabled(true);
        ui->APDUSendButton->setEnabled(true);
        ui->resetButton->setEnabled(true);
        ui->clearButton->setEnabled(true);
        ui->newButton->setEnabled(true);
        ui->CreditForLoad_Btn->setEnabled(true);//串口打开后，串口相关设置不可更改，功能相关按钮设置可用
        ui->OpenSerialButton->setText(tr("关闭串口"));


        //连接信号槽
        QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(ReadData()));

        //提示打开成功
        //ui->textEdit->setText(tr("打开串口成功!"));
        //ui->textEdit->insertPlainText("\n");
        qDebug()<<"打开串口设置成功";
        ui->textEdit->insertPlainText(tr("打开串口成功=>>"));
        ui->textEdit->insertPlainText("\n");
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        //serial->deleteLater();

        //恢复菜单使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->SearchSerialButton->setEnabled(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_SD->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->SendButton->setEnabled(false);
        ui->ClearButton->setEnabled(false);
        ui->huanhangButton->setEnabled(false);
        ui->APDUSendButton->setEnabled(false);
        ui->resetButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->newButton->setEnabled(false);
        ui->CreditForLoad_Btn->setEnabled(false);
        ui->OpenSerialButton->setText(tr("打开串口"));
        qDebug()<<"关闭串口设置成功";
        ui->textEdit->insertPlainText(tr("关闭串口成功=>>"));
        ui->textEdit->insertPlainText("\n");

    }
}


//发送按钮槽函数
void MainWindow::on_SendButton_clicked()
{
    QString str = ui->textEdit_2->toPlainText();//从textEdit_2得到字符串
    QByteArray senddata;
    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serial->write(senddata);
    qDebug()<<"发送成功";
    ui->textEdit->insertPlainText(tr("发送成功=>>"));
    ui->textEdit->insertPlainText("\n");

}

//APDU组包函数
void MainWindow::APDUPack(QByteArray APDU, QByteArray &RevBuff)
{
    int i = 0;
    RevBuff[0] = 0x02;
    RevBuff[1] = 0x00; //发送标志
    RevBuff[2] = 0x0B;RevBuff[3] = 0x01;RevBuff[4] = 0x0E;RevBuff[5] = 0x01;
    RevBuff[6] = 0x34;RevBuff[7] = 0x00;
    RevBuff[8] = (char)(APDU.length() & 0xFF);
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[9 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    unsigned char crcsrc[RevBuff.length()-1];
    for (int j=0;j<RevBuff.length()-1;j++)
    {
        crcsrc[j]=(unsigned char)RevBuff[j+1];
    }
    int crcdst=(int)crc16(crcsrc,sizeof(crcsrc));
    QByteArray out1=intToByte(crcdst);
    RevBuff[9+i] = out1[0];
    RevBuff[10+i] = 0x03;
}

//APDU发送(新协议)
void MainWindow::on_APDUSendButton_clicked()
{
    //int i = 0;
    QString str = ui->textEdit_3->toPlainText();
    QByteArray APDU;
    StringToHex(str,APDU);
    QByteArray RevBuff;//接收缓存
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"发送APDU成功";
    ui->textEdit->insertPlainText(tr("APDU发送成功=>>"));
    ui->textEdit->insertPlainText("\n");
}

//读取接收到的所有信息
void MainWindow::ReadData()
{
    buf.clear();
    qint8 outChar;
    QString str;
    qDebug()<<serial->bytesAvailable();  //显示缓冲区接收到的数据长度
    buf = serial->readAll();

    if (0x02==buf[0]  && buf[buf.length()-1] ==0x03)
    {
        buf2.clear();
    }
    else if (0x02==buf[0]  && buf[buf.length()-1] != 0x03)
    {
        buf2 = buf;
        buf.clear();
    }
    else if (buf[0] != 0x02 &&  0x03 == buf[buf.length()-1])
    {
        buf2 +=buf;
    }
    else if(buf[0] != 0x02 && buf[buf.length()-1] != 0x03)
    {
        buf2 += buf;
        buf.clear();  //每次接受完后应把临时储存数据的变量清空
    }                 //数据出现接收分段的情况，组包，使用全局变量储存，待数据接收完整再打印

    QDataStream out(&buf,QIODevice::ReadWrite);
    ui->textEdit->insertPlainText(tr("读取信息为=>>"));
    ui->textEdit->insertPlainText("\n");
    while(!out.atEnd())
    {
        outChar = 0;
        out>>outChar;   //每字节填充一次，直到结束
        //十六进制的转换
        str = QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0'));
        ui->textEdit->insertPlainText(str.toUpper());//大写
        ui->textEdit->insertPlainText(" ");//每发送两个字符后添加一个空格
        ui->textEdit->moveCursor(QTextCursor::End);
    }
    ui->textEdit->insertPlainText("\n");
}


//十进制转十六进制算法
void MainWindow::StringToHex(QString str, QByteArray &senddata) //字符串转换为十六进制数据0-F
{
    int hexdata,lowhexdata;
    int hexdatalen;
    hexdatalen = 0;
    int len;
    len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;

    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}


//十进制转十六进制具体转换函数
char MainWindow::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return ch-ch;//不在0-f范围内的会发送成0
}


//计算BCC校验码(新协议不需要)
char MainWindow::CheckBCC(QByteArray nums, int firstIndex, int lastIndex)
{
    char tmp = 0x00;
    for (int i = firstIndex; i <= lastIndex; i++)
    {
        tmp ^= nums[i];    //第一位到最后一位依次计算异或
    }
    return tmp;
}


//延时函数(单位是毫秒)
void MainWindow::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


//寻卡指令
void MainWindow::on_pushButton_3_clicked()
{
    QString str = ui->textEdit_FindCard->toPlainText();//得到字符串
    QByteArray senddata;
    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serial->write(senddata);
    qDebug()<<"寻卡成功";
}


//获取卡号
void MainWindow::on_pushButton_4_clicked()
{
    QString str = ui->textEdit_GetID->toPlainText();//得到字符串
    QByteArray senddata;
    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serial->write(senddata);
    qDebug()<<"获取卡序列号成功";
}


//发送RATS
void MainWindow::on_pushButton_5_clicked()
{
    QString str = ui->textEdit_RATS->toPlainText();//得到字符串
    QByteArray senddata;
    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serial->write(senddata);
    qDebug()<<"RATS成功";
}


//发送PPS指令(可省略)
void MainWindow::on_pushButton_6_clicked()
{
    QString str = ui->textEdit_PPS->toPlainText();//得到字符串
    QByteArray senddata;
    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serial->write(senddata);
    qDebug()<<"PPS成功";
}


//发送选择MF命令
void MainWindow::on_pushButton_clicked()
{
    QString str = ui->textEdit_MF->toPlainText();//得到字符串
    int i = 0;
    QByteArray APDU;
    StringToHex(str,APDU);
    QByteArray RevBuff;//接收缓存
    RevBuff[0] = 0x02;
    RevBuff[1] = 0x00; //发送标志
    RevBuff[2] = 0x0B;RevBuff[3] = 0x01;RevBuff[4] = 0x0E;RevBuff[5] = 0x01;
    RevBuff[6] = 0x34;RevBuff[7] = 0x00;
    RevBuff[8] = (char)(APDU.length() & 0xFF);
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[9 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    unsigned char crcsrc[RevBuff.length()-1];
    for (int j=0;j<RevBuff.length()-1;j++)
    {
        crcsrc[j]=(unsigned char)RevBuff[j+1];
    }
    int crcdst=(int)crc16(crcsrc,sizeof(crcsrc));
    QByteArray out1=intToByte(crcdst);
    RevBuff[9+i] = out1[0];
    RevBuff[10+i] = 0x03;
    serial->write(RevBuff);

    qDebug()<<"选择MF成功";
}


//发送接触式PSAM卡上电命令
void MainWindow::on_pushButton_SD_clicked()
{    
    QString str = ui->textEdit_SD->toPlainText();//得到字符串
    QByteArray senddata;

    StringToHex(str,senddata);//将str字符串转换为16进制的形式

    serial->write(senddata);
    qDebug()<<"RATS成功";
}


//重新查找可用串口
void MainWindow::on_SearchSerialButton_clicked()
{
    ui->PortBox->clear();
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))//读写方式打开串口
        {
            ui->PortBox->addItem(serial.portName());//重新查找可用串口号，添加到portbox
            serial.close();//关闭串口等待人为打开

        }
    }
    qDebug()<<"查找可用串口成功";
    ui->textEdit->insertPlainText(tr("查找可用串口成功=>>"));
    ui->textEdit->insertPlainText("\n");
}


//清空接收文本框
void MainWindow::on_ClearButton_clicked()
{
    ui->textEdit->setText(tr(""));
    qDebug()<<"清空成功";
}


//换行按钮
void MainWindow::on_huanhangButton_clicked()
{
    ui->textEdit->insertPlainText("\n");
}


//Hash-SHA1算法(QT库中需要密钥的HmacSHA1哈希算法)
QByteArray hmacSha1(QByteArray key, QByteArray baseString)
 {
     int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
     if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
         key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
     }
     QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
     QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "/"
     for (int i = 0; i < key.length(); i++) {
         innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
         outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
     }
     QByteArray total = outerPadding;
     QByteArray part = innerPadding;
     part.append(baseString);
     total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
     QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
          // 注意——>把字符串hashed转换为Hex，内存中的ASCII码arrayFromHexString
     QByteArray arrayFromHexString = QByteArray::fromHex(hashed.toHex());
     qDebug()<<"hmacSha1内存中的ASCII码 arrayFromHexString:"<<arrayFromHexString.toHex().toUpper();
     return arrayFromHexString;
}



//SHA1(connect信号槽连接)
void MainWindow::Sha1Bt()
{
    auto Message = ui->Sha1Message->toPlainText();
    QString Key = ui->Sha1Key->toPlainText();
    QByteArray mes = Message.toLatin1();
    QByteArray key = Key.toLatin1();
    QByteArray arrayFromHexString =hmacSha1(key,mes);
    QString result = arrayFromHexString.toHex().toUpper();
    ui->Sha1Result->clear();
    ui->Sha1Result->insertPlainText(result);//此段是HmacSHA1加密方式
    qDebug()<<"SHA1成功";
}



//获取AID部分函数
void MainWindow::GetAID(QByteArray indata,QByteArray &outdata)
{
    int i;
    for(i = 0;i<indata.length();i++)
    {
        if (0x4F == indata[i])  //第一个tag4F后内容是AID
        {
            char len = indata[i+1];
            for(int j = 0;j<=(int)len;j++)
            {
                outdata[j]=indata[i+1+j];
            }
            break;
        }
    }
}


//GPO组包函数
void MainWindow::GetGPO(QByteArray indata1,QByteArray &outdata1)
{
    int i;
    int n=0;
    for(i = 0;i<indata1.length();i++)
    {
        if (indata1[i] == 0x9F && indata1[i+1] == 0x38)//检测是否有9F38的GPOtag,有再继续组包
        {
            char len = indata1[i+2];
            for(int j = 0;j<(int)len;j+=0)
            {
                if (indata1[i+3+j] == 0x9F && indata1[i+3+j+1] == 0x66)//终端交易属性9F66
                {
                    outdata1[n]=0x26;
                    outdata1[n+1]=0x00;
                    outdata1[n+2]=0x00;
                    outdata1[n+3]=0x00;
                    n+=4;
                    j+=3;
                    continue;
                }
                if (indata1[i+3+j] == 0xDF && indata1[i+3+j+1] == 0x60)//特殊应用DF60
                {
                    outdata1[n]=0x00;
                    n+=1;
                    j+=3;
                    continue;
                }
                if (indata1[i+3+j] == 0xDF && indata1[i+3+j+1] == 0x69)//特殊应用DF69
                {
                    outdata1[n]=0x00;
                    n+=1;
                    j+=3;
                    continue;
                }
                if (indata1[i+3+j]==0x9F && indata1[i+3+j+1]==0x02)//授权金额9F02
                {
                    outdata1[n]=0x00;
                    outdata1[n+1]=0x00;
                    outdata1[n+2]=0x00;
                    outdata1[n+3]=0x00;
                    outdata1[n+4]=0x00;
                    outdata1[n+5]=0x00;
                    n+=6;
                    j+=3;
                    continue;
                }
                if (indata1[i+3+j]==0x9F && indata1[i+3+j+1]==0x03)//其他金额9F03
                {
                    outdata1[n]=0x00;
                    outdata1[n+1]=0x00;
                    outdata1[n+2]=0x00;
                    outdata1[n+3]=0x00;
                    outdata1[n+4]=0x00;
                    outdata1[n+5]=0x00;
                    n+=6;
                    j+=3;
                    continue;
                }
                if (indata1[i+3+j]==0x9F && indata1[i+3+j+1]==0x1A)//终端国家代码9F1A
                {
                    outdata1[n]=0x01;
                    outdata1[n+1]=0x56;
                    n+=2;
                    j+=3;
                    continue;
                }
                if (indata1[i+3+j]==0x95)//终端验证结果95
                {
                    outdata1[n]=0x00;
                    outdata1[n+1]=0x00;
                    outdata1[n+2]=0x00;
                    outdata1[n+2]=0x00;
                    outdata1[n+4]=0x00;
                    n+=5;
                    j+=2;
                    continue;
                }
                if (indata1[i+3+j]==0x5F && indata1[i+3+j+1]==0x2A)//交易货币代码5F2A
                {
                    outdata1[n]=0x01;
                    outdata1[n+1]=0x56;
                    n+=2;
                    j+=3;
                    continue;
                }
                if (indata1[i+3+j]==0x9A)//交易日期9A
                {
                    outdata1[n]=0x19;
                    outdata1[n+1]=0x03;
                    outdata1[n+2]=0x22;
                    n+=3;
                    j+=2;
                    continue;
                }
                if (indata1[i+3+j]==0x9C)//交易类型9C
                {
                    outdata1[n]=0x00;
                    n+=1;
                    j+=2;
                    continue;
                }
                if (indata1[i+3+j]==0x9F && indata1[i+3+j+1]==0x37)//不可预知数9F37
                {
                    outdata1[n]=0x11;
                    outdata1[n+1]=0x22;
                    outdata1[n+2]=0x33;
                    outdata1[n+3]=0x44;
                    n+=4;
                    j+=3;
                    continue;
                }
            }
            break;
        }
    }
}


//读记录
void MainWindow::ReadRecord(QByteArray indata1)
{
    QByteArray AFL;
    for (int i =0;i<indata1.length();i++)
    {
        if (indata1[i]==0x94)             //记录文件tag94
        {
            int len = (int)indata1[i+1];

            for (int j=0;j<len;j++)
            {
                AFL[j]=indata1[i+2+j];
            }
            break;
        }
    }
    int AFLlen=AFL.length()/4;
    QByteArray APDU;
    QByteArray RevBuff;
    for (int i=0;i<AFLlen;i++)
    {
        int temp=(int)AFL[4*i+2]-(int)AFL[4*i+1]+1;//计算该读取记录文件的位置
        for (int m=0;m<temp;m++)
        {
            APDU[0]=0x00;
            APDU[1]=0xB2;
            APDU[3]=AFL[0+i*4]+0x04;
            APDU[2]=AFL[1+i*4]+m;
            RevBuff[0] = 0x02;
            RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
            RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
            RevBuff[3] = 0x37;
            RevBuff[4] = 0x31;
            RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
            RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
            int j;
            for (j=0; j < APDU.length(); j++)
            {
                RevBuff[7 + j] = APDU[j];//APDU指令内容 从RevBuff[7]开始
            }
            RevBuff[7+j] = 0x03;
            RevBuff[8+j] = CheckBCC(RevBuff,0,7+j);
            serial->write(RevBuff);
            qDebug()<<"发送read recode成功";
            APDU.clear();
            RevBuff.clear();
            Sleep(500);
        }
    }

}



//DES encryption
void MainWindow::on_encryption_btn_clicked()
{
    QString mingwen = ui->mingwen_input_lineEdit->text();
    QString user_key = ui->miwen_input_lineEdit->text();
    QByteArray mingwenary;
    StringToHex(mingwen,mingwenary);
    QByteArray keyary;
    StringToHex(user_key,keyary);
    unsigned char mingwenchar[8];
    unsigned char keychar[8];
    memcpy(mingwenchar,mingwenary,8);
    memcpy(keychar,keyary,8);
    unsigned char msgoutch[8];
    Des(mingwenchar,msgoutch,keychar,0);
    char* out1=(char*)msgoutch;
    QByteArray out2=QByteArray(out1,8);
    ui->miwen_output_lineEdit->clear();
    ui->miwen_output_lineEdit->setText(out2.toHex().toUpper());
}


//DES decryption
void MainWindow::on_decryption_btn_clicked()
{
    QString key_test = ui->jiemi_key_input_lineEdit->text();
    QString miwen = ui->miwen_output_lineEdit->text();
    QByteArray key_testary;
    QByteArray miwenary;
    StringToHex(key_test,key_testary);
    StringToHex(miwen,miwenary);
    unsigned char miwenchar[8];
    unsigned char keytestchar[8];
    memcpy(miwenchar,miwenary,8);
    memcpy(keytestchar,key_testary,8);
    unsigned char msgoutch[8];
    Des(miwenchar,msgoutch,keytestchar,1);
    char* out1=(char*)msgoutch;
    QByteArray out2=QByteArray(out1,8);
    ui->jiemi_output_lineEdit->clear();
    ui->jiemi_output_lineEdit->setText(out2.toHex().toUpper());
}


//3DES encryption
void MainWindow::on_tdesencryption_btn_clicked()
{
    QString mingwen = ui->tdesmingwen_input->text();
    QString user_key = ui->tdeskey_input->text();
    QByteArray mingwenary;
    StringToHex(mingwen,mingwenary);
    QByteArray keyary;
    StringToHex(user_key,keyary);
    unsigned char mingwenchar[8];
    unsigned char keychar[16];
    memcpy(mingwenchar,mingwenary,8);
    memcpy(keychar,keyary,16);
    unsigned char msgoutch[8];
    CurCalc_3DES_Encrypt(keychar,mingwenchar,msgoutch);
    char* out1=(char*)msgoutch;
    QByteArray out2=QByteArray(out1,8);
    ui->tdesmiwen_output->clear();
    ui->tdesmiwen_output->setText(out2.toHex().toUpper());
}

//DES_MAC
void MainWindow::on_desmac_btn_clicked()
{
    QString mingwen = ui->desmac_input->text();
    QString init = ui->desmac_init_input->text();
    QString mackey=ui->desmac_key_input->text();  //取输入的明文，密钥，初始向量
    QByteArray mingwenary;
    StringToHex(mingwen,mingwenary);
    QByteArray keyary;
    StringToHex(mackey,keyary);
    QByteArray initary;
    StringToHex(init,initary);
    int buf_size=mingwenary.size();
    unsigned char mingwenchar[buf_size];
    unsigned char keychar[16];
    unsigned char initchar[8];
    memcpy(mingwenchar,mingwenary,buf_size);
    memcpy(keychar,keyary,16);
    memcpy(initchar,initary,8);
    unsigned char msgoutch[4];                     //转为unsigned char
    PBOC_DES_MAC(initchar,mingwenchar,buf_size,keychar,msgoutch);//计算DES_MAC
    char* out1=(char*)msgoutch;
    QByteArray out2=QByteArray(out1,4);
    ui->desmac_output->clear();
    ui->desmac_output->setText(out2.toHex().toUpper());//输出到文本框
}

//3DES_MAC
void MainWindow::on_tdesmac_btn_clicked()
{
    QString mingwen = ui->tdesmac_input->text();
    QString init = ui->tdesmac_init_input->text();
    QString mackey=ui->tdesmac_key_input->text();   //读取初始向量，数据源，key
    QByteArray mingwenary;
    StringToHex(mingwen,mingwenary);
    QByteArray keyary;
    StringToHex(mackey,keyary);
    QByteArray initary;
    StringToHex(init,initary);//读取到的值全部转为QByteArray
    int buf_size=mingwenary.size();
    unsigned char mingwenchar[buf_size];
    unsigned char keychar[16];
    unsigned char initchar[8];
    memcpy(mingwenchar,mingwenary,buf_size);
    memcpy(keychar,keyary,16);
    memcpy(initchar,initary,8);
    unsigned char msgoutch[4]; //再转为unsigned char,方便计算
    PBOC_3DES_MAC(initchar,mingwenchar,buf_size,keychar,msgoutch); //计算
    char* out1=(char*)msgoutch;
    QByteArray out2=QByteArray(out1,4);
    ui->tdesmac_output->clear();
    ui->tdesmac_output->setText(out2.toHex().toUpper());//转为QByteArray方便16进制输出
}

//CRC16(MODBUS)
void MainWindow::on_CRCwork_btn_clicked()
{
    QString src = ui->CRC_input->text();
    QByteArray srctemp;
    StringToHex(src,srctemp);
    unsigned char crcsrc[srctemp.size()];
    memcpy(crcsrc,srctemp,srctemp.size());
    unsigned int crcdst;
    crcdst=crc16(crcsrc,sizeof(crcsrc));
    int out1=(int)crcdst;
    QByteArray out2;
    out2=intToByte(out1);
    ui->CRC_output->clear();
    ui->CRC_output->setText(out2.toHex().toUpper());
}



//卡复位
void MainWindow::on_resetButton_clicked()
{

    //寻卡
    QString str = ui->textEdit_FindCard->toPlainText();//得到字符串
    QByteArray senddata;
    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serial->write(senddata);
    qDebug()<<"寻卡成功";
    str.clear();
    senddata.clear();
    Sleep(500);


    //获取卡号
    str = ui->textEdit_GetID->toPlainText();//得到字符串
    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serial->write(senddata);
    qDebug()<<"获取卡序列号成功";
    str.clear();
    senddata.clear();
    Sleep(500);


    //RATS
    str = ui->textEdit_RATS->toPlainText();//得到字符串
    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serial->write(senddata);
    qDebug()<<"RATS成功";
    str.clear();
    senddata.clear();
    Sleep(500);
}

//洗卡
void MainWindow::on_clearButton_clicked()
{
    //get challenge
    int i =0;
    QByteArray APDU;
    APDU[0]=0x00;
    APDU[1]=0x84;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x08;
    QByteArray RevBuff;//接收缓存
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"获取随机数成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);
/*
    //DES 主控密钥为8位时使用DES（一般为初始白卡）
    QByteArray temp;
    temp.resize(8);
    for(i=0;i<8;i++)
    {
        temp[i]=buf[i+8]; //前八位为返回报文头，略过
    }
    qDebug()<<"随机数为："<<temp.toHex().toUpper();//temp为明文
    unsigned char desmingwen[8];
    memcpy(desmingwen,temp,8);
    unsigned char renzhenkey[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};//外部认证密钥在此处修改
    unsigned char desout[8];
    Des(desmingwen,desout,renzhenkey,0);
    char* desout1=(char*)desout;
    QByteArray desout2=QByteArray(desout1,8);
    qDebug()<<"DES:"<<desout2.toHex().toUpper();
    qDebug()<<"计算DES成功";
    Sleep(10);
*/
    //3DES  主控密钥16位时使用3DES
    QByteArray temp2;
    temp2.resize(8);
    for(i=0;i<8;i++)
    {
        temp2[i]=buf[i+8]; //前八位为返回报文头，略过
    }
    qDebug()<<"随机数为："<<temp2.toHex().toUpper();//temp为明文
    unsigned char tdesmingwen[8];
    memcpy(tdesmingwen,temp2,8);
    unsigned char renzhenkey2[]={0x58,0xB0,0xFD,0x07,0xC1,0xFD,0x26,0x6D,0x68,0x19,0x37,0x26,0x45,0xCD,0x67,0xAE};//外部认证密钥在此处修改(当前为测试卡标准二次分散密钥)
    unsigned char tdesout[8];
    CurCalc_3DES_Encrypt(renzhenkey2,tdesmingwen,tdesout);
    char* tdesout1=(char*)tdesout;
    QByteArray tdesout2=QByteArray(tdesout1,8);
    qDebug()<<"3DES:"<<tdesout2.toHex().toUpper();
    qDebug()<<"计算3DES成功";
    Sleep(10);


    //外部认证
    //QByteArray tdesout2h=tdesout2.toHex();
    APDU[0]=0x00;
    APDU[1]=0x82;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x08;
    for (i=0;i<8;i++)
    {
        APDU[i+5]=tdesout2[i];
    }
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"外部认证成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //擦除内容
    //APDU[]={0x80,0x0E,0x00,0x00,0x00};
    APDU[0]=0x80;
    APDU[1]=0x0E;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x00;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"发送擦除命令成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

}

//发卡
void MainWindow::on_newButton_clicked()
{

    //创建MF
    QByteArray APDU;
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x3F;
    APDU[3]=0x00;
    APDU[4]=0x13;
    APDU[5]=0x38;
    APDU[6]=0xFF;
    APDU[7]=0xFF;
    APDU[8]=0xFA;
    APDU[9]=0xFA;
    APDU[10]=0x01;
    APDU[11]=0xFF;
    APDU[12]=0xFF;
    APDU[13]=0xFF;
    APDU[14]=0x12;
    APDU[15]=0x34;
    APDU[16]=0x56;
    APDU[17]=0x78;
    APDU[18]=0x46;
    APDU[19]=0x4D;
    APDU[20]=0x53;
    APDU[21]=0x48;
    APDU[22]=0x4D;
    APDU[23]=0x46;
    QByteArray RevBuff;//接收缓存
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"创建MF成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //Select 3F00
    APDU[0]=0x00;
    APDU[1]=0xA4;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x02;
    APDU[5]=0x3F;
    APDU[6]=0x00;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"选择MF成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //建立KEY文件
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x07;
    APDU[5]=0x3F;
    APDU[6]=0x00;
    APDU[7]=0xC0;
    APDU[8]=0x01;
    APDU[9]=0xFA;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"建立密钥文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);




    //添加MOT主控密钥  58B0FD07C1FD266D6819372645CD67AE
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x00;
    APDU[4]=0x15;
    APDU[5]=0xF9;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xAA;
    APDU[9]=0x88;
    APDU[10]=0x58;
    APDU[11]=0xB0;
    APDU[12]=0xFD;
    APDU[13]=0x07;
    APDU[14]=0xC1;
    APDU[15]=0xFD;
    APDU[16]=0x26;
    APDU[17]=0x6D;
    APDU[18]=0x68;
    APDU[19]=0x19;
    APDU[20]=0x37;
    APDU[21]=0x26;
    APDU[22]=0x45;
    APDU[23]=0xCD;
    APDU[24]=0x67;
    APDU[25]=0xAE;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"添加MOT主控密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //添加维护密钥  FFFFFFFFFFFFFFFF
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x00;
    APDU[4]=0x0D;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDU[12]=0xFF;
    APDU[13]=0xFF;
    APDU[14]=0xFF;
    APDU[15]=0xFF;
    APDU[16]=0xFF;
    APDU[17]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"添加维护密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写入MOT维护密钥1 834973D3295E76A168926BD580C20473
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x01;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0x83;
    APDU[11]=0x49;
    APDU[12]=0x73;
    APDU[13]=0xD3;
    APDU[14]=0x29;
    APDU[15]=0x5E;
    APDU[16]=0x76;
    APDU[17]=0xA1;
    APDU[18]=0x68;
    APDU[19]=0x92;
    APDU[20]=0x6B;
    APDU[21]=0xD5;
    APDU[22]=0x80;
    APDU[23]=0xC2;
    APDU[24]=0x04;
    APDU[25]=0x73;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"添加MOT维护密钥1成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //添加MOT维护密钥2 834973D3295E76A168926BD580C20473
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x02;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0x83;
    APDU[11]=0x49;
    APDU[12]=0x73;
    APDU[13]=0xD3;
    APDU[14]=0x29;
    APDU[15]=0x5E;
    APDU[16]=0x76;
    APDU[17]=0xA1;
    APDU[18]=0x68;
    APDU[19]=0x92;
    APDU[20]=0x6B;
    APDU[21]=0xD5;
    APDU[22]=0x80;
    APDU[23]=0xC2;
    APDU[24]=0x04;
    APDU[25]=0x73;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"添加MOT维护密钥2成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //share key 00
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x00;
    APDU[4]=0x15;
    APDU[5]=0xEF;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x00;
    APDU[9]=0x02;
    APDU[10]=0x3F;
    APDU[11]=0x01;
    APDU[12]=0x10;
    APDU[13]=0x01;
    APDU[14]=0xFF;
    APDU[15]=0xFF;
    APDU[16]=0xFF;
    APDU[17]=0xFF;
    APDU[18]=0xFF;
    APDU[19]=0xFF;
    APDU[20]=0xFF;
    APDU[21]=0xFF;
    APDU[22]=0xFF;
    APDU[23]=0xFF;
    APDU[24]=0xFF;
    APDU[25]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"share key 00成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //share key 01
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x01;
    APDU[4]=0x15;
    APDU[5]=0xEF;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x00;
    APDU[9]=0x04;
    APDU[10]=0x00;
    APDU[11]=0x02;
    APDU[12]=0x00;
    APDU[13]=0xFF;
    APDU[14]=0x00;
    APDU[15]=0x1A;
    APDU[16]=0x00;
    APDU[17]=0x1E;
    APDU[18]=0xFF;
    APDU[19]=0xFF;
    APDU[20]=0xFF;
    APDU[21]=0xFF;
    APDU[22]=0xFF;
    APDU[23]=0xFF;
    APDU[24]=0xFF;
    APDU[25]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"share key 01成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //share key 80
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x80;
    APDU[4]=0x15;
    APDU[5]=0xEF;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x00;
    APDU[9]=0x02;
    APDU[10]=0x3F;
    APDU[11]=0x01;
    APDU[12]=0x10;
    APDU[13]=0x01;
    APDU[14]=0xFF;
    APDU[15]=0xFF;
    APDU[16]=0xFF;
    APDU[17]=0xFF;
    APDU[18]=0xFF;
    APDU[19]=0xFF;
    APDU[20]=0xFF;
    APDU[21]=0xFF;
    APDU[22]=0xFF;
    APDU[23]=0xFF;
    APDU[24]=0xFF;
    APDU[25]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"share key 80成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //share key 81
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x81;
    APDU[4]=0x15;
    APDU[5]=0xEF;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x00;
    APDU[9]=0x02;
    APDU[10]=0x00;
    APDU[11]=0x02;
    APDU[12]=0x00;
    APDU[13]=0xFF;
    APDU[14]=0xFF;
    APDU[15]=0xFF;
    APDU[16]=0xFF;
    APDU[17]=0xFF;
    APDU[18]=0xFF;
    APDU[19]=0xFF;
    APDU[20]=0xFF;
    APDU[21]=0xFF;
    APDU[22]=0xFF;
    APDU[23]=0xFF;
    APDU[24]=0xFF;
    APDU[25]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"share key 81成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //Create PPSE FCI File
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x0A;
    APDU[4]=0x07;
    APDU[5]=0x2C;
    APDU[6]=0x00;
    APDU[7]=0x50;
    APDU[8]=0xF0;
    APDU[9]=0xFA;
    APDU[10]=0xFF;
    APDU[11]=0xFE;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"PPSE FCI File创建成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //update fci ec
    APDU[0]=0x00;
    APDU[1]=0xDC;
    APDU[2]=0x01;
    APDU[3]=0x54;
    APDU[4]=0x1D;
    APDU[5]=0x70;
    APDU[6]=0x1B;
    APDU[7]=0x61;
    APDU[8]=0x19;
    APDU[9]=0x4F;
    APDU[10]=0x08;
    APDU[11]=0xA0;
    APDU[12]=0x00;
    APDU[13]=0x00;
    APDU[14]=0x06;
    APDU[15]=0x32;
    APDU[16]=0x01;
    APDU[17]=0x01;
    APDU[18]=0x06;
    APDU[19]=0x50;
    APDU[20]=0x0A;
    APDU[21]=0x4D;
    APDU[22]=0x4F;
    APDU[23]=0x54;
    APDU[24]=0x5F;
    APDU[25]=0x54;
    APDU[26]=0x5F;
    APDU[27]=0x43;
    APDU[28]=0x41;
    APDU[29]=0x53;
    APDU[30]=0x48;
    APDU[31]=0x87;
    APDU[32]=0x01;
    APDU[33]=0x01;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"update fci ec成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //update fci ep
    APDU[0]=0x00;
    APDU[1]=0xDC;
    APDU[2]=0x02;
    APDU[3]=0x54;
    APDU[4]=0x1B;
    APDU[5]=0x70;
    APDU[6]=0x19;
    APDU[7]=0x61;
    APDU[8]=0x17;
    APDU[9]=0x4F;
    APDU[10]=0x08;
    APDU[11]=0xA0;
    APDU[12]=0x00;
    APDU[13]=0x00;
    APDU[14]=0x06;
    APDU[15]=0x32;
    APDU[16]=0x01;
    APDU[17]=0x01;
    APDU[18]=0x05;
    APDU[19]=0x50;
    APDU[20]=0x08;
    APDU[21]=0x4D;
    APDU[22]=0x4F;
    APDU[23]=0x54;
    APDU[24]=0x5F;
    APDU[25]=0x54;
    APDU[26]=0x5F;
    APDU[27]=0x45;
    APDU[28]=0x50;
    APDU[29]=0x87;
    APDU[30]=0x01;
    APDU[31]=0x02;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"update fci ep成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create PPSE
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x3F;
    APDU[3]=0x32;
    APDU[4]=0x16;
    APDU[5]=0x38;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0xFA;
    APDU[9]=0xFA;
    APDU[10]=0x0A;
    APDU[11]=0xFB;
    APDU[12]=0xFF;
    APDU[13]=0x32;
    APDU[14]=0x50;
    APDU[15]=0x41;
    APDU[16]=0x59;
    APDU[17]=0x2E;
    APDU[18]=0x53;
    APDU[19]=0x59;
    APDU[20]=0x53;
    APDU[21]=0x2E;
    APDU[22]=0x44;
    APDU[23]=0x44;
    APDU[24]=0x46;
    APDU[25]=0x30;
    APDU[26]=0x31;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create PPSE成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0002 wallet
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x02;
    APDU[4]=0x07;
    APDU[5]=0x2F;
    APDU[6]=0x02;
    APDU[7]=0x08;
    APDU[8]=0xF0;
    APDU[9]=0x00;
    APDU[10]=0xFF;
    APDU[11]=0x18;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 0002 wallet成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create PBOC借、贷记钱包文件
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0xFF;
    APDU[4]=0x07;
    APDU[5]=0x2F;
    APDU[6]=0x02;
    APDU[7]=0x70;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0x0B;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create PBOC借、贷记钱包文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 001A
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x1A;
    APDU[4]=0x07;
    APDU[5]=0xA4;
    APDU[6]=0x09;
    APDU[7]=0xCE;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xEE;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 001A成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 001E
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x1E;
    APDU[4]=0x07;
    APDU[5]=0xAE;
    APDU[6]=0x1E;
    APDU[7]=0x30;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xED;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 001A成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create MOT 电子钱包应用
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x3F;
    APDU[3]=0x01;
    APDU[4]=0x10;
    APDU[5]=0x38;
    APDU[6]=0x03;
    APDU[7]=0x5A;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0x95;
    APDU[11]=0xFF;
    APDU[12]=0xFF;
    APDU[13]=0xA0;
    APDU[14]=0x00;
    APDU[15]=0x00;
    APDU[16]=0x06;
    APDU[17]=0x32;
    APDU[18]=0x01;
    APDU[19]=0x01;
    APDU[20]=0x05;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create MOT电子钱包应用成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create MOT 电子现金应用
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x10;
    APDU[3]=0x01;
    APDU[4]=0x10;
    APDU[5]=0x38;
    APDU[6]=0x0D;
    APDU[7]=0xE2;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0x9D;
    APDU[11]=0xFB;
    APDU[12]=0xFF;
    APDU[13]=0xA0;
    APDU[14]=0x00;
    APDU[15]=0x00;
    APDU[16]=0x06;
    APDU[17]=0x32;
    APDU[18]=0x01;
    APDU[19]=0x01;
    APDU[20]=0x06;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create MOT电子现金应用成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //MOT钱包个人化开始,选择互通ep应用
    APDU[0]=0x00;
    APDU[1]=0xA4;
    APDU[2]=0x04;
    APDU[3]=0x00;
    APDU[4]=0x08;
    APDU[5]=0xA0;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0x06;
    APDU[9]=0x32;
    APDU[10]=0x01;
    APDU[11]=0x01;
    APDU[12]=0x05;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"MOT钱包个人化开始";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create key file
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x07;
    APDU[5]=0x3F;
    APDU[6]=0x01;
    APDU[7]=0x93;
    APDU[8]=0x01;
    APDU[9]=0xFA;
    APDU[10]=0xFC;
    APDU[11]=0xDF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create key file";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写钱包主控密钥 70C7C37A5D943F4C1B13EE1708FBFFFB
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x00;
    APDU[4]=0x15;
    APDU[5]=0xF9;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xAA;
    APDU[9]=0x33;
    APDU[10]=0x70;
    APDU[11]=0xC7;
    APDU[12]=0xC3;
    APDU[13]=0x7A;
    APDU[14]=0x5D;
    APDU[15]=0x94;
    APDU[16]=0x3F;
    APDU[17]=0x4C;
    APDU[18]=0x1B;
    APDU[19]=0x13;
    APDU[20]=0xEE;
    APDU[21]=0x17;
    APDU[22]=0x08;
    APDU[23]=0xFB;
    APDU[24]=0xFF;
    APDU[25]=0xFB;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create钱包主控密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写钱包维护密钥 E4BB4FC2CBBAF767469AFBC8BA580145
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x00;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0xE4;
    APDU[11]=0xBB;
    APDU[12]=0x4F;
    APDU[13]=0xC2;
    APDU[14]=0xCB;
    APDU[15]=0xBA;
    APDU[16]=0xF7;
    APDU[17]=0x67;
    APDU[18]=0x46;
    APDU[19]=0x9A;
    APDU[20]=0xFB;
    APDU[21]=0xC8;
    APDU[22]=0xBA;
    APDU[23]=0x58;
    APDU[24]=0x01;
    APDU[25]=0x45;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写钱包维护密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写1A文件维护密钥 62B51A2AF059354337AFC4E99E5B0C57
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x01;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0x62;
    APDU[11]=0xB5;
    APDU[12]=0x1A;
    APDU[13]=0x2A;
    APDU[14]=0xF0;
    APDU[15]=0x59;
    APDU[16]=0x35;
    APDU[17]=0x43;
    APDU[18]=0x37;
    APDU[19]=0xAF;
    APDU[20]=0xC4;
    APDU[21]=0xE9;
    APDU[22]=0x9E;
    APDU[23]=0x5B;
    APDU[24]=0x0C;
    APDU[25]=0x57;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写1A文件维护密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写1E文件维护密钥 760140108E15DAD41AC8DF7B8A013EB6
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x02;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0x76;
    APDU[11]=0x01;
    APDU[12]=0x40;
    APDU[13]=0x10;
    APDU[14]=0x8E;
    APDU[15]=0x15;
    APDU[16]=0xDA;
    APDU[17]=0xD4;
    APDU[18]=0x1A;
    APDU[19]=0xC8;
    APDU[20]=0xDF;
    APDU[21]=0x7B;
    APDU[22]=0x8A;
    APDU[23]=0x01;
    APDU[24]=0x3E;
    APDU[25]=0xB6;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写1E文件维护密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写15 16 17 维护密钥  977CD167B88836AE833A22B99AF8AE09
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x03;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0x97;
    APDU[11]=0x7C;
    APDU[12]=0xD1;
    APDU[13]=0x67;
    APDU[14]=0xB8;
    APDU[15]=0x88;
    APDU[16]=0x36;
    APDU[17]=0xAE;
    APDU[18]=0x83;
    APDU[19]=0x3A;
    APDU[20]=0x22;
    APDU[21]=0xB9;
    APDU[22]=0x9A;
    APDU[23]=0xF8;
    APDU[24]=0xAE;
    APDU[25]=0x09;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写151617维护密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);



    //写钱包应用解锁密钥 2573E5B2E67B1ECC49F655EDB6998416
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0xFC;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0x25;
    APDU[11]=0x73;
    APDU[12]=0xE5;
    APDU[13]=0xB2;
    APDU[14]=0xE6;
    APDU[15]=0x7B;
    APDU[16]=0x1E;
    APDU[17]=0xCC;
    APDU[18]=0x49;
    APDU[19]=0xF6;
    APDU[20]=0x55;
    APDU[21]=0xED;
    APDU[22]=0xB6;
    APDU[23]=0x99;
    APDU[24]=0x84;
    APDU[25]=0x16;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写钱包应用解锁密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写钱包应用锁定密钥 64D043100CBC047B150F4EA9E94DC7DF
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0xFD;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0x64;
    APDU[11]=0xD0;
    APDU[12]=0x43;
    APDU[13]=0x10;
    APDU[14]=0x0C;
    APDU[15]=0xBC;
    APDU[16]=0x04;
    APDU[17]=0x7B;
    APDU[18]=0x15;
    APDU[19]=0x0F;
    APDU[20]=0x4E;
    APDU[21]=0xA9;
    APDU[22]=0xE9;
    APDU[23]=0x4D;
    APDU[24]=0xC7;
    APDU[25]=0xDF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写钱包应用锁定密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写钱包下消费密钥 183E71E17FE65B3FB9E2E35C54354C25
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x01;
    APDU[4]=0x15;
    APDU[5]=0xFE;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x01;
    APDU[9]=0x00;
    APDU[10]=0x18;
    APDU[11]=0x3E;
    APDU[12]=0x71;
    APDU[13]=0xE1;
    APDU[14]=0x7F;
    APDU[15]=0xE6;
    APDU[16]=0x5B;
    APDU[17]=0x3F;
    APDU[18]=0xB9;
    APDU[19]=0xE2;
    APDU[20]=0xE3;
    APDU[21]=0x5C;
    APDU[22]=0x54;
    APDU[23]=0x35;
    APDU[24]=0x4C;
    APDU[25]=0x25;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写钱包下消费密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写MOT钱包应用backup消费密钥 6B30C409F8928C1300E791A83D2E997D
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x02;
    APDU[4]=0x15;
    APDU[5]=0xFE;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x01;
    APDU[9]=0x00;
    APDU[10]=0x6B;
    APDU[11]=0x30;
    APDU[12]=0xC4;
    APDU[13]=0x09;
    APDU[14]=0xF8;
    APDU[15]=0x92;
    APDU[16]=0x8C;
    APDU[17]=0x13;
    APDU[18]=0x00;
    APDU[19]=0xE7;
    APDU[20]=0x91;
    APDU[21]=0xA8;
    APDU[22]=0x3D;
    APDU[23]=0x2E;
    APDU[24]=0x99;
    APDU[25]=0x7D;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写MOT钱包应用backup消费密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写MOT钱包应用圈存密钥1 580593DFF541B0EAB81DA2F8D8AC9BE9
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x01;
    APDU[4]=0x15;
    APDU[5]=0xFF;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x01;
    APDU[9]=0x00;
    APDU[10]=0x58;
    APDU[11]=0x05;
    APDU[12]=0x93;
    APDU[13]=0xDF;
    APDU[14]=0xF5;
    APDU[15]=0x41;
    APDU[16]=0xB0;
    APDU[17]=0xEA;
    APDU[18]=0xB8;
    APDU[19]=0x1D;
    APDU[20]=0xA2;
    APDU[21]=0xF8;
    APDU[22]=0xD8;
    APDU[23]=0xAC;
    APDU[24]=0x9B;
    APDU[25]=0xE9;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写MOT钱包应用圈存密钥1成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写MOT钱包应用圈存密钥2 580593DFF541B0EAB81DA2F8D8AC9BE9
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x02;
    APDU[4]=0x15;
    APDU[5]=0xFF;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x01;
    APDU[9]=0x00;
    APDU[10]=0x58;
    APDU[11]=0x05;
    APDU[12]=0x93;
    APDU[13]=0xDF;
    APDU[14]=0xF5;
    APDU[15]=0x41;
    APDU[16]=0xB0;
    APDU[17]=0xEA;
    APDU[18]=0xB8;
    APDU[19]=0x1D;
    APDU[20]=0xA2;
    APDU[21]=0xF8;
    APDU[22]=0xD8;
    APDU[23]=0xAC;
    APDU[24]=0x9B;
    APDU[25]=0xE9;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写MOT钱包应用圈存密钥2成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写MOT钱包应用TAC密钥1 0227432C09D5E059571A3D1810AC9464
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x01;
    APDU[4]=0x15;
    APDU[5]=0xF4;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x01;
    APDU[9]=0x00;
    APDU[10]=0x02;
    APDU[11]=0x27;
    APDU[12]=0x43;
    APDU[13]=0x2C;
    APDU[14]=0x09;
    APDU[15]=0xD5;
    APDU[16]=0xE0;
    APDU[17]=0x59;
    APDU[18]=0x57;
    APDU[19]=0x1A;
    APDU[20]=0x3D;
    APDU[21]=0x18;
    APDU[22]=0x10;
    APDU[23]=0xAC;
    APDU[24]=0x94;
    APDU[25]=0x64;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写MOT钱包应用TAC密钥1成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);


    //写MOT钱包应用TAC密钥2 0227432C09D5E059571A3D1810AC9464
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x02;
    APDU[4]=0x15;
    APDU[5]=0xF4;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x01;
    APDU[9]=0x00;
    APDU[10]=0x02;
    APDU[11]=0x27;
    APDU[12]=0x43;
    APDU[13]=0x2C;
    APDU[14]=0x09;
    APDU[15]=0xD5;
    APDU[16]=0xE0;
    APDU[17]=0x59;
    APDU[18]=0x57;
    APDU[19]=0x1A;
    APDU[20]=0x3D;
    APDU[21]=0x18;
    APDU[22]=0x10;
    APDU[23]=0xAC;
    APDU[24]=0x94;
    APDU[25]=0x64;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写MOT钱包应用TAC密钥2成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写MOT钱包应用圈提密钥1 590DF08FD06D33B2DB412A166429E730
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x01;
    APDU[4]=0x15;
    APDU[5]=0xFD;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x01;
    APDU[9]=0x00;
    APDU[10]=0x59;
    APDU[11]=0x0D;
    APDU[12]=0xF0;
    APDU[13]=0x8F;
    APDU[14]=0xD0;
    APDU[15]=0x6D;
    APDU[16]=0x33;
    APDU[17]=0xB2;
    APDU[18]=0xDB;
    APDU[19]=0x41;
    APDU[20]=0x2A;
    APDU[21]=0x16;
    APDU[22]=0x64;
    APDU[23]=0x29;
    APDU[24]=0xE7;
    APDU[25]=0x30;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写MOT钱包应用圈提密钥1成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写MOT钱包应用圈提密钥2 590DF08FD06D33B2DB412A166429E730
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x02;
    APDU[4]=0x15;
    APDU[5]=0xFD;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x01;
    APDU[9]=0x00;
    APDU[10]=0x59;
    APDU[11]=0x0D;
    APDU[12]=0xF0;
    APDU[13]=0x8F;
    APDU[14]=0xD0;
    APDU[15]=0x6D;
    APDU[16]=0x33;
    APDU[17]=0xB2;
    APDU[18]=0xDB;
    APDU[19]=0x41;
    APDU[20]=0x2A;
    APDU[21]=0x16;
    APDU[22]=0x64;
    APDU[23]=0x29;
    APDU[24]=0xE7;
    APDU[25]=0x30;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写MOT钱包应用圈提密钥2成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写MOT钱包应用修改透支限额密钥 780F1CF1D78A8AFE2B88FCD6EED115CB
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x00;
    APDU[4]=0x15;
    APDU[5]=0xFC;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0x01;
    APDU[9]=0x00;
    APDU[10]=0x78;
    APDU[11]=0x0F;
    APDU[12]=0x1C;
    APDU[13]=0xF1;
    APDU[14]=0xD7;
    APDU[15]=0x8A;
    APDU[16]=0x8A;
    APDU[17]=0xFE;
    APDU[18]=0x2B;
    APDU[19]=0x88;
    APDU[20]=0xFC;
    APDU[21]=0xD6;
    APDU[22]=0xEE;
    APDU[23]=0xD1;
    APDU[24]=0x15;
    APDU[25]=0xCB;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写MOT钱包应用修改透支限额密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);


    //create file 0x15
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x15;
    APDU[4]=0x07;
    APDU[5]=0xA8;
    APDU[6]=0x00;
    APDU[7]=0x1E;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFC;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"创建15文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);


    //create file 0x16
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x16;
    APDU[4]=0x07;
    APDU[5]=0xA8;
    APDU[6]=0x00;
    APDU[7]=0x37;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFC;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"创建16文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0x17
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x17;
    APDU[4]=0x07;
    APDU[5]=0xA8;
    APDU[6]=0x00;
    APDU[7]=0x3C;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFC;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"创建17文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //建立pboc借贷记钱包文件
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x02;
    APDU[4]=0x07;
    APDU[5]=0x2F;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0xF0;
    APDU[9]=0x00;
    APDU[10]=0xFF;
    APDU[11]=0x18;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"建立pboc借贷记钱包文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0x18
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x18;
    APDU[4]=0x07;
    APDU[5]=0x2E;
    APDU[6]=0x0A;
    APDU[7]=0x17;
    APDU[8]=0xF0;
    APDU[9]=0xEF;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"创建18文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0x1A
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x1A;
    APDU[4]=0x07;
    APDU[5]=0xA4;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xEE;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"创建1A文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0x1E
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x1E;
    APDU[4]=0x07;
    APDU[5]=0xAE;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xED;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"创建1E文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);
/*
    //更新文件记录
    //选择互联互通钱包应用
    APDU[0]=0x00;
    APDU[1]=0xA4;
    APDU[2]=0x04;
    APDU[3]=0x00;
    APDU[4]=0x08;
    APDU[5]=0xA0;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0x06;
    APDU[9]=0x32;
    APDU[10]=0x01;
    APDU[11]=0x01;
    APDU[12]=0x05;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"选择互通EP成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //更新15文件记录
    APDU[0]=0x00;
    APDU[1]=0xD0;
    APDU[2]=0x95;
    APDU[3]=0x00;
    APDU[4]=0x1E;
    APDU[5]=0x09;
    APDU[6]=0x99;
    APDU[7]=0x10;
    APDU[8]=0x01;
    APDU[9]=0x32;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDU[12]=0xFF;
    APDU[13]=0xFF;
    APDU[14]=0x02;
    APDU[15]=0x01;
    APDU[16]=0x03;
    APDU[17]=0x10;
    APDU[18]=0x62;
    APDU[19]=0x28;
    APDU[20]=0x00;
    APDU[21]=0x01;
    APDU[22]=0x00;
    APDU[23]=0x00;
    APDU[24]=0x11;
    APDU[25]=0x17;
    APDU[26]=0x20;
    APDU[27]=0x15;
    APDU[28]=0x01;
    APDU[29]=0x01;
    APDU[30]=0x20;
    APDU[31]=0x40;
    APDU[32]=0x12;
    APDU[33]=0x31;
    APDU[34]=0x00;
    APDU[35]=0x00;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"更新15文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);


    //更新16文件
    APDU[0]=0x00;
    APDU[1]=0xD0;
    APDU[2]=0x96;
    APDU[3]=0x00;
    APDU[4]=0x37;
    APDU[5]=0x00;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0x00;
    APDU[9]=0x00;
    APDU[10]=0x00;
    APDU[11]=0x00;
    APDU[12]=0x00;
    APDU[13]=0x00;
    APDU[14]=0x00;
    APDU[15]=0x00;
    APDU[16]=0x00;
    APDU[17]=0x00;
    APDU[18]=0x00;
    APDU[19]=0x00;
    APDU[20]=0x00;
    APDU[21]=0x00;
    APDU[22]=0x00;
    APDU[23]=0x00;
    APDU[24]=0x00;
    APDU[25]=0x00;
    APDU[26]=0x00;
    APDU[27]=0x00;
    APDU[28]=0x00;
    APDU[29]=0x00;
    APDU[30]=0x00;
    APDU[31]=0x00;
    APDU[32]=0x00;
    APDU[33]=0x00;
    APDU[34]=0x00;
    APDU[35]=0x00;
    APDU[36]=0x00;
    APDU[37]=0x00;
    APDU[38]=0x00;
    APDU[39]=0x00;
    APDU[40]=0x00;
    APDU[41]=0x00;
    APDU[42]=0x00;
    APDU[43]=0x00;
    APDU[44]=0x00;
    APDU[45]=0x00;
    APDU[46]=0x00;
    APDU[47]=0x00;
    APDU[48]=0x00;
    APDU[49]=0x00;
    APDU[50]=0x00;
    APDU[51]=0x00;
    APDU[52]=0x00;
    APDU[53]=0x00;
    APDU[54]=0x00;
    APDU[55]=0x00;
    APDU[56]=0x00;
    APDU[57]=0x00;
    APDU[58]=0x00;
    APDU[59]=0x00;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"更新16文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);


    //更新17文件
    APDU[0]=0x00;
    APDU[1]=0xD0;
    APDU[2]=0x97;
    APDU[3]=0x00;
    APDU[4]=0x31;
    APDU[5]=0x00;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0x00;
    APDU[9]=0x00;
    APDU[10]=0x00;
    APDU[11]=0x00;
    APDU[12]=0x00;
    APDU[13]=0x00;
    APDU[14]=0x00;
    APDU[15]=0x00;
    APDU[16]=0x00;
    APDU[17]=0x00;
    APDU[18]=0x00;
    APDU[19]=0x00;
    APDU[20]=0x00;
    APDU[21]=0x00;
    APDU[22]=0x00;
    APDU[23]=0x00;
    APDU[24]=0x00;
    APDU[25]=0x00;
    APDU[26]=0x00;
    APDU[27]=0x00;
    APDU[28]=0x00;
    APDU[29]=0x00;
    APDU[30]=0x00;
    APDU[31]=0x00;
    APDU[32]=0x00;
    APDU[33]=0x00;
    APDU[34]=0x00;
    APDU[35]=0x00;
    APDU[36]=0x00;
    APDU[37]=0x00;
    APDU[38]=0x00;
    APDU[39]=0x00;
    APDU[40]=0x00;
    APDU[41]=0x00;
    APDU[42]=0x00;
    APDU[43]=0x00;
    APDU[44]=0x00;
    APDU[45]=0x00;
    APDU[46]=0x00;
    APDU[47]=0x00;
    APDU[48]=0x00;
    APDU[49]=0x00;
    APDU[50]=0x00;
    APDU[51]=0x00;
    APDU[52]=0x00;
    APDU[53]=0x00;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"更新17文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);
*/
    //select MOT现金应用
    APDU[0]=0x00;
    APDU[1]=0xA4;
    APDU[2]=0x04;
    APDU[3]=0x00;
    APDU[4]=0x08;
    APDU[5]=0xA0;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0x06;
    APDU[9]=0x32;
    APDU[10]=0x01;
    APDU[11]=0x01;
    APDU[12]=0x06;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"select MOT现金应用成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create key file
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x07;
    APDU[5]=0x3F;
    APDU[6]=0x01;
    APDU[7]=0xA0;
    APDU[8]=0x01;
    APDU[9]=0xFA;
    APDU[10]=0xFE;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create key file成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //write EC主控 58B0FD07C1FD266D6819372645CD67AE
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x00;
    APDU[4]=0x15;
    APDU[5]=0xF9;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xAA;
    APDU[9]=0x88;
    APDU[10]=0x58;
    APDU[11]=0xB0;
    APDU[12]=0xFD;
    APDU[13]=0x07;
    APDU[14]=0xC1;
    APDU[15]=0xFD;
    APDU[16]=0x26;
    APDU[17]=0x6D;
    APDU[18]=0x68;
    APDU[19]=0x19;
    APDU[20]=0x37;
    APDU[21]=0x26;
    APDU[22]=0x45;
    APDU[23]=0xCD;
    APDU[24]=0x67;
    APDU[25]=0xAE;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"write EC主控成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //write EC维护 834973D3295E76A168926BD580C20473
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x00;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0x83;
    APDU[11]=0x49;
    APDU[12]=0x73;
    APDU[13]=0xD3;
    APDU[14]=0x29;
    APDU[15]=0x5E;
    APDU[16]=0x76;
    APDU[17]=0xA1;
    APDU[18]=0x68;
    APDU[19]=0x92;
    APDU[20]=0x6B;
    APDU[21]=0xD5;
    APDU[22]=0x80;
    APDU[23]=0xC2;
    APDU[24]=0x04;
    APDU[25]=0x73;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"write EC维护成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //write 维护  834973D3295E76A168926BD580C20473
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x02;
    APDU[4]=0x15;
    APDU[5]=0xF6;
    APDU[6]=0xF0;
    APDU[7]=0xF0;
    APDU[8]=0xFF;
    APDU[9]=0x33;
    APDU[10]=0x83;
    APDU[11]=0x49;
    APDU[12]=0x73;
    APDU[13]=0xD3;
    APDU[14]=0x29;
    APDU[15]=0x5E;
    APDU[16]=0x76;
    APDU[17]=0xA1;
    APDU[18]=0x68;
    APDU[19]=0x92;
    APDU[20]=0x6B;
    APDU[21]=0xD5;
    APDU[22]=0x80;
    APDU[23]=0xC2;
    APDU[24]=0x04;
    APDU[25]=0x73;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"write维护成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //写口令密钥
    APDU[0]=0x80;
    APDU[1]=0xD4;
    APDU[2]=0x01;
    APDU[3]=0x00;
    APDU[4]=0x0D;
    APDU[5]=0xFA;
    APDU[6]=0xF0;
    APDU[7]=0xEF;
    APDU[8]=0x01;
    APDU[9]=0x33;
    APDU[10]=0x06;
    APDU[11]=0x12;
    APDU[12]=0x34;
    APDU[13]=0x56;
    APDU[14]=0xFF;
    APDU[15]=0xFF;
    APDU[16]=0xFF;
    APDU[17]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"写口令密钥成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 1D
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x1D;
    APDU[4]=0x07;
    APDU[5]=0xEC;
    APDU[6]=0x01;
    APDU[7]=0x37;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 1D成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);


    //create file 4 PrivateKey
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x1F;
    APDU[4]=0x07;
    APDU[5]=0x29;
    APDU[6]=0x05;
    APDU[7]=0x30;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0x1F;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 4 PrivateKey成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0001
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x01;
    APDU[4]=0x07;
    APDU[5]=0xAC;
    APDU[6]=0x01;
    APDU[7]=0x70;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 0001成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0002
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x02;
    APDU[4]=0x07;
    APDU[5]=0xAC;
    APDU[6]=0x01;
    APDU[7]=0xF7;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 0002成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0003
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x03;
    APDU[4]=0x07;
    APDU[5]=0xAC;
    APDU[6]=0x01;
    APDU[7]=0xAF;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 0003成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0004
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x04;
    APDU[4]=0x07;
    APDU[5]=0xAC;
    APDU[6]=0x00;
    APDU[7]=0x1A;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 0004成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0005
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x05;
    APDU[4]=0x07;
    APDU[5]=0xAC;
    APDU[6]=0x00;
    APDU[7]=0x0F;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 0005成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0008(学生卡老年卡)
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x08;
    APDU[4]=0x07;
    APDU[5]=0xAC;
    APDU[6]=0x00;
    APDU[7]=0x1E;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create file 0008成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create 钱包文件
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0xFF;
    APDU[4]=0x07;
    APDU[5]=0x2F;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0x0B;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create 钱包文件成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0B
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x0B;
    APDU[4]=0x07;
    APDU[5]=0x2E;
    APDU[6]=0x0A;
    APDU[7]=0x2D;
    APDU[8]=0xF0;
    APDU[9]=0xEF;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create文件0B成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 0C
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x0C;
    APDU[4]=0x07;
    APDU[5]=0x2E;
    APDU[6]=0x0A;
    APDU[7]=0x3B;
    APDU[8]=0xF0;
    APDU[9]=0xEF;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create文件0C成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 1A
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x1A;
    APDU[4]=0x07;
    APDU[5]=0xA4;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xEE;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create文件1A成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 1E
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x00;
    APDU[3]=0x1E;
    APDU[4]=0x07;
    APDU[5]=0xAE;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xED;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create文件1E成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //create file 01FF(透支记录)
    APDU[0]=0x80;
    APDU[1]=0xE0;
    APDU[2]=0x01;
    APDU[3]=0xFF;
    APDU[4]=0x07;
    APDU[5]=0x25;
    APDU[6]=0x03;
    APDU[7]=0x09;
    APDU[8]=0xF0;
    APDU[9]=0xF0;
    APDU[10]=0xFF;
    APDU[11]=0xBE;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"create文件01FF成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //select MOT.CPTIC01
    APDU[0]=0x00;
    APDU[1]=0xA4;
    APDU[2]=0x04;
    APDU[3]=0x00;
    APDU[4]=0x08;
    APDU[5]=0xA0;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0x06;
    APDU[9]=0x32;
    APDU[10]=0x01;
    APDU[11]=0x01;
    APDU[12]=0x06;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"select MOT.CPTIC01成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //initialize update
    APDU[0]=0x80;
    APDU[1]=0x50;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x08;
    APDU[5]=0xFF;
    APDU[6]=0xFF;
    APDU[7]=0xFF;
    APDU[8]=0xFF;
    APDU[9]=0xFF;
    APDU[10]=0xFF;
    APDU[11]=0xFF;
    APDU[12]=0xFF;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"initialize update成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //?
    APDU[0]=0x84;
    APDU[1]=0x82;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x10;
    APDU[5]=0x56;
    APDU[6]=0xBE;
    APDU[7]=0x4B;
    APDU[8]=0xD4;
    APDU[9]=0x24;
    APDU[10]=0x85;
    APDU[11]=0xE2;
    APDU[12]=0xEA;
    APDU[13]=0x62;
    APDU[14]=0x9C;
    APDU[15]=0x26;
    APDU[16]=0x00;
    APDU[17]=0x77;
    APDU[18]=0xC9;
    APDU[19]=0x8F;
    APDU[20]=0x81;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<" ? 成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);
/*
    //0101词条等效数据
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x45;
    APDU[5]=0x01;
    APDU[6]=0x01;
    APDU[7]=0x42;
    APDU[8]=0x70;
    APDU[9]=0x40;
    APDU[10]=0x57;
    APDU[11]=0x13;
    APDU[12]=0x31;
    APDU[13]=0x06;
    APDU[14]=0x22;
    APDU[15]=0x80;
    APDU[16]=0x00;
    APDU[17]=0x10;
    APDU[18]=0x00;
    APDU[19]=0x01;
    APDU[20]=0x11;
    APDU[21]=0x7D;
    APDU[22]=0x40;
    APDU[23]=0x12;
    APDU[24]=0x20;
    APDU[25]=0x10;
    APDU[26]=0x12;
    APDU[27]=0x34;
    APDU[28]=0x56;
    APDU[29]=0x78;
    APDU[30]=0x9F;
    APDU[31]=0x5F;
    APDU[32]=0x20;
    APDU[33]=0x0F;
    APDU[34]=0x46;
    APDU[35]=0x55;
    APDU[36]=0x4C;
    APDU[37]=0x4C;
    APDU[38]=0x20;
    APDU[39]=0x46;
    APDU[40]=0x55;
    APDU[41]=0x4E;
    APDU[42]=0x43;
    APDU[43]=0x54;
    APDU[44]=0x49;
    APDU[45]=0x4F;
    APDU[46]=0x4E;
    APDU[47]=0x41;
    APDU[48]=0x4C;
    APDU[49]=0x9F;
    APDU[50]=0x61;
    APDU[51]=0x12;
    APDU[52]=0x31;
    APDU[53]=0x32;
    APDU[54]=0x33;
    APDU[55]=0x34;
    APDU[56]=0x35;
    APDU[57]=0x36;
    APDU[58]=0x37;
    APDU[59]=0x38;
    APDU[60]=0x39;
    APDU[61]=0x31;
    APDU[62]=0x32;
    APDU[63]=0x32;
    APDU[64]=0x34;
    APDU[65]=0x35;
    APDU[66]=0x36;
    APDU[67]=0x37;
    APDU[68]=0x38;
    APDU[69]=0x39;
    APDU[70]=0x9F;
    APDU[71]=0x62;
    APDU[72]=0x01;
    APDU[73]=0x0B;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"创建词条等效数据成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //发卡机构公钥证书

    //0201 OLMOT的SDA
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x03;
    APDU[4]=0x51;
    APDU[5]=0x02;
    APDU[6]=0x01;
    APDU[7]=0x4E;
    APDU[8]=0x70;
    APDU[9]=0x4C;
    APDU[10]=0x5F;
    APDU[11]=0x2F;
    APDU[12]=0x03;
    APDU[13]=0x00;
    APDU[14]=0x01;
    APDU[15]=0x01;
    APDU[16]=0x5F;
    APDU[17]=0x24;
    APDU[18]=0x03;
    APDU[19]=0x40;
    APDU[20]=0x12;
    APDU[21]=0x31;
    APDU[22]=0x5A;
    APDU[23]=0x0A;
    APDU[24]=0x31;
    APDU[25]=0x06;
    APDU[26]=0x22;
    APDU[27]=0x80;
    APDU[28]=0x00;
    APDU[29]=0x10;
    APDU[30]=0x00;
    APDU[31]=0x01;
    APDU[32]=0x11;
    APDU[33]=0x7F;
    APDU[34]=0x5F;
    APDU[35]=0x34;
    APDU[36]=0x01;
    APDU[37]=0x01;//SN
    APDU[38]=0x9F;
    APDU[39]=0x07;
    APDU[40]=0x02;
    APDU[41]=0xFF;
    APDU[42]=0x00;
    APDU[43]=0x8E;
    APDU[44]=0x0C;
    APDU[45]=0x00;
    APDU[46]=0x00;
    APDU[47]=0x00;
    APDU[48]=0x00;
    APDU[49]=0x00;
    APDU[50]=0x00;
    APDU[51]=0x00;
    APDU[52]=0x00;
    APDU[53]=0x02;
    APDU[54]=0x03;
    APDU[55]=0x1F;
    APDU[56]=0x00;
    APDU[57]=0x9F;
    APDU[58]=0x0D;
    APDU[59]=0x05;
    APDU[60]=0xD8;
    APDU[61]=0x60;
    APDU[62]=0x04;
    APDU[63]=0xA8;
    APDU[64]=0x00;
    APDU[65]=0x9F;
    APDU[66]=0x0E;
    APDU[67]=0x05;
    APDU[68]=0x00;
    APDU[69]=0x10;
    APDU[70]=0x98;
    APDU[71]=0x00;
    APDU[72]=0x00;
    APDU[73]=0x9F;
    APDU[74]=0x0F;
    APDU[75]=0x05;
    APDU[76]=0xD8;
    APDU[77]=0x68;
    APDU[78]=0x04;
    APDU[79]=0xF8;
    APDU[80]=0x00;
    APDU[81]=0x5F;
    APDU[82]=0x28;
    APDU[83]=0x02;
    APDU[84]=0x01;
    APDU[85]=0x56;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"OLMOT的SDA成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 0202
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x04;
    APDU[4]=0xE0;
    APDU[5]=0x02;
    APDU[6]=0x02;
    APDU[7]=0xDD;
    APDU[8]=0x70;
    APDU[9]=0x81;
    APDU[10]=0xDA;
    APDU[11]=0x93;
    APDU[12]=0x81;
    APDU[13]=0x90;
    APDU[14]=0x6C;
    APDU[15]=0xC2;
    APDU[16]=0x91;
    APDU[17]=0xAF;
    APDU[18]=0x4F;
    APDU[19]=0x8F;
    APDU[20]=0x72;
    APDU[21]=0x83;
    APDU[22]=0x64;
    APDU[23]=0x85;
    APDU[24]=0x67;
    APDU[25]=0xF5;
    APDU[26]=0xAE;
    APDU[27]=0x57;
    APDU[28]=0xB8;
    APDU[29]=0x4C;
    APDU[30]=0x2F;
    APDU[31]=0x78;
    APDU[32]=0x38;
    APDU[33]=0x8C;
    APDU[34]=0x07;
    APDU[35]=0x27;
    APDU[36]=0x20;
    APDU[37]=0x11;
    APDU[38]=0x3A;
    APDU[39]=0x0E;
    APDU[40]=0xB0;
    APDU[41]=0x18;
    APDU[42]=0x5C;
    APDU[43]=0x36;
    APDU[44]=0x4C;
    APDU[45]=0xC9;
    APDU[46]=0x3A;
    APDU[47]=0x31;
    APDU[48]=0xB0;
    APDU[49]=0xDD;
    APDU[50]=0x62;
    APDU[51]=0xCE;
    APDU[52]=0xD5;
    APDU[53]=0x12;
    APDU[54]=0xA8;
    APDU[55]=0xED;
    APDU[56]=0xB7;
    APDU[57]=0x46;
    APDU[58]=0x6E;
    APDU[59]=0xD5;
    APDU[60]=0x0A;
    APDU[61]=0x5C;
    APDU[62]=0x0F;
    APDU[63]=0xC3;
    APDU[64]=0xE3;
    APDU[65]=0xC1;
    APDU[66]=0xE2;
    APDU[67]=0xB1;
    APDU[68]=0xA2;
    APDU[69]=0xD3;
    APDU[70]=0xAB;
    APDU[71]=0x57;
    APDU[72]=0xC0;
    APDU[73]=0x5C;
    APDU[74]=0x1F;
    APDU[75]=0x3C;
    APDU[76]=0xC1;
    APDU[77]=0x6C;
    APDU[78]=0xA0;
    APDU[79]=0x6B;
    APDU[80]=0x11;
    APDU[81]=0xE8;
    APDU[82]=0x0E;
    APDU[83]=0x06;
    APDU[84]=0x1F;
    APDU[85]=0x78;
    APDU[86]=0x85;
    APDU[87]=0x2C;
    APDU[88]=0x17;
    APDU[89]=0x34;
    APDU[90]=0x41;
    APDU[91]=0xA4;
    APDU[92]=0xF2;
    APDU[93]=0xF0;
    APDU[94]=0xF4;
    APDU[95]=0x0F;
    APDU[96]=0x77;
    APDU[97]=0x2B;
    APDU[98]=0x8D;
    APDU[99]=0xF8;
    APDU[100]=0xC2;
    APDU[101]=0x24;
    APDU[102]=0x06;
    APDU[103]=0xC6;
    APDU[104]=0x07;
    APDU[105]=0x41;
    APDU[106]=0x16;
    APDU[107]=0xF1;
    APDU[108]=0xCC;
    APDU[109]=0x24;
    APDU[110]=0x26;
    APDU[111]=0x1F;
    APDU[112]=0xE0;
    APDU[113]=0xF7;
    APDU[114]=0xBC;
    APDU[115]=0xB6;
    APDU[116]=0x34;
    APDU[117]=0xA6;
    APDU[118]=0xD1;
    APDU[119]=0x2E;
    APDU[120]=0x84;
    APDU[121]=0xC3;
    APDU[122]=0x7C;
    APDU[123]=0x9A;
    APDU[124]=0xF9;
    APDU[125]=0x62;
    APDU[126]=0xAD;
    APDU[127]=0xF2;
    APDU[128]=0xF9;
    APDU[129]=0xA4;
    APDU[130]=0xA5;
    APDU[131]=0x67;
    APDU[132]=0x1A;
    APDU[133]=0x81;
    APDU[134]=0x95;
    APDU[135]=0x85;
    APDU[136]=0x91;
    APDU[137]=0xFF;
    APDU[138]=0xF8;
    APDU[139]=0x45;
    APDU[140]=0x6A;
    APDU[141]=0x8B;
    APDU[142]=0x6C;
    APDU[143]=0x3A;
    APDU[144]=0x76;
    APDU[145]=0x4E;
    APDU[146]=0x24;
    APDU[147]=0xF4;
    APDU[148]=0xB2;
    APDU[149]=0x56;
    APDU[150]=0x67;
    APDU[151]=0xE1;
    APDU[152]=0x6E;
    APDU[153]=0x3D;
    APDU[154]=0xE6;
    APDU[155]=0x76;
    APDU[156]=0x9B;
    APDU[157]=0xFC;
    APDU[158]=0x8C;
    APDU[159]=0x1B;
    APDU[160]=0x9F;
    APDU[161]=0x02;
    APDU[162]=0x06;
    APDU[163]=0x9F;
    APDU[164]=0x03;
    APDU[165]=0x06;
    APDU[166]=0x9F;
    APDU[167]=0x1A;
    APDU[168]=0x02;
    APDU[169]=0x95;
    APDU[170]=0x05;
    APDU[171]=0x5F;
    APDU[172]=0x2A;
    APDU[173]=0x02;
    APDU[174]=0x9A;
    APDU[175]=0x03;
    APDU[176]=0x9C;
    APDU[177]=0x01;
    APDU[178]=0x9F;
    APDU[179]=0x37;
    APDU[180]=0x04;
    APDU[181]=0x9F;
    APDU[182]=0x21;
    APDU[183]=0x03;
    APDU[184]=0x9F;
    APDU[185]=0x4E;
    APDU[186]=0x14;
    APDU[187]=0x8D;
    APDU[188]=0x1A;
    APDU[189]=0x8A;
    APDU[190]=0x02;
    APDU[191]=0x9F;
    APDU[192]=0x02;
    APDU[193]=0x06;
    APDU[194]=0x9F;
    APDU[195]=0x03;
    APDU[196]=0x06;
    APDU[197]=0x9F;
    APDU[198]=0x1A;
    APDU[199]=0x02;
    APDU[200]=0x95;
    APDU[201]=0x05;
    APDU[202]=0x5F;
    APDU[203]=0x2A;
    APDU[204]=0x02;
    APDU[205]=0x9A;
    APDU[206]=0x03;
    APDU[207]=0x9F;
    APDU[208]=0x21;
    APDU[209]=0x03;
    APDU[210]=0x9C;
    APDU[211]=0x01;
    APDU[212]=0x9F;
    APDU[213]=0x37;
    APDU[214]=0x04;
    APDU[215]=0x9F;
    APDU[216]=0x49;
    APDU[217]=0x03;
    APDU[218]=0x9F;
    APDU[219]=0x37;
    APDU[220]=0x04;
    APDU[221]=0x9F;
    APDU[222]=0x14;
    APDU[223]=0x01;
    APDU[224]=0x00;
    APDU[225]=0x9F;
    APDU[226]=0x23;
    APDU[227]=0x01;
    APDU[228]=0x00;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 0202成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 0203   联机MOT

    //0301 qMOT的SDA

    //store data dgi 0302
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x07;
    APDU[4]=0x99;
    APDU[5]=0x03;
    APDU[6]=0x02;
    APDU[7]=0x96;
    APDU[8]=0x70;
    APDU[9]=0x81;
    APDU[10]=0x93;
    APDU[11]=0x93;
    APDU[12]=0x81;
    APDU[13]=0x90;
    APDU[14]=0x13;
    APDU[15]=0x44;
    APDU[16]=0x63;
    APDU[17]=0x6B;
    APDU[18]=0xC9;
    APDU[19]=0x1A;
    APDU[20]=0x9E;
    APDU[21]=0x28;
    APDU[22]=0x7E;
    APDU[23]=0x85;
    APDU[24]=0x32;
    APDU[25]=0x3E;
    APDU[26]=0x12;
    APDU[27]=0x9C;
    APDU[28]=0xA2;
    APDU[29]=0x1D;
    APDU[30]=0x76;
    APDU[31]=0x4E;
    APDU[32]=0xDA;
    APDU[33]=0xE1;
    APDU[34]=0xA7;
    APDU[35]=0x94;
    APDU[36]=0x47;
    APDU[37]=0xDD;
    APDU[38]=0xA3;
    APDU[39]=0xCD;
    APDU[40]=0x91;
    APDU[41]=0x8A;
    APDU[42]=0x58;
    APDU[43]=0xD8;
    APDU[44]=0x88;
    APDU[45]=0x75;
    APDU[46]=0x56;
    APDU[47]=0xE5;
    APDU[48]=0xAA;
    APDU[49]=0xD1;
    APDU[50]=0xD1;
    APDU[51]=0x00;
    APDU[52]=0x60;
    APDU[53]=0xB5;
    APDU[54]=0xA5;
    APDU[55]=0x82;
    APDU[56]=0x16;
    APDU[57]=0x0C;
    APDU[58]=0x87;
    APDU[59]=0x6C;
    APDU[60]=0x9E;
    APDU[61]=0x3F;
    APDU[62]=0x1D;
    APDU[63]=0xCC;
    APDU[64]=0x80;
    APDU[65]=0x84;
    APDU[66]=0xCE;
    APDU[67]=0xBC;
    APDU[68]=0x62;
    APDU[69]=0x25;
    APDU[70]=0x5E;
    APDU[71]=0xDF;
    APDU[72]=0xB9;
    APDU[73]=0x94;
    APDU[74]=0x06;
    APDU[75]=0x74;
    APDU[76]=0x5B;
    APDU[77]=0xC4;
    APDU[78]=0x6E;
    APDU[79]=0x3F;
    APDU[80]=0x65;
    APDU[81]=0x71;
    APDU[82]=0x3A;
    APDU[83]=0xD7;
    APDU[84]=0xCE;
    APDU[85]=0x54;
    APDU[86]=0x30;
    APDU[87]=0x29;
    APDU[88]=0x6F;
    APDU[89]=0x5C;
    APDU[90]=0x37;
    APDU[91]=0xEE;
    APDU[92]=0x97;
    APDU[93]=0x32;
    APDU[94]=0xF9;
    APDU[95]=0x4F;
    APDU[96]=0xF5;
    APDU[97]=0x6A;
    APDU[98]=0xC7;
    APDU[99]=0x46;
    APDU[100]=0xDA;
    APDU[101]=0x01;
    APDU[102]=0xF6;
    APDU[103]=0x6C;
    APDU[104]=0xA0;
    APDU[105]=0x39;
    APDU[106]=0x54;
    APDU[107]=0xCB;
    APDU[108]=0xB3;
    APDU[109]=0x4D;
    APDU[110]=0x70;
    APDU[111]=0x9E;
    APDU[112]=0x5C;
    APDU[113]=0xB4;
    APDU[114]=0x8E;
    APDU[115]=0x74;
    APDU[116]=0xD1;
    APDU[117]=0x22;
    APDU[118]=0x0F;
    APDU[119]=0x7A;
    APDU[120]=0xB3;
    APDU[121]=0x86;
    APDU[122]=0x42;
    APDU[123]=0x76;
    APDU[124]=0xD8;
    APDU[125]=0x52;
    APDU[126]=0x62;
    APDU[127]=0x09;
    APDU[128]=0xB5;
    APDU[129]=0x78;
    APDU[130]=0x09;
    APDU[131]=0x01;
    APDU[132]=0xD2;
    APDU[133]=0xBF;
    APDU[134]=0xBE;
    APDU[135]=0xF0;
    APDU[136]=0x0E;
    APDU[137]=0x6B;
    APDU[138]=0x6B;
    APDU[139]=0xC5;
    APDU[140]=0xE2;
    APDU[141]=0x3C;
    APDU[142]=0x75;
    APDU[143]=0x6A;
    APDU[144]=0xF9;
    APDU[145]=0x54;
    APDU[146]=0x07;
    APDU[147]=0xFA;
    APDU[148]=0x75;
    APDU[149]=0x90;
    APDU[150]=0x2A;
    APDU[151]=0x9C;
    APDU[152]=0x1D;
    APDU[153]=0xAF;
    APDU[154]=0xCC;
    APDU[155]=0xB8;
    APDU[156]=0x45;
    APDU[157]=0x63;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 0302成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 0303  QMOT

    //store data dgi 0401(电子现金发卡机构授权码)
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x07;
    APDU[4]=0x99;
    APDU[5]=0x03;
    APDU[6]=0x02;
    APDU[7]=0x96;
    APDU[8]=0x70;
    APDU[9]=0x81;
    APDU[10]=0x93;
    APDU[11]=0x93;
    APDU[12]=0x81;
    APDU[13]=0x90;
    APDU[14]=0x13;
    APDU[15]=0x44;
    APDU[16]=0x63;
    APDU[17]=0x6B;
    APDU[18]=0xC9;
    APDU[19]=0x1A;
    APDU[20]=0x9E;
    APDU[21]=0x28;
    APDU[22]=0x7E;
    APDU[23]=0x85;
    APDU[24]=0x32;
    APDU[25]=0x3E;
    APDU[26]=0x12;
    APDU[27]=0x9C;
    APDU[28]=0xA2;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 0401成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 0801(启用标志)
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x0A;
    APDU[4]=0x20;
    APDU[5]=0x08;
    APDU[6]=0x01;
    APDU[7]=0x1D;
    APDU[8]=0x70;
    APDU[9]=0x1B;
    APDU[10]=0xDF;
    APDU[11]=0x24;
    APDU[12]=0x04;
    APDU[13]=0x20;
    APDU[14]=0x30;
    APDU[15]=0x12;
    APDU[16]=0x31;
    APDU[17]=0xDF;
    APDU[18]=0x25;
    APDU[19]=0x04;
    APDU[20]=0x20;
    APDU[21]=0x15;
    APDU[22]=0x01;
    APDU[23]=0x01;
    APDU[24]=0xDF;
    APDU[25]=0x21;
    APDU[26]=0x01;
    APDU[27]=0x30;
    APDU[28]=0xDF;
    APDU[29]=0x22;
    APDU[30]=0x02;
    APDU[31]=0x00;
    APDU[32]=0x00;
    APDU[33]=0xDF;
    APDU[34]=0x23;
    APDU[35]=0x01;
    APDU[36]=0x00;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 0801成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 0D01(卡片内部风险管理数据)
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x0B;
    APDU[4]=0x4C;
    APDU[5]=0x0D;
    APDU[6]=0x01;
    APDU[7]=0x49;
    APDU[8]=0x9F;
    APDU[9]=0x55;
    APDU[10]=0x01;
    APDU[11]=0xC0;
    APDU[12]=0x9F;
    APDU[13]=0x56;
    APDU[14]=0x01;
    APDU[15]=0x00;
    APDU[16]=0x9F;
    APDU[17]=0x57;
    APDU[18]=0x02;
    APDU[19]=0x01;
    APDU[20]=0x56;
    APDU[21]=0x9F;
    APDU[22]=0x58;
    APDU[23]=0x01;
    APDU[24]=0x00;
    APDU[25]=0x9F;
    APDU[26]=0x59;
    APDU[27]=0x01;
    APDU[28]=0x00;
    APDU[29]=0x9F;
    APDU[30]=0x72;
    APDU[31]=0x01;
    APDU[32]=0x00;
    APDU[33]=0x9F;
    APDU[34]=0x53;
    APDU[35]=0x01;
    APDU[36]=0x00;
    APDU[37]=0x9F;
    APDU[38]=0x54;
    APDU[39]=0x06;
    APDU[40]=0x00;
    APDU[41]=0x00;
    APDU[42]=0x00;
    APDU[43]=0x00;
    APDU[44]=0x00;
    APDU[45]=0x00;
    APDU[46]=0x9F;
    APDU[47]=0x5C;
    APDU[48]=0x06;
    APDU[49]=0x00;
    APDU[50]=0x00;
    APDU[51]=0x00;
    APDU[52]=0x00;
    APDU[53]=0x00;
    APDU[54]=0x00;
    APDU[55]=0x9F;
    APDU[56]=0x73;
    APDU[57]=0x04;
    APDU[58]=0x20;
    APDU[59]=0x00;
    APDU[60]=0x01;
    APDU[61]=0x75;
    APDU[62]=0x9F;
    APDU[63]=0x75;
    APDU[64]=0x06;
    APDU[65]=0x00;
    APDU[66]=0x00;
    APDU[67]=0x00;
    APDU[68]=0x00;
    APDU[69]=0x00;
    APDU[70]=0x00;
    APDU[71]=0x9F;
    APDU[72]=0x76;
    APDU[73]=0x02;
    APDU[74]=0x00;
    APDU[75]=0x00;
    APDU[76]=0x9F;
    APDU[77]=0x36;
    APDU[78]=0x02;
    APDU[79]=0x00;
    APDU[80]=0x00;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 0D01成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 0E01

    //store data dgi 8000(对称密钥 国际算法 应用密文DEA密钥 报文鉴别码DEA密钥 数据加密DEA密钥)
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x60;
    APDU[3]=0x0D;
    APDU[4]=0x33;
    APDU[5]=0x80;
    APDU[6]=0x00;
    APDU[7]=0x30;
    APDU[8]=0xF2;
    APDU[9]=0xA2;
    APDU[10]=0x82;
    APDU[11]=0xDD;
    APDU[12]=0xB9;
    APDU[13]=0x08;
    APDU[14]=0xDA;
    APDU[15]=0x3B;
    APDU[16]=0xA1;
    APDU[17]=0x91;
    APDU[18]=0x99;
    APDU[19]=0xA8;
    APDU[20]=0xED;
    APDU[21]=0x72;
    APDU[22]=0x60;
    APDU[23]=0x1F;
    APDU[24]=0xF2;
    APDU[25]=0xA2;
    APDU[26]=0x82;
    APDU[27]=0xDD;
    APDU[28]=0xB9;
    APDU[29]=0x08;
    APDU[30]=0xDA;
    APDU[31]=0x3B;
    APDU[32]=0xA1;
    APDU[33]=0x91;
    APDU[34]=0x99;
    APDU[35]=0xA8;
    APDU[36]=0xED;
    APDU[37]=0x72;
    APDU[38]=0x60;
    APDU[39]=0x1F;
    APDU[40]=0xF2;
    APDU[41]=0xA2;
    APDU[42]=0x82;
    APDU[43]=0xDD;
    APDU[44]=0xB9;
    APDU[45]=0x08;
    APDU[46]=0xDA;
    APDU[47]=0x3B;
    APDU[48]=0xA1;
    APDU[49]=0x91;
    APDU[50]=0x99;
    APDU[51]=0xA8;
    APDU[52]=0xED;
    APDU[53]=0x72;
    APDU[54]=0x60;
    APDU[55]=0x1F;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 8000成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 9000(应用密文DEA密钥 报文鉴别码DEA密钥 数据加密DEA密钥 对称密钥DES校验值)
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x10;
    APDU[4]=0x0C;
    APDU[5]=0x90;
    APDU[6]=0x00;
    APDU[7]=0x09;
    APDU[8]=0x8D;
    APDU[9]=0x66;
    APDU[10]=0x4A;
    APDU[11]=0x8D;
    APDU[12]=0x66;
    APDU[13]=0x4A;
    APDU[14]=0x8D;
    APDU[15]=0x66;
    APDU[16]=0x4A;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 9000成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 8010  脱机PIN 123456
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x60;
    APDU[3]=0x0F;
    APDU[4]=0x0B;
    APDU[5]=0x80;
    APDU[6]=0x10;
    APDU[7]=0x08;
    APDU[8]=0x06;
    APDU[9]=0x1F;
    APDU[10]=0x2B;
    APDU[11]=0x12;
    APDU[12]=0x75;
    APDU[13]=0x33;
    APDU[14]=0xBD;
    APDU[15]=0xAE;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 8010成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 9010 脱机PIN 尝试计数器
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x10;
    APDU[4]=0x05;
    APDU[5]=0x90;
    APDU[6]=0x10;
    APDU[7]=0x02;
    APDU[8]=0x03;
    APDU[9]=0x03;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 9010成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 8F01
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x11;
    APDU[4]=0x33;
    APDU[5]=0x8F;
    APDU[6]=0x01;
    APDU[7]=0x30;
    APDU[8]=0xA6;
    APDU[9]=0x16;
    APDU[10]=0xDD;
    APDU[11]=0x77;
    APDU[12]=0xD4;
    APDU[13]=0xA3;
    APDU[14]=0x11;
    APDU[15]=0xE0;
    APDU[16]=0xA6;
    APDU[17]=0x16;
    APDU[18]=0xDD;
    APDU[19]=0x77;
    APDU[20]=0xD4;
    APDU[21]=0xA3;
    APDU[22]=0x11;
    APDU[23]=0xE0;
    APDU[24]=0xA6;
    APDU[25]=0x16;
    APDU[26]=0xDD;
    APDU[27]=0x77;
    APDU[28]=0xD4;
    APDU[29]=0xA3;
    APDU[30]=0x11;
    APDU[31]=0xE0;
    APDU[32]=0xA6;
    APDU[33]=0x16;
    APDU[34]=0xDD;
    APDU[35]=0x77;
    APDU[36]=0xD4;
    APDU[37]=0xA3;
    APDU[38]=0x11;
    APDU[39]=0xE0;
    APDU[40]=0xA6;
    APDU[41]=0x16;
    APDU[42]=0xDD;
    APDU[43]=0x77;
    APDU[44]=0xD4;
    APDU[45]=0xA3;
    APDU[46]=0x11;
    APDU[47]=0xE0;
    APDU[48]=0xA6;
    APDU[49]=0x16;
    APDU[50]=0xDD;
    APDU[51]=0x77;
    APDU[52]=0xD4;
    APDU[53]=0xA3;
    APDU[54]=0x11;
    APDU[55]=0xE0;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 8F01成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 7F01
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x12;
    APDU[4]=0x0F;
    APDU[5]=0x7F;
    APDU[6]=0x01;
    APDU[7]=0x0C;
    APDU[8]=0x00;
    APDU[9]=0x20;
    APDU[10]=0x80;
    APDU[11]=0x8C;
    APDU[12]=0xA6;
    APDU[13]=0x4D;
    APDU[14]=0x8C;
    APDU[15]=0xA6;
    APDU[16]=0x4D;
    APDU[17]=0x8C;
    APDU[18]=0xA6;
    APDU[19]=0x4D;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 7F01成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi A001
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x13;
    APDU[4]=0x25;
    APDU[5]=0xA0;
    APDU[6]=0x01;
    APDU[7]=0x22;
    APDU[8]=0x1A;
    APDU[9]=0x19;
    APDU[10]=0x1A;
    APDU[11]=0x5F;
    APDU[12]=0x02;
    APDU[13]=0x60;
    APDU[14]=0x01;
    APDU[15]=0xDF;
    APDU[16]=0x25;
    APDU[17]=0x9A;
    APDU[18]=0x03;
    APDU[19]=0x01;
    APDU[20]=0x9C;
    APDU[21]=0x37;
    APDU[22]=0x04;
    APDU[23]=0x9F;
    APDU[24]=0x11;
    APDU[25]=0x1E;
    APDU[26]=0x19;
    APDU[27]=0x1A;
    APDU[28]=0x5F;
    APDU[29]=0x02;
    APDU[30]=0x60;
    APDU[31]=0x01;
    APDU[32]=0xDF;
    APDU[33]=0x25;
    APDU[34]=0x9A;
    APDU[35]=0x03;
    APDU[36]=0x01;
    APDU[37]=0x9C;
    APDU[38]=0x37;
    APDU[39]=0x04;
    APDU[40]=0x9F;
    APDU[41]=0x11;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi A001成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 8201 IC卡 RSA CRT私钥QINV(Coefficent)分量

    //store data dgi 8202  IC卡 RSA CRT私钥Dp(Exp1)分量

    //store data dgi 8203  IC卡 RSA CRT私钥Dq（Exp2）分量

    //store data dgi 8204  IC卡 RSA CRT私钥p分量

    //store data dgi 8205  RSA CRT私钥q分量

    //store data dgi 9102   选择AID响应数据FCI（借贷记、电子现金）
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x19;
    APDU[4]=0x55;
    APDU[5]=0x91;
    APDU[6]=0x02;
    APDU[7]=0x52;
    APDU[8]=0xA5;
    APDU[9]=0x50;
    APDU[10]=0x50;
    APDU[11]=0x0B;
    APDU[12]=0x50;
    APDU[13]=0x42;
    APDU[14]=0x4F;
    APDU[15]=0x43;
    APDU[16]=0x20;
    APDU[17]=0x43;
    APDU[18]=0x72;
    APDU[19]=0x65;
    APDU[20]=0x64;
    APDU[21]=0x69;
    APDU[22]=0x74;
    APDU[23]=0x87;
    APDU[24]=0x01;
    APDU[25]=0x01;
    APDU[26]=0x9F;
    APDU[27]=0x38;
    APDU[28]=0x0F;
    APDU[29]=0x9F;
    APDU[30]=0x1A;
    APDU[31]=0x02;
    APDU[32]=0x9F;
    APDU[33]=0x7A;
    APDU[34]=0x01;
    APDU[35]=0x9F;
    APDU[36]=0x02;
    APDU[37]=0x06;
    APDU[38]=0x5F;
    APDU[39]=0x2A;
    APDU[40]=0x02;
    APDU[41]=0x9F;
    APDU[42]=0x4E;
    APDU[43]=0x14;
    APDU[44]=0x5F;
    APDU[45]=0x2D;
    APDU[46]=0x08;
    APDU[47]=0x7A;
    APDU[48]=0x68;
    APDU[49]=0x65;
    APDU[50]=0x6E;
    APDU[51]=0x66;
    APDU[52]=0x72;
    APDU[53]=0x64;
    APDU[54]=0x65;
    APDU[55]=0x9F;
    APDU[56]=0x11;
    APDU[57]=0x01;
    APDU[58]=0x01;
    APDU[59]=0x9F;
    APDU[60]=0x12;
    APDU[61]=0x0F;
    APDU[62]=0x43;
    APDU[63]=0x41;
    APDU[64]=0x52;
    APDU[65]=0x44;
    APDU[66]=0x20;
    APDU[67]=0x49;
    APDU[68]=0x4D;
    APDU[69]=0x41;
    APDU[70]=0x47;
    APDU[71]=0x45;
    APDU[72]=0x20;
    APDU[73]=0x30;
    APDU[74]=0x30;
    APDU[75]=0x30;
    APDU[76]=0x31;
    APDU[77]=0xBF;
    APDU[78]=0x0C;
    APDU[79]=0x0A;
    APDU[80]=0x9F;
    APDU[81]=0x4D;
    APDU[82]=0x02;
    APDU[83]=0x0B;
    APDU[84]=0x0A;
    APDU[85]=0xDF;
    APDU[86]=0x4D;
    APDU[87]=0x02;
    APDU[88]=0x0C;
    APDU[89]=0x0A;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 9102成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 9103   选择AID应用响应数据FCI（qMOT）

    //store data dgi 9104 GPO响应数据RSA算法（联机MOT）-
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x1B;
    APDU[4]=0x11;
    APDU[5]=0x91;
    APDU[6]=0x04;
    APDU[7]=0x0E;
    APDU[8]=0x82;
    APDU[9]=0x02;
    APDU[10]=0x7C;
    APDU[11]=0x00;
    APDU[12]=0x94;
    APDU[13]=0x08;
    APDU[14]=0x08;
    APDU[15]=0x01;
    APDU[16]=0x02;
    APDU[17]=0x00;
    APDU[18]=0x10;
    APDU[19]=0x01;
    APDU[20]=0x03;
    APDU[21]=0x01;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 9104成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 9200 GAC响应数据（联机MOT）-
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x1D;
    APDU[4]=0x10;
    APDU[5]=0x92;
    APDU[6]=0x03;
    APDU[7]=0x0D;
    APDU[8]=0x9F;
    APDU[9]=0x10;
    APDU[10]=0x0A;
    APDU[11]=0x07;
    APDU[12]=0x01;
    APDU[13]=0x01;
    APDU[14]=0x03;
    APDU[15]=0x00;
    APDU[16]=0x00;
    APDU[17]=0x00;
    APDU[18]=0x01;
    APDU[19]=0x0A;
    APDU[20]=0x01;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 9200成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 9203  GAC响应数据（qMOT）-
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x00;
    APDU[3]=0x1D;
    APDU[4]=0x10;
    APDU[5]=0x92;
    APDU[6]=0x03;
    APDU[7]=0x0D;
    APDU[8]=0x9F;
    APDU[9]=0x10;
    APDU[10]=0x0A;
    APDU[11]=0x07;
    APDU[12]=0x01;
    APDU[13]=0x01;
    APDU[14]=0x03;
    APDU[15]=0x00;
    APDU[16]=0x00;
    APDU[17]=0x00;
    APDU[18]=0x01;
    APDU[19]=0x0A;
    APDU[20]=0x01;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 9203成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //store data dgi 9207 GPO响应数据RSA算法（qMOT）-
    APDU[0]=0x80;
    APDU[1]=0xE2;
    APDU[2]=0x80;
    APDU[3]=0x1E;
    APDU[4]=0x15;
    APDU[5]=0x92;
    APDU[6]=0x07;
    APDU[7]=0x12;
    APDU[8]=0x82;
    APDU[9]=0x02;
    APDU[10]=0x7C;
    APDU[11]=0x00;
    APDU[12]=0x94;
    APDU[13]=0x0C;
    APDU[14]=0x08;
    APDU[15]=0x02;
    APDU[16]=0x02;
    APDU[17]=0x00;
    APDU[18]=0x18;
    APDU[19]=0x01;
    APDU[20]=0x03;
    APDU[21]=0x01;
    APDU[22]=0x20;
    APDU[23]=0x01;
    APDU[24]=0x01;
    APDU[25]=0x00;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"store data dgi 9207成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //select EC
    APDU[0]=0x00;
    APDU[1]=0xA4;
    APDU[2]=0x04;
    APDU[3]=0x00;
    APDU[4]=0x08;
    APDU[5]=0xA0;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0x06;
    APDU[9]=0x32;
    APDU[10]=0x01;
    APDU[11]=0x01;
    APDU[12]=0x06;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"select EC成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //read ATC(9F36)
    APDU[0]=0x80;
    APDU[1]=0xCA;
    APDU[2]=0x9F;
    APDU[3]=0x36;
    APDU[4]=0x00;
    RevBuff[0] = 0x02;
    RevBuff[1] = (char)((4 + APDU.length()) >> 8 & 0xFF);//协议总长度高8位
    RevBuff[2] = (char)((4 + APDU.length()) & 0xFF);//协议总长度低8位
    RevBuff[3] = 0x37;
    RevBuff[4] = 0x31;
    RevBuff[5] = (char)(APDU.length() >> 8 & 0xFF);//APDU指令长度高8位
    RevBuff[6] = (char)(APDU.length() & 0xFF);//APDU指令长度低8位
    for (i=0; i < APDU.length(); i++)
    {
        RevBuff[7 + i] = APDU[i];//APDU指令内容 从RevBuff[7]开始
    }
    RevBuff[7+i] = 0x03;
    RevBuff[8+i] = CheckBCC(RevBuff,0,7+i);
    serial->write(RevBuff);
    qDebug()<<"read ATC成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

*/
}


//圈存
void MainWindow::on_CreditForLoad_Btn_clicked()
{
    //选择MF
    int i =0;
    QByteArray APDU;
    APDU[0]=0x00;
    APDU[1]=0xA4;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x02;
    APDU[5]=0x3F;
    APDU[6]=0x00;
    QByteArray RevBuff;//接收缓存
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"选择MF成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //选择互通EP
    APDU[0]=0x00;
    APDU[1]=0xA4;
    APDU[2]=0x04;
    APDU[3]=0x00;
    APDU[4]=0x08;
    APDU[5]=0xA0;
    APDU[6]=0x00;
    APDU[7]=0x00;
    APDU[8]=0x06;
    APDU[9]=0x32;
    APDU[10]=0x01;
    APDU[11]=0x01;
    APDU[12]=0x05;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"选择互通EP成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);

    //初始化圈存
    APDU[0]=0x80;
    APDU[1]=0x50;
    APDU[2]=0x00;
    APDU[3]=0x02;
    APDU[4]=0x0B;
    APDU[5]=0x02;
    APDU[6]=0x00;
    APDU[7]=0x01;
    APDU[8]=0x85;
    APDU[9]=0x42;//充996.5元
    APDU[10]=0x34;
    APDU[11]=0x01;
    APDU[12]=0x42;
    APDU[13]=0x30;
    APDU[14]=0x00;
    APDU[15]=0x72;//终端机编号
    APDU[16]=0x10;
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"初始化圈存成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);


    //过程密钥计算
    //数据准备
    QByteArray temp;
    temp.resize(8);
    for(i=4;i<6;i++)
    {
        temp[i]=buf[i+8]; //填充联机交易序号
    }
    for(i=0;i<4;i++)
    {
        temp[i]=buf[i+16]; //填充随机数
    }
    temp[6]=0x80;
    temp[7]=0x00;
    qDebug()<<"过程密钥输入数据:"<<temp.toHex().toUpper();
    Sleep(10);

    //计算过程密钥
    unsigned char creditkey[]={0x58,0x05,0x93,0xDF,0xF5,0x41,0xB0,0xEA,0xB8,0x1D,0xA2,0xF8,0xD8,0xAC,0x9B,0xE9};
    unsigned char tempch[8];
    memcpy(tempch,temp,8);
    unsigned char processkey[8];
    CurCalc_3DES_Encrypt(creditkey,tempch,processkey);
    char* testout1=(char*)processkey;
    QByteArray testout2=QByteArray(testout1,8);
    qDebug()<<"过程密钥为:"<<testout2.toHex().toUpper();
    Sleep(10);

    //MAC2计算
    /*
    QByteArray mac2in;
    mac2in.resize(18);
    mac2in[0]=0x00;
    mac2in[1]=0x01;
    mac2in[2]=0x85;
    mac2in[3]=0x42;
    mac2in[4]=0x02;
    mac2in[5]=0x34;
    mac2in[6]=0x01;
    mac2in[7]=0x42;
    mac2in[8]=0x30;
    mac2in[9]=0x00;
    mac2in[10]=0x72;
    mac2in[11]=0x20;
    mac2in[12]=0x19;
    mac2in[13]=0x08;
    mac2in[14]=0x22;
    mac2in[15]=0x11;
    mac2in[16]=0x12;
    mac2in[17]=0x13;
    */
    unsigned char mac2inch[]={0x00,0x01,0x85,0x42,0x02,0x34,0x01,0x42,0x30,0x00,0x72,0x20,0x19,0x08,0x22,0x11,0x12,0x13};
    //memcpy(mac2inch,mac2in,18);
    unsigned char mac2ch[4];
    unsigned char initdata[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    PBOC_DES_MAC(initdata,mac2inch,18,processkey,mac2ch);
    char* out=(char*)mac2ch;
    QByteArray out2=QByteArray(out,4);
    Sleep(10);

    //圈存命令
    APDU[0]=0x80;
    APDU[1]=0x52;
    APDU[2]=0x00;
    APDU[3]=0x00;
    APDU[4]=0x0B;
    APDU[5]=0x20;
    APDU[6]=0x19;
    APDU[7]=0x08;
    APDU[8]=0x22;
    APDU[9]=0x11;
    APDU[10]=0x12;
    APDU[11]=0x13;
    APDU[12]=out2[0];
    APDU[13]=out2[1];
    APDU[14]=out2[2];
    APDU[15]=out2[3];
    APDUPack(APDU,RevBuff);
    serial->write(RevBuff);
    qDebug()<<"圈存命令成功";
    APDU.clear();
    RevBuff.clear();
    Sleep(500);
}

