#pragma once

#include <cmath>
#include <cstdint>
#include <cstring>

namespace Scoop::Math
{
    #define __VEC_FOREACH for (size_t i = 0; i < Size; i++)

    template <typename Type, size_t Size> class Vector
    {
        public:

        // Vector elements
        
        Type data[Size];

        // Constructors

        Vector() = default;

        explicit Vector(Type value)
        { this->Assign(value); }
        
        explicit Vector(const std::vector<Type> &values)
        { this->Assign(values); }

        // Assignment

        void Assign(Type value)
        { __VEC_FOREACH this->data[i] = value; }

        void Assign(const Vector<Type, Size> &vec)
        { std::memcpy(this->data, vec.data, sizeof(Type) * Size); }

        void Assign(const std::vector<Type> &values)
        {
            if (values.size() != Size)
                throw Error::Create("Vector", "Assign", "Specified std::vector::size does not match this vector's size.");
            std::memcpy(this->data, &values[0], sizeof(Type) * Size);
        }

        // Indexing

        Type &At(size_t index)
        {
            if (index >= Size)
                throw Error::IndexError("Vector", "At", index, Size);
            return this->data[index];
        }

        const Type &At(size_t index) const
        {
            if (index >= Size)
                throw Error::IndexError("Vector", "At", index, Size);
            return this->data[index];
        }

        // Index operator

        inline Type &operator[](size_t index) { return this->data[index]; }
        inline const Type &operator[](size_t index) const { return this->data[index]; }

        // Range-based iteration

        Type *begin()
        { return this->data; }
        Type *end()
        { return this->data + Size; }

        const Type *begin() const
        { return this->data; }
        const Type *end() const
        { return this->data + Size; }

        // Vector properties

        Type Sum() const
        {
            Type sum = 0;
            __VEC_FOREACH sum += this->data[i];
            return sum;
        }

        double Magnitude() const
        {
            Type sum = 0;

            __VEC_FOREACH
            {
                const Type &element = this->data[i];
                sum += element * element;
            }

            return sqrt(sum);
        }

        double Distance(const Vector<Type, Size> &vec) const
        {
            Type sum = 0;

            __VEC_FOREACH
            {
                Type delta = this->data[i] - vec->data[i];
                sum += delta * delta;
            }

            return sqrt(sum);
        }

        Type Dot(const Vector<Type, Size> &vec) const
        {
            Type product = 0;
            __VEC_FOREACH product += this->data[i] * vec.data[i];
            return product;
        }
        
        template <size_t N = Size, typename std::enable_if<N == 3, size_t>::type = 0>
        Vector<Type, 3> Cross(const Vector<Type, 3> &b) const
        {
            Vector<Type, 3> cross;

            cross[0] = this->data[1] * b.data[2] - this->data[2] * b.data[1];
            cross[1] = this->data[2] * b.data[0] - this->data[0] * b.data[2];
            cross[2] = this->data[0] * b.data[1] - this->data[1] * b.data[0];

            return cross;
        }

        // Normalization

        Vector<Type, Size> Normalize() const
        { return this->Scale(1 / this->Magnitude()); }

        void NormalizeInPlace()
        { this->ScaleInPlace(1 / this->Magnitude()); }

        // Scalar arithmetic

        Vector<Type, Size> Add(Type scalar) const
        {
            Vector<Type, Size> vec(*this);
            __VEC_FOREACH vec.data[i] += scalar;
            return vec;
        }

        Vector<Type, Size> Subtract(Type scalar) const
        {
            Vector<Type, Size> vec(*this);
            __VEC_FOREACH vec.data[i] -= scalar;
            return vec;
        }

        Vector<Type, Size> Scale(Type scalar) const
        {
            Vector<Type, Size> vec(*this);
            __VEC_FOREACH vec.data[i] *= scalar;
            return vec;
        }

        // In-place scalar arithmetic

        void AddInPlace(Type scalar)
        { __VEC_FOREACH this->data[i] += scalar; }

        void SubtractInPlace(Type scalar)
        { __VEC_FOREACH this->data[i] -= scalar; }

        void ScaleInPlace(Type scalar)
        { __VEC_FOREACH this->data[i] *= scalar; }

        // Vector arithmetic

        Vector<Type, Size> Add(const Vector<Type, Size> &vec) const
        {
            Vector<Type, Size> newVec(*this);
            __VEC_FOREACH newVec.data[i] += vec.data[i];
            return newVec;
        }

        Vector<Type, Size> Subtract(const Vector<Type, Size> &vec) const
        {
            Vector<Type, Size> newVec(*this);
            __VEC_FOREACH newVec.data[i] -= vec.data[i];
            return newVec;
        }

        Vector<Type, Size> Hadamard(const Vector<Type, Size> &vec) const
        {
            Vector<Type, Size> newVec(*this);
            __VEC_FOREACH newVec.data[i] *= vec.data[i];
            return newVec;
        }

        // In-place vector arithmetic

        void AddInPlace(const Vector<Type, Size> &vec)
        { __VEC_FOREACH this->data[i] += vec.data[i]; }

        void SubtractInPlace(const Vector<Type, Size> &vec)
        { __VEC_FOREACH this->data[i] -= vec.data[i]; }

        void HadamardInPlace(const Vector<Type, Size> &vec)
        { __VEC_FOREACH this->data[i] *= vec.data[i]; }

        // Scalar arithmetic operators

        inline Vector<Type, Size> operator+(Type s) const { return Add(s); }
        inline Vector<Type, Size> operator-(Type s) const { return Subtract(s); }
        inline Vector<Type, Size> operator*(Type s) const { return Scale(s); }
        inline Vector<Type, Size> operator/(Type s) const { return Scale(1 / s); }

        inline Vector<Type, Size> &operator+=(Type s) { this->AddInPlace(s); return *this; }
        inline Vector<Type, Size> &operator-=(Type s) { this->SubtractInPlace(s); return *this; }
        inline Vector<Type, Size> &operator*=(Type s) { this->ScaleInPlace(s); return *this; }
        inline Vector<Type, Size> &operator/=(Type s) { this->ScaleInPlace(1 / s); return *this; }

        // Vector arithmetic operators

        inline Vector<Type, Size> operator+(const Vector<Type, Size> &vec) const { return Add(vec); }
        inline Vector<Type, Size> operator-(const Vector<Type, Size> &vec) const { return Subtract(vec); }

        inline Vector<Type, Size> &operator+=(const Vector<Type, Size> &vec) { this->AddInPlace(vec); return *this; }
        inline Vector<Type, Size> &operator-=(const Vector<Type, Size> &vec) { this->SubtractInPlace(vec); return *this; }
    };

