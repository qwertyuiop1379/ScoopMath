# ScoopMath

A C++ header-only library providing vector and matrix implementations

# Vector

`Vector` is a template class, where `Type` determines the data type, and `Size` determines the number of elements in the vector.

### Public members

```c++
Type data[Size];
```
A c-array containing the elements of the vector.

### Constructors

```c++
Vector() = default;
```
Does not perform any initialization.

```c++
Vector(Type value);
```
Calls `this->Assign(value);`

```c++
Vector(const std::vector<Type> &values);
```
Calls `this->Assign(values);`

### Public methods

```c++
void Assign(Type value);
```
Assigns each vector element to `value`.

```c++
void Assign(const Vector<Type, Size> &vec);
```
Copies the elements of `vec`.

```c++
void Assign(const std::vector<Type> &vec);
```
Copies the elements of `vec`. If `vec::size` does not equal `Size`, an error is thrown.

```c++
Type &At(size_t index);
const Type &At(size_t index) const;
```
Returns the element at `index`. If `index` exceeds the bounds of the vector, an error is thrown.

```c++
Type &operator[](size_t index);
const Type &operator[](size_t index) const;
```
Returns the element at `index`. No bound checks are performed, so out-of-bounds indexing results in undefined behavior.

```c++
Type *begin();
const Type *begin() const;
```
Returns a pointer to the beginning of the element array. Enables range-based for loop iteration.

```c++
Type *end();
const Type *end() const;
```
Returns a pointer to the end of the element array. Enables range-based for loop iteration.

```c++
Type Sum() const;
```
Adds all the elements together and returns the sum.

```c++
double Magnitude() const;
```
Calculates the magnitude of the vector.

```c++
double Distance(const Vector<Type, Size> &vec) const;
```
Calculates the distance between this and `vec`.

```c++
Type Dot(const Vector<Size, Type> &vec) const;
```
Calculates the dot-product between this and `vec`.

```c++
Vector<Type, 3> Cross(const Vector<Type, 3> &b) const;
```
Calculates the cross-product between this and `vec`. Only applicable to vectors where `Size` is 3.

```c++
Vector<Type, Size> Normalize() const;
```
Returns a new vector that has been normalized.

```c++
void NormalizeInPlace() const;
```
Normalizes the vector.

```c++
Vector<Type, Size> Add(Type scalar) const;
Vector<Type, Size> operator+(Type s) const;
```
Returns a new vector where each a scalar is added to each element of the vector.

```c++
void AddInPlace(Type scalar);
Vector<Type, Size> &operator+=(Type s);
```
Adds a scalar to each element of the vector.

```c++
Vector<Type, Size> Subtract(Type scalar) const;
Vector<Type, Size> operator-(Type s) const;
```
Returns a new vector where a scalar is subtracted from each element of the vector.

```c++
void SubtractInPlace(Type scalar);
Vector<Type, Size> &operator-=(Type s);
```
Subtracts a scalar from each element of the vector.

```c++
Vector<Type, Size> Scale(Type scalar) const;
Vector<Type, Size> operator*(Type s) const;
Vector<Type, Size> operator/(Type s) const;
```
Returns a new vector where each element is multiplied (or in the case of `operator/`, divided) by a scalar.

```c++
void ScaleInPlace(Type scalar);
Vector<Type, Size> &operator*=(Type s);
Vector<Type, Size> &operator/=(Type s);
```
Multiplies (or in the case of `operator/=`, divides) each element of the vector by a scalar.

```c++
Vector<Type, Size> Add(const Vector<Type, Size> &vec) const;
Vector<Type, Size> operator+(const Vector<Type, Size> &vec) const;
```
Returns a new vector where each element is the element-wise sum of this and `vec`.

```c++
void AddInPlace(const Vector<Type, Size> &vec);
Vector<Type, Size> &operator+=(const Vector<Type, Size> &vec);
```
Performs element-wise addition for each element of the vector.

```c++
Vector<Type, Size> Subtract(const Vector<Type, Size> &vec) const;
Vector<Type, Size> operator-(const Vector<Type, Size> &vec) const;
```
Returns a new vector where each element is the element-wise sum of this and `vec`.

