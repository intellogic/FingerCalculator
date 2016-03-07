#include "widget.h"
#include "neuron.h"
#include "polska.h"
PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent) {
    this->resize(700,200);
    this->setWindowTitle("FingerCalculator");
    this->setWindowIcon(QIcon("icon.bmp"));
    Button_Eq=new QPushButton(this);
    Button_Clear = new QPushButton(this);
    Button_Eq->setIcon(QIcon("equal.bmp"));
    Button_Eq->setIconSize(QSize(48,48));
    Button_Eq->move(650,0);
    Button_Eq->resize(50,50);
    Button_Clear->setIcon(QIcon("trash.png"));
    Button_Clear->setIconSize(QSize(48,48));
    Button_Clear->resize(50,50);
    Button_Clear->move(650,49);
    lbl_ans = new QLabel("Result",this);
    lbl_ans -> setFixedWidth(700);
    lbl_ans->setAlignment(Qt::AlignCenter);
    lbl_ans->move(5, 110);
    QFont Font;
    Font.setPointSize(35);
    lbl_ans->setFont(Font);
    A=new QImage(700,100,QImage::Format_Mono);
    A->fill(Qt::black);
    A->save("a.bmp");
    connect(Button_Eq, SIGNAL (released()), this, SLOT (Button_Event()));
    connect(Button_Clear, SIGNAL (released()), this, SLOT (Clear_Event()));
    this->setMouseTracking(true);
    k=1;
    for (int i=0; i<=9; i++){
        for (int x=0; x<25; x++)
            for (int y=0; y<25; y++){
                T[i].sum=0;
                T[i].weight[x][y]=0;
                T[i].mul[x][y]=0;
                T[i].input[x][y]=0;
            }
        QString FileName;
        FileName.setNum(i);
        FileName="Temp/"+FileName;
        QFile file(FileName+".txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        for (int x=0; x<25; x++){
            for (int y=0; y<25; y++)
                in >> T[i].weight[x][y];
        }
    }
}

PaintWidget::~PaintWidget() {
}

QString PaintWidget:: ifex (int **a, int n, int m, int x, int y){
    QString s="0000";
    if ((y-1)>=0) { if (a[x][y-1]==1) s[0]='1'; }
    if ((x+1)<n)  { if (a[x+1][y]==1) s[1]='1'; }
    if ((y+1)<m)  { if (a[x][y+1]==1) s[2]='1'; }
    if ((x-1)>=0) { if (a[x-1][y]==1) s[3]='1'; }
    return s;
}

int PaintWidget::goto_ (int **a, int n, int m, int x, int y, int k, int **b){
    d[x][y]=k;
    b[x][y]=k;
    QString s = ifex(a,n,m,x,y);
    if ((s[0]=='1')&&(!d[x][y-1])) goto_(a,n,m,x,y-1,k,b);
    if ((s[1]=='1')&&(!d[x+1][y])) goto_(a,n,m,x+1,y,k,b);
    if ((s[2]=='1')&&(!d[x][y+1])) goto_(a,n,m,x,y+1,k,b);
    if ((s[3]=='1')&&(!d[x-1][y])) goto_(a,n,m,x-1,y,k,b);
    return 0;
}

