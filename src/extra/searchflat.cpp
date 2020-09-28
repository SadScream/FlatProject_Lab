#include "src/headers/searchflat.h"
#include "ui_searchflat.h"
#include "src/headers/mainwindow.h"

#include <QCloseEvent>
#include <QMessageBox>
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
        this->show_error();
        return;
    }
    else if (block.toInt() != 0 && rooms.toInt() == 0) {
        this->p->search_by(block);
    }
    else if (block.toInt() == 0 && rooms.toInt() != 0) {
        this->p->search_by("", rooms);
    }
    else if (block.toInt() != 0 && rooms.toInt() != 0) {
        this->p->search_by(block, rooms);
    }

    this->close();
    return;
}

void SearchFlat::show_error()
{
    QMessageBox *show_msg = new QMessageBox;

    QIcon icon = QIcon();
    icon.addFile(":/new/window_icons/icons/card.png", QSize(), QIcon::Normal, QIcon::Off);

    show_msg->setWindowIcon(icon);
    show_msg->setIcon(QMessageBox::Warning);
    show_msg->setText("Проверьте корректность данных, введенных в поля");
    show_msg->setWindowTitle("Ошибка");
    show_msg->exec();

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
