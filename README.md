# crossword

Данная программа была сделана мною во время учебы в университете. это было моей проектной работой.
Программа представляет собой кроссворд, который использует многопоточность для облегчения работы.

В главном фалйе происходит запуск окна
```c++
int main(int ac,char** av)
{
    QApplication app(ac, av);

    Win *w=new Win();
    w->setFixedSize(700,650);
             w->show();
      return app.exec();
}
```

во втором файле идет создание всех объектов интерфейса.
одновременно с этим запускается второй поток, отвечающий за обработку сигналов с клавиатуры и мыши
```c++
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
```

это один из 5 слотов для выведения подсказок пользователю
```c++
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
```

Так выглядит начало функции, которая распознает какие вопросы и слова нужно дать пользователь, чтобы он начал отгадывать
```c++
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
```

Далее идет начало функции, которая проверяет правильность ввода данных пользователем.
Также эта функция работает в другом потоке, чтобы сама программа не проверяла каждый раз новую букву.
```c++
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
              }
```

Дальше идут функции оброботчика клавиатуры и мыши
```c++
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

```
