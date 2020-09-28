#include "src/headers/addflat.h"
#include "ui_addflat.h"

#include <string>

#include <QCloseEvent>
#include <QMainWindow>
#include <QString>
#include <QChar>
#include <QDebug>

AddFlat::AddFlat(QWidget *parent, MainWindow *parent_window) : QDialog(parent), ui(new Ui::AddFlat)
{
    p = parent_window;
    ui->setupUi(this);

    connect(ui->cancel_button, &QPushButton::clicked,
            this, &AddFlat::close);
    connect(ui->save_button, &QPushButton::clicked,
            this, &AddFlat::save_clicked);
    this->setFocus();
}

void AddFlat::save_clicked()
{
    QString addres, block, rooms, area;

    addres = ui->addres_line->text();
    block = ui->block_line->text();
    rooms = ui->rooms_line->text();
    area = ui->area_line->text();

    if (addres.length() < 6 || block.toInt() == 0 || rooms.toInt() == 0 || area.toInt() == 0)
    {
        // сделать вызов окна ошибки
        this->close();
        return;
    }

    this->p->add_item(addres, block, rooms, area);
    this->close();
}

void AddFlat::closeEvent(QCloseEvent *event) {
    event->accept();
}

AddFlat::~AddFlat()
{
    QDebug dbg = qDebug();

    dbg << "distructing AddFlat..";
    delete ui;
    delete p;
    dbg << "distructed";
}
