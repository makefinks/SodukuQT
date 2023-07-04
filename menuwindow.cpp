#include "menuwindow.h"
#include "./ui_menuwindow.h"
#include "gamedialog.h"

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}


void MenuWindow::on_addPlayer_Button_clicked()
{
    playerCount++;
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*> (ui->PlayerContainer_LayoutVertical->layout());
 //QString buttonText = "Hello";
 //   QPushButton* button = new QPushButton(buttonText, ui->centralwidget);

    //Create Slot (BoxLayout, Label, Lineedit)
    QHBoxLayout* newPlayerSlot = new QHBoxLayout();

    QLabel* label = new QLabel(("Player " + std::to_string(layout->count()+1)).c_str());
    newPlayerSlot->addWidget(label);

    QLineEdit* lineEdit = new QLineEdit();
    newPlayerSlot->addWidget(lineEdit);

    layout->insertLayout(layout->count(), newPlayerSlot);

}

QVector<QVector<QString>> MenuWindow::getPlayers() {
   QVector<QVector<QString>> playersAndScores;
    int index = 0;
    for(int i = 0; i< ui->PlayerContainer_LayoutVertical->layout()->count(); i++){
        QLayoutItem* item = ui->PlayerContainer_LayoutVertical->layout()->itemAt(i);

        if (item) {
            // Cast the QLayoutItem to a QLayout
            QLayout* layout = item->layout();

            if(layout) {
                // Get the second item in the QHBoxLayout (the QLineEdit) and cast it to a QWidgetItem
                QWidgetItem* lineEditItem = dynamic_cast<QWidgetItem*>(layout->itemAt(1));

                if(lineEditItem) {
                    // Cast the QWidget to a QLineEdit
                    QLineEdit* lineEdit = dynamic_cast<QLineEdit*>(lineEditItem->widget());

                    if(lineEdit) {
                        // Get the text from the QLineEdit and add it to the players QVector
                        QVector<QString> playerAndScore;
                        playerAndScore.append(lineEdit->text());
                        playerAndScore.append(0);

                        playersAndScores.append(playerAndScore);
                    }
                }
            }
        }
    }

    return playersAndScores;
}




void MenuWindow::on_startGame_Button_clicked()
{
    threexthreedialog = new GameDialog(getPlayers());
    threexthreedialog->show();
}

