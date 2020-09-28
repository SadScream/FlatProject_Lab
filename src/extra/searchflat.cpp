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
    /*
     * тут проверяется корректность введенных в поля данных
     * если данные некорректны, то вызывается функция, создающая окно ошибки
     */

    QString block, rooms;
    bool result_block, result_rooms;

    block = ui->block_line->text();
    rooms = ui->rooms_line->text();

    // qDebug() << (QString::fromUtf8(block.toLocal8Bit()).length());

    result_block = this->is_digit(block); // состоит ли строка из цифр
    result_rooms = this->is_digit(rooms);

    if (( !result_block && !result_rooms )
            || (( !result_block ) && !( this->is_empty(block) ))
            || (( !result_rooms ) && !( this->is_empty(rooms) ))
         ) {
        this->show_error();
        return;
    }
    else if (result_block && !result_rooms) {
        this->p->search_by(block);
    }
    else if (result_rooms && !result_block) {
        this->p->search_by("", rooms);
    }
    else if (result_block && result_rooms) {
        this->p->search_by(block, rooms);
    }

    this->close();
    return;
}

bool SearchFlat::is_empty(QString str)
{
    /*
     * возвращает true, когда строка является пустой
     */

    if (str == "") {
        return true;
    }
    return false;
}

bool SearchFlat::is_digit(QString str)
{
    /*
     * возвращает true, когда строка состоит строго из цифр
     */

    str = QString::fromUtf8(str.toLocal8Bit());

    for (int i = 0; i < str.length(); i++)
    {
        if ( (str[i] < "0") || (str[i] > "9") ) {
            return false;
        }
    }

    return true;
}

void SearchFlat::show_error()
{
    /*
     * создает окно ошибки
     */

    QMessageBox *show_msg = new QMessageBox;

    QIcon icon = QIcon();
    icon.addFile(":/new/window_icons/icons/card.png", QSize(), QIcon::Normal, QIcon::Off);

    show_msg->setWindowIcon(icon);
    show_msg->setIcon(QMessageBox::Warning);
    show_msg->setText("Проверьте корректность данных, введенных в поля\n"
                      "Убедитесь в том, что ни одно из полей НЕ содержит НЕчисловые значения(в т.ч пробелы)");
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
