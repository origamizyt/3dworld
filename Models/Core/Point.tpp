/*************************************************************************
【文件名】 Point.tpp
【功能模块和目的】 为 Point.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cmath>
#include <cstddef>
#include <string>
#include "Point.hpp"
using namespace std;

namespace C3w {

// 原点。
template <size_t N>
const Point<N> Point<N>::Origin { Point<N>() };

/**********************************************************************
【函数名称】 Distance
【函数功能】 求两个点之间的直线距离。
【参数】 
    left: 第一个点。
    right: 第二个点。
【返回值】
    两点之间的直线距离。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
double Point<N>::Distance(const Point<N>& left, const Point<N>& right) {
    return (left - right).Module();
}

/**********************************************************************
【函数名称】 Distance
【函数功能】 求自身与另一点之间的直线距离。
【参数】 
    other: 另一个点。
【返回值】
    两点之间的直线距离。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
double Point<N>::Distance(const Point<N>& other) const {
    return Distance(*this, other);
}

/**********************************************************************
【函数名称】 GeneralDistance
【函数功能】 求两个点之间的广义直线距离。
【参数】 
    left: 第一个点。
    right: 第二个点。
【返回值】
    两点之间的直线距离。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
template <size_t M>
double Point<N>::GeneralDistance(const Point<N>& left, const Point<M>& right) {
    constexpr size_t D = max(M, N);
    return Point<D>::Distance(
        left.template Promote<D>(),
        right.template Promote<D>()
    );
}

/**********************************************************************
【函数名称】 GeneralDistance
【函数功能】 求自身与另一点之间的广义直线距离。
【参数】 
    other: 另一个点。
【返回值】
    两点之间的直线距离。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
template <size_t M>
double Point<N>::GeneralDistance(const Point<M>& other) const {
    return GeneralDistance(*this, other);
}

/**********************************************************************
【函数名称】 Project
【函数功能】 将自身从 N 维投影至更低的 M 维。
【参数】 无
【返回值】
    一个 M 维的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
template <size_t M>
Point<M> Point<N>::Project() const {
    static_assert(M <= N, "Cannot project to a higher dimension.");
    if (M == N) {
        // 直接返回 *this，节省一次复制
        // 必须强制转换，否则 M != N 时编译不通过
        return *reinterpret_cast<const Point<M>*>(this);
    }
    array<double, M> components;
    for (size_t i = 0; i < M; i++) {
        components[i] = this->GetComponent(i);
    }
    return Point<M>(components);
}

/**********************************************************************
【函数名称】 Promote
【函数功能】 将自身从 N 维升至更高的 M 维。
【参数】 无
【返回值】
    一个 M 维的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
template <size_t M>
Point<M> Point<N>::Promote(double pad) const {
    static_assert(M >= N, "Cannot promote to a lower dimension.");
    if (M == N) {
        // 直接返回 *this，节省一次复制
        // 必须强制转换，否则 M != N 时编译不通过
        return *reinterpret_cast<const Point<M>*>(this);
    }
    array<double, M> components;
    for (size_t i = 0; i < M; i++) {
        if (i < N) {
            components[i] = this->GetComponent(i);
        }
        else {
            components[i] = pad;
        }
    }
    return Point<M>(components);
}

/**********************************************************************
【函数名称】 Negate
【函数功能】 反转此点并存为新的点。
【参数】 无
【返回值】 
    反转后的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Negate() const {
    return Negate(*this);
}

/**********************************************************************
【函数名称】 Negate
【函数功能】 反转给定点并存为新的点。
【参数】 
    point: 要反转的点。
【返回值】 
    反转后的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Negate(const Point<N>& point) {
    return Point<N>(Vector<double, N>::Negate(point));
}

/**********************************************************************
【函数名称】 Add
【函数功能】 将自身与一向量相加并存储为新的点。
【参数】 
    delta: 相加的向量。
【返回值】 
    点与向量相加形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Add(const Vector<double, N>& delta) const {
    return Add(*this, delta);
}

/**********************************************************************
【函数名称】 Add
【函数功能】 将点与一向量相加并存储为新的点。
【参数】 
    point: 相加的点
    delta: 相加的向量。
【返回值】 
    点与向量相加形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Add(
    const Point<N>& point, 
    const Vector<double, N>& delta
) {
    return Point<N>(Vector<double, N>::Add(point, delta));
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将自身与一向量相减并存储为新的点。
【参数】 
    delta: 相减的向量。
【返回值】 
    点与向量相减形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Subtract(const Vector<double, N>& delta) const {
    return Subtract(*this, delta);
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将自身与另一点相减并存储为向量。
【参数】 
    other: 相减的点。
【返回值】 
    点与点相减形成的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Vector<double, N> Point<N>::Subtract(const Point<N>& other) const {
    return Subtract(*this, other);
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将点与一向量相减并存储为新的点。
【参数】 
    point: 相减的点
    delta: 相减的向量。
【返回值】 
    点与向量相减形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Subtract(
    const Point<N>& point,
    const Vector<double, N>& delta
) {
    return Point<N>(Vector<double, N>::Subtract(point, delta));
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将两点点相减并存储为向量。
【参数】 
    left: 第一个点。
    right: 第二个点。
【返回值】 
    点与点相减形成的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Vector<double, N> Point<N>::Subtract(
    const Point<N>& left,
    const Point<N>& right
) {
    return Vector<double, N>::Subtract(left, right);
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 反转此点并存为新的点。
【参数】 无
【返回值】 
    反转后的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::operator-() const {
    return Negate();
}

/**********************************************************************
【函数名称】 operator+
【函数功能】 将自身与一向量相加并存储为新的点。
【参数】 
    delta: 相加的向量。
【返回值】 
    点与向量相加形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::operator+(const Vector<double, N>& delta) const {
    return Add(delta);
}

/**********************************************************************
【函数名称】 operator+=
【函数功能】 将自身与一向量相加。
【参数】 
    delta: 相加的向量。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N>& Point<N>::operator+=(const Vector<double, N>& delta) {
    Vector<double, N>::operator+=(delta);
    return *this;
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 将自身与一向量相减并存储为新的点。
【参数】 
    delta: 相减的向量。
【返回值】 
    点与向量相减形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::operator-(const Vector<double, N>& delta) const {
    return Subtract(delta);
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 将自身与另一点相减并存储为向量。
【参数】 
    other: 相减的点。
【返回值】 
    点与点相减形成的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Vector<double, N> Point<N>::operator-(const Point<N>& other) const {
    return Subtract(other);
}

/**********************************************************************
【函数名称】 operator-=
【函数功能】 将自身与一向量相减并存储为新的点。
【参数】 
    delta: 相减的向量。
【返回值】 
    点与向量相减形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N>& Point<N>::operator-=(const Vector<double, N>& delta) {
    Vector<double, N>::operator-=(delta);
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
template <size_t N>
string Point<N>::ToString() const {
    auto s = Vector<double, N>::ToString();
    s[0] = '(';
    s[s.size() - 1] = ')';
    return s;
}

}