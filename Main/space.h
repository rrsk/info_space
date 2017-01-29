#ifndef SPACE_H
#define SPACE_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class Space;
}

class Space : public QDialog
{
    Q_OBJECT

public:
    explicit Space(QWidget *parent = 0);
    void setData(const QString &labelText);
    ~Space();

private slots:
    void handleButton();


private:
    Ui::Space *ui;
    QPushButton *p_button;

signals:
void mySignal(int value);
};

#endif // SPACE_H
