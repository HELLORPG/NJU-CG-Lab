﻿#include "DrawingArea.h"

#include "Define.h"

//constexpr int INIT_WIDTH = 800;
#define INIT_WIDTH 800
#define INIT_HEIGHT 600



DrawingArea::DrawingArea(QWidget* parent) : QWidget(parent)
{
	/*qDebug() << this->width() << " " << this->height() << endl;
	qDebug() << this->geometry().width() << " " << this->geometry().height() << endl;*/
	/*
	 * 在这里通过这种方式是无法获得在Qt Designer中设计好的DrawingArea的大小的
	 * 这是因为，在ui_mainwindow.h的初始化中，是先调用了new DrawingArea函数，然后才进行setGeometry设定的，所以此时还无法捕获大小
	 */
	paperBackground = qRgb(255, 255, 255);
	paper = QImage(INIT_WIDTH, INIT_HEIGHT, QImage::Format_RGB32);
	paper.fill(paperBackground);
	tempPaper = paper;
	/*QPainter painter(this);
	painter.drawImage(0, 0, paper);*/
	// 需要重写绘图函数paintEvent来完成

	pen.setWidth(1);
	pen.setColor(qRgb(0, 0, 0));

	this->setMouseTracking(true);
	this->update();

	//show_command_text = new QTextEdit(this);
	return;
}


// 重写事件函数区域
void DrawingArea::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	//painter.drawImage(0, 0, paper);
	isDrawing ? painter.drawImage(0, 0, tempPaper) : painter.drawImage(0, 0, paper);	// 当处于画图阶段的时候，输出的是临时图像，否则则为真实图像

	return;
}


//void DrawingArea::mousePressEvent(QMouseEvent* event)
//{
//
//	if (event->button() == Qt::LeftButton) // 识别左键
//	{
//#ifdef PRINT_MOUSE_EVENT
//		qDebug() << "[Press Mouse Left Button]" << endl;
//#endif
//		if (!isDrawing)
//		{
//			isDrawing = true;
//			begin_point = event->pos(); // 获得当前鼠标的位置
//			end_point = event->pos(); // 增加这行代码为了防止在点击和释放中间没有移动鼠标而导致的错误图元问题
//		}
//	}
//
//	else if (event->button() == Qt::RightButton) // 识别右键
//	{
//#ifdef PRINT_MOUSE_EVENT
//		qDebug() << "[Press Mouse Right Button]" << endl;
//#endif
//	}
//
//	this->update();
//	return;
//}

void DrawingArea::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) // 识别左键
	{
#ifdef PRINT_MOUSE_EVENT
		qDebug() << "[Press Mouse Left Button]" << endl;
#endif
		if (!isDrawing)
		{
			isDrawing = true;
			begin_point = event->pos(); // 获得当前鼠标的位置
			end_point = event->pos(); // 增加这行代码为了防止在点击和释放中间没有移动鼠标而导致的错误图元问题
		}

		else if (isDrawing) // 此时的逻辑是终止绘图
		{
			isDrawing = false;
			if (temp_primitive != nullptr) // 当前图元不为空，为空则跳过
			{
				primitives.push_back(temp_primitive);
				now_primitive_num++;
				paper = tempPaper;
				temp_primitive = nullptr;
			}
		}
	}

	else if (event->button() == Qt::RightButton) // 识别右键，用于如多边形，曲线的增加信息点
	{
#ifdef PRINT_MOUSE_EVENT
		qDebug() << "[Press Mouse Right Button]" << endl;
#endif
		if (isDrawing)
		{
			mouseDrawAdd(tempPaper);
		}
	}

	this->update();
	return;
}



//void DrawingArea::mouseReleaseEvent(QMouseEvent* event)
//{
//	if (event->button() == Qt::LeftButton) // 识别左键
//	{
//#ifdef PRINT_MOUSE_EVENT
//		qDebug() << "[Release Mouse Left Button]" << endl;
//#endif
//
//		if (isDrawing)
//		{
//			isDrawing = false;
//
//			// 此时应该将缓存的直线刷新进入真实图片
//			paper = tempPaper;
//			this->update();
//
//			// 同时还需要，存储图元信息
//			appendPrimitiveByMouseEvent();
//		}
//	}
//
//	else if (event->button() == Qt::RightButton) // 识别右键
//	{
//#ifdef PRINT_MOUSE_EVENT
//		qDebug() << "[Release Mouse Right Button]" << endl;
//#endif
//	}
//
//	return;
//}

