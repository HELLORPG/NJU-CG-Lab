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
		QApplication app(argc, argv); // һ����Ҫ
		/*QDialog dialog;
		dialog.setWindowTitle(QObject::tr("Hello, dialog!"));
		dialog.exec();*/
		//AllocConsole();
		//freopen("CONOUT$", "w+t", stdout);
		///*
		// * https://blog.csdn.net/lwwl12/article/details/79816739
		// */
		/*cout << "[������ģʽ����] �����б�Ϊ" << endl;
		cout << argv[1] << endl;
		cout << argv[2] << endl;*/ // ��δ������޷�����ģ���Ϊû�п���̨�Ĵ���
		DrawingArea drawingArea(nullptr); // ��ʵ���Բ���Ҫ����������ΪĬ�ϲ�������nullptr������ֻ��Ϊ�˹淶����
		drawingArea.update();
		
		string dir_path = argv[2];
		dir_path = drawingArea.formatDirPath(dir_path);
		drawingArea.setOutputPath(dir_path);
		drawingArea.openCommandFile(argv[1]);
		
		drawingArea.runCommand();
	}
	else
	{
		QApplication app(argc, argv);
		MainWindow window;
		window.show();
		return app.exec();
	}
}
