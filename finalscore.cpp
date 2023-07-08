#include "finalscore.h"
#include "ui_finalscore.h"
#include <QString>
#include <QDebug>

finalscore::finalscore(const QVector<QVector<QString>>& scoreArray, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finalscore)
{
    ui->setupUi(this);

    int indexWinner;
    int winnerScore = 0;
    for(int i = 0; i < scoreArray.size(); i++){
        if(scoreArray[i][1].toInt() > winnerScore){
            indexWinner = i;
            winnerScore = scoreArray[i][1].toInt();
        }
    }


    qInfo() << "Winner " + scoreArray[indexWinner][0];

    ui->WinnerLabel->setText("Der Sieger ist: " + scoreArray[indexWinner][0]);


    int insertionIndex = 1;
    QLabel *playerScoreLabel = new QLabel(scoreArray[indexWinner][0] + ": " + scoreArray[indexWinner][1]);
    QFont font = playerScoreLabel->font();
    font.setPointSize(18); // set the size as per your need
    playerScoreLabel->setFont(font);
    ui->PlayerScoreContainer->insertWidget(insertionIndex, playerScoreLabel);

    insertionIndex++;


    for(int i = 0; i< scoreArray.size(); i++){
        if(i != indexWinner){
            QLabel *playerScoreLabel = new QLabel(scoreArray[i][0] + ": " + scoreArray[i][1]);
            QFont font = playerScoreLabel->font();
            font.setPointSize(14); // set the size as per your need
            playerScoreLabel->setFont(font);
            ui->PlayerScoreContainer->insertWidget(insertionIndex, playerScoreLabel);
            insertionIndex++;
        }
    }
}
finalscore::~finalscore()
{
    delete ui;
}

void finalscore::on_continueButton_clicked()
{
    this->close();
}

