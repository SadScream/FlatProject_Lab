#ifndef SEARCHFLAT_H
#define SEARCHFLAT_H

#include <QDialog>
#include <mainwindow.h>

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

    void search_clicked();
    void closeEvent(QCloseEvent *event);
private:
    Ui::SearchFlat *ui;
};

#endif // SEARCHFLAT_H
