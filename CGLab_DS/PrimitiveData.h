#ifndef PRIMITIVEDATA_H
#define PRIMITIVEDATA_H

#include <QPen>

class PrimitiveData
{
protected:
	QPen pen_in_use; // ������ǰͼԪʹ�õĻ�����ʲô

public:
    PrimitiveData(QPen pen);
};

#endif // PRIMITIVEDATA_H
