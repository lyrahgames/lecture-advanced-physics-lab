#ifndef __GRID_H__
#define __GRID_H__

#include "vec.h"


template <class T>
class Grid2{
	public:
		// constructors
		Grid2(): _size(vec2u(2,2)), _min(vec2<T>(0,0)), _max(vec2<T>(1,1)), _scale(vec2<T>(1,1)), inv_scale(vec2<T>(1,1)) {}
		Grid2(vec2<T> grid_min, vec2<T> grid_max, vec2u grid_size): Grid2() {
			setSize(grid_size);
			setArea(grid_min, grid_max);
		}


		// set grid size in x, y direction - minimum is 2
		void setSize(const vec2u &grid_size){
			_size = grid_size; 
			_size.setmaxvec(vec2u(2,2));
			calcScale();
		}

		// set grid area
		void setArea(const vec2<T> &grid_min, const vec2<T> &grid_max){
			const vec2<T> tmp_max = maxvec(grid_max, grid_min);
			const vec2<T> tmp_min = minvec(grid_max, grid_min);
			const vec2<T> tmp = tmp_max - tmp_min;

			if (tmp.x == 0 || tmp.y == 0)
				return;

			_max = tmp_max;
			_min = tmp_min;
			calcScale();
		}


		// get grid dimension (size)
		vec2u size() const { return _size; }
		// get count of grid points
		unsigned int count() const { return _size.prod(); }

		// get parameters for grid area on plane
		vec2<T> min() const { return _min; }
		vec2<T> max() const { return _max; }
		// get diameter vector of used area
		vec2<T> diam() const { return _max-_min; }

		// get distance between two grid points
		vec2<T> scale() const { return _scale; }
		// get inverse scale
		vec2<T> invScale() const { return inv_scale; }


		// get position in plane to given grid point
		vec2<T> pos(const vec2u &idx_vec) const { return _min + comp(_scale, vec2<T>(idx_vec.x, idx_vec.y)); }
		vec2<T> pos(unsigned int x, unsigned int y) const { return pos(vec2u(x,y)); }
		vec2<T> pos(const vec2<T> &con_idx_vec) const { return _min + comp(_scale, con_idx_vec); }

		// get continuous index of a (near) grid point to given position in plane (no rounding)
		vec2<T> conIdx(const vec2<T> &pos_vec) const { return comp(pos_vec - _min, inv_scale); }
		vec2<T> idx(const vec2<T> &pos_vec) const { return conIdx(pos_vec); }

		// get approximated grid point to given position in plane (normal rounding)
		vec2u rIdx(const vec2<T> &pos_vec) const { const vec2<T> tmp = conIdx(pos_vec); return vec2u(tmp.x, tmp.y); }


	private:
		// grid dimensions
		vec2u _size;
		// position and scale
		vec2<T> _min;
		vec2<T> _max;

		// temporary vector for distance between grid points
		vec2<T> _scale;
		vec2<T> inv_scale;



		// calculate temporary scale parameter
		void calcScale(){
			const vec2u tmp = _size - vec2u(1,1);
			_scale = cdiv(_max-_min, vec2<T>((T)tmp.x, (T)tmp.y) );
			inv_scale = _scale.inv();
		}
};

typedef Grid2<float> Grid2f;
typedef Grid2<double> Grid2d;


#endif // __GRID_H__