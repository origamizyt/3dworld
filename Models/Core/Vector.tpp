/*************************************************************************
【文件名】 Vector.tpp
【功能模块和目的】 为 Vector.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include "../Errors/IndexOverflowException.hpp"
#include "../Errors/InvalidSizeException.hpp"
#include "Vector.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Errors;

// 浮点数比较的范围
template <typename T, size_t N>
const T Vector<T, N>::EPSILON { is_floating_point<T>::value ? 1e-6 : 0 };

// 零向量。
template <typename T, size_t N>
const Vector<T, N> Vector<T, N>::ZERO { Vector<T, N>() };

/**********************************************************************
【函数名称】 构造函数
【函数功能】 初始化分量全部为 0 的 Vector 对象。
【参数】 无
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>::Vector(): Vector(0) {}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 初始化分量全部为 "Filler" 的 Vector 对象。
【参数】 
    Filler: 填充的数值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>::Vector(T Filler) {
    m_Components.fill(Filler);
}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用初始化列表初始化 Vector 对象。
【参数】 
    Components: 分量构成的初始化列表。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>::Vector(initializer_list<T> Components) {
    if (Components.size() != N) {
        throw InvalidSizeException(Components.size(), N);
    }
    copy(Components.begin(), Components.end(), m_Components.begin());
}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用分量数组初始化 Vector 对象。
【参数】 
    Components: 分量构成的数组。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>::Vector(const array<T, N>& Components)
    : m_Components(Components) {}

/**********************************************************************
【函数名称】 GetComponent
【函数功能】 返回指定下标处的分量。
【参数】 
    Index: 要获取分量的下标。
【返回值】 
    对指定下标处的分量的常引用。
    如果下标越界，抛出 IndexOverflowException。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
const T& Vector<T, N>::GetComponent(size_t Index) const {
    if (Index >= N) {
        throw IndexOverflowException(Index, N);
    }
    return m_Components[Index];
}

/**********************************************************************
【函数名称】 GetComponent
【函数功能】 返回指定下标处的分量。
【参数】 
    Index: 要获取分量的下标。
【返回值】 
    对指定下标处的分量的可变引用。
    如果下标越界，抛出 IndexOverflowException。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T& Vector<T, N>::GetComponent(size_t Index) {
    if (Index >= N) {
        throw IndexOverflowException(Index, N);
    }
    return m_Components[Index];
}

/**********************************************************************
【函数名称】 SetComponent
【函数功能】 设置指定下标处的分量。
【参数】 
    Index: 要设置分量的下标。
    Value: 要设置的分量值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::SetComponent(size_t Index, const T& Value) {
    if (Index >= N) {
        throw IndexOverflowException(Index, N);
    }
    m_Components[Index] = Value;
}

/**********************************************************************
【函数名称】 SetAllComponents
【函数功能】 使用数组设置所有分量。
【参数】 
    Components: 分量构成的数组。不进行越界检测。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::SetAllComponents(const array<T, N>& Components) {
    m_Components = Components;
}

/**********************************************************************
【函数名称】 Module
【函数功能】 求此向量的模长。
【参数】 无
【返回值】 此向量的模长。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T Vector<T, N>::Module() const {
    T SquareSum = 0;
    for (size_t i = 0; i < N; i++) {
        SquareSum += pow(m_Components[i], 2);
    }
    return sqrt(SquareSum);
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断自身是否和指定的向量相等。
【参数】 
    Other: 要与之判断的向量。
【返回值】 
    自身和指定向量是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::IsEqual(const Vector<T, N>& Other, bool Exact) const {
    return IsEqual(*this, Other, Exact);
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断两个向量是否相等。
【参数】 
    Left: 要判断的第一个向量。
    Right: 要判断的第二个向量。
【返回值】 
    两个向量是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::IsEqual(
    const Vector<T, N>& Left, 
    const Vector<T, N>& Right,
    bool Exact
) {
    if (Exact) {
        return Left.m_Components == Right.m_Components;
    }
    else {
        for (size_t i = 0; i < N; i++) {
            if (fabs(Left[i] - Right[i]) > EPSILON) {
                return false;
            }
        }
        return true;
    }
}

/**********************************************************************
【函数名称】 IsParallel
【函数功能】 判断自身是否和指定的向量平行。
【参数】 
    Other: 要与之判断的向量。
【返回值】 
    自身和指定向量是否平行。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::IsParallel(const Vector<T, N>& Other) const {
    return IsParallel(*this, Other);
}

/**********************************************************************
【函数名称】 IsParallel
【函数功能】 判断两个向量是否平行。
【参数】 
    Left: 要判断的第一个向量。
    Right: 要判断的第二个向量。
【返回值】 
    两个向量是否平行。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::IsParallel(
    const Vector<T, N>& Left, 
    const Vector<T, N>& Right
) {
    if (N == 1) {
        return true;
    }
    // 由于一些数据类型对除法不封闭，只能使用乘法。
    for (size_t i = 1; i < N; i++) {
        if (Left[0] * Right[i] != Right[0] * Left[i]) {
            return false;
        }
    }
    return true;
}

/**********************************************************************
【函数名称】 IsPerpendicular
【函数功能】 判断自身是否和指定的向量垂直。
【参数】 
    Other: 要与之判断的向量。
【返回值】 
    自身和指定向量是否垂直。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::IsPerpendicular(const Vector<T, N>& Other) const {
    return IsPerpendicular(*this, Other);
}

/**********************************************************************
【函数名称】 IsPerpendicular
【函数功能】 判断两个向量是否垂直。
【参数】 
    Left: 要判断的第一个向量。
    Right: 要判断的第二个向量。
【返回值】 
    两个向量是否垂直。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::IsPerpendicular(
    const Vector<T, N>& Left,
    const Vector<T, N>& Right
) {
    return fabs(InnerProduct(Left, Right)) <= EPSILON;
}

/**********************************************************************
【函数名称】 NegateInplace
【函数功能】 反转此向量。
【参数】 无
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::NegateInplace() {
    for (auto& component: m_Components) {
        component = -component;
    }
}

/**********************************************************************
【函数名称】 Negate
【函数功能】 反转此向量并存为新的向量。
【参数】 无
【返回值】 
    反转后的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Negate() const {
    return Negate(*this);
}

/**********************************************************************
【函数名称】 Negate
【函数功能】 反转给定向量并存为新的向量。
【参数】 
    AVector: 要反转的向量。
【返回值】 
    反转后的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Negate(const Vector<T, N>& AVector) {
    Vector<T, N> Result;
    for (size_t i = 0; i < N; i++) {
        Result[i] = -AVector[i];
    }
    return Result;
}

/**********************************************************************
【函数名称】 AddInplace
【函数功能】 将自身加以另一个向量。
【参数】 
    Other: 另一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::AddInplace(const Vector<T, N>& Other) {
    for (size_t i = 0; i < N; i++) {
        m_Components[i] += Other[i];
    }
}

/**********************************************************************
【函数名称】 Add
【函数功能】 将自身与另一向量相加并存储为新的向量。
【参数】 
    Other: 另一向量。
【返回值】 
    两向量相加形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Add(const Vector<T, N>& Other) const {
    return Add(*this, Other);
}

/**********************************************************************
【函数名称】 Add
【函数功能】 将两个向量相加并存储为新的向量。
【参数】 
    Left: 要相加的第一个向量。
    Right: 要相加的第二个向量。
【返回值】 
    两向量相加形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Add(
    const Vector<T, N>& Left, 
    const Vector<T, N>& Right
) {
    Vector<T, N> Result;
    for (size_t i = 0; i < N; i++) {
        Result[i] = Left[i] + Right[i];
    }
    return Result;
}

/**********************************************************************
【函数名称】 SubtractInplace
【函数功能】 将自身减去另一个向量。
【参数】 
    Other: 另一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::SubtractInplace(const Vector<T, N>& Other) {
    for (size_t i = 0; i < N; i++) {
        m_Components[i] -= Other[i];
    }
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将自身与另一向量相减并存储为新的向量。
【参数】 
    Other: 另一向量。
【返回值】 
    两向量相减形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Subtract(const Vector<T, N>& Other) const {
    return Subtract(*this, Other);
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将两个向量相减并存储为新的向量。
【参数】 
    Left: 要相减的第一个向量。
    Right: 要相减的第二个向量。
【返回值】 
    两向量相减形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Subtract(
    const Vector<T, N>& Left, 
    const Vector<T, N>& Right
) {
    Vector<T, N> Result;
    for (size_t i = 0; i < N; i++) {
        Result[i] = Left[i] - Right[i];
    }
    return Result;
}

/**********************************************************************
【函数名称】 MultiplyInplace
【函数功能】 将自身与标量数乘。
【参数】 
    Factor: 要数乘的标量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::MultiplyInplace(T Factor) {
    for (auto& component: m_Components) {
        component *= Factor;
    }
}

/**********************************************************************
【函数名称】 Multiply
【函数功能】 将自身与标量数乘。
【参数】 
    Factor: 要数乘的标量。
【返回值】 
    数乘形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Multiply(T Factor) const {
    return Multiply(*this, Factor);
}

/**********************************************************************
【函数名称】 Multiply
【函数功能】 将向量与标量数乘。
【参数】 
    AVector: 要数乘的向量。
    Factor: 要数乘的标量。
【返回值】 
    数乘形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Multiply(const Vector<T, N> AVector, T Factor) {
    Vector<T, N> Result;
    for (size_t i = 0; i < N; i++) {
        Result[i] = AVector[i] * Factor;
    }
    return Result;
}

/**********************************************************************
【函数名称】 InnerProduct
【函数功能】 将自身和另一向量做内积。
【参数】 
    Other: 另一个向量。
【返回值】 与另一向量的内积。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T Vector<T, N>::InnerProduct(const Vector<T, N>& Other) {
    return InnerProduct(*this, Other);
}

/**********************************************************************
【函数名称】 InnerProduct
【函数功能】 将两个向量做内积。
【参数】 
    Left: 要做内积的第一个向量。
    Right: 要做内积的第二个向量。
【返回值】 
    两向量的内积。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T Vector<T, N>::InnerProduct(
    const Vector<T, N>& Left, 
    const Vector<T, N>& Right
) {
    T Result = 0;
    for (size_t i = 0; i < N; i++) {
        Result += Left[i] * Right[i];
    }
    return Result;
}

/**********************************************************************
【函数名称】 operator[]
【函数功能】 通过下标访问分量。
【参数】 
    Index: 要访问的下标。
【返回值】 
    分量的常引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
const T& Vector<T, N>::operator[](size_t Index) const {
    return GetComponent(Index);
}

/**********************************************************************
【函数名称】 operator[]
【函数功能】 通过下标访问分量。
【参数】 
    Index: 要访问的下标。
【返回值】 
    分量的可变引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T& Vector<T, N>::operator[](size_t Index) {
    return GetComponent(Index);
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 反转此向量并存为新的向量。
【参数】 无
【返回值】 
    反转后的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator-() const {
    return Negate();
}

/**********************************************************************
【函数名称】 operator+
【函数功能】 将自身与另一个向量的和存储为新的向量。
【参数】 
    Other: 另一个向量。
【返回值】
    自身与另一向量相加形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& Other) const {
    return Add(Other);
}

/**********************************************************************
【函数名称】 operator+=
【函数功能】 将自身加以另一个向量。
【参数】 
    Other: 另一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& Other) {
    AddInplace(Other);
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 将自身与另一个向量的差存储为新的向量。
【参数】 
    Other: 另一个向量。
【返回值】
    自身与另一向量相减形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector<T, N>& Other) const {
    return Subtract(Other);
}

/**********************************************************************
【函数名称】 operator-=
【函数功能】 将自身减去另一个向量。
【参数】 
    Other: 另一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& Other) {
    SubtractInplace(Other);
}

/**********************************************************************
【函数名称】 operator*
【函数功能】 将自身做数乘。
【参数】 
    Factor: 要数乘的标量。
【返回值】 
    数乘得到的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator*(T Factor) const {
    return Multiply(Factor);
}

/**********************************************************************
【函数名称】 operator*=
【函数功能】 将自身做数乘。
【参数】 
    Factor: 要数乘的标量。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator*=(T Factor) {
    MultiplyInplace(Factor);
    return *this;
}

/**********************************************************************
【函数名称】 operator*
【函数功能】 将自身和另一向量做内积。
【参数】 
    Other: 另一个向量。
【返回值】 与另一向量的内积。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T Vector<T, N>::operator*(const Vector<T, N>& Other) const {
    return InnerProduct(Other);
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身是否和指定的向量相等。
【参数】 
    Other: 要与之判断的向量。
【返回值】 
    自身和指定向量是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::operator==(const Vector<T, N>& Other) const {
    return IsEqual(Other);
}

/**********************************************************************
【函数名称】 operator!=
【函数功能】 判断自身是否和指定的向量不等。
【参数】 
    Other: 要与之判断的向量。
【返回值】 
    自身和指定向量是否不等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::operator!=(const Vector<T, N>& Other) const {
    return !IsEqual(Other);
}

/**********************************************************************
【函数名称】 ToString
【函数功能】 返回此对象的字符串表达形式。
【参数】 无
【返回值】 
    此对象的字符串表达形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
string Vector<T, N>::ToString() const {
    ostringstream Stream;
    Stream << "[";
    for (size_t i = 0; i < N - 1; i++) {
        Stream << m_Components[i] << ", ";
    }
    Stream << m_Components[N-1] << "]";
    return Stream.str();
}

namespace C3w {
    /**********************************************************************
    【函数名称】 operator*
    【函数功能】 将向量与标量数乘。
    【参数】 
        AVector: 要数乘的向量。
        Factor: 要数乘的标量。
    【返回值】 
        数乘形成的新的向量。
    【开发者及日期】 赵一彤 2024/7/24
    **********************************************************************/
    template <typename U, size_t M>
    Vector<U, M> operator*(U Factor, const Vector<U, M>& AVector) {
        return AVector.Multiply(Factor);
    }
}