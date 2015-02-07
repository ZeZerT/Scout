#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QWidget>
#include <QtCore/qmath.h>
#include <iostream>
#include <QMessageBox>
#include <QDesktopServices>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void update_armes();
    void update_camp();
    void LogAction(QString message);
    void UpdateBesoinDodo(bool reset =false, int nbDodo =-1);

private slots:
    void on_pushButton_armes_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_Type_currentTextChanged(const QString &arg1);
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_1Dolyak_clicked();

    void on_comboBox_Ravit_currentTextChanged(const QString &arg1);
    void on_checkBox_double_clicked();
    void viderLog();
    void credits();

private:
    Ui::MainWindow *ui;
    QTimer* c_timer;
    QTimer* a_timer;

    int c_secondes;
    int c_minutes;
    bool c_start;

    int a_secondes;
    int a_minutes;
    bool a_start;

    int nbDolyaksRestant;
    int nbDolyaksTotal;
    int nbDolyaksRavit;
};

#endif // MAINWINDOW_H
