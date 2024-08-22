#pragma once

#include <Math/Vector.hpp>

namespace Scoop::Math
{
    template <typename Type, size_t Rows, size_t Cols> class Matrix
    {
        public:

        // Matrix elements

        Type data[Rows * Cols];

        // Constructors

        Matrix() = default;

        explicit Matrix(Type diagonal)
        { this->Assign(diagonal); }

        explicit Matrix(const std::vector<Type> &values)
        { this->Assign(values); }

        // Assignment

        void Assign(Type diagonal)
        {
            size_t i = 0;

            for (size_t row = 0; row < Rows; row++)
            {
                for (size_t col = 0; col < Cols; col++)
                {
                    if (row == col)
                        this->data[i] = diagonal;
                    else
                        this->data[i] = 0;
                    i++;
                }
            }
        }

        void Assign(const std::vector<Type> &values)
        {
            if (values.size() != Rows * Cols)
                throw std::runtime_error("Matrix::Assign: vector size mismatch.");
            std::memcpy(this->data, data, sizeof(Type) * Rows * Cols);
        }

        // Indexing

        Type &At(size_t index)
        {
            if (index >= Rows * Cols)
                throw std::out_of_range("Matrix::At: index out of range.");
            return this->data[index];
        }

        const Type &At(size_t index) const
        {
            if (index >= Rows * Cols)
                throw std::out_of_range("Matrix::At: index out of range.");
            return this->data[index];
        }

        inline Type &At(size_t row, size_t col) { return this->At(col * Rows + row); }
        inline const Type &At(size_t row, size_t col) const { return this->At(col * Rows + row); }

        // Index operators

        inline Type &operator[](size_t index) { return this->data[index]; }
        inline const Type &operator[](size_t index) const { return this->data[index]; }

        // Vector conversion

        Vector<Type, Rows> AsVector() const
        {
            if (Cols != 1)
                throw std::runtime_error("Matrix::AsVector: matrix must have 1 column to be interpreted as a vector.");
            return Vector<Type, Rows>(this->data);
        }

        // Matrix properties

        Matrix<Type, Cols, Rows> Transpose() const
        {
            Matrix<Type, Cols, Rows> newMat(Cols, Rows);

            for (size_t row = 0; row < Rows; row++)
            {
                for (size_t col = 0; col < Cols; col++)
                    newMat.At(col, row) = this->At(row, col);
            }

            return newMat;
        }

        // Scalar arithmetic

        Matrix<Type, Rows, Cols> Add(Type scalar) const
        {
            Matrix<Type, Rows, Cols> mat(*this);

            for (size_t i = 0; i < Rows * Cols; i++)
                mat.data[i] += scalar;
                
            return mat;
        }

        Matrix<Type, Rows, Cols> Subtract(Type scalar) const
        {
            Matrix<Type, Rows, Cols> mat(*this);

            for (size_t i = 0; i < Rows * Cols; i++)
                mat.data[i] -= scalar;
                
            return mat;
        }

        Matrix<Type, Rows, Cols> Scale(Type scalar) const
        {
            Matrix<Type, Rows, Cols> mat(*this);

            for (size_t i = 0; i < Rows * Cols; i++)
                mat.data[i] *= scalar;
                
            return mat;
        }

        // In-place scalar arithmetic

        void AddInPlace(Type scalar)
        {
            for (size_t i = 0; i < Rows * Cols; i++)
                this->data[i] += scalar;
        }

        void SubtractInPlace(Type scalar)
        {
            for (size_t i = 0; i < Rows * Cols; i++)
                this->data[i] -= scalar;
        }

        void ScaleInPlace(Type scalar)
        {
            for (size_t i = 0; i < Rows * Cols; i++)
                this->data[i] *= scalar;
        }

        // Matrix arithmetic

        Matrix<Type, Rows, Cols> Add(const Matrix<Type, Rows, Cols> &mat) const
        {
            Matrix<Type, Rows, Cols> newMat(*this);

            for (size_t i = 0; i < Rows * Cols; i++)
                newMat.data[i] += mat.data[i];

            return newMat;
        }

        Matrix<Type, Rows, Cols> Subtract(const Matrix<Type, Rows, Cols> &mat) const
        {
            Matrix<Type, Rows, Cols> newMat(*this);

            for (size_t i = 0; i < Rows * Cols; i++)
                newMat.data[i] -= mat.data[i];

            return newMat;
        }

        Matrix<Type, Rows, Cols> Hadamard(const Matrix<Type, Rows, Cols> &mat) const
        {
            Matrix<Type, Rows, Cols> newMat(*this);

            for (size_t i = 0; i < Rows * Cols; i++)
                newMat.data[i] *= mat.data[i];

            return newMat;
        }

        template <size_t Cols2> Matrix<Type, Rows, Cols2> Multiply(const Matrix<Type, Cols, Cols2> &mat) const
        {
            Matrix<Type, Rows, Cols2> newMat;

            for (size_t row = 0; row < Rows; row++)
            {
                for (size_t col = 0; col < Cols2; col++)
                {
                    Type dot = 0;

                    for (size_t m = 0; m < Cols; m++)
                        dot += this->At(row, m) * mat.At(m, col);

                    newMat.At(row, col) = dot;
                }
            }
            
            return newMat;
        }

        Vector<Type, Rows> Multiply(const Vector<Type, Rows> &vec) const
        {
            Vector<Type, Rows> newVec;

            for (size_t row = 0; row < Rows; row++)
            {
                Type dot = 0;
                
                for (size_t col = 0; col < Cols; col++)
                    dot += this->At(row, col) * vec.data[col];

                newVec.data[row] = dot;
            }

            return newVec;
        }

        // In-place matrix arithmetic

        void AddInPlace(const Matrix<Type, Rows, Cols> &mat)
        {
            for (size_t i = 0; i < Rows * Cols; i++)
                this->data[i] = this->data[i] + mat.data[i];
        }

        void SubtractInPlace(const Matrix<Type, Rows, Cols> &mat)
        {
            for (size_t i = 0; i < Rows * Cols; i++)
                this->data[i] = this->data[i] - mat.data[i];
        }

        void HadamardInPlace(const Matrix<Type, Rows, Cols> &mat)
        {
            for (size_t i = 0; i < Rows * Cols; i++)
                this->data[i] = this->data[i] * mat.data[i];
        }

        void MultiplyInPlace(const Matrix<Type, Rows, Cols> &mat)
        {
            Matrix<Type, Rows, Cols> newMat(Rows, Cols);

            for (size_t row = 0; row < Rows; row++)
            {
                for (size_t col = 0; col < Cols; col++)
                {
                    Type dot = 0;

                    for (size_t m = 0; m < Cols; m++)
                        dot += this->At(row, m) * mat.At(m, col);

                    newMat.At(row, col) = dot;
                }
            }
            
            *this = newMat;
        }

        // Scalar arithmetic operators

        inline Matrix<Type, Rows, Cols> operator+(Type s) const { return Add(s); }
        inline Matrix<Type, Rows, Cols> operator-(Type s) const { return Subtract(s); }
        inline Matrix<Type, Rows, Cols> operator*(Type s) const { return Scale(s); }
        inline Matrix<Type, Rows, Cols> operator/(Type s) const { return Scale(1 / s); }

        inline Matrix<Type, Rows, Cols> &operator+=(Type s) { this->AddInPlace(s); return *this; }
        inline Matrix<Type, Rows, Cols> &operator-=(Type s) { this->SubtractInPlace(s); return *this; }
        inline Matrix<Type, Rows, Cols> &operator*=(Type s) { this->ScaleInPlace(s); return *this; }
        inline Matrix<Type, Rows, Cols> &operator/=(Type s) { this->ScaleInPlace(1 / s); return *this; }

        // Matrix arithmetic operators

        inline Matrix<Type, Rows, Cols> operator+(const Matrix<Type, Rows, Cols> &mat) const { return Add(mat); }
        inline Matrix<Type, Rows, Cols> operator-(const Matrix<Type, Rows, Cols> &mat) const { return Subtract(mat); }
        template <size_t Cols2> inline Matrix<Type, Rows, Cols2> operator*(const Matrix<Type, Cols, Cols2> &mat) const { return Multiply(mat); }
        inline Vector<Type, Rows> operator*(const Vector<Type, Rows> &vec) const { return Multiply(vec); }

        inline Matrix<Type, Rows, Cols> &operator+=(const Matrix<Type, Rows, Cols> &mat) { this->AddInPlace(mat); return *this; }
        inline Matrix<Type, Rows, Cols> &operator-=(const Matrix<Type, Rows, Cols> &mat) { this->SubtractInPlace(mat); return *this; }
        inline Matrix<Type, Rows, Cols> &operator*=(const Matrix<Type, Rows, Cols> &mat) { this->MultiplyInPlace(mat); return *this; }

        // Identity matrix

        static Matrix<Type, Rows, Cols> Identity()
        { return Matrix<Type, Rows, Cols>(1); }

        // Transformation

        template <size_t R = Rows, size_t C = Cols, typename std::enable_if<R == 4 && C == 4, int>::type = 0>
        static Matrix<Type, 4, 4> Translation(const Vector<Type, 3> &delta)
        {
            return Matrix<Type, 4, 4>
            ({
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                delta[0], delta[1], delta[2], 1,
            });
        }

        template <size_t R = Rows, size_t C = Cols, typename std::enable_if<R == 4 && C == 4, int>::type = 0>
        static Matrix<Type, 4, 4> Scale(const Vector<Type, 3> &multipliers)
        {
            return Matrix<Type, 4, 4>
            ({
                multipliers[0], 0, 0, 0,
                0, multipliers[1], 0, 0,
                0, 0, multipliers[2], 0,
                0, 0, 0, 1,
            });
        }
    };
    
