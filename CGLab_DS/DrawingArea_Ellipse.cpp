﻿#include "DrawingArea.h"

void DrawingArea::drawCircle(QImage& thisPaper, const QPoint begin, const QPoint end)
{
	int x1 = begin.x(), x2 = end.x();
	int y1 = begin.y(), y2 = end.y();
	int x0 = (x2 + x1) / 2;
	int y0 = (y2 + y1) / 2;
	int rx = abs(x2 - x1) / 2;
	int ry = abs(y2 - y1) / 2;

	ry > rx ? rx = ry : rx = rx;

	vector<MyPoint> points;
	QPainter painter(&thisPaper); // 使用QImage初始化QPainter，需要使用指针
	painter.setPen(pen);

	points = createEllipse(x0, y0, rx, rx);

	for (int i(0); i < points.size(); ++i)
	{
		painter.drawPoint(points[i].x, points[i].y);
	}
	this->update(); // 更新窗体，可以使得QWidget调用paintEvent函数，绘制窗体
	
	return;
}

void DrawingArea::drawEllipse(QImage& thisPaper, const QPoint begin, const QPoint end)
{
	const int x1 = begin.x(), x2 = end.x();
	const int y1 = begin.y(), y2 = end.y();

	const int x0 = (x2 + x1) / 2;
	const int y0 = (y2 + y1) / 2;
	const int rx = abs(x2 - x1) / 2;
	const int ry = abs(y2 - y1) / 2;

	vector<MyPoint> points;
	QPainter painter(&thisPaper); // 使用QImage初始化QPainter，需要使用指针
	painter.setPen(pen);

	points = createEllipse(x0, y0, rx, ry);

	for (int i(0); i < points.size(); ++i)
	{
		painter.drawPoint(points[i].x, points[i].y);
	}
	this->update(); // 更新窗体，可以使得QWidget调用paintEvent函数，绘制窗体

	return;
}




vector<MyPoint> DrawingArea::createEllipse(int x0, int y0, int rx, int ry)
{
	vector<MyPoint> points;

	//qDebug() << "output" << rx << ry << endl;
	// 首先依照圆心在原点，进行计算
	//points.push_back({ 0, ry }); // 第一个点
	double p1(static_cast<double>(ry) * ry - static_cast<double>(rx) * rx * ry + static_cast<double>(rx) * rx / 4.0);
	int x(0), y(ry); // 设置初始点

	while (2.0 * static_cast<double>(ry) * ry * x < 2.0 * static_cast<double>(rx) * rx * y)
	{
		//qDebug() << x << y << p1;
		points.push_back({ x, y });
		++x; // 此时x已经是xk+1
		if (p1 < 0)
		{
			p1 += 2 * static_cast<double>(ry) * ry * x + static_cast<double>(ry) * ry;
		}
		else
		{
			--y;
			p1 += 2 * static_cast<double>(ry) * ry * x - 2 * static_cast<double>(rx) * rx * y + static_cast<double>(ry) * ry;
		}
	}

	/*if (points.size() != 0)
	{
		x = points[points.size() - 1].x;
		y = points[points.size() - 1].y;
	}*/
	// 这一段对应导致不满足上述条件的运算，进行还原
	
	
	double p2(static_cast<double>(ry) * ry * (x + 1.0/2.0) * (x + 1.0/2.0) + static_cast<double>(rx) * rx * (static_cast<double>(y) - 1) * (static_cast<double>(y) - 1) - static_cast<double>(rx) * rx * ry * ry);
	//qDebug() << x << y << p2;
	//p2 = -151;
	//points.push_back({ 4, 14 });
	while (x <= rx && y >= 0)
	{
		//qDebug() << x << y << p2;
		points.push_back({ x, y });
		--y; // 此时的y已经是yk-1
		if (p2 > 0)
		{
			p2 += static_cast<double>(rx) * rx - 2 * static_cast<double>(rx) * rx * y;
		}
		else
		{
			++x;
			p2 += 2 * static_cast<double>(ry) * ry * x - 2 * static_cast<double>(rx) * rx * y + static_cast<double>(rx) * rx;
		}
	}

	// 下面需要将所有的坐标都取对称
	int old_length(points.size());

	for (int i(0); i < old_length; ++i)
	{
		MyPoint point = points[i];
		points.push_back({ -point.x, point.y });
		points.push_back({ -point.x, -point.y });
		points.push_back({ point.x, -point.y });
	}

	for (auto &point : points)
	{
		point.x += x0;
		point.y += y0;
	}
	
	return points;
}
