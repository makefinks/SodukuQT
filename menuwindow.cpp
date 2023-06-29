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


void MenuWindow::on_startGame_Button_clicked()
{
    threexthreedialog = new GameDialog();
    threexthreedialog->show();
}

