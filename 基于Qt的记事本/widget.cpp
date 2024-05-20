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

    //�����ź����
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

    //�Ͽ�����
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
//�ۺ���ʵ�֣��ļ���
void Widget::on_pushButtonOpen_clicked()
{
    //�ļ���
    QString fileNameOpen = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "D:/QTcode/NoteBook",
                                                     tr("All files (*)"));
    if(fileNameOpen != "")
    {
        //qDebug() << "file open cancel";
        //���ô���title
        this->setWindowTitle(fileNameOpen + "    NotePad");
        //���������ʽ
        QFont font("Microsoft YaHei", Widget::fontsize, 50);
        ui->textEdit->setFont(font);
        //���textEdit����
        ui->textEdit->clear();
        //���ļ�
        file.setFileName(fileNameOpen);
       //ʵ����QTextStream����
        QTextStream in(&file);
        //��ȡ��ǰѡ�е������б�����
        QString str = ui->comboBox->currentText();
        //QStringת��Ϊconst char *
        const char* c_str = str.toStdString().c_str();
        //��������
        in.setCodec(c_str);
        std::cout << "��������" << std::endl;
        //���ļ�
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
            qDebug() << "file failed to open";
        //�ж��Ƿ����β��
        while(!in.atEnd())
        {
            //QTextStream��ʽ�����ж�ȡ�ļ�����
            QString line = in.readLine();
            //��ȡ������׷�ӵ�textEdit�ı�����
            ui->textEdit->append(line);
        }
    }
    //qDebug() << "filename:" <<fileNameOpen;
}

//�ۺ���ʵ�֣��ļ�����
void Widget::on_pushButtonSave_clicked()
{
    if(!file.isOpen())
    {
        //�����ļ���
        QString fileNameSave = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "D:/QTcode/NoteBook/untitled.txt",
                                   tr("Text (*.txt *.doc)"));
        //�ļ�����
        file.setFileName(fileNameSave);
        //���ô���title
        this->setWindowTitle(fileNameSave + "    NotePad");
    }
    if(file.isOpen())
        file.close();
    //���ļ����ɶ���д���ضϷ�ʽ
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text |QIODevice::Truncate))
//        qDebug() << "file failed to open";
        return;
    //ʵ����QTextStream����
    QTextStream out(&file);
    //���ñ����ʽ
    QString str = ui->comboBox->currentText();
    const char * c_str = str.toStdString().c_str();
    out.setCodec(c_str);
    std::cout << "д������" << std::endl;
    //���ı����ж�ȡ����
    QString context = ui->textEdit->toPlainText();
//    qDebug() << context;
//    qDebug() << context.indexOf('\n');
//    qDebug() << context.mid(context.indexOf('\n') + 1, -1);
//    qDebug() << (context.mid(0, 15) == "****codedformat");
    //QStringƴ���ַ���
    QString tip = QString("****codedformat: %1****Delete the row before saving****\n").arg(str);
    //����д�뵽�ļ�
    if(context.mid(0, 15) == "****codedformat")
    {
        //�ַ����ض�
        context =  context.mid(context.indexOf('\n') + 1, -1);
    }
    out << tip;
    out << context;
}

