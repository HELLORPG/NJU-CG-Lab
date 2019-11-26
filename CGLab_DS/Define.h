#ifndef DEFINE_H
#define DEFINE_H

//#define PRINT_MOUSE_LOCATION
#define PRINT_MOUSE_EVENT
#define PRINT_PEN
#define PRINT_DRAW
#define PRINT_ACTION // ������壬������������action����
#define PRINT_FILE_OP // ������壬���������ļ���д�Ĺ���


#define PI 3.141592653


enum class DrawMode
{
	None, 
	Nature, 
	StraightLine,
	Circle,
	Ellipse
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
	Polygon
};


enum class StraightLineAlgorithm
{
	DDA,
	Bresenham,
	None
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


#endif // DEFINE_H