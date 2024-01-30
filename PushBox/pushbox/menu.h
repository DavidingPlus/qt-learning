#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
    class Menu;
}

class Menu : public QWidget {
    Q_OBJECT

public:
    explicit Menu(QWidget* parent = nullptr);
    ~Menu();

    void paintEvent(QPaintEvent* );

private slots:
    void on_startBtn_clicked();

    void on_closeBtn_clicked();

signals:
    void startGame();

private:
    Ui::Menu* ui;

    QPainter* _painter;
};

#endif // MENU_H
