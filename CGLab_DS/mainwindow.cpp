#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AboutAuthorDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // �������Ƿ�������֮����UI���ֵĲ��ִ���
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAboutAuthor_triggered()
/*
 * �ڵ�ǰ���е���Ŀ�ļ��У����Ҳ���connect���������Ӵ˲ۺ���������ź�
 * �����ֱ�ӱ�д���źŲۻ��Ʋ�ͬ�������������ʾ�ģ���ͨ��Qt Designerֱ���γɺ�����ܵ�
 * <<����ע�⣬��Ҫ�Լ����ĺ�����>>
 * ʵ���ϣ���صĶ���ʹ�����BuildĿ¼�е�moc_*.cpp��
 * ����Qt�����������Ŀ��ʱ���Լ�������ά�����ļ����ݣ���ʹ������Ŀ�ļ�Ŀ¼�У�Ҳ��Ӱ����Ŀ�����ɺͱ���
 * ��ʵ�ϣ���Qt Designer��Ƶ�ҳ��Ĳ��ִ������ɣ������϶���ui->setupUi(this);����
 */
{
    QDialog* about_author_dialog = new AboutAuthorDialog();
    about_author_dialog->exec();
    return;
}
