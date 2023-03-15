#pragma once
#ifndef Cubic_Interpolation_Spline_1D_h
#define Cubic_Interpolation_Spline_1D_h

#include "Spline.h"

namespace Com_Methods
{
	//кубический интерпол€ционный сплайн
	class Cubic_Interpolation_Spline_1D : public Spline
	{
	private:
		//точки сетки
		std::vector<Point> Points;
		//коэффициенты сплайна
		std::vector<double> a, b, c, d;
	public:
		//обновить сплайн
		void Update_Spline(const std::vector<Point> &Points, const std::vector<double> &F_Value) override;
		//вычислить значение сплайна в точке P
		void Get_Value(const Point &P, std::vector<double>& Res)const override;
	};
}

#endif
