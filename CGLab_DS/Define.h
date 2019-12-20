#ifndef DEFINE_H
#define DEFINE_H

//#define PRINT_MOUSE_LOCATION
#define PRINT_MOUSE_EVENT
#define PRINT_PEN
#define PRINT_DRAW
#define PRINT_ACTION // ������壬������������action����
#define PRINT_FILE_OP // ������壬���������ļ���д�Ĺ���


#define PI 3.141592653

#define BEZIER_DELTA 0.001


enum class DrawMode
{
	None, 
	Nature, 
	StraightLine,
	Circle,
	Ellipse,
	Polygon,
	Curve_Bezier
};

enum class PrimitiveType
{
	/*
	 * ���ڶ���洢��ͼԪ������
	 */
	None,
	Nature,
	StraightLine,
	Ellipse,
	Polygon,
	Curve
};


enum class StraightLineAlgorithm
{
	DDA,
	Bresenham,
	None
};

enum class CurveAlgorithm
{
	Bezier,
	B_spline
};


enum class ClearToolBarCheckedMode // �����˶������������ѡ��״̬��ģʽ
{
	DrawMode,
	All
};


enum class ClipAlgorithm
{
	Cohen_Sutherland,
	Liang_Barsky
};


struct MyPoint
{
	int x;
	int y;
};

struct MyPoint_double
{
	double x;
	double y;
};

MyPoint_double operator+(const MyPoint_double left, const MyPoint_double right); // ����������������������
MyPoint_double operator*(const MyPoint_double left, const MyPoint_double right); // 
MyPoint_double operator*(const double left, const MyPoint_double right);

#endif // DEFINE_H