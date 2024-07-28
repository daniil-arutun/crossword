#include "win.h"
#include <QApplication>


int main(int ac,char** av)
{
    QApplication app(ac, av);

    Win *w=new Win();
    w->setFixedSize(700,650);
             w->show();
      return app.exec();
}

