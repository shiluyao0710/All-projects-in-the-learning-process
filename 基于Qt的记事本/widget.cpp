#include "widget.h"
#include "ui_widget.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QShortcut>
#include <QTextCursor>

Widget::Widget(QWidget *parent) : QWidget(parent) , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->widgetBottom->setLayout(ui->horizontalLayout_2);
    ui->textEdit->installEventFilter(this);
    auto shortcutOpen = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")), this);
    auto shortcutSave = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")), this);
    auto shortcutClose = new QShortcut(QKeySequence(tr("Ctrl+W", "File|Close")), this);
    auto shortcutZoomIn = new QShortcut(QKeySequence(tr("Ctrl+=", "File|ZoomIn")), this);
    auto shortcutZoomOut = new QShortcut(QKeySequence(tr("Ctrl+-", "File|ZoomOut")), this);
    auto shortcutQuit = new QShortcut(QKeySequence(tr("Ctrl+F4", "File|Quit")), this);

    //连接信号与槽
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_activated(int)));
    QObject::connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &Widget::on_textEdit_cursorPositionChanged);
    QObject::connect(ui->pushButtonOpen, &QPushButton::clicked, this, &Widget::on_pushButtonOpen_clicked);
    QObject::connect(ui->pushButtonSave, &QPushButton::clicked, this, &Widget::on_pushButtonSave_clicked);
    QObject::connect(ui->pushButtonClose, &QPushButton::clicked, this, &Widget::on_pushButtonClose_clicked);
    QObject::connect(ui->pushButtonAdd, &QPushButton::clicked, this, &Widget::on_pushButtonAdd_clicked);
    QObject::connect(ui->pushButtonSub, &QPushButton::clicked, this, &Widget::on_pushButtonSub_clicked);

    QObject::connect(shortcutOpen, &QShortcut::activated , this, [=](){
        on_pushButtonOpen_clicked();
    });
    QObject::connect(shortcutSave, &QShortcut::activated , this, [=](){
        on_pushButtonSave_clicked();
    });
    QObject::connect(shortcutClose, &QShortcut::activated , this, [=](){
        on_pushButtonClose_clicked();
    });
    QObject::connect(shortcutZoomIn, &QShortcut::activated , this, [=](){
        on_pushButtonAdd_clicked();
    });
    QObject::connect(shortcutZoomOut, &QShortcut::activated , this, [=](){
        on_pushButtonSub_clicked();
    });
    QObject::connect(shortcutQuit, &QShortcut::activated , this, [=](){
        quit();
    });

    //断开连接
    QObject::disconnect(ui->pushButtonOpen, &QPushButton::clicked, this, &Widget::on_pushButtonOpen_clicked);
    QObject::disconnect(ui->pushButtonSave, &QPushButton::clicked, this, &Widget::on_pushButtonSave_clicked);
    QObject::disconnect(ui->pushButtonClose, &QPushButton::clicked, this, &Widget::on_pushButtonClose_clicked);
    QObject::disconnect(ui->pushButtonAdd, &QPushButton::clicked, this, &Widget::on_pushButtonAdd_clicked);
    QObject::disconnect(ui->pushButtonSub, &QPushButton::clicked, this, &Widget::on_pushButtonSub_clicked);
    QObject::disconnect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_activated(int)));
    QObject::disconnect(ui->textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(on_textEdit_cursorPositionChanged()));

}

Widget::~Widget()
{
    delete ui;
}

int Widget::fontsize = 9;
int Widget::ctrlKey = 0;
//槽函数实现，文件打开
void Widget::on_pushButtonOpen_clicked()
{
    //文件打开
    QString fileNameOpen = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "D:/QTcode/NoteBook",
                                                     tr("All files (*)"));
    if(fileNameOpen != "")
    {
        //qDebug() << "file open cancel";
        //设置窗口title
        this->setWindowTitle(fileNameOpen + "    NotePad");
        //设置字体格式
        QFont font("Microsoft YaHei", Widget::fontsize, 50);
        ui->textEdit->setFont(font);
        //清楚textEdit内容
        ui->textEdit->clear();
        //绑定文件
        file.setFileName(fileNameOpen);
       //实例化QTextStream对象
        QTextStream in(&file);
        //获取当前选中的下拉列表内容
        QString str = ui->comboBox->currentText();
        //QString转换为const char *
        const char* c_str = str.toStdString().c_str();
        //编码设置
        in.setCodec(c_str);
        std::cout << "读入数据" << std::endl;
        //打开文件
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
            qDebug() << "file failed to open";
        //判断是否读到尾部
        while(!in.atEnd())
        {
            //QTextStream方式，按行读取文件内容
            QString line = in.readLine();
            //读取的内容追加到textEdit文本框中
            ui->textEdit->append(line);
        }
    }
    //qDebug() << "filename:" <<fileNameOpen;
}

