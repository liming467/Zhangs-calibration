#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	system("chcp 65001");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
