#ifndef __RENDER_W_H__
#define __RENDER_W_H__

// #include <vector>
#include <stdlib.h>

#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>

#include "grid.h"
#include "vec-field.h"
#include "scalar-field.h"
#include "nsg.h"


class RenderW : public QWidget{
	Q_OBJECT

	public:
		// constants
		static const float STEP_SIZE_PAR = 1.01f;



		// constructors
		RenderW(QWidget *parent = 0): vec_field(0), rand_pos(0), rand_pos_size(300) {
			timer = new QTimer(this);
			connect(timer, SIGNAL(timeout()), this, SLOT(update()));
			timer->start(1);

			running = true;
		}

		// destructor
		~RenderW(){
			delete timer;
			delete[] rand_pos;
		}


		// get pointer to current vector field
		VecField2f* field() { return vec_field; }

		// get count of random positions
		unsigned int randPosSize() { return rand_pos_size; }



	public slots:
		// set vector field currently showing
		void setVecField(VecField2f* field){
			if (field == 0) 
				return;
			
			vec_field = field;
			pixel_grid.setArea(vec_field->grid().min(), vec_field->grid().max());
			initRandPos();
			step_size = STEP_SIZE_PAR * vec_field->grid().scale().mag();
		}

		// set count of random positions
		void setRandPosSize(unsigned int count) { rand_pos_size = count; initRandPos(); }



	protected:
		void paintEvent(QPaintEvent *event){
			if (vec_field == 0)
				return;

			if (running)
				nsg->calc();

			printf("%u: %f\n", nsg->step, nsg->t);

			QPainter painter(this);
			painter.setRenderHints(QPainter::Antialiasing, true);
			
			// QImage map(width(), height(), QImage::Format_RGB32);
			// const float inv_max_mag = 1.0f / (s->maxMag() + 0.001);

			// for (unsigned int i = 0; i < width(); i++){
			// 	for (unsigned int j = 0; j < height(); j++){
			// 		const vec2f pos = pixel_grid.pos(i,j);
			// 		const float col_par = 0.5f * ((*s)(pos) * inv_max_mag + 1.0f);

			// 		const QRgb value = qRgb(255.0f * col_par, 255.0f * (1.0f - col_par), 255.0f * (1.0f - col_par));
			// 		map.setPixel(i, j, value);
			// 	}
			// }

			// painter.drawImage(QRect(0, 0, width(), height()), map, QRect(0, 0, width(), height()));


			for (unsigned int i = 0; i < rand_pos_size; i++){
				// random position in plane
				vec2f pos = rand_pos[i];
				
				// construct vector path
				QPainterPath path;
				vec2f pixel_pos = pixel_grid.idx(pos);
				path.moveTo(pixel_pos.x, pixel_pos.y);

				for (int t = 0; t < 50; t++){
					pos += step_size * (*vec_field)(pos);
					
					if ( (pos.x <= vec_field->grid().min().x) || (pos.x >= vec_field->grid().max().x) || (pos.y <= vec_field->grid().min().y) || (pos.y >= vec_field->grid().max().y) )
						break;

					pixel_pos = pixel_grid.idx(pos);
					path.lineTo(pixel_pos.x, pixel_pos.y);
				}

				painter.setBrush(Qt::NoBrush);
				painter.drawPath(path);

				// draw arrow at the end of path
				QPainterPath arrow_path;
				vec2f dir = (*vec_field)(pos);
				dir.setnorm();
				const float par = 2.5f;

				arrow_path.moveTo(pixel_pos.x, pixel_pos.y);
				arrow_path.lineTo(pixel_pos.x - 1.5f*par*dir.x - 0.5f*par*dir.y, pixel_pos.y - 1.5f*par*dir.y + 0.5f*par*dir.x);
				arrow_path.lineTo(pixel_pos.x - 1.5f*par*dir.x + 0.5f*par*dir.y, pixel_pos.y - 1.5f*par*dir.y - 0.5f*par*dir.x);
				arrow_path.closeSubpath();

				painter.setBrush(Qt::black);
				painter.drawPath(arrow_path);
			}

			painter.end();
		}

		void resizeEvent(QResizeEvent *event) { pixel_grid.setSize(vec2u(width(), height())); }

		void keyPressEvent(QKeyEvent *event){
			if (event->key() == Qt::Key_Space)
				running = !running;
		}



	public:
		// grid of pixels over plane
		Grid2f pixel_grid;
		// vector field
		VecField2f *vec_field;
		// random position vector
		vec2f *rand_pos;
		unsigned int rand_pos_size;
		ScalarField2f *s;

		// temporary
		float step_size;


	public:
		NSG *nsg;
		QTimer *timer;
		bool running;


	private:
		// initializes random positions for vector arrows
		void initRandPos(){
			if (vec_field == 0)
				return;

			if (rand_pos != 0)
				delete[] rand_pos;

			rand_pos = new vec2f[rand_pos_size];

			for (unsigned int i = 0; i < rand_pos_size; i++){
				const float rx = (float)rand() / (float)RAND_MAX;
				const float ry = (float)rand() / (float)RAND_MAX;
				rand_pos[i] = comp(vec2f(rx,ry), vec_field->grid().diam()) + vec_field->grid().min();
			}
		}
};


#endif // __RENDER_W_H__