int** PaintWidget::fin (QImage *image, QPoint LH){
    QPoint lr, lh;
    QRgb brgb= qRgb(0,0,0);
    QRgb wrgb= qRgb(255,255,255);
    QImage im(image->width(), image->height(), QImage::Format_RGB32);
    im.fill(Qt::white);
    bool t=0;
    int n=image->height();
    int m=image->width();
    int min=999, max=0;
    int k=0;
    int **b = new int *[n];
        for (int i=0; i<n; i++)
            b[i] = new int [m];
    int **a = new int *[n];
        for (int i=0; i<n; i++)
            a[i] = new int [m];
    for (int i=0; i<n; i++)
           for (int j=0; j<m; j++){
                   b[i][j]=0;
                   a[i][j]=0;
           }

    for (int i=0; i<image->width(); i++)
        for (int j=0; j<image->height(); j++){
            QColor rgb(image->pixel(i,j));
            int m = (rgb.red()+rgb.green()+rgb.blue())/3;
            if (m<LH.x()-10 || m>LH.y()+10) {if (m>max) max=m; if (m<min) min=m; a[j][i]=1; im.setPixel(i,j,brgb);}
                else { a[j][i]=0; im.setPixel(i,j,wrgb); }
        }

    for (int j=0; j<m; j++)
        for (int i=0; i<n; i++)
            if (!d[i][j]&&a[i][j])
                {
                    k++;
                    goto_(a,n,m,i,j,k,b);
                }
    //qDebug() << k;
    for (int x=1; x<=k; x++){
         t=0;
         for (int j=0; j<m; j++){
            for (int i=0; i<n; i++){
                if ((b[i][j]==x)&&!t) {lr.setX(j); t=1;}
                if ((b[i][j]==x)&&t) {lr.setY(j);}
            }
         }
         t=0;
         for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                if ((b[i][j]==x)&&!t) {lh.setX(i); t=1;}
                if ((b[i][j]==x)&&t) {lh.setY(i);}
            }
         }
         QImage U(lr.y()-lr.x()+1,lh.y()-lh.x()+1, QImage::Format_RGB32);
         U.fill(Qt::white);
         QString I;
         for (int i=lr.x(); i<=lr.y(); i++)
             for (int j=lh.x(); j<=lh.y(); j++)
                if (b[j][i]==x) U.setPixel(i-lr.x(), j-lh.x(), brgb);
         I.setNum(x);
         U.save("GM/"+I+".bmp");
         AllParts.append(U);
      }
    return b;
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
    this->update();
    k=0;
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (k!=1) {
        mDrawBuffer.append(event->pos());
        this->update();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint t(-2,-2);
    k=1;
    mDrawBuffer.append(t);
}

void PaintWidget::Clear_Event()
{
    mDrawBuffer.clear();
    this->update();
    lbl_ans->setText("Result");
    AllParts.clear();
    A->fill(Qt::black);
    //qDebug() << AllParts.size();
    for (int i=0; i<1000; i++)
        for (int j=0; j<1000; j++)
            d[i][j]=0;
}

QString PaintWidget::CharRecognize(QImage *A){
    int maxr = 0, maxj;
    long int d_h=0;
    float r = 0;
    QPoint t1 = RM_x(A);
    QPoint t2 =RM_y(A);
    int x1 = t1.x (), x2 = t1.y(), y1 = t2.x(), y2 = t2.y();
    QImage Curr(50,50,QImage::Format_Mono);
    Curr.fill(Qt::black);
    Curr = A->copy(QRect(x2,y2,x1-x2,y1-y2));
    Curr = Curr.scaled(50,50);
    for (int j = 0; j <= 2; j++){
       r=0;
       d_h=0;
       for (int i = 0; i <= 8; i++){
            d_h=0;
            QString fname1, fname2;
            fname2.setNum(j);
            fname1.setNum(i);
            fname2+=fname1+".bmp";
            QImage CurrTest(fname2);
            t1 = RM_x(&CurrTest);
            t2 = RM_y(&CurrTest);
            x1 = t1.x();
            x2 = t1.y();
            y1 = t2.x();
            y2 = t2.y();
            CurrTest = CurrTest.copy(QRect(x2,y2,x1-x2,y1-y2));
            CurrTest = CurrTest.scaled(50,50);
            int quan=0;
            for (int x=0; x<50; x++){
                for (int y=0; y<50; y++){
                    QColor rgb(Curr.pixel(x,y));
                    int m = (rgb.red()+rgb.green()+rgb.blue())/3;
                    if (m<250) quan++;
                }
            }

            if (quan >= 2000) return "-";
            for (int x = 0; x < 50; x++)
                for (int y = 0; y < 50; y++)
                    if (CurrTest.pixel(x,y) != Curr.pixel(x,y)) d_h++;
            r += 1000000000/(1+d_h*d_h);

        }
        if (r > maxr) {maxr = r; maxj = j;}

   }
   if (maxj == 0) return "+"; else  if (maxj == 1) return "-"; else  if (maxj == 2) return "*";

}

int PaintWidget::Recognize(QImage *image){
    int res, rnn;
    QImage Curr;

    Curr = image->scaled(25, 25);
    Curr.save("curr.jpg");
    for (int nn = 0; nn <= 9; nn++){
        for (int x = 0; x < 25; x++){
            for (int y = 0; y < 25; y++){
                QColor rgb(Curr.pixel(x,y));
                int m = (rgb.red()+rgb.green()+rgb.blue())/3;
                if (m < 250) T[nn].input[y][x] = 1; else T[nn].input[y][x] = 0;
            }
        }
        T[nn].mul_w();
        T[nn].Sum();
        qDebug() << nn << "  " << T[nn].sum;
        if (nn == 0) {res = T[nn].sum; rnn = nn;}
        if (T[nn].sum > res) { res = T[nn].sum;rnn = nn;}
    }
    return rnn;
}

