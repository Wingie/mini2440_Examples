/**     Tic Tac Toe - Game
 *
 *      Kalagatha Ravi Kanth - k.ravikanth447@gmail.com & Team
 *      NIE, Macherla
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
int player=0, count = 0;
int f[9] = {0,0,0,0,0,0,0,0,0};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // start code here
    ui->label->setText("player1");
    player=1;
   }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check()
{
    int t[3][3];
    t[0][0] = (ui->pushButton_1->text() == "X")?1:0;
    t[0][1] = (ui->pushButton_2->text() == "X")?1:0;
    t[0][2] = (ui->pushButton_3->text() == "X")?1:0;
    t[1][0] = (ui->pushButton_4->text() == "X")?1:0;
    t[1][1] = (ui->pushButton_5->text() == "X")?1:0;
    t[1][2] = (ui->pushButton_6->text() == "X")?1:0;
    t[2][0] = (ui->pushButton_7->text() == "X")?1:0;
    t[2][1] = (ui->pushButton_8->text() == "X")?1:0;
    t[2][2] = (ui->pushButton_9->text() == "X")?1:0;

    if(((t[0][0]&&t[0][1]&&t[0][2])||(t[1][0]&&t[1][1]&&t[1][2])||(t[2][0]&&t[2][1]&&t[2][2])||(t[0][0]&&t[1][0]&&t[2][0])||(t[0][1]&&t[1][1]&&t[2][1])||(t[0][2]&&t[1][2]&&t[2][2])||(t[0][0]&&t[1][1]&&t[2][2])||(t[0][2]&&t[1][1]&&t[2][0]))==1)
    {
        ui->label->setText("player1 won the game");
        for(int i=0;i<9;i++)
            f[i]=1;
    }
    else
    {
    int s[3][3];
    s[0][0] = (ui->pushButton_1->text() == "O")?1:0;
    s[0][1] = (ui->pushButton_2->text() == "O")?1:0;
    s[0][2] = (ui->pushButton_3->text() == "O")?1:0;
    s[1][0] = (ui->pushButton_4->text() == "O")?1:0;
    s[1][1] = (ui->pushButton_5->text() == "O")?1:0;
    s[1][2] = (ui->pushButton_6->text() == "O")?1:0;
    s[2][0] = (ui->pushButton_7->text() == "O")?1:0;
    s[2][1] = (ui->pushButton_8->text() == "O")?1:0;
    s[2][2] = (ui->pushButton_9->text() == "O")?1:0;

    if(((s[0][0]&&s[0][1]&&s[0][2])||(s[1][0]&&s[1][1]&&s[1][2])||(s[2][0]&&s[2][1]&&s[2][2])||(s[0][0]&&s[1][0]&&s[2][0])||(s[0][1]&&s[1][1]&&s[2][1])||(s[0][2]&&s[1][2]&&s[2][2])||(s[0][0]&&s[1][1]&&s[2][2])||(s[0][2]&&s[1][1]&&s[2][0]))==1)
    {
        ui->label->setText("player2 won the game");
        for(int i=0;i<9;i++)
            f[i]=1;
    }
 }
    if(count==9)
    ui->label->setText("the game is tied");
}

void MainWindow::on_pushButton_1_clicked()
{

    if (f[0] == 1)
        return;

    if(player==1)
    {
        ui->pushButton_1->setText("X");
        ui->label->setText("player2");
        player=2;
    }
    else
    {
        ui->pushButton_1->setText("O");
        ui->label->setText("player1");
        player=1;
    }
   f[0] = 1;
   count++;
    check();
}


void MainWindow::on_pushButton_2_clicked()
{


    if (f[1] == 1)
        return;

    if(player==1)
    {
        ui->pushButton_2->setText("X");
        ui->label->setText("player");
        player=2;
    }
    else
    {
        ui->pushButton_2->setText("O");
        ui->label->setText("player1");
        player=1;
    }
   f[1] = 1;
    count++;
   check();
}

void MainWindow::on_pushButton_3_clicked()
{

    if (f[2] == 1)
        return;

    if(player==1)
    {
        ui->pushButton_3->setText("X");
        ui->label->setText("player2");
        player=2;
    }
    else
    {
        ui->pushButton_3->setText("O");
        ui->label->setText("player1");
        player=1;
    }
   f[2] = 1;
    count++;
   check();
}

void MainWindow::on_pushButton_4_clicked()
{

    if (f[3] == 1)
        return;

    if(player==1)
    {
        ui->pushButton_4->setText("X");
        ui->label->setText("player2");
        player=2;
    }
    else
    {
        ui->pushButton_4->setText("O");
        ui->label->setText("player1");
        player=1;
    }
   f[3] = 1;
    count++;
   check();
}

void MainWindow::on_pushButton_5_clicked()
{

    if (f[4] == 1)
        return;

    if(player==1)
    {
        ui->pushButton_5->setText("X");
        ui->label->setText("player2");
        player=2;
    }
    else
    {
        ui->pushButton_5->setText("O");
        ui->label->setText("player1");
        player=1;
    }
   f[4] = 1;
    count++;
   check();
}

void MainWindow::on_pushButton_6_clicked()
{
    if (f[5] == 1)
        return;

    if(player==1)
    {
        ui->pushButton_6->setText("X");
        ui->label->setText("player2");
        player=2;
    }
    else
    {
        ui->pushButton_6->setText("O");
        ui->label->setText("player1");
        player=1;
    }
   f[5] = 1;
    count++;
   check();
}

void MainWindow::on_pushButton_7_clicked()
{

    if (f[6] == 1)
        return;

    if(player==1)
    {
        ui->pushButton_7->setText("X");
        ui->label->setText("player2");
        player=2;
    }
    else
    {
        ui->pushButton_7->setText("O");
        ui->label->setText("player1");
        player=1;
    }
   f[6] = 1;
    count++;
   check();
}

void MainWindow::on_pushButton_8_clicked()
{

    if (f[7] == 1)
        return;

    if(player==1)
    {
        ui->pushButton_8->setText("X");
        ui->label->setText("player2");
        player=2;
    }
    else
    {
        ui->pushButton_8->setText("O");
        ui->label->setText("player1");
        player=1;
    }
   f[7] = 1;
    count++;
   check();
}

void MainWindow::on_pushButton_9_clicked()
{

    if (f[8] == 1)
        return;

    if(player==1)
    {
        ui->pushButton_9->setText("X");
        ui->label->setText("player2");
        player=2;
    }
    else
    {
        ui->pushButton_9->setText("O");
        ui->label->setText("player1");
        player=1;
    }
   f[8] = 1;
    count++;
   check();
}



void MainWindow::on_pushButton_clicked()
{
    ui->pushButton_1->setText("");
    ui->pushButton_2->setText("");
    ui->pushButton_3->setText("");
    ui->pushButton_4->setText("");
    ui->pushButton_5->setText("");
    ui->pushButton_6->setText("");
    ui->pushButton_7->setText("");
    ui->pushButton_8->setText("");
    ui->pushButton_9->setText("");
    count=0;
    player=1;
    for(int i=0;i<9;i++)
        f[i]=0;
    ui->label->setText("player1");
}
