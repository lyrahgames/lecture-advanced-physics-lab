#ifndef __NSG_H__
#define __NSG_H__

#include "vec.h"
#include "grid.h"
#include "scalar-field.h"
#include "vec-field.h"
#include "utils.h"

#include <iostream>
#include <algorithm>


class NSG{
	public:
		NSG(const Grid2f &grid_def, const vec2f &g_vec, float re_number):
		grid(grid_def), p(grid_def), u(grid_def), v(grid_def), velocity(grid_def),
		F(grid_def), G(grid_def), RHS(grid_def), res(grid_def),
		g(g_vec), Re(re_number), Re_inv(1.0f/re_number), gamma(0.5f), omega2(0.5f), omega1(0.5f), t(0.0f), step(0) {
			epsilon = 0.001;
			dt_tmp = 0.5f * Re * (1.0f / grid.invScale().sqmag());
		}

		// initialize, set dirichlet boundaries
		void init(){}

		void calc(){
			// for (unsigned j = 0; j < grid.size().x; j++){
			// 	u(j,0) = 0.99f * cos(3.0f*t);
			// 	// nsg.u(j,grid.size().y-1) = 0.0f;
			// }

			const float u_max = u.maxMag();
			const float v_max = v.maxMag();

			dt = fmin(grid.scale().x / u_max, grid.scale().y / v_max );
			dt = 0.5 * fmin(dt, dt_tmp);
			inv_dt = 1.0f / dt;

			t += dt;
			step += 1;

			// calculate F,G
			for (unsigned int i = 1; i < grid.size().x - 1; i++){
				for (unsigned int j = 1; j < grid.size().y - 1; j++){
					const float F_tmp1 = Re_inv * ( (u(i+1,j) - 2*u(i,j) + u(i-1,j))/(grid.scale().x * grid.scale().x) + (u(i,j+1) - 2*u(i,j) + u(i,j-1))/(grid.scale().y * grid.scale().y) );
					const float F_tmp2 = grid.invScale().x * ( sq( 0.5f * (u(i,j) + u(i+1,j)) ) - sq( 0.5f * (u(i-1,j) + u(i,j)) ) )
										+ gamma * grid.invScale().x * 0.25f * ( fabs(u(i,j) + u(i+1,j)) * (u(i,j) - u(i+1,j))  -  fabs(u(i-1,j) + u(i,j)) * (u(i-1,j) - u(i,j)) );
					const float F_tmp3 = grid.invScale().y * 0.25f * ( (v(i,j) + v(i+1,j))*(u(i,j) + u(i,j+1)) - (v(i,j-1) + v(i+1,j-1))*(u(i,j-1) + u(i,j)) )
										+ gamma * grid.invScale().y * 0.25f * ( fabs(v(i,j) + v(i+1,j))*(u(i,j) - u(i,j+1)) - fabs(v(i,j-1) + v(i+1,j-1))*(u(i,j-1) - u(i,j)) );
					F(i,j) = u(i,j) + dt * ( F_tmp1 - F_tmp2 - F_tmp3 + g.x );

					const float G_tmp1 = Re_inv * ( (v(i+1,j) - 2*v(i,j) + v(i-1,j))/(grid.scale().x * grid.scale().x) + (v(i,j+1) - 2*v(i,j) + v(i,j-1))/(grid.scale().y * grid.scale().y) );
					const float G_tmp2 = grid.invScale().y * ( sq( 0.5f * (v(i,j) + v(i,j+1)) ) - sq( 0.5f * (v(i,j-1) + v(i,j)) ) )
										+ gamma * grid.invScale().y * 0.25f * ( fabs(v(i,j) + v(i,j+1)) * (v(i,j) - v(i,j+1))  -  fabs(v(i,j-1) + v(i,j)) * (v(i,j-1) - v(i,j)) );
					const float G_tmp3 = grid.invScale().x * 0.25f * ( (v(i,j) + v(i+1,j))*(u(i,j) + u(i,j+1)) - (u(i-1,j) + u(i-1,j+1))*(v(i-1,j) + v(i,j)) )
										+ gamma * grid.invScale().x * 0.25f * ( fabs(u(i,j) + u(i,j+1))*(v(i,j) - v(i+1,j)) - fabs(u(i-1,j) + u(i-1,j+1))*(v(i-1,j) - v(i,j)) );
					G(i,j) = v(i,j) + dt * ( G_tmp1 - G_tmp2 - G_tmp3 + g.y );

					RHS(i,j) = inv_dt * ( grid.invScale().x * (F(i,j) - F(i-1,j)) + grid.invScale().y * (G(i,j) - G(i,j-1)) );
				}
			}

			float r;
			int step = 0;

			const float p_max = p.maxMag();

			do{
				for (unsigned int i = 1; i < grid.size().x - 1; i++){
					p(i,0) = p(i,1);
					p(i, grid.size().y - 1) = p(i, grid.size().y - 2);
				}

				for (unsigned int j = 1; j < grid.size().y - 1; j++){
					p(0,j) = p(1,j);
					p(grid.size().x - 1, j) = p(grid.size().y - 2, j);
				}

				for (unsigned int i = 1; i < grid.size().x - 1; i++){
					for (unsigned int j = 1; j < grid.size().y - 1; j++){
						p(i,j) = omega1 * p(i,j) + 0.5f * omega2 * (1.0f / grid.invScale().sqmag()) * ( sq(grid.invScale().x) * (p(i+1,j) + p(i-1,j)) + sq(grid.invScale().y) * (p(i,j+1) + p(i,j-1)) - RHS(i,j));

						
					}
				}

				r = 0.0f;
				for (unsigned int i = 1; i < grid.size().x - 1; i++){
					for (unsigned int j = 1; j < grid.size().y - 1; j++){
						res(i,j) = sq(grid.invScale().x) * ( p(i+1,j) - 2*p(i,j) + p(i-1,j) ) + sq(grid.invScale().y) * ( p(i,j+1) - 2*p(i,j) + p(i,j-1) ) - RHS(i,j);
						const float tmp = fabs(res(i,j));

						if (tmp > r)
							r = tmp;
					}
				}

				step += 1;

			}while(r >= epsilon*p_max && step < 100);

			for (unsigned int i = 1; i < grid.size().x - 1; i++){
				for (unsigned int j = 1; j < grid.size().y - 1; j++){
					u(i,j) = F(i,j) - dt * grid.invScale().x * ( p(i+1,j) - p(i,j) );
					v(i,j) = G(i,j) - dt * grid.invScale().y * ( p(i,j+1) - p(i,j) );

					velocity(i,j) = vec2f(u(i,j),v(i,j));
				}
			}
		}

	// private:
	public:
		ScalarField2f p;
		ScalarField2f u, v;
		VecField2f velocity;
		Grid2f grid;
		vec2f g;
		float Re;
		float Re_inv;
		float gamma;
		float epsilon;
		float omega1, omega2;
		float t;
		unsigned int step;

		// temporary
		// ScalarField2f tmp_u, tmp_v, tmp_p;
		ScalarField2f F,G,RHS, res;
		float dt, inv_dt, dt_tmp;
};


#endif // __NSG_H__