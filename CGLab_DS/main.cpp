#include "mainwindow.h"

#include <QApplication>

#include <iostream>
//#include <Windows.h>
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		//AllocConsole();
		//freopen("CONOUT$", "w+t", stdout);
		///*
		// * https://blog.csdn.net/lwwl12/article/details/79816739
		// */
		/*cout << "[������ģʽ����] �����б�Ϊ" << endl;
		cout << argv[1] << endl;
		cout << argv[2] << endl;*/ // ��δ������޷�����ģ���Ϊû�п���̨�Ĵ���
		DrawingArea drawingArea(nullptr); // ��ʵ���Բ���Ҫ����������ΪĬ�ϲ�������nullptr������ֻ��Ϊ�˹淶����
	}
	else
	{
		QApplication app(argc, argv);
		MainWindow window;
		window.show();
		return app.exec();
	}
}