```c++
void SubtractInPlace(const Vector<Type, Size> &vec);
Vector<Type, Size> &operator-=(const Vector<Type, Size> &vec);
```
Performs element-wise subtraction for each element of the vector.

```c++
Vector<Type, Size> Hadamard(const Vector<Type, Size> &vec) const;
```
Returns a new vector where each element is the element-wise product of this and `vec`.

```c++
void HadamardInPlace(const Vector<Type, Size> &vec);
```
Performs element-wise multiplication for each element of the vector.

### Template aliases

The following template aliases are provided:

```c++
FVector<Size> = Vector<float, Size>
DVector<Size> = Vector<double, Size>

I8Vector<Size> = Vector<int8_t, Size>
I16Vector<Size> = Vector<int16_t, Size>
I32Vector<Size> = Vector<int32_t, Size>
I64Vector<Size> = Vector<int64_t, Size>

U8Vector<Size> = Vector<uint8_t, Size>
U16Vector<Size> = Vector<uint16_t, Size>
U32Vector<Size> = Vector<uint32_t, Size>
U64Vector<Size> = Vector<uint64_t, Size>
```

Each one of the aforementioned vector aliases also has the following aliases for sizes of 2, 3, and 4:
```c++
FVector2 = FVector<2>
FVector3 = FVector<3>
FVector4 = FVector<4>

DVector2 = DVector<2>
...
```

# Matrix

`Matrix` is a template class, where `Type` determines the data type, and `Rows`/`Cols` determine the dimensions of the matrix.

### Public members

```c++
Type data[Rows * Cols];
```
A c-array containing the elements of the matrix.

### Public methods

```c++
Matrix() = default;
```
Does not perform any initialization.

```c++
Matrix(Type diagonal);
```
Calls `this->Assign(diagonal);`

```c++
Matrix(const std::vector<Type> &values);
```
Calls `this->Assign(values);`

```c++
void Assign(Type diagonal);
```
Assigns each diagonal entry in the matrix to `diagonal`. All other values are set to 0.

```c++
void Assign(const std::vector<Type> &values);
```
Copies each value into the matrix. If `values::size` is not equal to `Rows * Cols`, an error is thrown.

```c++
Type &At(size_t index);
const Type &At(size_t index) const;
```
Returns the element at `index`. If `index` is out-of-bounds, an error is thrown.

```c++
Type &At(size_t row, size_t col);
const Type &At(size_t row, size_t col) const;
```
Returns the element at `col * Rows + row`. If the resulting index is out-of-bounds, an error is thrown.

```c++
Type &operator[](size_t index);
const Type &operator[](size_t index) const;
```
Returns the element at `index`. No bounds checking is performed, so out-of-bounds indices result in undefined behavior.

```c++
Vector<Type, Rows> AsVector() const;
```
If `Cols` is 1, returns a vector containing the elements of the matrix. Otherwise, an error is thrown.

```c++
Matrix<Type, Cols, Rows> Transpose() const;
```
Returns the transposition of the matrix.

```c++
Matrix<Type, Rows, Cols> Add(Type scalar) const;
Matrix<Type, Rows, Cols> operator+(Type s) const;
```
Returns a new matrix where a scalar is added to each element of the matrix.

```c++
void AddInPlace(Type scalar);
Matrix<Type, Rows, Cols> &operator+=(Type s);
```
Adds a scalar to each element of the matrix.

```c++
Matrix<Type, Rows, Cols> Subtract(Type scalar) const;
Matrix<Type, Rows, Cols> operator-(Type s) const;
```
Returns a new matrix where a scalar is added to each element of the matrix.

```c++
void SubtractInPlace(Type scalar);
Matrix<Type, Rows, Cols> &operator-=(Type s);
```
Subtracts a scalar from each element of the matrix.

```c++
Matrix<Type, Rows, Cols> Scale(Type scalar) const;
Matrix<Type, Rows, Cols> operator*(Type s) const;
Matrix<Type, Rows, Cols> operator/(Type s) const;
```
Returns a new matrix where each element is multiplied (or in the case of `operator/`, divided) by a scalar.

