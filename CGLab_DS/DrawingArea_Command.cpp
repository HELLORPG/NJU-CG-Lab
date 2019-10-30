#include "DrawingArea.h"

using std::atoi;

void DrawingArea::runCommand()
{
	for (const auto &command : commands) // ��ÿһ��ָ����н���
	{
		if (command.size() < 1)
			continue;
		if (command[0] == "resetCanvas") // ���û�����С
		{
			const int width(std::stoi(command[1])), height(std::stoi(command[2]));
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

		else if (command[0] == "drawLine") // ��ֱ��
		{
			const int id(stoi(command[1])), x1(stoi(command[2])), y1(stoi(command[3])), x2(stoi(command[4])), y2(stoi(command[5]));
			
			vector<MyPoint> points;
			QPainter painter(&paper); // ʹ��QImage��ʼ��QPainter����Ҫʹ��ָ��
			painter.setPen(pen);
			
			points = command[6] == "DDA" ? createStraightLineByDDA(x1, y1, x2, y2) : createStraightLineByBresenham(x1, y1, x2, y2);

			for (const auto &point : points)
			{
				painter.drawPoint(point.x, point.y);
			}

			appendStraightLinePrimitive(x1, y1, x2, y2, id, pen);

			this->update();
		}

		else if (command[0] == "drawEllipse")
		{
			const int id(stoi(command[1])), x0(stoi(command[2])), y0(stoi(command[3])), rx(stoi(command[4])), ry(stoi(command[5]));

			vector<MyPoint> points;
			QPainter painter(&paper); // ʹ��QImage��ʼ��QPainter����Ҫʹ��ָ��
			painter.setPen(pen);

			points = createEllipse(x0, y0, rx, ry);

			for (const auto& point : points)
			{
				painter.drawPoint(point.x, point.y);
			}

			appendEllipsePrimitive(x0, y0, rx, ry, id, pen);

			this->update();
		}

	}
	
	return;
}
