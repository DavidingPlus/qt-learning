#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent = nullptr);
    Button(QWidget* parent,QString name);
    ~Button();

signals:

};

#endif // BUTTON_H
