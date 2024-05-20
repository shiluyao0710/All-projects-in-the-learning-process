#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtDebug>
#include <QFile>
#include <iostream>
#include <string>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    static int fontsize;
    static int ctrlKey;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QFile file;
    void quit();
    void ZoomInText();
    void ZoomOutText();
protected:
    void closeEvent(QCloseEvent *event) override;


//    void keyPressEvent(QKeyEvent *event) override;
//    void keyReleaseEvent(QKeyEvent *event) override;
    //    void wheelEvent(QWheelEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *e) override;
private slots:
    void on_pushButtonOpen_clicked();
    void on_pushButtonSave_clicked();

    void on_pushButtonClose_clicked();

    void on_comboBox_activated(int index);

    void on_textEdit_cursorPositionChanged();

    void on_pushButtonAdd_clicked();

    void on_pushButtonSub_clicked();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
