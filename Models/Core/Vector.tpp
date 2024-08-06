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
#include "Errors.hpp"
#include "Vector.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Errors;

// 零向量。
template <typename T, size_t N>
const Vector<T, N> Vector<T, N>::Zero { Vector<T, N>() };

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用初始化列表初始化 Vector 对象。
【参数】 
    components: 分量构成的初始化列表。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>::Vector(initializer_list<T> components) {
    if (components.size() != N) {
        throw InvalidSizeException();
    }
    copy(components.begin(), components.end(), m_Components.begin());
}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用分量数组初始化 Vector 对象。
【参数】 
    components: 分量构成的数组。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>::Vector(const array<T, N>& components)
    : m_Components(components) {}

/**********************************************************************
【函数名称】 拷贝构造函数
【函数功能】 使用另一 Vector 初始化 Vector 对象。
【参数】 
    other: 另一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>::Vector(const Vector<T, N>& other): Vector(other.m_Components) {}

/**********************************************************************
【函数名称】 GetComponent
【函数功能】 返回指定下标处的分量。
【参数】 
    index: 要获取分量的下标。
【返回值】 
    对指定下标处的分量的常引用。
    如果下标越界，抛出 IndexOverflowException。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
const T& Vector<T, N>::GetComponent(size_t index) const {
    if (index >= N) {
        throw IndexOverflowException();
    }
    return m_Components[index];
}

/**********************************************************************
【函数名称】 GetComponent
【函数功能】 返回指定下标处的分量。
【参数】 
    index: 要获取分量的下标。
【返回值】 
    对指定下标处的分量的可变引用。
    如果下标越界，抛出 IndexOverflowException。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T& Vector<T, N>::GetComponent(size_t index) {
    if (index >= N) {
        throw IndexOverflowException();
    }
    return m_Components[index];
}

/**********************************************************************
【函数名称】 SetComponent
【函数功能】 设置指定下标处的分量。
【参数】 
    index: 要设置分量的下标。
    value: 要设置的分量值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::SetComponent(size_t index, const T& value) {
    if (index >= N) {
        throw IndexOverflowException();
    }
    m_Components[index] = value;
}

/**********************************************************************
【函数名称】 SetAllComponents
【函数功能】 使用数组设置所有分量。
【参数】 
    components: 分量构成的数组。不进行越界检测。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::SetAllComponents(const array<T, N>& components) {
    m_Components = components;
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
    T squareSum = 0;
    for (size_t i = 0; i < N; i++) {
        squareSum += pow(m_Components[i], 2);
    }
    return sqrt(squareSum);
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断自身是否和指定的向量相等。
【参数】 
    other: 要与之判断的向量。
【返回值】 
    自身和指定向量是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::IsEqual(const Vector<T, N>& other) const {
    return IsEqual(*this, other);
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断两个向量是否相等。
【参数】 
    left: 要判断的第一个向量。
    right: 要判断的第二个向量。
【返回值】 
    两个向量是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::IsEqual(
    const Vector<T, N>& left, 
    const Vector<T, N>& right
) {
    for (size_t i = 0; i < N; i++) {
        if (left.m_Components[i] != right.m_Components[i]) {
            return false;
        }
    }
    return true;
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
    vector: 要反转的向量。
【返回值】 
    反转后的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Negate(const Vector<T, N>& vector) {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.m_Components[i] = -vector.m_Components[i];
    }
    return result;
}

/**********************************************************************
【函数名称】 AddInplace
【函数功能】 将自身加以另一个向量。
【参数】 
    other: 另一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::AddInplace(const Vector<T, N>& other) {
    for (size_t i = 0; i < N; i++) {
        m_Components[i] += other.m_Components[i];
    }
}

/**********************************************************************
【函数名称】 Add
【函数功能】 将自身与另一向量相加并存储为新的向量。
【参数】 
    other: 另一向量。
【返回值】 
    两向量相加形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Add(const Vector<T, N>& other) const {
    return Add(*this, other);
}

/**********************************************************************
【函数名称】 Add
【函数功能】 将两个向量相加并存储为新的向量。
【参数】 
    left: 要相加的第一个向量。
    right: 要相加的第二个向量。
【返回值】 
    两向量相加形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Add(
    const Vector<T, N>& left, 
    const Vector<T, N>& right
) {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.m_Components[i] = left.m_Components[i] + right.m_Components[i];
    }
    return result;
}

/**********************************************************************
【函数名称】 SubtractInplace
【函数功能】 将自身减去另一个向量。
【参数】 
    other: 另一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::SubtractInplace(const Vector<T, N>& other) {
    for (size_t i = 0; i < N; i++) {
        m_Components[i] -= other.m_Components[i];
    }
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将自身与另一向量相减并存储为新的向量。
【参数】 
    other: 另一向量。
【返回值】 
    两向量相减形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Subtract(const Vector<T, N>& other) const {
    return Subtract(*this, other);
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将两个向量相减并存储为新的向量。
【参数】 
    left: 要相减的第一个向量。
    right: 要相减的第二个向量。
【返回值】 
    两向量相减形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Subtract(
    const Vector<T, N>& left, 
    const Vector<T, N>& right
) {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.m_Components[i] = left.m_Components[i] - right.m_Components[i];
    }
    return result;
}

/**********************************************************************
【函数名称】 MultiplyInplace
【函数功能】 将自身与标量数乘。
【参数】 
    factor: 要数乘的标量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void Vector<T, N>::MultiplyInplace(T factor) {
    for (auto& component: m_Components) {
        component *= factor;
    }
}

/**********************************************************************
【函数名称】 Multiply
【函数功能】 将自身与标量数乘。
【参数】 
    factor: 要数乘的标量。
【返回值】 
    数乘形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Multiply(T factor) const {
    return Multiply(*this, factor);
}

/**********************************************************************
【函数名称】 Multiply
【函数功能】 将向量与标量数乘。
【参数】 
    vector: 要数乘的向量。
    factor: 要数乘的标量。
【返回值】 
    数乘形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::Multiply(const Vector<T, N> vector, T factor) {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.m_Components[i] = vector.m_Components[i] * factor;
    }
    return result;
}

/**********************************************************************
【函数名称】 InnerProduct
【函数功能】 将自身和另一向量做内积。
【参数】 
    other: 另一个向量。
【返回值】 与另一向量的内积。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T Vector<T, N>::InnerProduct(const Vector<T, N>& other) {
    return InnerProduct(*this, other);
}

/**********************************************************************
【函数名称】 InnerProduct
【函数功能】 将两个向量做内积。
【参数】 
    left: 要做内积的第一个向量。
    right: 要做内积的第二个向量。
【返回值】 
    两向量的内积。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T Vector<T, N>::InnerProduct(
    const Vector<T, N>& left, 
    const Vector<T, N>& right
) {
    T result = 0;
    for (size_t i = 0; i < N; i++) {
        result += (left.m_Components[i] * right.m_Components[i]);
    }
    return result;
}

/**********************************************************************
【函数名称】 operator[]
【函数功能】 通过下标访问分量。
【参数】 
    index: 要访问的下标。
【返回值】 
    分量的常引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
const T& Vector<T, N>::operator[](size_t index) const {
    return GetComponent(index);
}

/**********************************************************************
【函数名称】 operator[]
【函数功能】 通过下标访问分量。
【参数】 
    index: 要访问的下标。
【返回值】 
    分量的可变引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T& Vector<T, N>::operator[](size_t index) {
    return GetComponent(index);
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
    other: 另一个向量。
【返回值】
    自身与另一向量相加形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& other) const {
    return Add(other);
}

/**********************************************************************
【函数名称】 operator+=
【函数功能】 将自身加以另一个向量。
【参数】 
    other: 另一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& other) {
    AddInplace(other);
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 将自身与另一个向量的差存储为新的向量。
【参数】 
    other: 另一个向量。
【返回值】
    自身与另一向量相减形成的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector<T, N>& other) const {
    return Subtract(other);
}

/**********************************************************************
【函数名称】 operator-=
【函数功能】 将自身减去另一个向量。
【参数】 
    other: 另一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& other) {
    SubtractInplace(other);
}

/**********************************************************************
【函数名称】 operator*
【函数功能】 将自身做数乘。
【参数】 
    factor: 要数乘的标量。
【返回值】 
    数乘得到的新的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator*(T factor) const {
    return Multiply(factor);
}

/**********************************************************************
【函数名称】 operator*=
【函数功能】 将自身做数乘。
【参数】 
    factor: 要数乘的标量。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator*=(T factor) {
    MultiplyInplace(factor);
    return *this;
}

/**********************************************************************
【函数名称】 operator*
【函数功能】 将自身和另一向量做内积。
【参数】 
    other: 另一个向量。
【返回值】 与另一向量的内积。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
T Vector<T, N>::operator*(const Vector<T, N>& other) const {
    return InnerProduct(other);
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身是否和指定的向量相等。
【参数】 
    other: 要与之判断的向量。
【返回值】 
    自身和指定向量是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::operator==(const Vector<T, N>& other) const {
    return IsEqual(other);
}

/**********************************************************************
【函数名称】 operator!=
【函数功能】 判断自身是否和指定的向量不等。
【参数】 
    other: 要与之判断的向量。
【返回值】 
    自身和指定向量是否不等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::operator!=(const Vector<T, N>& other) const {
    return !IsEqual(other);
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将其他向量赋值给自身。
【参数】 
    other: 从之取值的向量。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator=(const Vector<T, N>& other) {
    if (this != &other) {
        SetAllComponents(other.m_Components);
    }
    return *this;
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
    ostringstream stream;
    stream << "[";
    for (size_t i = 0; i < N - 1; i++) {
        stream << m_Components[i] << ", ";
    }
    stream << m_Components[N-1] << "]";
    return stream.str();
}

namespace C3w {
    /**********************************************************************
    【函数名称】 operator*
    【函数功能】 将向量与标量数乘。
    【参数】 
        vector: 要数乘的向量。
        factor: 要数乘的标量。
    【返回值】 
        数乘形成的新的向量。
    【开发者及日期】 赵一彤 2024/7/24
    **********************************************************************/
    template <typename U, size_t M>
    Vector<U, M> operator*(U factor, const Vector<U, M>& vector) {
        return vector.Multiply(factor);
    }
}