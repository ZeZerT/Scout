#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedWidth(this->width());

    if((QTime::currentTime().hour() >=6) && (QTime::currentTime().hour()<=18)) LogAction("Bonjour à toi, Scout !");
    else LogAction("Bonsoir à toi, Scout !");

    nbDolyaksRestant = 0;
    nbDolyaksTotal = 0;
    nbDolyaksRavit = 35;

    a_timer = new QTimer(this);
    c_timer = new QTimer(this);

    connect(a_timer, SIGNAL(timeout()), this, SLOT(update_armes()));
    connect(c_timer, SIGNAL(timeout()), this, SLOT(update_camp()));

    a_start = false;    a_minutes = 45;     a_secondes = 0;     a_timer->start(1000);
    c_start = false;    c_minutes = 5;      c_secondes = 0;     c_timer->start(1000);

    nbDolyaksRavit = 35;
    ui->comboBox_Ravit->setItemText(0, "T1");
    ui->comboBox_Ravit->setItemText(1, "T2");
    ui->comboBox_Ravit->setItemText(2, "T3");
    ui->comboBox_Ravit->setItemText(3, "Huile");
    ui->comboBox_Ravit->setItemText(4, "Canons");
    ui->comboBox_Ravit->setItemText(5, "Mortiers");

    nbDolyaksTotal =6;
    UpdateBesoinDodo(false, 0);
    connect(ui->actionVider_le_log, SIGNAL(triggered()), this, SLOT(viderLog()));
    connect(ui->actionCredits, SIGNAL(triggered()), this, SLOT(credits()));
    connect(ui->actionAide, SIGNAL(triggered()), this, SLOT(aide()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_armes_clicked()
{
    a_start = false;    a_minutes = 45;     a_secondes = 0;
    ui->label_timer_armes->setStyleSheet("QLabel {color : black; }");
    LogAction("Armes reset.");
    a_start = true;
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    c_start = false;
    c_minutes = 5;  c_secondes = 0;
    ui->label_timer_camp->setStyleSheet("QLabel {color : black; }");

    if(arg1 == "UP 100"){
        ui->label_timer_camp->setText("05:00");
        LogAction("Amélioration à 100 de ravit lancé.");
    }
    if(arg1 == "Camp buff"){
        ui->label_timer_camp->setText("05:00");
        LogAction("Le camp a été reset.");
    }
    if(arg1 == "UP 150"){
        LogAction("Amélioration à 150 de ravit lancé.");
        ui->label_timer_camp->setText("07:30");
        c_minutes += 2;  c_secondes += 30;
    }
    c_start = true;
}

void MainWindow::on_comboBox_Type_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Tour"){
        nbDolyaksRavit = 35;
        ui->comboBox_Ravit->setItemText(0, "T1");         //200
        ui->comboBox_Ravit->setItemText(1, "T2");         //400
        ui->comboBox_Ravit->setItemText(2, "T3");         //800
        ui->comboBox_Ravit->setItemText(3, "Huile");      //100
        ui->comboBox_Ravit->setItemText(4, "Canons");     //200
        ui->comboBox_Ravit->setItemText(5, "Mortiers");   //400
    }

    if(arg1 == "Fort"){
        nbDolyaksRavit = 70;
        ui->comboBox_Ravit->setItemText(0, "T1");         //500
        ui->comboBox_Ravit->setItemText(1, "T2");         //1000
        ui->comboBox_Ravit->setItemText(2, "T3");         //2000
        ui->comboBox_Ravit->setItemText(3, "Canons");     //400
        ui->comboBox_Ravit->setItemText(4, "Mortiers");   //800
        ui->comboBox_Ravit->setItemText(5, "TP");         //1600
    }

    if(arg1 == "Château"){
        nbDolyaksRavit = 80;
        ui->comboBox_Ravit->setItemText(0, "T1");         //1000
        ui->comboBox_Ravit->setItemText(1, "T2");         //2000
        ui->comboBox_Ravit->setItemText(2, "T3");         //4000
        ui->comboBox_Ravit->setItemText(3, "Canons");     //750
        ui->comboBox_Ravit->setItemText(4, "Mortiers");   //1500
        ui->comboBox_Ravit->setItemText(5, "TP");         //3000
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int dodoNecessaire =0;
    if(ui->comboBox_Type->currentText() == "Tour"){
        if(ui->comboBox_Ravit->currentText() == "T1")         dodoNecessaire = (200/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "T2")         dodoNecessaire = (400/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "T3")         dodoNecessaire = (800/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "Huile")      dodoNecessaire = (100/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "Canons")     dodoNecessaire = (200/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "Mortiers")   dodoNecessaire = (400/nbDolyaksRavit)+1;
    }

    if(ui->comboBox_Type->currentText() == "Fort"){
        if(ui->comboBox_Ravit->currentText() == "T1")         dodoNecessaire = (500/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "T2")         dodoNecessaire = (1000/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "T3")         dodoNecessaire = (2000/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "Canons")     dodoNecessaire = (400/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "Mortiers")   dodoNecessaire = (800/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "TP")         dodoNecessaire = (1600/nbDolyaksRavit)+1;
    }

    if(ui->comboBox_Type->currentText() == "Château"){
        if(ui->comboBox_Ravit->currentText() == "T1")         dodoNecessaire = (1000/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "T2")         dodoNecessaire = 2000/nbDolyaksRavit;
        if(ui->comboBox_Ravit->currentText() == "T3")         dodoNecessaire = 4000/nbDolyaksRavit;
        if(ui->comboBox_Ravit->currentText() == "Canons")     dodoNecessaire = (750/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "Mortiers")   dodoNecessaire = (1500/nbDolyaksRavit)+1;
        if(ui->comboBox_Ravit->currentText() == "TP")         dodoNecessaire = (3000/nbDolyaksRavit)+1;
    }
    value *= dodoNecessaire;
    value /= 100;

    UpdateBesoinDodo(false, value);
}

void MainWindow::on_comboBox_Ravit_currentTextChanged(const QString &arg1)
{    ui->horizontalSlider->setValue(0);
     nbDolyaksRestant = 0;

     if(ui->comboBox_Type->currentText() == "Tour"){
         if(arg1 == "T1")         nbDolyaksTotal = (200/nbDolyaksRavit)+1;
         if(arg1 == "T2")         nbDolyaksTotal = (400/nbDolyaksRavit)+1;
         if(arg1 == "T3")         nbDolyaksTotal = (800/nbDolyaksRavit)+1;
         if(arg1 == "Huile")      nbDolyaksTotal = (100/nbDolyaksRavit)+1;
         if(arg1 == "Canons")     nbDolyaksTotal = (200/nbDolyaksRavit)+1;
         if(arg1 == "Mortiers")   nbDolyaksTotal = (400/nbDolyaksRavit)+1;
     }

     if(ui->comboBox_Type->currentText() == "Fort"){
         if(arg1 == "T1")         nbDolyaksTotal = (500/nbDolyaksRavit)+1;
         if(arg1 == "T2")         nbDolyaksTotal = (1000/nbDolyaksRavit)+1;
         if(arg1 == "T3")         nbDolyaksTotal = (2000/nbDolyaksRavit)+1;
         if(arg1 == "Canons")     nbDolyaksTotal = (400/nbDolyaksRavit)+1;
         if(arg1 == "Mortiers")   nbDolyaksTotal = (800/nbDolyaksRavit)+1;
         if(arg1 == "TP")         nbDolyaksTotal = (1600/nbDolyaksRavit)+1;
     }

     if(ui->comboBox_Type->currentText() == "Château"){
         if(arg1 == "T1")         nbDolyaksTotal = (1000/nbDolyaksRavit)+1;
         if(arg1 == "T2")         nbDolyaksTotal = 2000/nbDolyaksRavit;
         if(arg1 == "T3")         nbDolyaksTotal = 4000/nbDolyaksRavit;
         if(arg1 == "Canons")     nbDolyaksTotal = (750/nbDolyaksRavit)+1;
         if(arg1 == "Mortiers")   nbDolyaksTotal = (1500/nbDolyaksRavit)+1;
         if(arg1 == "TP")         nbDolyaksTotal = (3000/nbDolyaksRavit)+1;
     }

     UpdateBesoinDodo(true);
}

void MainWindow::on_checkBox_double_clicked()
{
    ui->pushButton_1Dolyak->setText("Dolyak simple");
    if(ui->checkBox_double->isChecked())ui->pushButton_1Dolyak->setText("Dolyak double");
}

void MainWindow::UpdateBesoinDodo(bool reset, int nbDodo){
    bool continuer = true;
    if(nbDodo==-1)  nbDolyaksRestant++;
    if(nbDolyaksRestant > nbDolyaksTotal)continuer = false;
    if(ui->checkBox_double->isChecked())  nbDolyaksRestant++;
    if(reset)       nbDolyaksRestant =0;

    if(continuer){
        if(nbDodo>-1)    nbDolyaksRestant = nbDodo;
        QString unite = QString("%1").arg((nbDolyaksRestant), 2, 10, QChar('0'));
        QString total = QString("%1").arg((nbDolyaksTotal), 2, 10, QChar('0'));

        ui->label_dolyaks->setText(unite + "/" + total);
        if(nbDolyaksRestant>=nbDolyaksTotal) ui->label_dolyaks->setText("GG!");
    }
}


void MainWindow::on_pushButton_1Dolyak_clicked()
{
    UpdateBesoinDodo();
}

void MainWindow::update_armes(){
    if(a_secondes == 0){
        if(a_minutes != 0){
            a_minutes--;
            a_secondes = 59;
        }
    }else   a_secondes--;

    if(ui->label_timer_armes->text() == "00:00"){
        if(ui->actionPop_up_reset_des_armes->isChecked()){
            if(a_start)QMessageBox::information( this, tr("Scout"), tr("Il faut reset les armes !"));
        }else    if(a_start)ui->label_timer_armes->setStyleSheet("QLabel { background-color : red; color : blue; }");
        a_start=false;
    }

    QString scnd = QString("%1").arg(a_secondes, 2, 10, QChar('0'));
    QString min = QString("%1").arg(a_minutes, 2, 10, QChar('0'));
    if(a_start)ui->label_timer_armes->setText(min+":"+scnd);
}

void MainWindow::update_camp(){
    if(c_secondes == 0){
        if(c_minutes != 0){
            c_minutes--;
            c_secondes = 59;
        }
    }else   c_secondes--;

    if(ui->label_timer_camp->text() == "00:00"){
        ui->label_timer_camp->setStyleSheet("QLabel { background-color : red; color : blue; }");
        a_start=false;
    }

    QString scnd = QString("%1").arg(c_secondes, 2, 10, QChar('0'));
    QString min = QString("%1").arg(c_minutes, 2, 10, QChar('0'));
    if(c_start) ui->label_timer_camp->setText(min+":"+scnd);

}

void MainWindow::LogAction(QString message){
    QString h = QString("%1").arg((QTime::currentTime().hour()), 2, 10, QChar('0'));
    QString m = QString("%1").arg((QTime::currentTime().minute()), 2, 10, QChar('0'));
    QString s = QString("%1").arg((QTime::currentTime().second()), 2, 10, QChar('0'));
    ui->textEdit_log->append("["+h+":"+m+":"+s+"] "+message);
}

void MainWindow::viderLog(){
    ui->textEdit_log->clear();
    LogAction("Log vidé.");
}

void MainWindow::credits(){
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("About..");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Cet outil vise à aider les scouts sur le serveur Roche de l'Augure, de Guild Wars 2. <br>J'accepte et me soumets à tous les machins décrit ici : <a href='https://www.guildwars2.com/en/legal/guild-wars-2-content-terms-of-use/'>Terms of use</a>.<br>Un probleme ou une suggestion ? <A HREF='mailto:weird.industry.dev@gmail.com'>weird.industry.dev@gmail.com</a>.<br><hr>Outil réalisé sous <a href='http://qt-project.org/'>QT Créator</a>.<br>Par <i>Alexandre PONELLE</i>  <small>(Alias : <i>Weird Has Renamed)</i></small>");
    msgBox.exec();
}

void MainWindow::aide(){
    QDesktopServices::openUrl(QUrl("http://auguryrock.com/forum/viewtopic.php?f=14&t=2828", QUrl::TolerantMode));
}
