#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string.h>

using namespace std;

int main(int argc, char const *argv[])
{
	float int_min = 200.0f;
	float int_max = 400.0f;

	if (argc < 2){
		cout << "argc < 2" << endl;
		return -1;
	}

	if (argc >= 3){
		int_min = strtof(argv[2], NULL);

		if (argc >= 4){
			int_max = strtof(argv[3], NULL);
		}
	}

	FILE *file;

	cout << argv[1] << endl;

	if ((file = fopen(argv[1], "r")) == NULL){
		cout << "fopen failed" << endl;
		return -1;
	}

	float x,y;
	float x_min, y_min = INFINITY;
	float x_max, y_max = -INFINITY;

	while (fscanf(file, "%f %f", &x, &y) != EOF){
		x *= -1.624;
		if ((x >= int_min) && (x <= int_max)){
			if (y < y_min){
				x_min = x;
				y_min = y;
			}

			if (y > y_max){
				x_max = x;
				y_max = y;
			}
		}
	}

	cout << "x_min = " << x_min << endl;
	cout << "y_min = " << y_min << endl;
	cout << "x_max = " << x_max << endl;
	cout << "y_max = " << y_max << endl;
	cout << "y_max - y_min = " << y_max - y_min << endl;

	return 0;
}