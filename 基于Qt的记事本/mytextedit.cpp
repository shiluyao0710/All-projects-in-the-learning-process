#include "mytextedit.h"
#include "widget.h"

#include <QWheelEvent>


MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    qDebug() << (e->key() == Qt::Key_Control);
    if(e->key() == Qt::Key_Control)
    {
        ctrlKeyPressed = 1;
    }
    else
    {
        QTextEdit::keyPressEvent(e);
    }

}

void MyTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    qDebug() << (e->key() == Qt::Key_Control);
    if(e->key() == Qt::Key_Control)
    {
        ctrlKeyPressed = 0;
    }
    else
    {
        QTextEdit::keyReleaseEvent(e);
    }
}

void MyTextEdit::wheelEvent(QWheelEvent *e)
{
    qDebug() << e->angleDelta().y();
    if(ctrlKeyPressed == 1)
    {
        if(e->angleDelta().y() > 0)
        {
//            Widget w;    //能够调用相应的函数，但不能改变字体大小。
//            w.ZoomInText();
            zoomIn();
        }
        else if(e->angleDelta().y() < 0)
        {
//            Widget w;
//            w.ZoomOutText();
            zoomOut();
        }
        e->accept();
    }
    else
    {
        QTextEdit::wheelEvent(e);
    }
}
