///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>

namespace scp
{
	namespace _scp
	{
		#pragma pack(push, 1)
		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		class Mat
		{
			static_assert(Row == 2 || Row == 3 || Row == 4);
			static_assert(Col == 2 || Col == 3 || Col == 4);
			static_assert(CVec<TRow> && TRow::size == Col);
			static_assert(CVec<TCol> && TCol::size == Row);

			public:

				using IsMat = bool;
				using ValueType = TValue;
				using RowType = TRow;
				using ColType = TCol;

				static constexpr uint8_t row = Row;
				static constexpr uint8_t col = Col;

				constexpr Mat() = default;
				constexpr Mat(TValue diagValue);
				constexpr Mat(const std::initializer_list<TValue>& values);
				constexpr Mat(const Mat<TValue, Row, Col, TRow, TCol>& mat) = default;
				constexpr Mat(Mat<TValue, Row, Col, TRow, TCol>&& mat) = default;

				constexpr Mat<TValue, Row, Col, TRow, TCol>& operator=(const Mat<TValue, Row, Col, TRow, TCol>& mat) = default;
				constexpr Mat<TValue, Row, Col, TRow, TCol>& operator=(Mat<TValue, Row, Col, TRow, TCol>&& mat) = default;

				constexpr TRow& operator[](uint8_t i);
				constexpr const TRow& operator[](uint8_t i) const;

				constexpr Mat<TValue, Row, Col, TRow, TCol>& operator+=(const Mat<TValue, Row, Col, TRow, TCol>& mat);
				constexpr Mat<TValue, Row, Col, TRow, TCol>& operator-=(const Mat<TValue, Row, Col, TRow, TCol>& mat);

				constexpr ~Mat() = default;

			private:

				TRow _rows[Row];
		};
		#pragma pack(pop)

		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr Mat<TValue, Row, Col, TRow, TCol> operator+(const Mat<TValue, Row, Col, TRow, TCol>& a, const Mat<TValue, Row, Col, TRow, TCol>& b);
		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr Mat<TValue, Row, Col, TRow, TCol> operator-(const Mat<TValue, Row, Col, TRow, TCol>& a, const Mat<TValue, Row, Col, TRow, TCol>& b);

		template<typename TValue, uint8_t RowA, uint8_t ColARowB, uint8_t ColB, typename TRowA, typename TColARowB, typename TColB>
		constexpr Mat<TValue, RowA, ColB, TRowA, TColB> operator*(const Mat<TValue, RowA, ColARowB, TRowA, TColARowB>& a, const Mat<TValue, ColARowB, ColB, TColARowB, TColB>& b);

		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr TRow operator*(const TRow& vec, const Mat<TValue, Row, Col, TRow, TCol>& mat);
		template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
		constexpr TCol operator*(const Mat<TValue, Row, Col, TRow, TCol>& mat, const TCol& vec);

		// TODO: unary minus, transpose
	}

	template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol>
	constexpr _scp::Mat<TValue, Col, Row, TCol, TRow> transpose(const _scp::Mat<TValue, Row, Col, TRow, TCol>& m);
	template<typename TValue, uint8_t Size, typename TRow>
	constexpr TValue determinant(const _scp::Mat<TValue, Size, Size, TRow, TRow>& m);
	template<typename TValue, uint8_t Size, typename TRow>
	constexpr _scp::Mat<TValue, Size, Size, TRow, TRow> inverse(const _scp::Mat<TValue, Size, Size, TRow, TRow>& m);
}
