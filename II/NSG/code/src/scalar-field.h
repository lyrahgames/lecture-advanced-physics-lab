#ifndef __SCALAR_FIELD_H__
#define __SCALAR_FIELD_H__

#include "grid.h"


template <class T>
class ScalarField2{
public:
	// constructors
	ScalarField2(const Grid2<T> &field_grid): _grid(field_grid), _field(0) { init(); }
	// destructor
	~ScalarField2() { delete[] _field; }


	// get reference to vector at given grid point
	T& operator ()(const vec2u &grid_point) { return _field[_grid.size().y * grid_point.x + grid_point.y]; }
	T& operator ()(unsigned int x, unsigned int y) { return (*this)(vec2u(x,y)); }
	const T& operator ()(const vec2u &grid_point) const { return _field[_grid.size().y * grid_point.x + grid_point.y]; }
	const T& operator ()(unsigned int x, unsigned int y) const { return (*this)(vec2u(x,y)); }

	// get reference to vector element for given linear coordinate
	T& operator [](unsigned int idx) { return _field[idx]; }
	const T& operator[](unsigned int idx) const { return _field[idx]; }
	
	// get constant reference to grid
	const Grid2<T>& grid() const { return _grid; }
	

	// set current grid
	void setGrid(const Grid2<T>& new_grid) { grid = new_grid; init(); }

	// set field values
	void set(const vec2u &grid_point, T value) { (*this)(grid_point) = value; }
	void set(unsigned int x, unsigned int y, T value) { (*this)(x,y) = value; }


	// get linear interpolated value of field for given position in plane
	T operator ()(const vec2<T> &pos_vec) const{
		const vec2<T> idx = _grid.idx(pos_vec);
		const T i = floor(idx.x);
		const T j = floor(idx.y);

		if (idx.x <= 0 || idx.x >= _grid.size().x - 1 || idx.y <= 0 || idx.y >= _grid.size().y - 1)
			return (*this)(idx.x, idx.y);

		const T tmp_x1 = idx.x - i;
		const T tmp_x2 = 1 - tmp_x1;
		const T tmp_y1 = idx.y - j;
		const T tmp_y2 = 1 - tmp_y1;

		return tmp_x2 * tmp_y2 * (*this)(i,j) 
			+ tmp_x1 * tmp_y2 * (*this)(i+1,j) 
			+ tmp_x2 * tmp_y1 * (*this)(i,j+1) 
			+ tmp_x1 * tmp_y1 * (*this)(i+1,j+1);
	}

	// get maximal magnitude of field values
	T maxMag() const{
		T max_sqmag = 0;

		for (unsigned int i = 0; i < _grid.count(); i++){
			const T tmp = fabs(_field[i]);

			if (tmp > max_sqmag)
				max_sqmag = tmp;
		}

		return max_sqmag;
	}


private:
	// array with values for field
	T *_field;
	// grid of field
	Grid2<T> _grid;


	// initializing array of vector
	void init(){
		if (_field != 0)
			delete[] _field;

		_field = new T[_grid.count()];

		for (unsigned int i = 0; i < _grid.count(); i++)
			_field[i] = 0;
	}
};

typedef ScalarField2<float> ScalarField2f;
typedef ScalarField2<double> ScalarField2d;


#endif // __SCALAR_FIELD_H__