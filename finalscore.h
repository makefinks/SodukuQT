#ifndef FINALSCORE_H
#define FINALSCORE_H

#include <QDialog>

namespace Ui {
class finalscore;
}

class finalscore : public QDialog
{
    Q_OBJECT

public:
    explicit finalscore(const QVector<QVector<QString>>& stringArray, QWidget *parent = nullptr);
    ~finalscore();

private slots:
    void on_continueButton_clicked();

private:
    Ui::finalscore *ui;
};

#endif // FINALSCORE_H