```c++
void ScaleInPlace(Type scalar);
Matrix<Type, Rows, Cols> &operator*=(Type s);
Matrix<Type, Rows, Cols> &operator/=(Type s);
```
Multiplies (or in the case of `operator/=`, divides) each element of the matrix by a scalar.

```c++
Matrix<Type, Rows, Cols> Add(const Matrix<Type, Rows, Cols> &mat) const;
Matrix<Type, Rows, Cols> operator+(const Matrix<Type, Rows, Cols> &mat) const;
```
Returns a new matrix where each element is the element-wise sum of this and `mat`.

```c++
void AddInPlace(const Matrix<Type, Rows, Cols> &mat);
Matrix<Type, Rows, Cols> &operator+=(const Matrix<Type, Rows, Cols> &mat);
```
Performs element-wise addition of this and `mat`.

```c++
Matrix<Type, Rows, Cols> Subtract(const Matrix<Type, Rows, Cols> &mat) const;
Matrix<Type, Rows, Cols> operator-(const Matrix<Type, Rows, Cols> &mat) const;
```
Returns a new matrix where each element is the element-wise difference of this and `mat.`

```c++
void SubtractInPlace(const Matrix<Type, Rows, Cols> &mat);
Matrix<Type, Rows, Cols> &operator-=(const Matrix<Type, Rows, Cols> &mat);
```
Performs element-wise subtraction of this and `mat`.

```c++
Matrix<Type, Rows, Cols> Hadamard(const Matrix<Type, Rows, Cols> &mat) const;
```
Returns a new matrix where each element is the element-wise product of this and `mat`.

```c++
void HadamardInPlace(const Matrix<Type, Rows, Cols> &mat);
```
Performs element-wise multiplication of this and `mat`.

```c++
template <size_t Cols2> Matrix<Type, Rows, Cols2> Multiply(const Matrix<Type, Cols, Cols2> &mat) const;
template <size_t Cols2> Matrix<Type, Rows, Cols2> operator*(const Matrix<Type, Cols, Cols2> &mat) const;
```
Returns the matrix product of this and `mat`.

```c++
Vector<Type, Rows> Multiply(const Vector<Type, Rows> &vec) const;
Vector<Type, Rows> operator*(const Vector<Type, Rows> &vec) const;
```
Returns the matrix product (where `vec` is interpreted as a matrix with 1 column) of this and `vec`.

```c++
void MultiplyInPlace(const Matrix<Type, Rows, Cols> &mat);
Matrix<Type, Rows, Cols> &operator*=(const Matrix<Type, Rows, Cols> &mat);
```
Performs matrix multiplication of this and `mat`.

```c++
static Matrix<Type, Rows, Cols> Identity();
```
Returns an identity matrix.

```c++
static Matrix<Type, 4, 4> Translation(const Vector<Type, 3> &delta);
```
Returns a translation matrix for use in 3D space.

```c++
static Matrix<Type, 4, 4> Scale(const Vector<Type, 3> &multipliers);
```
Returns a scale matrix for use in 3D space.



### Template aliases

The following template aliases are provided:

```c++
FMatrix<Rows, Cols> = Matrix<float, Rows, Cols>
DMatrix<Rows, Cols> = Matrix<double, Rows, Cols>

I8Matrix<Rows, Cols> = Matrix<int8_t, Rows, Cols>
I16Matrix<Rows, Cols> = Matrix<int16_t, Rows, Cols>
I32Matrix<Rows, Cols> = Matrix<int32_t, Rows, Cols>
I64Matrix<Rows, Cols> = Matrix<int64_t, Rows, Cols>

U8Matrix<Rows, Cols> = Matrix<uint8_t, Rows, Cols>
U16Matrix<Rows, Cols> = Matrix<uint16_t, Rows, Cols>
U32Matrix<Rows, Cols> = Matrix<uint32_t, Rows, Cols>
U64Matrix<Rows, Cols> = Matrix<uint64_t, Rows, Cols>
```

Each one of the aforementioned vector aliases also has the following aliases for square sizes of 2, 3, and 4:
```c++
FMatrix2 = FMatrix<2, 2>
FMatrix3 = FMatrix<3, 3>
FMatrix4 = FMatrix<4, 4>

DMatrix2 = DMatrix<2, 2>
...
```