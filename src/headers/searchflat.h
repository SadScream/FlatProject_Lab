#ifndef SEARCHFLAT_H
#define SEARCHFLAT_H

#include <QDialog>
#include <QString>
#include <src/headers/mainwindow.h>

namespace Ui {
class SearchFlat;
}

class SearchFlat : public QDialog
{
    Q_OBJECT

public:
    MainWindow *p = new MainWindow;

    explicit SearchFlat(QWidget *parent = nullptr, MainWindow *parent_window = nullptr);
    ~SearchFlat();

    bool is_digit(QString str);
    bool is_empty(QString str);

    void search_clicked();
    void show_error();
    void closeEvent(QCloseEvent *event);
private:
    Ui::SearchFlat *ui;
};

#endif // SEARCHFLAT_H
