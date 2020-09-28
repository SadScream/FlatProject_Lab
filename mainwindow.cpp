#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "queue.h"
#include "addflat.h"
#include "searchflat.h"

#include <QIcon>
#include <QResource>
#include <QtWidgets>
#include <QDebug>

#include <string>
#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    QTextCodec *codec = QTextCodec::codecForName("windows-1251"); // устанавливаем кириллицу в качестве кодировки
    QTextCodec::setCodecForLocale(codec);

    ui->setupUi(this);
    this->setFocus();
    this->setCentralWidget(ui->centralwidget);
    this->flats.read_from_file("input.txt"); // экземпляр очереди из Queue::Element(квартир)
}

MainWindow::~MainWindow()
{
    dbg = qDebug(); dbg << "distructing MainWindow..";

    delete ui;
    delete model;

    dbg << "MainWindow distructed";
}

void MainWindow::constructor()
{
    dbg = qDebug(); dbg << "constructing MainWindow..";

    ui->flat_list->setModel(model);
    this->remove_button_state(false);

    // создаем реакции на сигналы
    connect(ui->flat_list, &QListView::clicked, // сигнал нажатия на элемент внутри flat_list
            this, &MainWindow::clicked);

    connect(ui->add_button, &QPushButton::clicked,
            this, &MainWindow::add_button_clicked);

    connect(ui->search_button, &QPushButton::clicked,
            this, &MainWindow::search_button_clicked);

    connect(ui->remove_search_button, &QPushButton::clicked,
            this, &MainWindow::remove_search_button_clicked);

    connect(ui->complete_button, &QPushButton::clicked,
            this, &MainWindow::complete_button_clicked);
    //

    this->fill_flats_list(); // заполняет flats_list

    dbg << "MainWindow constructed";
    return;
}

void MainWindow::fill_flats_list()
{
    /*
     * заполняет flats_list
     */

    Queue::Element *tmp = flats.get_head();

    while (tmp != nullptr) {
        this->push_item(tmp);
        tmp = tmp->next;
    }
}

void MainWindow::add_button_clicked()
{
    qDebug("add_button_clicked emited");
    AddFlat *add_flat_window = new AddFlat(0, this);
    add_flat_window->exec();

    return;
}

void MainWindow::search_button_clicked()
{
    qDebug("search_button_clicked emited");
    SearchFlat *search_flat_window = new SearchFlat(0, this);
    search_flat_window->exec();

    return;
}

void MainWindow::search_by(QString block, QString rooms)
{
    /*
     * вызывается после нажатия кнопки поиска в окне SearchFlat если введенные поля валидны
     * выводит список только тех итемов, которые соответствуют критериям поиска(фильтра)
     */

    this->clear_flats_list();

    Queue::Element *tmp = flats.get_head();

    if (block != "" && rooms == "") {
        while (tmp != nullptr) {
            if (tmp->block == block) {
                this->push_item(tmp);
            }
            tmp = tmp->next;
        }
    }
    else if (block == "" && rooms != "") {
        while (tmp != nullptr) {
            if (tmp->rooms == rooms) {
                this->push_item(tmp);
            }
            tmp = tmp->next;
        }
    }
    else if (block != "" && rooms != "") {
        while (tmp != nullptr) {
            if (tmp->block == block && tmp->rooms == rooms) {
                this->push_item(tmp);
            }
            tmp = tmp->next;
        }
    }

    this->remove_button_state(true);
    return;
}

