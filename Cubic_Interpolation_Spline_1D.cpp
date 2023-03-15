#include <iostream>
#include "Cubic_Interpolation_Spline_1D.h"

namespace Com_Methods
{
	//обновить сплайн
	void Cubic_Interpolation_Spline_1D::Update_Spline(const std::vector<Point> &Points, 
		                                              const std::vector<double> &F_Value)
	{
		//обновление списка точек сплайна
		this->Points.clear();
		for (auto & elem : Points) this->Points.push_back(elem);

		//число отрезков разбиени€
		int Num_Segment = Points.size() - 1;

		//длина текущего отрезка и следующего
		double h_current, h_next;

		//изменение размеров векторов коэффициентов
		a.resize(Num_Segment);
		b.resize(Num_Segment);
		c.resize(Num_Segment);
		d.resize(Num_Segment);

		//вектор правой части —Ћј”
		std::vector<double> f(Num_Segment - 1);

		//вычисление коэффициентов
		for (int i = 0; i < Num_Segment - 1; i++)
		{
			//длина текущего и следующего отрезков
			h_current = Points[i + 1].x() - Points[i].x();
			h_next    = Points[i + 2].x() - Points[i + 1].x();

			//формируем диагональ
			b[i] = 2 * (h_current + h_next);
			//формируем нижнюю диагональ
			a[i + 1] = h_current;
			//формируем верхнюю диагональ
			d[i] = h_next;
			//права€ часть
			f[i] = 3.0 * ((F_Value[i + 2] - F_Value[i + 1]) / h_next - (F_Value[i + 1] - F_Value[i]) / h_current);
		}
		
		//метод прогонки: пр€мой ход
		for (int j = 1; j < Num_Segment - 1; j++)
		{
			b[j] -= a[j] / b[j - 1] * d[j - 1]; //диагональ
			f[j] -= a[j] / b[j - 1] * f[j - 1]; //права€ часть
		}

		//метод прогонки: обратный ход
		c[Num_Segment - 1] = f[Num_Segment - 2] / b[Num_Segment - 2];
		for (int j = Num_Segment - 2; j > 0; j--)
		{
			c[j] = (f[j - 1] - c[j + 1] * d[j - 1]) / b[j - 1];
		}

		//добавл€ем краевые услови€ нулевой кривизны
		c[0] = 0.0;

		for (int i = 0; i < Num_Segment - 1; i++)
		{
			h_current = Points[i + 1].x() - Points[i].x();
			a[i] = F_Value[i];
			b[i] = (F_Value[i + 1] - F_Value[i]) / h_current - (c[i + 1] + 2.0 * c[i]) * h_current / 3.0;
			d[i] = (c[i + 1] - c[i]) / h_current / 3.0;
		}

		//на последнем сегменте
		h_current = Points[Num_Segment].x() - Points[Num_Segment - 1].x();
		a[Num_Segment - 1] = F_Value[Num_Segment - 1];
		b[Num_Segment - 1] = (F_Value[Num_Segment] - F_Value[Num_Segment - 1]) / h_current - 2.0 * c[Num_Segment - 1] * h_current / 3.0;
		d[Num_Segment - 1] = -c[Num_Segment - 1] / h_current / 3.0;
	}

	//вычислить значение сплайна в точке P
	void Cubic_Interpolation_Spline_1D::Get_Value(const Point &P, std::vector<double>& Result)const
	{
		//машинный ноль
		double eps = 1e-7;
		//число отрезков
		int Num_Segment = Points.size() - 1;
		//поиск отрезка, которому принадлежит точка
		for (int i = 0; i < Num_Segment; i++)
		{
			if (P.x() > Points[i].x() && P.x() < Points[i + 1].x() ||
				fabs(P.x() - Points[i].x()) < eps ||
				fabs(P.x() - Points[i + 1].x()) < eps)
			{
				double diff = (P.x() - Points[i].x());
				Result.push_back(a[i] + b[i] * diff + c[i] * pow(diff, 2) + d[i] * pow(diff, 3));
				Result.push_back(b[i] + 2.0 * c[i] * diff + 3.0 * d[i] * pow(diff, 2));
				Result.push_back(2.0 * c[i] + 6.0 * d[i] * diff);
				return;
			}
		}
		throw std::exception("The point is not found in the segments...");
	}
}

