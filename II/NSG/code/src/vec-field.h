#ifndef __VEC_FIELD_H__
#define __VEC_FIELD_H__

#include "vec.h"
#include "grid.h"


template <class T>
class VecField2{
	public:
		// constructors
		VecField2(const Grid2<T> &field_grid): _grid(field_grid), _field(0), _offset(vec2<T>()) { init(); }
		// destructor
		~VecField2() { delete[] _field; }


		// get reference to vector at given grid point
		vec2<T>& operator ()(const vec2u &grid_point) { return _field[_grid.size().y * grid_point.x + grid_point.y]; }
		vec2<T>& operator ()(unsigned int x, unsigned int y) { return (*this)(vec2u(x,y)); }
		const vec2<T>& operator ()(const vec2u &grid_point) const { return _field[_grid.size().y * grid_point.x + grid_point.y]; }
		const vec2<T>& operator ()(unsigned int x, unsigned int y) const { return (*this)(vec2u(x,y)); }
		
		// get reference to vector element for given linear coordinate
		vec2<T>& operator [](unsigned int idx) { return _field[idx]; }
		const vec2<T>& operator[](unsigned int idx) const { return _field[idx]; }

		// get constant reference to grid
		const Grid2<T>& grid() const { return _grid; }
		

		// set current grid
		void setGrid(const Grid2<T>& new_grid) { grid = new_grid; init(); }

		// set offset
		void setOffset(const vec2<T> &offset_vec) { _offset = offset_vec; }

		// set field values
		void set(const vec2u &grid_point, const vec2<T> &value) { (*this)(grid_point) = value; }
		void set(unsigned int x, unsigned int y, const vec2<T> &value) { (*this)(x,y) = value; }


		// get offset
		vec2<T> offset() const { return _offset; }

		// get linear interpolated value of field for given position in plane
		vec2<T> operator ()(const vec2<T> &pos_vec) const{
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
				const T tmp = _field[i].sqmag();

				if (tmp > max_sqmag)
					max_sqmag = tmp;
			}

			return sqrt(max_sqmag);
		}


	private:
		// array with values for field
		vec2<T> *_field;
		// grid of field
		Grid2<T> _grid;
		// offset in x and y direction for staggered grids
		vec2<T> _offset;


		// initializing array of vector
		void init(){
			if (_field != 0)
				delete[] _field;

			_field = new vec2<T>[_grid.count()];
		}
};

typedef VecField2<float> VecField2f;
typedef VecField2<double> VecField2d;


#endif // __VEC_FIELD_H__