#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include <QWidget>
#include <QList>
#include <QPoint>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QTGui>
#include <QPushButton>
#include <QLabel>
#include <fstream>
#include <QPixmap>
#include <QTime>
#include "neuron.h"
#include "stack.h"

class PaintWidget : public QWidget
{   Q_OBJECT
public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();
     QLabel *lbl_ans;
     QPoint l_p;
     QPushButton *Button_Eq;
     QPushButton *Button_Clear;
     QImage *A;
     bool k;
     bool d[1000][1000];
     bool NewPat;
     QTime Time;
     int QParts;
     QPoint WiWh(QImage *image);
     QString ifex (int **a, int n, int m, int x, int y);
     int goto_ (int **a, int n, int m, int x, int y, int k, int **b);
     Neuron T[14];
     int** fin (QImage *image, QPoint LH);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    QPoint RM_x (QImage *image);
    QPoint RM_y (QImage *image);
    int Recognize (QImage *A);
    QString CharRecognize (QImage *A);
private:
    QList<QPoint> mDrawBuffer;
    QList<QImage> AllParts;
    QList <QImage> Templates;
private slots:
 void Button_Event();
 void Clear_Event();

};


#endif // PAINTWIDGET_H
