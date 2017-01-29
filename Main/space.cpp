#include "space.h"
#include "ui_space.h"
#include "mainwindow.h"
#include <QPushButton>
#include <QDir>
#include <QScrollArea>
#include <QDesktopServices>
#include <QUrl>
#include <QVariant>

QString s;
QPushButton *pb[1000];
QVBoxLayout *layout = new QVBoxLayout;
long long int max1=10000000,max2=0;

void Space::setData(const QString &labelText) {
   s = labelText;
   //name = s.toLatin1().data();
}

int h;

QDir dir2("G:/YouTube");

QFileInfoList list = dir2.entryInfoList();

int l = list.size();

long long int calSize(QString string)
{
    long long int sum=0;
    QDir dir(string);
    foreach(QFileInfo var,dir.entryInfoList())
    {
        if(var.isDir() == true && var.fileName()!="." && var.fileName()!="..")
        {
            sum += calSize(var.absoluteFilePath());
        }

        else if(var.isDir() == false)
            sum += var.size();
    }

    return sum;
}


QString getString(QFileInfo var)
{
    int sz;
    QString st;

    if(var.isDir()==true && var.fileName() != "." && var.fileName() != "..")
    {


         long long int size;



         size=calSize(var.absoluteFilePath());



           if(size>1000000)
           {
               sz = size/1000000;
               st = QString(var.fileName()+"<DIR> %1 MB").arg(sz,0,10);

               if(size>max1){max1=size;}
           }

           else if(size>1000)
           { sz = size/1000;
             st = QString(var.fileName()+"<DIR> %1 KB").arg(sz,0,10);

           }

           else
           {
               sz = size;
               st = QString(var.fileName()+"<DIR> %1 Bytes").arg(sz,0,10);
           }

        }

        else if(var.isDir()== false)
        {



        if(var.size()>1000000)
        {
            sz = var.size()/1000000;
            st = QString(var.fileName()+" %1 MB").arg(sz,0,10);

        }

        else if(var.size()>1000)
        { sz = var.size()/1000;
          st = QString(var.fileName()+" %1 KB").arg(sz,0,10);

        }

        else
        {
            sz = var.size();
            st = QString(var.fileName()+" %1 Bytes").arg(sz,0,10);
        }

}
        return st;

}

Space::Space(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Space)
{
    ui->setupUi(this);




    dir2.setSorting(QDir::Size | QDir::DirsFirst);





    int x,y;

    x=10;
    y=10;
    int n=0;
    long long int total = calSize("G:/YouTube");

    foreach (QFileInfo var, list)
    {

        if(var.isDir()==true && var.fileName() != "." && var.fileName() != "..")
        {
            QString st= getString(var);
            long long int size;

            size=calSize(var.absoluteFilePath());

            h=(size*800)/total;

            if(h<=30) h=30;

            if(y+h>750)
            {
                x+=260;
                y=10;
            }

            pb[n] = new QPushButton(st,ui->scrollArea);
            //pb[n]->setProperty("index",n);

            pb[n] ->setGeometry(QRect(QPoint(x, y),QSize(250, h)));
            //p_button->resize(100,100);
            y+=h;
            if(size==max1)
            {pb[n]->setStyleSheet("background-color: rgb(255,0,0);");
            }
            else
            {pb[n]->setStyleSheet("background-color: rgb(255,200,0);");}
                pb[n]->show();

            //layout->addWidget(pb[n]);

        }


        else if(var.isDir()== false)
        {
        QString st= getString(var);

        long long int size;

        size=calSize(var.absoluteFilePath());

        h=(var.size()*800)/total;

       if(h<=30) h=30;

       if(y+h>750)
       {
           x+=260;
           y=10;
       }

       pb[n] = new QPushButton(st,ui->scrollArea);

       //pb[n]->setProperty("index",n);

        // set size and location of the button
       pb[n] ->setGeometry(QRect(QPoint(x, y),QSize(250, h)));
       y+=h;
       pb[n]->setStyleSheet("background-color: rgb(255,200,0);");
       pb[n]->show();

       //layout->addWidget(pb[n]);

        }

        if(y>750)
        {
            x+=260;
            y=10;
        }
        else y+=10;

        n+=1;
    }


    // Create the button, make "this" the parent



    for(int i=0;i<l;i++)
    {
        // Connect button signal to appropriate slot
        connect(pb[i], SIGNAL (released()), this, SLOT (handleButton()));
    }


}



void Space::handleButton()
{

    QPushButton *button = (QPushButton *)sender();
   QString btext = button->text();
   int i=0;

       foreach (QFileInfo var, list)
       {
         QString s=getString(var);
         if(s==btext)break;

         i++;
       }

   QUrl url = QUrl::fromLocalFile(dir2.filePath(dir2[i]));
   QDesktopServices::openUrl(url);

    // resize button

}


Space::~Space()
{
    delete ui;
}