void DrawingArea::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) // 识别左键
	{
#ifdef PRINT_MOUSE_EVENT
		qDebug() << "[Release Mouse Left Button]" << endl;
#endif
	}
	else if (event->button() == Qt::RightButton) // 识别右键
	{
#ifdef PRINT_MOUSE_EVENT
		qDebug() << "[Release Mouse Right Button]" << endl;
#endif
	}
	return;
}


void DrawingArea::mouseMoveEvent(QMouseEvent* event)
{
	//qDebug() << QString("鼠标位置为") << event->pos() << endl;
	QString x = QString::number(event->pos().x());
	QString y = QString::number(event->pos().y());

#ifdef PRINT_MOUSE_LOCATION
	qDebug() << "当前鼠标的坐标为：" << x << "," << y << endl;
#endif

	QString location = "(" + x + "," + y + ")" +
		"    \xe7\x94\xbb\xe6\x9d\xbf\xe5\xa4\xa7\xe5\xb0\x8f = "/*画板大小*/ + QString::number(this->getXsize()) +
		"\xc3\x97"/*×*/ + QString::number(this->getYsize());
	// 两串UTF-8编码分别为：画板大小 ×
	// 使用了python来完成编码的转化，str.encode("utf-8")即可

	//this->setStatusTip(x + " , " + y);
	emit newLocationStatus(location); // 通过emit发出信号，鼠标位置更新


	// 应当进行相关的画图工作

	if (isDrawing) // 此时正在绘图
	{
		end_point = event->pos(); // 获取移动时的鼠标位置
		tempPaper = paper; // 将当前的图层保存到临时图层，之后都基于临时图层进行操作
		// 之后进行draw操作
		//draw(tempPaper); //进行绘图操作
		mouseDraw(tempPaper);
	}

	this->update();
	// END of Drawing Works
	return;
}


void DrawingArea::leaveEvent(QEvent* event)
{
	qDebug() << "[Mouse Out]" << endl;

	//// 此时，需要判定位鼠标已经抬起，也就是要终止所有的画图事件
	//isDrawing = false;
	/* 不需要这一段代码
	 * 这是因为当鼠标处于press状态下移出widget的时候，并不会停止坐标的捕获
	 * 事实上，这个时候鼠标的坐标显示可能是超出画布大小的
	 * 这个时候，保持绘画的状态不解除
	 */
	emit mouseLeave();
}


void DrawingArea::enterEvent(QEvent* event)
{
#ifdef PRINT_MOUSE_EVENT
	qDebug() << "[Mouse In]" << endl;
#endif

	return;
}


// 重写事件函数终止



// 关于画笔部分的函数

QString DrawingArea::penModeToQString(DrawMode mode)
{
	switch (mode)
	{
	case DrawMode::None: return("None");
	case DrawMode::Nature: return("Nature");
	case DrawMode::StraightLine: return("StraightLine");
	default: return("Undefine");
	}
}


// 关于画笔部分的函数结束


// 关于绘图的函数

void DrawingArea::draw(QImage& thisPaper)
{
	switch (drawMode)
	{
	case DrawMode::None: break; // 此时不做任何操作
	case DrawMode::Nature: break; // 目前没有实现这种方法
	case DrawMode::StraightLine:
	{
#ifdef PRINT_DRAW
		qDebug() << "[Draw Line " << begin_point << "to" << end_point << "]" << endl;
#endif
		//drawStraightLine(tempPaper, begin_point, end_point, StraightLineAlgorithm::None); // 这里实现的算法是可选的
		//drawStraightLine(tempPaper, begin_point, end_point, StraightLineAlgorithm::DDA);
		drawStraightLine(tempPaper, begin_point, end_point, StraightLineAlgorithm::Bresenham);
	}break;
	case DrawMode::Circle:
	{
#ifdef PRINT_DRAW
		qDebug() << "[Draw Circle " << begin_point << "to" << end_point << "]" << endl;
#endif
		drawCircle(tempPaper, begin_point, end_point);
	}break;
	case DrawMode::Ellipse:
	{
#ifdef PRINT_DRAW
		qDebug() << "[Draw Ellipse " << begin_point << "to" << end_point << "]" << endl;
#endif
		drawEllipse(tempPaper, begin_point, end_point);
	}
	}
	return;
}


// 对图元进行操作



// 对图元进行操作结束