//�ۺ���ʵ�֣��ļ��ر�
void Widget::on_pushButtonClose_clicked()
{
    if(ui->textEdit->toPlainText() != "" || file.isOpen())
    {
        //�����
        int ret = QMessageBox::warning(this, tr("NotePad"),
                                       tr("The document has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel,
                                       QMessageBox::Save);
        //ѡ��ֵ
        switch (ret) {
        case QMessageBox::Save:
            // Save was clicked
            on_pushButtonSave_clicked();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            //����ı����е�����
            ui->textEdit->clear();
            //�ж��ļ��Ƿ�Ϊ��״̬
            if(file.isOpen())
            {
                //���ô������
                this->setWindowTitle("NotePad");
                //�ر��ļ�
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

//�ۺ���ʵ�֣������б�
void Widget::on_comboBox_activated(int index)
{
    //����ı����е�����
    ui->textEdit->clear();
    //�ж��Ƿ����ļ���
    if(file.isOpen())
    {
        //ʵ����QTextStream����
        QTextStream in(&file);
        //���ñ����ʽ
        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
        //�ļ���ȡ����ƶ�����ʼλ��
        file.seek(0);
        //�ж��ļ��Ƿ����ĩβ
        while(!in.atEnd())
        {
            //���ж�ȡ�ļ�����
            QString line = in.readLine();
            //׷�Ӷ������ļ����ı�����
            ui->textEdit->append(line);
        }
    }
}

//�ۺ���ʵ�֣����λ�øı�
void Widget::on_textEdit_cursorPositionChanged()
{
    //��ȡ���λ��
    QTextCursor cursor = ui->textEdit->textCursor();
    //int����תQString����
    QString raw = QString::number(cursor.blockNumber()+1);
    QString col = QString::number(cursor.columnNumber()+1);
    //qDebug() << "raw:"<< cursor.blockNumber() << ",col:" << cursor.columnNumber();
    //QString�ַ���ƴ��
    QString rawcol = QString("raw:%1,col:%2").arg(raw).arg(col);
    //����QLabel�ı�����
    ui->labelRawCol->setText(rawcol);
    //���������ʽ
    QFont font("Microsoft YaHei", 9, 50);
    ui->labelRawCol->setFont(font);
    //����QList����
    QList<QTextEdit::ExtraSelection> extraselection;
    //���������еĶ���
    QTextEdit::ExtraSelection ex;
    //���ù��
    ex.cursor = ui->textEdit->textCursor();
    ex.cursor.clearSelection();
    //���ñ�����rgb��ɫ
    ex.format.setBackground(QColor(255, 255, 110));
    ex.format.setFontUnderline(true);
    ex.format.setProperty(QTextFormat::FullWidthSelection, true);
    //�������������
    extraselection.append(ex);
    //���õ�ǰ�и���
    ui->textEdit->setExtraSelections(extraselection);
}

void Widget::on_pushButtonAdd_clicked()
{
       ZoomInText();
//    //����ı����е�����
//    ui->textEdit->clear();
//    if(file.isOpen())
//    {
//        //ʵ����QTextStream����
//        QTextStream in(&file);
//        //�������ִ�С
//        if(Widget::fontsize < 30)
//            Widget::fontsize += 1;
//        QFont font("Microsoft YaHei", Widget::fontsize, 50);
//        ui->textEdit->setFont(font);
//        //���ñ����ʽ
//        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
//        //�ļ���ȡ����ƶ�����ʼλ��
//        file.seek(0);
//        //�ж��ļ��Ƿ����ĩβ
//        while(!in.atEnd())
//        {
//            //���ж�ȡ�ļ�����
//            QString line = in.readLine();
//            //׷�Ӷ������ļ����ı�����
//            ui->textEdit->append(line);
//        }
//    }
}

void Widget::on_pushButtonSub_clicked()
{
       ZoomOutText();
//    //����ı����е�����
//    ui->textEdit->clear();
//    //�ж��Ƿ����ļ���
//    if(file.isOpen())
//    {
//        //ʵ����QTextStream����
//        QTextStream in(&file);
//        //���ñ����ִ�С
//        if(Widget::fontsize > 5)
//            Widget::fontsize -= 1;
//        QFont font("Microsoft YaHei", Widget::fontsize, 50);
//        ui->textEdit->setFont(font);
//        //���ñ����ʽ
//        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
//        //�ļ���ȡ����ƶ�����ʼλ��
//        file.seek(0);
//        //�ж��ļ��Ƿ����ĩβ
//        while(!in.atEnd())
//        {
//            //���ж�ȡ�ļ�����
//            QString line = in.readLine();
//            //׷�Ӷ������ļ����ı�����
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
        //�����̵�CTRL�Ƿ񱻰���
        if (QGuiApplication::keyboardModifiers() & Qt::ControlModifier)
        {
            if (wheelEvent->angleDelta().y() > 0)
            {
                ZoomInText(); // �������Ϲ���
            } else {
                ZoomOutText(); // �������¹���
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
    //���TextEdit�ĵ�ǰ������Ϣ
    QFont font = ui->textEdit->font();
    //��õ�ǰ����Ĵ�С
    int fontSize = font.pointSize();
    if(fontSize == -1) return;
    //�ı��С�������������С
    int newFontSize = fontSize+1;
    font.setPointSize(newFontSize);
    ui->textEdit->setFont(font);

}

void Widget::ZoomOutText()
{
    qDebug() << "zoomoutText";
    //���TextEdit�ĵ�ǰ������Ϣ
    QFont font = ui->textEdit->font();
    //�ı��С�������������С
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

