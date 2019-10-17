﻿#ifndef DRAWINGAERA_H
#define DRAWINGAERA_H

#include <QWidget>
#include <QImage>

class DrawingArea : public QWidget
{
	Q_OBJECT
private:
	QImage paper; // 用于存储画布，作为当前显示的画面存储
	
public:
    DrawingArea(QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* event) override; // 绘图事件函数重写
	void mouseMoveEvent(QMouseEvent* event) override; // 鼠标移动函数重写

signals:
	void newLocation(const QString& location, int timeout = 0);
};

#endif // DRAWINGAERA_H
