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


// ����ӿڽ���