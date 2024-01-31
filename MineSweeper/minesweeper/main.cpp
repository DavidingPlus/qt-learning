#include "mainwindow.h"
#include "menu.h"

#include <QApplication>
#include <QFontDatabase>
#include <QTextEdit>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    Menu w;
    w.show();
    return a.exec();
}
