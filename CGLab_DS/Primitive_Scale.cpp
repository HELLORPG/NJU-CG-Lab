#include "Primitive.h"

int Primitive::scale_t(int t, int t0, double s)
{
	// ����������У�t��Ϊһ���������ȿ��Գ���x��Ҳ���Գ���y��������t��Ϊһ��ͨ�õĲ���
	double t_double(static_cast<double>(t)), t0_double(static_cast<double>(t0)), t_ret(0.0);
	t_ret = t_double * s + t0_double * (1.0 - s);
	return t_ret;
}


void StraightLine::scale(const int x, const int y, const double s)
{
	begin_x = Primitive::scale_t(begin_x, x, s);
	begin_y = Primitive::scale_t(begin_y, y, s);
	end_x = Primitive::scale_t(end_x, x, s);
	end_y = Primitive::scale_t(end_y, y, s);
	return;
}

void Ellipse::scale(const int x, const int y, const double s)
{
	/*
	 * ��Բ�������㷨û����PPT���ᵽ
	 * ����ֻ��д���Լ����뷨��
	 * ��������ֱ�ߵ�����ԭ����е�ı任��ͬʱ�����任rx��ry
	 */
	x0 = Primitive::scale_t(x0, x, s);
	y0 = Primitive::scale_t(y0, y, s);
	rx = static_cast<int>(static_cast<double>(rx) * s);
	ry = static_cast<int>(static_cast<double>(ry) * s);
	return;
}

void Polygon::scale(const int x, const int y, const double s)
{
	for (auto &vertex : vertices)
	{
		vertex.x = Primitive::scale_t(vertex.x, x, s);
		vertex.y = Primitive::scale_t(vertex.y, y, s);
	}
	return;
}


