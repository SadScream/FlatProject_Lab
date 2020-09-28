#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include <stdio.h>
#include <QString>

using namespace std;

class Queue
{
public:

    struct Element
    {
        QString addres,  // улица
        block,          // этаж
        rooms,          // кол-во комнат
        area;           // площадь
        Element *next;
    };

    string file;

    Element *head = nullptr;
    Element *tail = nullptr;

    Queue();

    bool read_from_file(string file);
    bool write_to_file();
    bool remove(Element *el);

    void push(QString addres, QString block, QString rooms, QString area);
    void out();

    Element* pop();
    Element* get_head();
    Element* get_next(Element *current);
};

#endif // QUEUE_H
