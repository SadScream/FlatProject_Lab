#ifndef ADDFLAT_H
#define ADDFLAT_H

#include <QDialog>
#include <QString>
#include "src/headers/mainwindow.h"

namespace Ui {
class AddFlat;
}

class AddFlat : public QDialog
{
    Q_OBJECT

public:
    MainWindow *p = new MainWindow;

    explicit AddFlat(QWidget *parent = nullptr, MainWindow *parent_window = nullptr);
    ~AddFlat();

    bool is_digit(QString str);

    void save_clicked();
    void show_error();
    void closeEvent(QCloseEvent *event);

private:
    Ui::AddFlat *ui;
};

#endif // ADDFLAT_H
