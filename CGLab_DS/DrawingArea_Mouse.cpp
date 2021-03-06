﻿#include "DrawingArea.h"

/*
 * 这个文件重新构建了鼠标绘制图像的事件
 * 独立出来文件表示重构信息
 */

void DrawingArea::mouseDraw(QImage& thisPaper)
{
	//if (!temp_primitive)
	//	delete temp_primitive; // 释放空间，防止内存泄漏
	switch (drawMode)
	{
	case DrawMode::None: break;	// 此时是不做图模式
	case DrawMode::Nature: break;	// 自然绘图模式当前没有实现
	case DrawMode::StraightLine: mouseDrawStraightLine(thisPaper, StraightLineAlgorithm::Bresenham); break;	// 默认使用Bresenham算法进行绘制
	case DrawMode::Circle: mouseDrawCircle(thisPaper); break;
	case DrawMode::Ellipse: mouseDrawEllipse(thisPaper); break;
	case DrawMode::Polygon: mouseDrawPolygon(thisPaper, StraightLineAlgorithm::Bresenham); break;
	case DrawMode::Curve_Bezier: mouseDrawCurve_Bezier(thisPaper); break;
	case DrawMode::Curve_B_spline: mouseDrawCurve_B_spline(thisPaper); break;
	default: break; // 如果找不到对应的，就不做任何处理
	}

	drawPrimitive(temp_primitive, thisPaper);

	if (drawMode == DrawMode::Curve_B_spline || drawMode == DrawMode::Curve_Bezier)
	{
		temptempPaper = thisPaper;
		drawVirtualPrimitive(temptemp_primitive, temptempPaper);
	}
	return;
}

void DrawingArea::mouseDrawAdd(QImage& thisPaper)
{
	switch (drawMode)
	{
	case DrawMode::Polygon: mouseDrawPolygonAddPoint(thisPaper);
	case DrawMode::Curve_Bezier: mouseDrawCurveAddPoint(thisPaper);
	case DrawMode::Curve_B_spline: mouseDrawCurveAddPoint(thisPaper);
	default: break;
	}

	return;
}



void DrawingArea::mouseDrawCircle(QImage& thisPaper)
{
	if (!temp_primitive)
		delete temp_primitive; // 释放空间，防止内存泄漏
	
	int x1 = begin_point.x(), x2 = end_point.x();
	int y1 = begin_point.y(), y2 = end_point.y();
	int x0 = (x2 + x1) / 2;
	int y0 = (y2 + y1) / 2;
	int rx = abs(x2 - x1) / 2;
	int ry = abs(y2 - y1) / 2;

	ry > rx ? rx = ry : rx = rx;

	temp_primitive = new Ellipse(x0, y0, rx, rx, now_primitive_num, pen);
	//temp_primitive->print();
	return;
}

void DrawingArea::mouseDrawEllipse(QImage& thisPaper)
{
	if (!temp_primitive)
		delete temp_primitive; // 释放空间，防止内存泄漏
	
	const int x1 = begin_point.x(), x2 = end_point.x();
	const int y1 = begin_point.y(), y2 = end_point.y();

	const int x0 = (x2 + x1) / 2;
	const int y0 = (y2 + y1) / 2;
	const int rx = abs(x2 - x1) / 2;
	const int ry = abs(y2 - y1) / 2;

	temp_primitive = new Ellipse(x0, y0, rx, ry, now_primitive_num, pen);
	return;
}

void DrawingArea::mouseDrawPolygon(QImage& thisPaper, const StraightLineAlgorithm algorithm)
{
	if (temp_primitive && temp_primitive->_type() == PrimitiveType::Polygon) // 此时，如果已经是多边形
	{
		Polygon* polygon = dynamic_cast<Polygon*>(temp_primitive);
		polygon->setTail(end_point.x(), end_point.y());
	}

	else
	{
		if (!temp_primitive)
			delete temp_primitive;

		vector<MyPoint> vertices;
		vertices.push_back({ begin_point.x(), begin_point.y() });
		vertices.push_back({ end_point.x(), end_point.y() });

		temp_primitive = new Polygon(vertices, now_primitive_num, pen, algorithm);
	}

	return;
}

void DrawingArea::mouseDrawCurve_Bezier(QImage& thisPaper)
{
	if (temp_primitive && temp_primitive->_type() == PrimitiveType::Curve) // 此时如果已经是曲线的话
	{
		Curve* curve = dynamic_cast<Curve*>(temp_primitive);
		curve->setTail(end_point.x(), end_point.y());
	}

	else
	{
		if (!temp_primitive)
			delete temp_primitive;

		vector<MyPoint> fixed_points;
		fixed_points.push_back({ begin_point.x(), begin_point.y() });
		fixed_points.push_back({ end_point.x(), end_point.y() });

		temp_primitive = new Curve(fixed_points, now_primitive_num, pen, CurveAlgorithm::Bezier);
	}

	// 下面是对临时的临时图元的操作
	if (temptemp_primitive != nullptr)
	{
		delete temptemp_primitive;
	}
	temptemp_primitive = new Curve(*dynamic_cast<Curve*>(temp_primitive));
	dynamic_cast<Curve*>(temptemp_primitive)->addPoint();

	return;
}

void DrawingArea::mouseDrawCurve_B_spline(QImage& thisPaper)
{
	if (temp_primitive && temp_primitive->_type() == PrimitiveType::Curve) // 此时如果已经是曲线的话
	{
		Curve* curve = dynamic_cast<Curve*>(temp_primitive);
		curve->setTail(end_point.x(), end_point.y());
	}

	else // 此时就增加一个对应的曲线图元
	{
		if (!temp_primitive)
			delete temp_primitive;

		vector<MyPoint> fixed_points;
		fixed_points.push_back({ begin_point.x(), begin_point.y() });
		fixed_points.push_back({ end_point.x(), end_point.y() });

		temp_primitive = new Curve(fixed_points, now_primitive_num, pen, CurveAlgorithm::B_spline);
	}

	// 下面是对临时的临时图元的操作
	if (temptemp_primitive != nullptr)
	{
		delete temptemp_primitive;
	}
	temptemp_primitive = new Curve(*dynamic_cast<Curve*>(temp_primitive));
	dynamic_cast<Curve*>(temptemp_primitive)->addPoint();

	return;
}



void DrawingArea::mouseDrawPolygonAddPoint(QImage& thisPaper)
{
	if (temp_primitive && temp_primitive->_type() == PrimitiveType::Polygon) // 此时，如果已经是多边形
	{
		Polygon* polygon = dynamic_cast<Polygon*>(temp_primitive);
		polygon->addPoint();
	}
	return;
}

void DrawingArea::mouseDrawCurveAddPoint(QImage& thisPaper)
{
	if (temp_primitive && temp_primitive->_type() == PrimitiveType::Curve)
	{
		Curve* curve = dynamic_cast<Curve*>(temp_primitive);
		curve->addPoint();
	}
}



void DrawingArea::mouseDrawStraightLine(QImage& thisPaper, const StraightLineAlgorithm algorithm)
{
	if (!temp_primitive)
		delete temp_primitive; // 释放空间，防止内存泄漏
	
	int x1 = begin_point.x(), x2 = end_point.x();
	int y1 = begin_point.y(), y2 = end_point.y();

	temp_primitive = new StraightLine(x1, y1, x2, y2, now_primitive_num, pen, algorithm);
	return;
}



