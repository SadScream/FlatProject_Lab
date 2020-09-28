#include "src/headers/addflat.h"
#include "ui_addflat.h"

#include <string>

#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>
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
        this->show_error();
        return;
    }

    this->p->add_item(addres, block, rooms, area);
    this->close();
}

void AddFlat::show_error()
{
    QMessageBox *show_msg = new QMessageBox;

    QIcon icon = QIcon();
    icon.addFile(":/new/window_icons/icons/card.png", QSize(), QIcon::Normal, QIcon::Off);

    show_msg->setWindowIcon(icon);
    show_msg->setIcon(QMessageBox::Warning);
    show_msg->setText("Проверьте правильность данных, введенных в поля\nОбратите внимание: "
                      "длина поля адрес не может быть меньше 6 символов");
    show_msg->setWindowTitle("Ошибка");
    show_msg->exec();

    return;
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