void PaintWidget::Button_Event()
{
    QString ans;
    QPoint LH(255,255);
    if (lbl_ans->text() == "Result") ans="";
    int **b = new int *[A->height()];
    for (int i=0; i<A->height(); i++)
        b[i] = new int [A->width()];
    for (int i=0; i<A->height(); i++)
        for (int j=0; j<A->width(); j++)
            b[i][j]=0;
    b=fin(A, LH);
    for (int n_im=0; n_im < AllParts.size(); n_im++){

        QString I;
        QString Z;
        if (n_im>0)
        Z+=ans[ans.size()-1];
        qDebug() << Z;
        if ( (n_im!=AllParts.size()-1 && Z=="-" && (AllParts[n_im].width() *2 <  AllParts[n_im+1].width() ||  AllParts[n_im].height() *2 <  AllParts[n_im+1].height())  )
             || (n_im!=0 && (AllParts[n_im].width() *2 <  AllParts[n_im-1].width() ||  AllParts[n_im].height() *2 <  AllParts[n_im-1].height() ) )
             )

        I=CharRecognize(&AllParts[n_im]); else
        I.setNum(Recognize(&AllParts[n_im]));
        ans+=I;
        if (n_im>=2 && ans[ans.size()-2]==ans[ans.size()-1] && ans[ans.size()-1] == '-'){
            ans.remove(ans.size()-2, 2);
            ans+="/";
            }
        }
    std::string k = ans.toUtf8().constData();
    double res = Count(k);
    //res=23.45;
    qDebug() << res;
    QString Res;
    Res.setNum(res,'f',3);
    lbl_ans->setAlignment(Qt::AlignCenter);
    lbl_ans->setText(ans+"="+Res);
    for (int i=0; i<1000; i++)
        for (int j=0; j<1000; j++)
            d[i][j]=0;
    AllParts.clear();
    ans="";

}

QPoint PaintWidget::RM_x(QImage *image){
    QPoint t;
    for (int x=0; x<image->width(); x++)
        for (int y=0; y<image->height(); y++){
            QColor rgb(image->pixel(x,y));
            int m = (rgb.red()+rgb.green()+rgb.blue())/3;
            if (m<250) {t.setX(x); break;};
        }
    for (int x=image->width()-1; x>=0; x--)
        for (int y=0; y<image->height(); y++){
            QColor rgb(image->pixel(x,y));
            int m = (rgb.red()+rgb.green()+rgb.blue())/3;
            if (m<250){t.setY(x); break;}
        }
    return t;
}

QPoint PaintWidget::RM_y(QImage *image){
    QPoint t;
    for (int y=0; y<image->height(); y++)
        for (int x=0; x<image->width(); x++){
            QColor rgb(image->pixel(x,y));
            int m = (rgb.red()+rgb.green()+rgb.blue())/3;
            if (m<250) {t.setX(y); break;};
        }
    for (int y=image->height()-1; y>=0; y--)
        for (int x=0; x<image->width(); x++){
            QColor rgb(image->pixel(x,y));
            int m = (rgb.red()+rgb.green()+rgb.blue())/3;
            if (m<250) {t.setY(y); break;}
         }
    return t;
}

void PaintWidget::paintEvent(QPaintEvent *)
{
    QPainter p_screen(this);
    QPainter p_image(A);
    p_screen.setClipRegion(QRegion(0,0,699,99),Qt::ReplaceClip);
    p_screen.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    p_screen.setPen(QPen(Qt::black,4));
    p_screen.fillRect(QRect(0,0,699,99),QBrush(Qt::white,Qt::SolidPattern));
    p_image.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    p_image.setPen(QPen(Qt::black,4));
    for (int i=0; i<mDrawBuffer.size()-1; i++){
        if (mDrawBuffer[i].x()==-2||mDrawBuffer[i+1].x()==-2)
            i++;
        else
        {
            p_screen.drawLine(mDrawBuffer[i],mDrawBuffer[i+1]);
            p_image.drawLine(mDrawBuffer[i].x(),mDrawBuffer[i].y(),mDrawBuffer[i+1].x(),mDrawBuffer[i+1].y());
            l_p=mDrawBuffer[i];
        }
    }
    p_screen.end();
    p_image.end();
}
