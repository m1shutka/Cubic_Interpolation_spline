#pragma once
#ifndef spline_h
#define spline_h

#include <vector>
#include "Point.h"

namespace Com_Methods
{
	//����������� ����� �������
	class Spline
	{
	public:
		//�������� ������
		virtual void Update_Spline(const std::vector<Point> &Points, const std::vector<double> &F_Value) = 0;
		//��������� �������� ������� � ����� P
		virtual void Get_Value(const Point &P, std::vector<double>& Res)const = 0;
	};
}

#endif