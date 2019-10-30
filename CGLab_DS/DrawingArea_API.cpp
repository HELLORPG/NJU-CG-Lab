#include "DrawingArea.h"


// ����ӿ�

QImage DrawingArea::getPaper() const
{
	return paper;
}


void DrawingArea::setPenColor(QColor color)
{
	pen.setColor(color);
	return;
}


void DrawingArea::setPaperSize(int x, int y)
{
	this->setGeometry(0, 0, x, y);
	//setMinimumSize(x, y);
	QImage old_paper = paper;
	QRect rect(0, 0, x, y);
	paper = old_paper.copy(rect);
	return;
}


// ����ӿڽ���