    #undef __VEC_FOREACH
    
    // Typed vector aliases

    #define __TYPED_VEC_ALIAS(type, name) template <size_t Size> using name = Vector<type, Size>

    __TYPED_VEC_ALIAS(float, FVector);
    __TYPED_VEC_ALIAS(double, DVector);

    __TYPED_VEC_ALIAS(int8_t, I8Vector);
    __TYPED_VEC_ALIAS(int16_t, I16Vector);
    __TYPED_VEC_ALIAS(int32_t, I32Vector);
    __TYPED_VEC_ALIAS(int64_t, I64Vector);
    
    __TYPED_VEC_ALIAS(uint8_t, U8Vector);
    __TYPED_VEC_ALIAS(uint16_t, U16Vector);
    __TYPED_VEC_ALIAS(uint32_t, U32Vector);
    __TYPED_VEC_ALIAS(uint64_t, U64Vector);

    #undef __TYPED_VEC_ALIAS

    // Vector2, Vector3, Vector4 aliases

    #define __TYPED_VEC234(alias) typedef alias<2> ##alias##2; typedef alias<3> ##alias##3; typedef alias<4> ##alias##4;

    __TYPED_VEC234(FVector);
    __TYPED_VEC234(DVector);

    __TYPED_VEC234(I8Vector);
    __TYPED_VEC234(I16Vector);
    __TYPED_VEC234(I32Vector);
    __TYPED_VEC234(I64Vector);

    __TYPED_VEC234(U8Vector);
    __TYPED_VEC234(U16Vector);
    __TYPED_VEC234(U32Vector);
    __TYPED_VEC234(U64Vector);

    #undef __TYPED_VEC234
}