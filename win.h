#ifndef WIN_H
#define WIN_H
#include <QPaintDevice>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QFont>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "generic.h"

class Win: public QWidget
{
private:
    Q_OBJECT
public:
    Win(QWidget* w=nullptr):QWidget(w)
    {
        cha=new QChar*[13];
        cha2=new QChar*[13];
        cvet=new int*[13];
        for(int r=0;r<13;r++)
        {
            cha[r]=new QChar[20];
             cha2[r]=new QChar[20];
            cvet[r]=new int[20];
         }

        for(int e=0;e<13;e++)
        {
            for(int w=0;w<20;w++)
            {
                cha[e][w]=' ';
                cha2[e][w]=' ';
                cvet[e][w]=0;
            }
        }
        nom=0;


        std::thread thr(&Win::beskon,this);
        thr.detach();
        b1=new QPushButton("1 СЛОВО",this);
        b2=new QPushButton("2 СЛОВО",this);
        b3=new QPushButton("3 СЛОВО",this);
        b4=new QPushButton("4 СЛОВО",this);
        b5=new QPushButton("5 СЛОВО",this);
        b1->setGeometry(100,550,100,50);
        b2->setGeometry(200,550,100,50);
        b3->setGeometry(300,550,100,50);
        b4->setGeometry(400,550,100,50);
        b5->setGeometry(500,550,100,50);
        regen=new QPushButton("НОВЫЙ",this);
        regen->setGeometry(50,50,100,50);
        connect(b1,SIGNAL(clicked(bool)),this,SLOT(fun_b1()));
        connect(b2,SIGNAL(clicked(bool)),this,SLOT(fun_b2()));
        connect(b3,SIGNAL(clicked(bool)),this,SLOT(fun_b3()));
        connect(b4,SIGNAL(clicked(bool)),this,SLOT(fun_b4()));
        connect(b5,SIGNAL(clicked(bool)),this,SLOT(fun_b5()));
        connect(regen,SIGNAL(clicked(bool)),this,SLOT(reg()));
    }
    ~Win()
    {
        for(int ww=0;ww<13;ww++)
        {
            delete[] cha[ww];
            delete[] cha2[ww];
            delete[] cvet[ww];
        }
        delete[] cha;
         delete[] cha2;
        delete[] cvet;
    }
private slots:
    void fun_b1()
    {
        QWidget* w=new QWidget(this,Qt::Dialog);
        w->setWindowModality(Qt::WindowModal);
        w->resize(400,100);
        if(nom==1)
        {
        QLabel* l=new QLabel("Живое существо, обладающее даром мышления и речи,\n"
                                   " способностью создавать орудия и пользоваться\n ими в процессе общественного труда.",w);
        }else if(nom==2)
        {
            QLabel* l=new QLabel("Короткое ручное огнестрельное оружие\n для стрельбы на коротких расстояниях.",w);
        }else if(nom==3)
        {
          QLabel* l=new QLabel("Аппарат для охлаждения воздуха в помещении.",w);
        }else if(nom==4)
        {
             QLabel* l=new QLabel("Система технических приспособлений для передачи звуков\n на расстояние по проводам при помощи электрической энергии.",w);
        }else if(nom==5)
        {
             QLabel* l=new QLabel("Многолетнее растение с твёрдым стволом\n и отходящими от него ветвями, образующими крону.",w);
        }
            w->show();
    }
    void fun_b3()
    {
        QWidget* w=new QWidget(this,Qt::Dialog);
        w->setWindowModality(Qt::WindowModal);
        w->resize(400,100);
        if(nom==1)
        {
        QLabel* l=new QLabel("Чертёж земной поверхности (или звёздного неба)",w);
        }else if(nom==2)
        {
             QLabel* l=new QLabel("маленький сочный или мясистый плод,\n обычно кустарниковых или травянистых растений",w);
        }else if(nom==3)
        {
         QLabel* l=new QLabel("Верхняя конечность человека от плеча до пальцев,\n а также от запястья до пальцев",w);
        }else if(nom==4)
        {
            QLabel* l=new QLabel("Осветительный прибор в виде стеклянного шара,\n коробки со стеклянными стенками,в к-рой помещается источник света",w);
        }else if(nom==5)
        {
            QLabel* l=new QLabel("Способность говорить, говорение",w);
        }
            w->show();
    }
    void fun_b2()
    {
        QWidget* w=new QWidget(this,Qt::Dialog);
        w->setWindowModality(Qt::WindowModal);
        w->resize(400,100);
        if(nom==1)
        {
        QLabel* l=new QLabel("способность двигательно выйти из любого положения,"
                               "\n то есть способность справиться с любой возникшей\n двигательной задачей",w);
        }else if(nom==2)
        {
             QLabel* l=new QLabel("Черта, определяющая направление, предел, уровень чего-н",w);
        }else if(nom==3)
        {
             QLabel* l=new QLabel("Зрелищное предприятие для устройства представлений\n с участием акробатов, гимнастов, клоунов, дрессированных животных.",w);
        }else if(nom==4)
        {
             QLabel* l=new QLabel("Крупное домашнее однокопытное животное",w);
        }else if(nom==5)
        {
            QLabel* l=new QLabel("Часть суток от утра до вечера",w);
        }
        w->show();
    }
    void fun_b4()
    {
        QWidget* w=new QWidget(this,Qt::Dialog);
        w->setWindowModality(Qt::WindowModal);
        w->resize(400,100);
        if(nom==1)
        {
        QLabel* l=new QLabel("Тонкая палка для опоры при ходьбе",w);
        }else if(nom==2)
        {
              QLabel* l=new QLabel("Система технических приспособлений для передачи звуков\n на расстояние по проводам при помощи электрической энергии.",w);
        }else if(nom==3)
        {
              QLabel* l=new QLabel("Короткая верхняя одежда, наглухо застёгивающаяся.",w);
        }else if(nom==4)
        {
              QLabel* l=new QLabel("Часть суток от вечера до утра.",w);
        }else if(nom==5)
        {
             QLabel* l=new QLabel(" боковой отросток растения, имеющий продолговатую форму.",w);
        }
            w->show();
    }
    void fun_b5()
    {
        QWidget* w=new QWidget(this,Qt::Dialog);
        w->setWindowModality(Qt::WindowModal);
        w->resize(400,100);
        if(nom==1)
        {
        QLabel* l=new QLabel("Отдельный предмет в пространстве, а также часть пространства,"
                               "\n заполненная материей, каким-н. веществом или ограниченная \nзамкнутой поверхностью",w);
        }else if(nom==2)
        {
            QLabel* l=new QLabel(" Орган обоняния, находящийся на лице у человека\n и на морде у животных.",w);
        }else if(nom==3)
        {
            QLabel* l=new QLabel("Плоский с двух сторон кусок дерева небольшой толщины,\n получаемый путём продольной распилки бревна",w);
        }else if(nom==4)
        {
            QLabel* l=new QLabel("состояние, при котором реакция организма\n на внешний мир сводится к минимуму.",w);
        }else if(nom==5)
        {
             QLabel* l=new QLabel("положительное духовно нравственное качество личности,\n характеризующее отношение человека к окружающим,\n забота о нуждах, запросах и желаниях людей.",w);
        }
            w->show();
    }

