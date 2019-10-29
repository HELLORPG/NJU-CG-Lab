#ifndef DEFINE_H
#define DEFINE_H

//#define PRINT_MOUSE_LOCATION
#define PRINT_MOUSE_EVENT
#define PRINT_PEN
#define PRINT_DRAW
#define PRINT_ACTION // 如果定义，则调试输出所有action触发
#define PRINT_FILE_OP // 如果定义，则调试输出文件读写的过程



enum class DrawMode
{
	None, 
	Nature, 
	StraightLine
};

enum class PrimitiveType
{
	/*
	 * 用于定义存储的图元的类型
	 */
	None,
	Nature,
	StraightLine
};


enum class StraightLineAlgorithm
{
	DDA,
	Bresenham,
	None
};



struct MyPoint
{
	int x;
	int y;
};


#endif // DEFINE_H