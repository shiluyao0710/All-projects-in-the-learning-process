#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>

class MyTextEdit : public QTextEdit
{
public:
    MyTextEdit(QWidget *parent);
    bool ctrlKeyPressed = 0;
protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
};

#endif // MYTEXTEDIT_H