    void reg()
    {int temp=0;
        if(nom!=0)
        {
            temp=nom;
            nom=0;
            var.notify_one();
        }else
        {
            nom++;
            if(nom==6)
            {
                nom=1;
            }
        }
        if(temp!=0)
        {if(temp+1!=6)
            {
            nom=temp+1;
            }else
            {
                nom=1;
            }
        }

        qDebug()<<nom<<"\n";
        if(nom==1)
        {
            for(int e=0;e<13;e++)
            {
                for(int w=0;w<20;w++)
                {
                    cha[e][w]=' ';
                    cha2[e][w]=' ';
                    cvet[e][w]=0;
                }
            }
            QString str1="ЧЕЛОВЕК";
            QString str2="АРТА";
            QString str3="ОВКОСТЬ";
            QString str4="РОСТЬ";
            QString str5="ЕЛО";
            cha[2][0]=str1.at(0);
            cha[3][0]=str1.at(1);
            cha[4][0]=str1.at(2);
            cha[5][0]=str1.at(3);
            cha[6][0]=str1.at(4);
            cha[7][0]=str1.at(5);
            cha[8][0]=str1.at(6);

            cha[8][1]=str2.at(0);
            cha[8][2]=str2.at(1);
            cha[8][3]=str2.at(2);
            cha[8][4]=str2.at(3);

            cha[4][1]=str3.at(0);
            cha[4][2]=str3.at(1);
            cha[4][3]=str3.at(2);
            cha[4][4]=str3.at(3);
            cha[4][5]=str3.at(4);
            cha[4][6]=str3.at(5);
            cha[4][7]=str3.at(6);

            cha[5][6]=str4.at(0);
            cha[6][6]=str4.at(1);
            cha[7][6]=str4.at(2);
            cha[8][6]=str4.at(3);
            cha[9][6]=str4.at(4);

            cha[8][7]=str5.at(0);
            cha[8][8]=str5.at(1);
            cha[8][9]=str5.at(2);
        }
        else if(nom==2)
        {
            for(int e=0;e<13;e++)
            {
                for(int w=0;w<20;w++)
                {
                    cha[e][w]=' ';
                    cha2[e][w]=' ';
                    cvet[e][w]=0;
                }
            }
            QString str1="ПИСТОЛЕТ";
            QString str2="ЛИНИЯ";
            QString str3="ГОДА";
            QString str4="ЕЛЕФОН";
            QString str5="ОС";
            cha[2][0]=str1.at(0);
            cha[2][1]=str1.at(1);
            cha[2][2]=str1.at(2);
            cha[2][3]=str1.at(3);
            cha[2][4]=str1.at(4);
            cha[2][5]=str1.at(5);
            cha[2][6]=str1.at(6);
            cha[2][7]=str1.at(7);

            cha[1][1]=str2.at(0);
            cha[2][1]=str2.at(1);
            cha[3][1]=str2.at(2);
            cha[4][1]=str2.at(3);
            cha[5][1]=str2.at(4);

            cha[5][2]=str3.at(0);
            cha[5][3]=str3.at(1);
            cha[5][4]=str3.at(2);
            cha[5][5]=str3.at(3);

            cha[3][7]=str4.at(0);
            cha[4][7]=str4.at(1);
            cha[5][7]=str4.at(2);
            cha[6][7]=str4.at(3);
            cha[7][7]=str4.at(4);
            cha[8][7]=str4.at(5);

            cha[8][8]=str5.at(0);
            cha[8][9]=str5.at(1);

        }
        else if(nom==3)
        {
            for(int e=0;e<13;e++)
            {
                for(int w=0;w<20;w++)
                {
                    cha[e][w]=' ';
                    cha2[e][w]=' ';
                    cvet[e][w]=0;
                }
            }
            QString str1="КОНДИЦИОНЕР";
            QString str2="ИРК";
            QString str3="УКА";
            QString str4="УРТК";
            QString str5="ОСКА";

            cha[2][0]=str1.at(0);
            cha[2][1]=str1.at(1);
            cha[2][2]=str1.at(2);
            cha[2][3]=str1.at(3);
            cha[2][4]=str1.at(4);
            cha[2][5]=str1.at(5);
            cha[2][6]=str1.at(6);
            cha[2][7]=str1.at(7);
            cha[2][8]=str1.at(8);
            cha[2][9]=str1.at(9);
            cha[2][10]=str1.at(10);

            cha[3][5]=str2.at(0);
            cha[4][5]=str2.at(1);
            cha[5][5]=str2.at(2);

            cha[3][10]=str3.at(0);
            cha[4][10]=str3.at(1);
            cha[5][10]=str3.at(2);

            cha[5][6]=str4.at(0);
            cha[5][7]=str4.at(1);
            cha[5][8]=str4.at(2);
            cha[5][9]=str4.at(3);

            cha[3][3]=str5.at(0);
            cha[4][3]=str5.at(1);
            cha[5][3]=str5.at(2);
            cha[6][3]=str5.at(3);

        }
        else if(nom==4)
        {
            for(int e=0;e<13;e++)
            {
                for(int w=0;w<20;w++)
                {
                    cha[e][w]=' ';
                    cha2[e][w]=' ';
                    cvet[e][w]=0;
                }
            }
            QString str1="ТЕЛЕФОН";
            QString str2="ОШАДЬ";
            QString str3="ОНАРЬ";
            QString str4="ОЧЬ";
            QString str5="СО";

            cha[2][0]=str1.at(0);
            cha[2][1]=str1.at(1);
            cha[2][2]=str1.at(2);
            cha[2][3]=str1.at(3);
            cha[2][4]=str1.at(4);
            cha[2][5]=str1.at(5);
            cha[2][6]=str1.at(6);

            cha[3][2]=str2.at(0);
            cha[4][2]=str2.at(1);
            cha[5][2]=str2.at(2);
            cha[6][2]=str2.at(3);
            cha[7][2]=str2.at(4);

            cha[3][4]=str3.at(0);
            cha[4][4]=str3.at(1);
            cha[5][4]=str3.at(2);
            cha[6][4]=str3.at(3);
            cha[7][4]=str3.at(4);

            cha[4][5]=str4.at(0);
            cha[4][6]=str4.at(1);
            cha[4][7]=str4.at(2);

            cha[0][6]=str5.at(0);
            cha[1][6]=str5.at(1);

        }
        else if(nom==5)
        {
            for(int e=0;e<13;e++)
            {
                for(int w=0;w<20;w++)
                {
                    cha[e][w]=' ';
                    cha2[e][w]=' ';
                    cvet[e][w]=0;
                }
            }
            QString str1="ДЕРЕВО";
            QString str2="ЕНЬ";
            QString str3="ЕЧЬ";
            QString str4="ЕТВЬ";
            QString str5="ЧУТКОСТЬ";

            cha[0][0]=str1.at(0);
            cha[1][0]=str1.at(1);
            cha[2][0]=str1.at(2);
            cha[3][0]=str1.at(3);
            cha[4][0]=str1.at(4);
            cha[5][0]=str1.at(5);

            cha[0][1]=str2.at(0);
            cha[0][2]=str2.at(1);
            cha[0][3]=str2.at(2);

            cha[2][1]=str3.at(0);
            cha[2][2]=str3.at(1);
            cha[2][3]=str3.at(2);

            cha[4][1]=str4.at(0);
            cha[4][2]=str4.at(1);
            cha[4][3]=str4.at(2);
            cha[4][4]=str4.at(3);

            cha[2][2]=str5.at(0);
            cha[3][2]=str5.at(1);
            cha[4][2]=str5.at(2);
            cha[5][2]=str5.at(3);
            cha[6][2]=str5.at(4);
            cha[7][2]=str5.at(5);
            cha[8][2]=str5.at(6);
            cha[9][2]=str5.at(7);

        }
        var.notify_one();
        repaint();
    }

protected:
    void paintEvent(QPaintEvent* e) override
    {

        QPainter pa;
        pa.begin(this);
      if(nom!=0)
        {

            if(nom==1)
            {
                pa.drawText(170,150,QString("1"));
                pa.drawText(140,270,QString("2"));
                pa.drawText(140,420,QString("3"));
                pa.drawText(420,230,QString("4"));
                pa.drawText(380,420,QString("5"));


            }else if(nom==2)
            {
                pa.drawText(140,180,QString("1"));
                pa.drawText(210,110,QString("2"));
                pa.drawText(180,310,QString("3"));
                pa.drawText(450,150,QString("4"));
                pa.drawText(420,430,QString("5"));


            }else if(nom==3)
            {
                pa.drawText(140,180,QString("1"));
                pa.drawText(370,150,QString("2"));
                pa.drawText(580,150,QString("3"));
                pa.drawText(340,310,QString("4"));
                pa.drawText(290,150,QString("5"));


            }else if(nom==4)
            {
                pa.drawText(140,180,QString("1"));
                pa.drawText(250,150,QString("2"));
                pa.drawText(330,150,QString("3"));
                pa.drawText(300,270,QString("4"));
                pa.drawText(410,70,QString("5"));


            }else if(nom==5)
            {
                pa.drawText(170,70,QString("1"));
                pa.drawText(330,100,QString("2"));
                pa.drawText(330,190,QString("3"));
                pa.drawText(370,270,QString("4"));
                pa.drawText(270,140,QString("5"));


            }

            for(int z=0;z<13;z++)
            {
                for(int w=0;w<20;w++)
                {

                    if(cvet[z][w]==1)
                    {
                        pa.fillRect(w*40+160,z*40+80,40,40,Qt::GlobalColor::yellow);

                    } if(cvet[z][w]==2)
                    {
                        pa.fillRect(w*40+160,z*40+80,40,40,Qt::GlobalColor::red);
                        QFont r=pa.font();
                        r.setPixelSize(35);
                        pa.setFont(r);
                        pa.drawText(w*40+160,z*40+80,50,50,0,QString(cha2[z][w]).toUpper());
                    }
                    if(cvet[z][w]==3)
                    {


                        pa.fillRect(w*40+160,z*40+80,40,40,Qt::GlobalColor::green);
                        QFont r=pa.font();
                        r.setPixelSize(35);
                        pa.setFont(r);
                        pa.drawText(w*40+160,z*40+80,50,50,0,QString(cha2[z][w]).toUpper());
                    }

                }
            }


            for(int e=0;e<13;e++)
            {
                for(int w=0;w<20;w++)
                {

                    if(cha[e][w]!=' ')
                    {
                        pa.drawRect(160+w*40,80+e*40,40,40);

                    }
                }

            }

        }
        pa.end();
    }


