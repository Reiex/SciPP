///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreDecl.hpp>

namespace scp
{
	namespace _scp
	{
		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr Mat<TValue, Row, Col, TRow, TCol>::Mat(TValue diagValue)
		{
			constexpr uint8_t size = Row * Col;
			std::memset(_rows, 0, size * sizeof(TValue));

			constexpr uint8_t n = std::min(Row, Col);

			for (uint8_t i = 0; i < n; ++i)
			{
				_rows[i][i] = diagValue;
			}
		}

		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr Mat<TValue, Row, Col, TRow, TCol>::Mat(const std::initializer_list<TValue>& tab)
		{
			constexpr uint8_t size = Row * Col;
			assert(size == tab.size());

			std::memcpy(_rows, tab.begin(), size * sizeof(TValue));
		}

		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr TRow& Mat<TValue, Row, Col, TRow, TCol>::operator[](uint8_t i)
		{
			assert(i < Row);
			return _rows[i];
		}

		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr const TRow& Mat<TValue, Row, Col, TRow, TCol>::operator[](uint8_t i) const
		{
			assert(i < Row);
			return _rows[i];
		}

		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr Mat<TValue, Row, Col, TRow, TCol>& Mat<TValue, Row, Col, TRow, TCol>::operator+=(const Mat<TValue, Row, Col, TRow, TCol>& mat)
		{
			for (uint8_t i = 0; i < Row; ++i)
			{
				_rows[i] += mat._rows[i];
			}

			return *this;
		}

		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr Mat<TValue, Row, Col, TRow, TCol>& Mat<TValue, Row, Col, TRow, TCol>::operator-=(const Mat<TValue, Row, Col, TRow, TCol>& mat)
		{
			for (uint8_t i = 0; i < Row; ++i)
			{
				_rows[i] -= mat._rows[i];
			}

			return *this;
		}


		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr Mat<TValue, Row, Col, TRow, TCol> operator+(const Mat<TValue, Row, Col, TRow, TCol>& a, const Mat<TValue, Row, Col, TRow, TCol>& b)
		{
			Mat<TValue, Row, Col, TRow, TCol> c(a);
			return c += b;
		}

		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr Mat<TValue, Row, Col, TRow, TCol> operator-(const Mat<TValue, Row, Col, TRow, TCol>& a, const Mat<TValue, Row, Col, TRow, TCol>& b)
		{
			Mat<TValue, Row, Col, TRow, TCol> c(a);
			return c -= b;
		}

		template<typename TValue, uint8_t RowA, uint8_t ColARowB, uint8_t ColB, typename TRowA, typename TColARowB, typename TColB>
		constexpr Mat<TValue, RowA, ColB, TRowA, TColB> operator*(const Mat<TValue, RowA, ColARowB, TRowA, TColARowB>& a, const Mat<TValue, ColARowB, ColB, TColARowB, TColB>& b)
		{
			Mat<TValue, RowA, ColB, TRowA, TColB> c(0);

			for (uint8_t i = 0; i < RowA; ++i)
			{
				for (uint8_t j = 0; j < ColB; ++j)
				{
					for (uint8_t k = 0; k < ColARowB; ++k)
					{
						c[i][j] += a[i][k] * b[k][j];
					}
				}
			}

			return c;
		}
	
		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr TRow operator*(const TRow& vec, const Mat<TValue, Row, Col, TRow, TCol>& mat)
		{
			TRow result(0);

			for (uint8_t i = 0; i < Row; ++i)
			{
				for (uint8_t j = 0; j < Col; ++j)
				{
					result[j] += vec[i] * mat[i][j];
				}
			}

			return result;
		}

		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr TCol operator*(const Mat<TValue, Row, Col, TRow, TCol>& mat, const TCol& vec)
		{
			TCol result(0);

			for (uint8_t i = 0; i < Row; ++i)
			{
				for (uint8_t j = 0; j < Col; ++j)
				{
					result[i] += vec[j] * mat[i][j];
				}
			}

			return result;
		}
	}

	template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
	constexpr _scp::Mat<TValue, Col, Row, TCol, TRow> transpose(const _scp::Mat<TValue, Row, Col, TRow, TCol>& m)
	{
		_scp::Mat<TValue, Col, Row, TCol, TRow> r;

		for (uint8_t i = 0; i < Row; ++i)
		{
			for (uint8_t j = 0; j < Col; ++j)
			{
				r[j][i] = m[i][j];
			}
		}

		return r;
	}

