#ifndef DEFINE_H
#define DEFINE_H

//#define PRINT_MOUSE_LOCATION
#define PRINT_MOUSE_EVENT
#define PRINT_PEN
#define PRINT_DRAW
#define PRINT_ACTION // ������壬������������action����
#define PRINT_FILE_OP // ������壬���������ļ���д�Ĺ���
//#define PRINT_PRIMITIVE


#define PI 3.141592653

#define BEZIER_DELTA 0.005
#define B_SPLINE_DELTA 0.001
#define B_SPLINE_K 3 // ��������B��������


enum class DrawMode
{
	None, 
	Nature, 
	StraightLine,
	Circle,
	Ellipse,
	Polygon,
	Curve_Bezier,
	Curve_B_spline
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
	All,
	Transform
};

enum class SetToolBarEnableMode
{
	DrawMode,
	All,
	Primitive,
	Transform
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
MyPoint_double operator*(const MyPoint left, const MyPoint_double right);
MyPoint_double operator*(const MyPoint left, const double right);
bool operator==(const MyPoint &left, const MyPoint &right);
bool operator!=(const MyPoint& left, const MyPoint& right);
bool operator==(const MyPoint_double& left, const MyPoint& right);
bool operator!=(const MyPoint_double& left, const MyPoint& right);
#endif // DEFINE_H