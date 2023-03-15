#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "Point.h"
#include "math.h"
#include "Cubic_Interpolation_Spline_1D.h"

std::vector<Com_Methods::Point> Generate_Mesh(double a, double b, int Num_Segment, int r, std::vector<double>& F_value) {
	std::vector<Com_Methods::Point> Mesh;
	double h = 0;
	double Mesh_Node = a;

	if (r == 1) {
		h = (b - a) / Num_Segment;
	}
	else if (r > 1) {
		h = ((r - 1) * (b - a)) / (pow(r, Num_Segment) - 1);
	}
 	for (int i = 0; i < Num_Segment + 1; i++) {
			Mesh.push_back(Com_Methods::Point(Mesh_Node, 0, 0));
			F_value.push_back(sin(Mesh_Node) - cos(Mesh_Node));
			Mesh_Node += h * r;
	}
	return Mesh;
}

int main() {
	std::vector<double> F_value;
	std::vector<Com_Methods::Point> Points = Generate_Mesh(0 ,(M_PI / 2), 16, 1, F_value);
	Com_Methods::Cubic_Interpolation_Spline_1D Spline1;
	Spline1.Update_Spline(Points, F_value);
	std::vector<double> Result;
	
	for (double i = 0; i <= M_PI / 2; i = i + M_PI / 20){
		Spline1.Get_Value(Com_Methods::Point(i, 0, 0), Result);
		std::cout << i << "\t";
		for (auto j = 0; j < Result.size(); ++j) {
			std::cout <<"\t" << Result[j] /*<< "\t"*/;
		}
		std::cout << std::endl;
		Result.clear();
	}
}