//槽函数实现，文件保存
void Widget::on_pushButtonSave_clicked()
{
    if(!file.isOpen())
    {
        //保存文件名
        QString fileNameSave = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "D:/QTcode/NoteBook/untitled.txt",
                                   tr("Text (*.txt *.doc)"));
        //文件设置
        file.setFileName(fileNameSave);
        //设置窗口title
        this->setWindowTitle(fileNameSave + "    NotePad");
    }
    if(file.isOpen())
        file.close();
    //打开文件，可读可写，截断方式
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text |QIODevice::Truncate))
//        qDebug() << "file failed to open";
        return;
    //实例化QTextStream对象
    QTextStream out(&file);
    //设置编码格式
    QString str = ui->comboBox->currentText();
    const char * c_str = str.toStdString().c_str();
    out.setCodec(c_str);
    std::cout << "写入数据" << std::endl;
    //从文本框中读取内容
    QString context = ui->textEdit->toPlainText();
//    qDebug() << context;
//    qDebug() << context.indexOf('\n');
//    qDebug() << context.mid(context.indexOf('\n') + 1, -1);
//    qDebug() << (context.mid(0, 15) == "****codedformat");
    //QString拼接字符串
    QString tip = QString("****codedformat: %1****Delete the row before saving****\n").arg(str);
    //内容写入到文件
    if(context.mid(0, 15) == "****codedformat")
    {
        //字符串截断
        context =  context.mid(context.indexOf('\n') + 1, -1);
    }
    out << tip;
    out << context;
}

