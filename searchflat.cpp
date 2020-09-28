#include "searchflat.h"
#include "ui_searchflat.h"
#include "mainwindow.h"

#include <QCloseEvent>
#include <QDebug>

SearchFlat::SearchFlat(QWidget *parent, MainWindow *parent_window) : QDialog(parent), ui(new Ui::SearchFlat)
{
    this->p = parent_window;
    ui->setupUi(this);

    connect(ui->cancel_button, &QPushButton::clicked,
            this, &SearchFlat::close);
    connect(ui->search_button, &QPushButton::clicked,
            this, &SearchFlat::search_clicked);
    this->setFocus();
}

void SearchFlat::search_clicked()
{
    QString block, rooms;

    block = ui->block_line->text();
    rooms = ui->rooms_line->text();

    if (block.toInt() == 0 && rooms.toInt() == 0) {
        this->close();
        return;
    }
    else if (block.toInt() != 0 && rooms.toInt() == 0) {
//        qDebug() << "1. block:" << block << "rooms:" << rooms;
        this->p->search_by(block);
    }
    else if (block.toInt() == 0 && rooms.toInt() != 0) {
//        qDebug() << "2. block:" << block << "rooms:" << rooms;
        this->p->search_by("", rooms);
    }
    else if (block.toInt() != 0 && rooms.toInt() != 0) {
//        qDebug() << "3. block:" << block << "rooms:" << rooms;
        this->p->search_by(block, rooms);
    }

    this->close();
    return;
}

void SearchFlat::closeEvent(QCloseEvent *event)
{
    event->accept();
}

SearchFlat::~SearchFlat()
{
    delete ui;
}
