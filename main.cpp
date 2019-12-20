#include "mainwindow.h"
#include <QApplication>
#include <qdebug.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("APDU工具（新协议）");


    unsigned char crcsrc[]={0x01,0x0b,0x01,0x0e,0x01,0x34,0x00,0x03,0x00,0x90,0x00};
    unsigned int crcdst;
    crcdst=crc16(crcsrc,sizeof(crcsrc));
    int out1=(int)crcdst;
    QByteArray out2;
    out2=intToByte(out1);
    qDebug()<<"CRCTest:"<<out2.toHex().toUpper();

    w.show();
    return a.exec();


}