//槽函数实现，文件关闭
void Widget::on_pushButtonClose_clicked()
{
    if(ui->textEdit->toPlainText() != "" || file.isOpen())
    {
        //警告框
        int ret = QMessageBox::warning(this, tr("NotePad"),
                                       tr("The document has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel,
                                       QMessageBox::Save);
        //选择值
        switch (ret) {
        case QMessageBox::Save:
            // Save was clicked
            on_pushButtonSave_clicked();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            //清除文本框中的内容
            ui->textEdit->clear();
            //判断文件是否为打开状态
            if(file.isOpen())
            {
                //设置窗体标题
                this->setWindowTitle("NotePad");
                //关闭文件
                file.close();
            }
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            break;
        default:
            // should never be reached
            break;
        }
    }
}

//槽函数实现，下拉列表
void Widget::on_comboBox_activated(int index)
{
    //清楚文本框中的内容
    ui->textEdit->clear();
    //判断是否有文件打开
    if(file.isOpen())
    {
        //实例化QTextStream对象
        QTextStream in(&file);
        //设置编码格式
        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
        //文件读取光标移动到开始位置
        file.seek(0);
        //判断文件是否读到末尾
        while(!in.atEnd())
        {
            //按行读取文件内容
            QString line = in.readLine();
            //追加读出的文件到文本框内
            ui->textEdit->append(line);
        }
    }
}

//槽函数实现：光标位置改变
void Widget::on_textEdit_cursorPositionChanged()
{
    //获取光标位置
    QTextCursor cursor = ui->textEdit->textCursor();
    //int类型转QString类型
    QString raw = QString::number(cursor.blockNumber()+1);
    QString col = QString::number(cursor.columnNumber()+1);
    //qDebug() << "raw:"<< cursor.blockNumber() << ",col:" << cursor.columnNumber();
    //QString字符串拼接
    QString rawcol = QString("raw:%1,col:%2").arg(raw).arg(col);
    //设置QLabel文本内容
    ui->labelRawCol->setText(rawcol);
    //设置字体格式
    QFont font("Microsoft YaHei", 9, 50);
    ui->labelRawCol->setFont(font);
    //创建QList容器
    QList<QTextEdit::ExtraSelection> extraselection;
    //创建容器中的对象
    QTextEdit::ExtraSelection ex;
    //设置光标
    ex.cursor = ui->textEdit->textCursor();
    ex.cursor.clearSelection();
    //设置背景，rgb颜色
    ex.format.setBackground(QColor(255, 255, 110));
    ex.format.setFontUnderline(true);
    ex.format.setProperty(QTextFormat::FullWidthSelection, true);
    //将对象加入容器
    extraselection.append(ex);
    //设置当前行高亮
    ui->textEdit->setExtraSelections(extraselection);
}

void Widget::on_pushButtonAdd_clicked()
{
       ZoomInText();
//    //清楚文本框中的内容
//    ui->textEdit->clear();
//    if(file.isOpen())
//    {
//        //实例化QTextStream对象
//        QTextStream in(&file);
//        //设置文字大小
//        if(Widget::fontsize < 30)
//            Widget::fontsize += 1;
//        QFont font("Microsoft YaHei", Widget::fontsize, 50);
//        ui->textEdit->setFont(font);
//        //设置编码格式
//        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
//        //文件读取光标移动到开始位置
//        file.seek(0);
//        //判断文件是否读到末尾
//        while(!in.atEnd())
//        {
//            //按行读取文件内容
//            QString line = in.readLine();
//            //追加读出的文件到文本框内
//            ui->textEdit->append(line);
//        }
//    }
}

void Widget::on_pushButtonSub_clicked()
{
       ZoomOutText();
//    //清楚文本框中的内容
//    ui->textEdit->clear();
//    //判断是否有文件打开
//    if(file.isOpen())
//    {
//        //实例化QTextStream对象
//        QTextStream in(&file);
//        //设置编文字大小
//        if(Widget::fontsize > 5)
//            Widget::fontsize -= 1;
//        QFont font("Microsoft YaHei", Widget::fontsize, 50);
//        ui->textEdit->setFont(font);
//        //设置编码格式
//        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
//        //文件读取光标移动到开始位置
//        file.seek(0);
//        //判断文件是否读到末尾
//        while(!in.atEnd())
//        {
//            //按行读取文件内容
//            QString line = in.readLine();
//            //追加读出的文件到文本框内
//            ui->textEdit->append(line);
//        }
//    }

}

void Widget::quit()
{
    QString context = ui->textEdit->toPlainText();
    //    qDebug() << context;
    if(context != "" || file.isOpen())
    {
        on_pushButtonSave_clicked();
    }
    Widget::close();

}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent *>(event);
        //检查键盘的CTRL是否被按下
        if (QGuiApplication::keyboardModifiers() & Qt::ControlModifier)
        {
            if (wheelEvent->angleDelta().y() > 0)
            {
                ZoomInText(); // 滚轮向上滚动
            } else {
                ZoomOutText(); // 滚轮向下滚动
            }
        }
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

void Widget::ZoomInText()
{
    qDebug() << "zoominText";
    //获得TextEdit的当前字体信息
    QFont font = ui->textEdit->font();
    //获得当前字体的大小
    int fontSize = font.pointSize();
    if(fontSize == -1) return;
    //改变大小，并设置字体大小
    int newFontSize = fontSize+1;
    font.setPointSize(newFontSize);
    ui->textEdit->setFont(font);

}

void Widget::ZoomOutText()
{
    qDebug() << "zoomoutText";
    //获得TextEdit的当前字体信息
    QFont font = ui->textEdit->font();
    //改变大小，并设置字体大小
    font.setPointSize(font.pointSize()-1);
    ui->textEdit->setFont(font);
}

//void Widget::keyPressEvent(QKeyEvent *event)
//{
//    if(event->key() == Qt::Key_Control)
//    {
//        Widget::ctrlKey = 1;
//    }
//    QWidget::keyPressEvent(event);
//}

//void Widget::keyReleaseEvent(QKeyEvent *event)
//{
//    if(event->key() == Qt::Key_Control)
//    {
//        Widget::ctrlKey = 0;
//    }
//    QWidget::keyReleaseEvent(event);
//}

//void Widget::wheelEvent(QWheelEvent *event)
//{
//    if(Widget::ctrlKey == 1)
//    {
//        if(event->angleDelta().y() > 0)
//        {
//            on_pushButtonAdd_clicked();
//        }
//        if(event->angleDelta().y() < 0)
//        {
//            on_pushButtonSub_clicked();
//        }
//        event->accept();
//    }
//    else
//    {
//        QWidget::wheelEvent(event);
//    }
//}


void Widget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::warning(this, tr("Notepad"),
                                   tr("close the window\n"
                                      "Do you want to close the window?"),
                                   QMessageBox::Ok | QMessageBox::No
                                   );
    switch(ret)
    {
    case QMessageBox::Ok:
        if(ui->textEdit->toPlainText() != "" || file.isOpen())
        {
            on_pushButtonSave_clicked();
            event->accept();
            break;
        }
        event->accept();
        break;
    case QMessageBox::No:
        event->ignore();
        break;
    }
}

