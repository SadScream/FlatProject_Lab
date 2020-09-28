#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QString>
#include <QDebug>

#include <vector>

#include "queue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Item : public QStandardItem
{
public:
    Queue::Element *element = new Queue::Element;
    explicit Item(Queue::Element* e) : QStandardItem(e->addres + ", " + e->block + " этаж"){element = e;}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Queue flats;
    Item *selected_item = nullptr;
    QStandardItemModel *model = new QStandardItemModel();
    std::vector<Item*> items;

    QDebug dbg = qDebug();

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void constructor();
    void remove_button_state(bool state);
    void add_item(QString addres, QString block, QString flats, QString area);
    void push_item(Queue::Element *tmp);
    void search_by(QString block = "", QString flats = "");
    void clear_flats_list();
    void fill_flats_list();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
private slots:
    void clicked(const QModelIndex &index);
    void add_button_clicked();
    void search_button_clicked();
    void complete_button_clicked();
    void remove_search_button_clicked();
};
#endif // MAINWINDOW_H