void MainWindow::complete_button_clicked()
{
    dbg = qDebug(); dbg << "processing complete_button_clicked slot..";

    if (this->selected_item == nullptr)
        return;

    // получаем QList из QModelIndex(length = 1) элементов, которые являются "selected"
    QModelIndexList list_of_indexes = ui->flat_list->selectionModel()->selectedRows();

    QModelIndex item_index;
    item_index = list_of_indexes[0];

    // создаем новый массив элементов Item и копируем в него все элементы, кроме выбранного
    std::vector<Item*> copy_items;

    for (unsigned long long i = 0; i < items.size(); i++) {
        if (items[i]->element != this->selected_item->element) {
            copy_items.push_back(items[i]);
        }
    }

    items.clear();
    items = copy_items; // приравниваем атрибут items к скопированному массиву
    //

    model->removeRow(item_index.row()); // удаляем данный итем из модели
    this->flats.remove(this->selected_item->element); // удаляем итем из очереди
    this->flats.out();

//    delete this->selected_item->element;

    // когда удалили выбранный элемент нужно очистить виджет info_text
    // а также выставить кнопке complete_button setEnabled на false, т.к сейчас никакой элемент не выбран
    this->selected_item = nullptr;
    ui->flat_list->clearSelection();
    ui->info_text->setText("");
    ui->complete_button->setEnabled(false);

    dbg << "complete_button_clicked processed";
    return;
}

void MainWindow::clicked(const QModelIndex &index)
{
    /*
     * вызывается при нажатии на какой-либо итем
     * заполняет информацию в виджете info_text в соответствии с данными, хранящимися в итеме
     */
    qDebug("clicked emited");

    Queue::Element *el = this->items[index.row()]->element;
    this->selected_item = items[index.row()];

    QString html;

    html = (QString)("<!DOCTYPE HTML>"
                   "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                   "p, li { white-space: pre-wrap; }"
                   "</style></head><body style=\" font-family:Calibri; font-size:14px; font-weight:400; font-style:normal;\">"
                   "Улица: " + el->addres +
                   "<br><br>Этаж: " + el->block +
                   "<br>Кол-во комнат: " + el->rooms +
                   "<br>Площадь: " + el->area + " кв.м." +
                   "</body></html>");

    ui->info_text->setHtml(html);
    ui->complete_button->setEnabled(true);
}

void MainWindow::add_item(QString addres, QString block, QString rooms, QString area) {
    /*
     * добавляет новый item в очередь и вызывает push_item
     * который в свою очередь добавляет item в модель и в массив items
     */

    dbg = qDebug(); dbg << "adding item..";

    this->flats.push(addres, block, rooms, area);
    this->push_item(this->flats.tail);

    dbg << "added";
    return;
}

void MainWindow::push_item(Queue::Element *tmp)
{
    /*
     * добавляет элемент в массив items, а также в модель
     */

    dbg = qDebug(); dbg << "pushing item..";

    Item *item = new Item(tmp);
    item->setEditable(false);
    this->items.push_back(item);
    model->appendRow(item);

    dbg<< "pushed";
    return;
}

void MainWindow::clear_flats_list()
{
    /*
     * очищает модель и массив items
     */

    dbg = qDebug(); dbg << "clearing flats_list field..";

    ui->info_text->clear();
    this->selected_item = nullptr;
    ui->complete_button->setEnabled(false);
    items.clear();
    model->clear();

    dbg << "clean";
    return;
}

void MainWindow::remove_search_button_clicked()
{
    this->clear_flats_list();
    this->fill_flats_list();
    this->remove_button_state(false);
    return;
}

void MainWindow::remove_button_state(bool state)
{
    /*
     * :state: - true/false
     * если true, то кнопка remove_search_button появляется
     * иначе - исчезает
     * remove_search_button - кнопка для очистки условий поиска среди квартир
     */

    if (state)
    {
        QIcon icon = QIcon();
        icon.addFile(":/new/button_icons/icons/cancel.png", QSize(21, 21), QIcon::Normal, QIcon::Off);
        ui->remove_search_button->setIcon(icon);
        ui->remove_search_button->setToolTip("Удалить фильтр поиска");
    }
    else
    {
        ui->remove_search_button->setIcon(QIcon());
        ui->remove_search_button->setToolTip("");
    }

    ui->remove_search_button->setEnabled(state);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    dbg = qDebug(); dbg << "close event discovered..";

    this->flats.write_to_file();
    event->accept();

    dbg << "accepted";
    return;
}
