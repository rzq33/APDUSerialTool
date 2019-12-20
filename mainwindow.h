#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QTime>
#include <QCryptographicHash>
#include <QString>
#include <tool.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QSerialPort *serial = new QSerialPort();
    QByteArray buf;
    QByteArray buf2;
    ~MainWindow();

private slots:
    void on_OpenSerialButton_clicked();

    void ReadData();

    void on_SendButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_SD_clicked();

    void StringToHex(QString str,QByteArray &senddata);

    char ConvertHexChar(char ch);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_SearchSerialButton_clicked();

    void on_ClearButton_clicked();

    void on_APDUSendButton_clicked();

    char CheckBCC(QByteArray nums, int firstIndex, int lastIndex);

    void on_huanhangButton_clicked();

    void GetAID(QByteArray indata,QByteArray &outdata);

    void GetGPO(QByteArray indata1, QByteArray &outdata1);

    void ReadRecord(QByteArray indata1);

    void Sleep(int msec);

    void on_encryption_btn_clicked();

    void on_decryption_btn_clicked();

    void Sha1Bt();

    void on_resetButton_clicked();

    void on_clearButton_clicked();

    void on_newButton_clicked();

    void on_tdesencryption_btn_clicked();

    void on_desmac_btn_clicked();

    void on_tdesmac_btn_clicked();

    void on_CreditForLoad_Btn_clicked();

    void on_CRCwork_btn_clicked();

    void APDUPack(QByteArray APDU, QByteArray &RevBuff);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
