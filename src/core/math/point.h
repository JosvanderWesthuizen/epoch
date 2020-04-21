#ifndef POINT_H_
#define POINT_H_

#include "core/ehm/result.h"

// epoch point
// epoch/src/core/math/point.h

#include "matrix.h"

template <typename TValue, int N>
class point :
	public matrix<TValue, N, 1>
{
public:
	point() = default;
	virtual ~point() override = default;

	point(std::initializer_list<TValue> values) {
		int index = 0;
		for (auto val : values) {
			data[index++] = val;
		}
	}

	inline TValue& x() { return this->data[0]; }
	inline TValue& y() { return this->data[1]; }
	inline TValue& z() { return this->data[2]; }
	inline TValue& w() { return this->data[3]; }

	inline TValue& x(const TValue &val) { return this->data[0] = val; }
	inline TValue& y(const TValue &val) { return this->data[1] = val; }
	inline TValue& z(const TValue &val) { return this->data[2] = val; }
	inline TValue& w(const TValue &val) { return this->data[3] = val; }

};

//// Not sure if this will work
//template <typename TValue>
//point<TValue, 4>::point(TValue x, TValue y, TValue z, TValue w) {
//	data[0] = x;
//	data[1] = y;
//	data[2] = z;
//	data[3] = w;
//}



#endif // ! POINT_H_