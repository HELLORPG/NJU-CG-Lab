#include "DrawingArea.h"

void DrawingArea::runCommand()
{
	for (const auto &command : commands) // ��ÿһ��ָ����н���
	{
		if (command.size() < 1)
			continue;
		if (command[0] == "resetCanvas") // ���û�����С
		{
			int width(std::stoi(command[1])), height(std::stoi(command[2]));
			setPaperSize(width, height);
		}

		else if (command[0] == "saveCanvas") // ���滭��
		{
			string file_name(command[1] + ".bmp");
			paper.save(QString::fromStdString(file_name));
		}

		else if (command[0] == "setColor") // ���û�����ɫ
		{
			QRgb c = qRgb(std::stoi(command[1]), std::stoi(command[2]), std::stoi(command[3]));
			QColor color(c);
			setPenColor(color);
		}
		
	}
	
	return;
}
