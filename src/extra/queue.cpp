#include "src/headers/queue.h"
#include <stdio.h>
#include <iostream>
#include <string>

#include <QString>
#include <QTextCodec>
#include <QDebug>
#include <QChar>

using namespace std;

Queue::Queue()
{

}

void Queue::push(QString addres, QString block, QString rooms, QString area)
{
    Element *element = new Element;
    element->addres = addres;
    element->block = block;
    element->rooms = rooms;
    element->area = area;

    if (head == NULL)
    {
        head = element;
        head->next = nullptr;
        return;
    }
    else if (tail == NULL)
    {
        tail = element;
        tail->next = nullptr;
        head->next = tail;
        return;
    }
    else
    {
        Element *tmp = tail;
        tail = element;
        tail->next = nullptr;
        tmp->next = element;
        return;
    }
}

Queue::Element *Queue::pop()
{
    Queue::Element *tmp = head;
    head = head->next;
    delete tmp;

    return head;
}

bool Queue::remove(Queue::Element *el)
{
    Queue::Element *tmp = head;
    Queue::Element *prev = nullptr;

    while (tmp != nullptr)
    {
        if (tmp == el)
        {
            if (tmp == head) {
                head = head->next;
                return true;
            }
            else if (tmp == tail) {
                tail = prev;
                tail->next = nullptr;
                return true;
            }

            prev->next = tmp->next;
            return true;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    return false;
}

void Queue::out()
{
    Queue::Element *tmp = head;

    printf("\n");
    QDebug deb = qDebug();

    deb << "head:" << this->head->addres << "tail:" << tail->addres;

    while (tmp != nullptr)
    {
        deb << tmp->addres << "=>";
        tmp = tmp->next;
    }

    deb << "null";
}

bool Queue::read_from_file(string f)
{
    /*
    на вход поступает путь к файлу
    формату данных в файле:
    str 1:улица;этаж;кол-во комнат;площадь;
    str 2:улица;этаж;кол-во комнат;площадь;
    str ...:
    */

    this->file = f;

    FILE *in;

    in = fopen(file.c_str(), "r");

    if (in == NULL)
    {
        in = fopen(this->file.c_str(), "w+");
    }

    QTextCodec *codec = QTextCodec::codecForName("windows-1251");
    QTextCodec::setCodecForLocale(codec);

    char s;
    QString addres = "", block = "", rooms = "", area = "";

    int j = 0;

    while (fscanf(in, "%c", &s) != EOF)
    {
        if (s == '\n')
        {
            continue;
        }

        if (s == ';')
        {
            if (j == 3)
            {
                j = 0;

                this->push(addres, block, rooms, area);

                addres = "", block = "", rooms = "", area = "";
                continue;
            }
            else
            {
                j++;
                continue;
            }
        }

        if (j == 0)
        {
            addres += QString::fromLocal8Bit(string(1, s).c_str());
        }
        else if (j == 1)
        {
            block += s; /*block * 10 + ((int)s - 48);*/
        }
        else if (j == 2)
        {
            rooms += s;
        }
        else if (j == 3)
        {
            area += s;
        }
    }

    fclose(in);
    qDebug("data read");
    return true;
}

bool Queue::write_to_file()
{
    Queue::Element *tmp = this->head;
    FILE *out;

    out = fopen(this->file.c_str(), "w");

    while (tmp != nullptr) {
        const char *s = ((tmp->addres.toLocal8Bit() + ";" +
                         tmp->block.toLocal8Bit() + ";" +
                         tmp->rooms.toLocal8Bit() + ";" +
                         tmp->area.toLocal8Bit()  + ";\n"));
        fprintf(out, s);
        tmp = this->pop();
//        delete s;
    }

    fclose(out);
    qDebug("data written");
    return true;
}

Queue::Element* Queue::get_head()
{
    return this->head;
}

Queue::Element* Queue::get_next(Element *current)
{
    return current->next;
}
