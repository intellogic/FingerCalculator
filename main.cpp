#include "widget.h"
#include <QApplication>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QApp
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintWidget w;
    w.show();
    return a.exec();
}