    void beskon()
    {
        bool b=true;
        int ch=0;
        std::unique_lock<std::mutex> lo(mut);

        while(b)
        {

            var.wait(lo,[this](){ return (nom!=0)?true:false;});
            if(nom!=0)
            {


              if(nom==1)
                {

                    if(cha2[2][0]==cha[2][0])
                    {   bool q=false;
                        for(int e=2;e<9;e++)
                        {
                            if(cha2[e][0]==cha[e][0])
                            {
                                q=true;
                            }else
                            {
                                q=false;
                                break;
                            }
                        }
                        if(q)
                        {
                            if(cvet[3][0]!=3)
                            {
                                for(int e=2;e<9;e++)
                                {
                                    cvet[e][0]=3;
                                }
                                ch++;
                            }
                        }
                    }
                    if(cha2[8][0]==cha[8][0])
                    {
                        bool q=true;

                        for(int e=0;e<5;e++)
                        {
                            if(cha2[8][e]==cha[8][e])
                            {
                                q=true;

                            }else
                            {
                                q=false;
                                break;
                            }
                        }
                        if(q)
                        {
                            if(cvet[8][1]!=3)
                            {
                                for(int e=0;e<5;e++)
                                {
                                    cvet[8][e]=3;
                                }
                                ch++;
                            }
                        }
                    }
                    if(cha2[4][0]==cha[4][0])
                    {
                        bool q=true;
                        for(int e=0;e<8;e++)
                        {
                            if(cha2[4][e]==cha[4][e])
                            {
                                q=true;
                            }else
                            {
                                q=false;
                                break;
                            }
                        }
                        if(q)
                        {
                            if(cvet[4][1]!=3)
                            {
                                for(int e=0;e<8;e++)
                                {
                                    cvet[4][e]=3;
                                }
                                ch++;
                            }
                        }
                    }

                    if(cha2[4][6]==cha[4][6])
                    {
                        bool q=true;
                        for(int e=4;e<10;e++)
                        {
                            if(cha2[e][6]==cha[e][6])
                            {
                                q=true;
                            }else
                            {
                                q=false;
                                break;
                            }
                        }
                        if(q)
                        {
                            if(cvet[5][6]!=3)
                            {
                                for(int e=4;e<10;e++)
                                {
                                    cvet[e][6]=3;
                                }
                                ch++;
                            }
                        }

                    }
                    if(cha2[8][6]==cha[8][6])
                    {
                        bool q=true;
                        for(int e=6;e<10;e++)
                        {
                            if(cha2[8][e]==cha[8][e])
                            {
                                q=true;
                            }else
                            {
                                q=false;
                                break;
                            }
                        }
                        if(q)
                        {
                            if(cvet[8][7]!=3)
                            {
                                for(int e=6;e<10;e++)
                                {
                                    cvet[8][e]=3;
                                }
                                ch++;
                            }
                        }
                    }
                    if(ch==25)
                    {qDebug()<<"\nend\n";
                        break;
                    }
              }else if(nom==2)
              {

                  if(cha2[2][0]==cha[2][0])
                  {   bool q=false;
                      for(int e=0;e<8;e++)
                      {
                          if(cha2[2][e]==cha[2][e])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[2][0]!=3)
                          {
                              for(int e=0;e<8;e++)
                              {
                                  cvet[2][e]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(cha2[1][1]==cha[1][1])
                  {
                      bool q=true;

                      for(int e=1;e<6;e++)
                      {
                          if(cha2[e][1]==cha[e][1])
                          {
                              q=true;

                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[1][1]!=3)
                          {
                              for(int e=1;e<6;e++)
                              {
                                  cvet[e][1]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(cha2[5][1]==cha[5][1])
                  {
                      bool q=true;
                      for(int e=1;e<6;e++)
                      {
                          if(cha2[5][e]==cha[5][e])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[5][2]!=3)
                          {
                              for(int e=1;e<6;e++)
                              {
                                  cvet[5][e]=3;
                              }
                              ch++;
                          }
                      }
                  }

                  if(cha2[2][7]==cha[2][7])
                  {
                      bool q=true;
                      for(int e=2;e<9;e++)
                      {
                          if(cha2[e][7]==cha[e][7])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[3][7]!=3)
                          {
                              for(int e=2;e<9;e++)
                              {
                                  cvet[e][7]=3;
                              }
                              ch++;
                          }
                      }

                  }
                  if(cha2[8][7]==cha[8][7])
                  {
                      bool q=true;
                      for(int e=7;e<10;e++)
                      {
                          if(cha2[8][e]==cha[8][e])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[8][8]!=3)
                          {
                              for(int e=7;e<10;e++)
                              {
                                  cvet[8][e]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(ch==25)
                  {qDebug()<<"\nend\n";
                      break;
                  }
              }

              else if(nom==3)
              {
                   if(cha2[2][0]==cha[2][0])
                  {   bool q=false;
                      for(int e=0;e<11;e++)
                      {
                          if(cha2[2][e]==cha[2][e])
                          {
                              q=true;

                          }else
                          {

                              q=false;
                              break;
                          }
                      }

                      if(q)
                      {
                          if(cvet[2][1]!=3)
                          {
                              for(int e=0;e<11;e++)
                              {
                                  cvet[2][e]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(cha2[2][5]==cha[2][5])
                  {
                      bool q=true;

                      for(int e=2;e<6;e++)
                      {
                          if(cha2[e][5]==cha[e][5])
                          {
                              q=true;

                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[3][5]!=3)
                          {
                              for(int e=2;e<6;e++)
                              {
                                  cvet[e][5]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(cha2[2][10]==cha[2][10])
                  {
                      bool q=true;
                      for(int e=2;e<6;e++)
                      {
                          if(cha2[e][10]==cha[e][10])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[3][10]!=3)
                          {
                              for(int e=2;e<6;e++)
                              {
                                  cvet[e][10]=3;
                              }
                              ch++;
                          }
                      }
                  }

                  if(cha2[5][5]==cha[5][5])
                  {
                      bool q=true;
                      for(int e=5;e<11;e++)
                      {
                          if(cha2[5][e]==cha[5][e])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[5][6]!=3)
                          {
                              for(int e=5;e<11;e++)
                              {
                                  cvet[5][e]=3;
                              }
                              ch++;
                          }
                      }

                  }
                  if(cha2[2][3]==cha[2][3])
                  {
                      bool q=true;
                      for(int e=2;e<7;e++)
                      {
                          if(cha2[e][3]==cha[e][3])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[3][3]!=3)
                          {
                              for(int e=2;e<7;e++)
                              {
                                  cvet[e][3]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(ch==25)
                  {qDebug()<<"\nend\n";
                      break;
                  }

              }else if(nom==4)
              {


                  if(cha2[2][0]==cha[2][0])
                  {   bool q=false;
                      for(int e=0;e<7;e++)
                      {
                          if(cha2[2][e]==cha[2][e])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[2][0]!=3)
                          {
                              for(int e=0;e<7;e++)
                              {
                                  cvet[2][e]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(cha2[2][3]==cha[2][3])
                  {
                      bool q=true;

                      for(int e=2;e<8;e++)
                      {
                          if(cha2[e][2]==cha[e][2])
                          {
                              q=true;

                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[3][2]!=3)
                          {
                              for(int e=2;e<8;e++)
                              {
                                  cvet[e][2]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(cha2[2][4]==cha[2][4])
                  {
                      bool q=true;
                      for(int e=2;e<8;e++)
                      {
                          if(cha2[e][4]==cha[e][4])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[3][4]!=3)
                          {
                              for(int e=2;e<8;e++)
                              {
                                  cvet[e][4]=3;
                              }
                              ch++;
                          }
                      }
                  }

                  if(cha2[4][4]==cha[4][4])
                  {
                      bool q=true;
                      for(int e=4;e<8;e++)
                      {
                          if(cha2[4][e]==cha[4][e])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[4][5]!=3)
                          {
                              for(int e=4;e<8;e++)
                              {
                                  cvet[4][e]=3;
                              }
                              ch++;
                          }
                      }

                  }
                  if(cha2[1][6]==cha[1][6])
                  {
                      bool q=true;
                      for(int e=0;e<3;e++)
                      {
                          if(cha2[e][6]==cha[e][6])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[0][6]!=3)
                          {
                              for(int e=0;e<3;e++)
                              {
                                  cvet[e][6]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(ch==25)
                  {qDebug()<<"\nend\n";
                      break;
                  }


              }else if(nom==5)
              {

                  if(cha2[0][0]==cha[0][0])
                  {   bool q=false;
                      for(int e=0;e<6;e++)
                      {
                          if(cha2[e][0]==cha[e][0])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[1][0]!=3)
                          {
                              for(int e=0;e<6;e++)
                              {
                                  cvet[e][0]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(cha2[0][1]==cha[0][1])
                  {
                      bool q=true;

                      for(int e=0;e<4;e++)
                      {
                          if(cha2[0][e]==cha[0][e])
                          {
                              q=true;

                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[0][1]!=3)
                          {
                              for(int e=0;e<4;e++)
                              {
                                  cvet[0][e]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(cha2[2][0]==cha[2][0])
                  {
                      bool q=true;
                      for(int e=0;e<4;e++)
                      {
                          if(cha2[2][e]==cha[2][e])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[2][1]!=3)
                          {
                              for(int e=0;e<4;e++)
                              {
                                  cvet[2][e]=3;
                              }
                              ch++;
                          }
                      }
                  }

                  if(cha2[4][0]==cha[4][0])
                  {
                      bool q=true;
                      for(int e=0;e<5;e++)
                      {
                          if(cha2[4][e]==cha[4][e])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[4][1]!=3)
                          {
                              for(int e=0;e<5;e++)
                              {
                                  cvet[4][e]=3;
                              }
                              ch++;
                          }
                      }

                  }
                  if(cha2[3][2]==cha[3][2])
                  {
                      bool q=true;
                      for(int e=2;e<10;e++)
                      {
                          if(cha2[e][2]==cha[e][2])
                          {
                              q=true;
                          }else
                          {
                              q=false;
                              break;
                          }
                      }
                      if(q)
                      {
                          if(cvet[3][2]!=3)
                          {
                              for(int e=2;e<10;e++)
                              {
                                  cvet[e][2]=3;
                              }
                              ch++;
                          }
                      }
                  }
                  if(ch==25)
                  {qDebug()<<"\nend\n";
                      break;
                  }



              }

            }

        }
    }

    bool event(QEvent *ev) override
    {
        if(ev->type()==QKeyEvent::KeyPress)
        {
     QKeyEvent *e=static_cast<QKeyEvent*>(ev);
            for(int z=0;z<13;z++)
            {
                for(int w=0;w<20;w++)
                {
                    if(cvet[z][w]==1)
                    {
                    cha2[z][w]=e->text().at(0).toUpper();
                    cvet[z][w]=2;
                    repaint();
                    }
                }
            }
   }

        return QWidget::event(ev);
    }

    void mousePressEvent(QMouseEvent* e) override
    {
var.notify_one();

            for(int z=0;z<13;z++)
            {
                for(int w=0;w<20;w++)
                {
                    if(e->button()==Qt::LeftButton)//можно еще вот так уточнять какая кнопка была нажата
                    {

                            if(((e->x()>=160+w*40)&&(e->x()<=200+w*40))&&((e->y()>=80+z*40)&&(e->y()<=120+z*40)))
                            {
                                if(cvet[z][w]!=3)
                                {
                                    for(int z=0;z<13;z++)
                                    {
                                        for(int w=0;w<20;w++)
                                        {
                                            if(cvet[z][w]==1)
                                            {
                                                cvet[z][w]=0;
                                            }
                                        }
                                    }
                                        if(cha[z][w]!=' ')
                                        {
                                            cvet[z][w]=1;
                                        x1=160+w*40;
                                        y1=80+z*40;
                                        repaint();
                                        }

                                }
                            }

                     }
                    else if(e->button()==Qt::RightButton)
                    {
                        if(cvet[z][w]==1)
                        {
                        cvet[z][w]=0;
                        repaint();
                        }else
                        {
                            repaint();
                        }
                    }

                }

            }

        QWidget::mousePressEvent(e);
    }

private:
    QPushButton *b1,*b2,*b3,*b4,*b5;
    QPushButton *regen;
//    QLabel* prov;
    GEN* ge;
    QChar** cha,**cha2;
    int** cvet;
    int x1;
    int y1;
    int nom;
    std::mutex mut;
    std::condition_variable var;
};

#endif // WIN_H