	template<typename TValue, uint8_t Size, typename TRow>
	constexpr TValue determinant(const _scp::Mat<TValue, Size, Size, TRow, TRow>& m)
	{
		if constexpr (Size == 2)
		{
			return m[0][0] * m[1][1] - m[0][1] * m[1][0];
		}
		else if constexpr (Size == 3)
		{
			return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
				- m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1])
				+ m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]);
		}
		else if constexpr (Size == 4)
		{
			const TValue tmp[6] = {
				m[2][2] * m[3][3] - m[2][3] * m[3][2],
				m[2][1] * m[3][3] - m[2][3] * m[3][1],
				m[2][1] * m[3][2] - m[2][2] * m[3][1],
				m[2][0] * m[3][3] - m[2][3] * m[3][0],
				m[2][0] * m[3][2] - m[2][2] * m[3][0],
				m[2][0] * m[3][1] - m[2][1] * m[3][0]
			};

			return m[0][0] * (m[1][1] * tmp[0] - m[1][2] * tmp[1] + m[1][3] * tmp[2])
				- m[0][1] * (m[1][0] * tmp[0] - m[1][2] * tmp[3] + m[1][3] * tmp[4])
				+ m[0][2] * (m[1][0] * tmp[1] - m[1][1] * tmp[3] + m[1][3] * tmp[5])
				- m[0][3] * (m[1][0] * tmp[2] - m[1][1] * tmp[4] + m[1][2] * tmp[5]);
		}
	}

	template<typename TValue, uint8_t Size, typename TRow>
	constexpr _scp::Mat<TValue, Size, Size, TRow, TRow> inverse(const _scp::Mat<TValue, Size, Size, TRow, TRow>& m)
	{
		assert(determinant(m) != 0);

		if constexpr (Size == 2)
		{
			const TValue tmp = TValue(1) / determinant(m);
			
			return { 
				m[1][1] * tmp, -m[0][1] * tmp,
				-m[1][0] * tmp, m[0][0] * tmp
			};
		}
		else if constexpr (Size == 3)
		{
			const TValue tmp[3] = {
				m[1][1] * m[2][2] - m[1][2] * m[2][1],
				m[0][2] * m[2][1] - m[0][1] * m[2][2],
				m[0][1] * m[1][2] - m[0][2] * m[1][1]
			};

			const TValue det = TValue(1) / (m[0][0] * tmp[0] + m[1][0] * tmp[1] + m[2][0] * tmp[2]);

			return {
				det * tmp[0],									det * tmp[1],									det * tmp[2],
				det * (m[1][2] * m[2][0] - m[1][0] * m[2][2]),	det * (m[0][0] * m[2][2] - m[0][2] * m[2][0]),	det * (m[0][2] * m[1][0] - m[0][0] * m[1][2]),
				det * (m[1][0] * m[2][1] - m[1][1] * m[2][0]),	det * (m[0][1] * m[2][0] - m[0][0] * m[2][1]),	det * (m[0][0] * m[1][1] - m[0][1] * m[1][0]),
			};
		}
		else if constexpr (Size == 4)
		{
			const TValue tmp[18] = {
				m[2][2] * m[3][3] - m[2][3] * m[3][2],
				m[2][1] * m[3][3] - m[2][3] * m[3][1],
				m[2][1] * m[3][2] - m[2][2] * m[3][1],
				m[2][0] * m[3][3] - m[2][3] * m[3][0],
				m[2][0] * m[3][2] - m[2][2] * m[3][0],
				m[2][0] * m[3][1] - m[2][1] * m[3][0],
				m[1][2] * m[3][3] - m[1][3] * m[3][2],
				m[1][1] * m[3][3] - m[1][3] * m[3][1],
				m[1][1] * m[3][2] - m[1][2] * m[3][1],
				m[1][2] * m[2][3] - m[1][3] * m[2][2],
				m[1][1] * m[2][3] - m[1][3] * m[2][1],
				m[1][1] * m[2][2] - m[1][2] * m[2][1],
				m[1][0] * m[3][3] - m[1][3] * m[3][0],
				m[1][0] * m[3][2] - m[1][2] * m[3][0],
				m[1][0] * m[2][3] - m[1][3] * m[2][0],
				m[1][0] * m[2][2] - m[1][2] * m[2][0],
				m[1][0] * m[3][1] - m[1][1] * m[3][0],
				m[1][0] * m[2][1] - m[1][1] * m[2][0]
			};

			const TValue det = TValue(1) / (
				  m[0][0] * (m[1][1] * tmp[0] - m[1][2] * tmp[1] + m[1][3] * tmp[2])
				- m[0][1] * (m[1][0] * tmp[0] - m[1][2] * tmp[3] + m[1][3] * tmp[4])
				+ m[0][2] * (m[1][0] * tmp[1] - m[1][1] * tmp[3] + m[1][3] * tmp[5])
				- m[0][3] * (m[1][0] * tmp[2] - m[1][1] * tmp[4] + m[1][2] * tmp[5])
			);

			return {
				det *  (m[1][1] * tmp[0]  - m[1][2] * tmp[1]  + m[1][3] * tmp[2]),
				det * -(m[0][1] * tmp[0]  - m[0][2] * tmp[1]  + m[0][3] * tmp[2]),
				det *  (m[0][1] * tmp[6]  - m[0][2] * tmp[7]  + m[0][3] * tmp[8]),
				det * -(m[0][1] * tmp[9]  - m[0][2] * tmp[10] + m[0][3] * tmp[11]),
				det * -(m[1][0] * tmp[0]  - m[1][2] * tmp[3]  + m[1][3] * tmp[4]),
				det *  (m[0][0] * tmp[0]  - m[0][2] * tmp[3]  + m[0][3] * tmp[4]),
				det * -(m[0][0] * tmp[6]  - m[0][2] * tmp[12] + m[0][3] * tmp[13]),
				det *  (m[0][0] * tmp[9]  - m[0][2] * tmp[14] + m[0][3] * tmp[15]),
				det *  (m[1][0] * tmp[1]  - m[1][1] * tmp[3]  + m[1][3] * tmp[5]),
				det * -(m[0][0] * tmp[1]  - m[0][1] * tmp[3]  + m[0][3] * tmp[5]),
				det *  (m[0][0] * tmp[7]  - m[0][1] * tmp[12] + m[0][3] * tmp[16]),
				det * -(m[0][0] * tmp[10] - m[0][1] * tmp[14] + m[0][3] * tmp[17]),
				det * -(m[1][0] * tmp[2]  - m[1][1] * tmp[4]  + m[1][2] * tmp[5]),
				det *  (m[0][0] * tmp[2]  - m[0][1] * tmp[4]  + m[0][2] * tmp[5]),
				det * -(m[0][0] * tmp[8]  - m[0][1] * tmp[13] + m[0][2] * tmp[16]),
				det *  (m[0][0] * tmp[11] - m[0][1] * tmp[15] + m[0][2] * tmp[17]),
			};
		}
	}
}
