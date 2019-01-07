#include <iostream>
#include <stdlib.h>
using namespace std;

#include <QApplication>

#include "vec-field.h"
#include "nsg.h"
#include "render-w.h"


int main(int argc, char *argv[]){
	// srand(time(NULL));

	const vec2f min(0.0f, 0.0f);
	const vec2f max(1.0f, 1.0f);
	const vec2u size(1<<6, 1<<6);
	const Grid2f grid(min, max, size);

	VecField2f v(grid);
	ScalarField2f s(grid);

	for (unsigned int i = 0; i < v.grid().size().x; i++){
		for (unsigned int j = 0; j < v.grid().size().y; j++){
			vec2f offset;
			// offset = vec2f(0.5f,0.5f);

			const vec2f pos = v.grid().pos(i,j) - offset;

			// v(i,j) = vec2f(pos.x, sqrt(pos.x) * sin(3*M_PI*pos.x) * sin(M_PI*pos.y));
			// v(i,j) = vec2f(pos.x*pos.x + pos.y*pos.y, pos.x*pos.x - pos.y*pos.y);
			s(i,j) = sqrt(pos.x) * sin(3*M_PI*pos.x) * sin(M_PI*pos.y);
			// s(i,j) = cos(10.0f * pos.x) * cos(10.0f * pos.y);
			// v(i,j) = vec2f(-pos.x*pos.y, pos.x*pos.x + pos.y*pos.y);
			// v(i,j) = vec2f(-pos.y, pos.x);
		}
	}


	NSG nsg(grid, vec2f(), 100);

	// 
	for (unsigned j = 0; j < grid.size().x; j++){
		nsg.u(j,0) = 1.0f;
		nsg.u(j,grid.size().y-1) = 0.0f;
	}
	for (unsigned j = 0; j < grid.size().y; j++){
		nsg.v(0,j) = 0.0f;
		nsg.v(grid.size().x-1, j) = 0.0f;
	}

	for (unsigned int i = 0; i < grid.size().x; i++){
		for (unsigned int j = 0; j < grid.size().y; j++){
			nsg.p(i,j) = 0.0f;
		}
	}

	// float t = 0.0f;

	// for (int i = 0; i < 1000; ++i){
	// 	nsg.calc();
	// 	cout << (t+=nsg.dt) << "s" << endl;
	// }

	QApplication app(argc, argv);

	RenderW *render = new RenderW;
	render->resize(max.x * 600, max.y * 600);
	render->setVecField(&(nsg.velocity));
	// render->setVecField(&v);
	render->nsg = &nsg;
	render->s = &(nsg.p);
	render->show();

	app.exec();
	
	delete render;

	return 0;
}