    // Typed matrix aliases

    #define __TYPED_MAT_ALIAS(type, name) template <size_t Rows, size_t Cols> using name = Matrix<type, Rows, Cols>

    __TYPED_MAT_ALIAS(float, FMatrix);
    __TYPED_MAT_ALIAS(double, DMatrix);

    __TYPED_MAT_ALIAS(int8_t, I8Matrix);
    __TYPED_MAT_ALIAS(int16_t, I16Matrix);
    __TYPED_MAT_ALIAS(int32_t, I32Matrix);
    __TYPED_MAT_ALIAS(int64_t, I64Matrix);
    __TYPED_MAT_ALIAS(uint8_t, U8Matrix);

    __TYPED_MAT_ALIAS(uint16_t, U16Matrix);
    __TYPED_MAT_ALIAS(uint32_t, U32Matrix);
    __TYPED_MAT_ALIAS(uint64_t, U64Matrix);

    #undef __TYPED_MAT_ALIAS

    // Matrix2, Matrix3, Matrix4 aliases

    #define __TYPED_MAT234_ALIAS(alias) typedef alias<2, 2> ##alias##2; typedef alias<3, 3> ##alias##3; typedef alias<4, 4> ##alias##4;

    __TYPED_MAT234_ALIAS(FMatrix);
    __TYPED_MAT234_ALIAS(DMatrix);

    __TYPED_MAT234_ALIAS(I8Matrix);
    __TYPED_MAT234_ALIAS(I16Matrix);
    __TYPED_MAT234_ALIAS(I32Matrix);
    __TYPED_MAT234_ALIAS(I64Matrix);

    __TYPED_MAT234_ALIAS(U8Matrix);
    __TYPED_MAT234_ALIAS(U16Matrix);
    __TYPED_MAT234_ALIAS(U32Matrix);
    __TYPED_MAT234_ALIAS(U64Matrix);

    #undef __TYPED_MAT234_ALIAS
}