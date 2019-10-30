#include "DrawingArea.h"
#include "mainwindow.h"


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
	//QImage old_paper = paper;
	//QRect rect(0, 0, x, y);
	//paper = old_paper.copy(rect);
	paper = QImage(x, y, QImage::Format_RGB32);
	tempPaper = paper;

	emit setPaperSizeSignal(x, y);
	
	clearPaper(true);
	drawAll();
	
	return;
}



void DrawingArea::changePenMode(const DrawMode new_mode)
{
	drawMode = new_mode;

#ifdef PRINT_PEN
	QString penModeStr = penModeToQString(drawMode);
	qDebug() << "[Change Pen Mode to" << penModeStr << "]" << endl;
#endif


	return;
}



void DrawingArea::drawAll()
{

	QPen now_pen = pen; // ���浱ǰ��pen
	for (const auto &p : primitives)
	{
		vector<MyPoint> points;
		pen = p->_pen();
		switch (p->_type())
		{
		case PrimitiveType::None: break;
		case PrimitiveType::Nature: break; // Ŀǰû�н����Ȼ�����Ļ���
		case PrimitiveType::StraightLine:
		{
			StraightLinePrimitive* p_straightline = dynamic_cast<StraightLinePrimitive*>(p);
			points = createStraightLineByBresenham(p_straightline->x1(), p_straightline->y1(), p_straightline->x2(), p_straightline->y2());
		}break;
		case PrimitiveType::Ellipse:
		{
			EllipsePrimitive* p_ellipse = dynamic_cast<EllipsePrimitive*>(p);
			points = createEllipse(p_ellipse->_x0(), p_ellipse->_y0(), p_ellipse->_rx(), p_ellipse->_ry());
		}break;
		}
		QPainter painter(&paper); // ʹ��QImage��ʼ��QPainter����Ҫʹ��ָ��
		painter.setPen(pen);
		
		for (const auto &point : points)
		{
			painter.drawPoint(point.x, point.y);
		}
	}
	pen = now_pen;
	tempPaper = paper;
	
	this->update(); // ���´��壬����ʹ��QWidget����paintEvent���������ƴ���
	
	return;
}


void DrawingArea::clearPaper(bool save_primitives)
{
	paper.fill(paperBackground);
	tempPaper.fill(paperBackground);

	if (!save_primitives)
		primitives.clear();
	 
	this->update();
	return;
}


// ����ӿڽ���