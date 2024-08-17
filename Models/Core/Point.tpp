/*************************************************************************
【文件名】 Point.tpp
【功能模块和目的】 为 Point.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <array>
#include <cmath>
#include <cstddef>
#include <string>
#include "Point.hpp"
using namespace std;

namespace C3w {

// 原点。
template <size_t N>
const Point<N> Point<N>::Origin { Point<N>() };

// 分量全部为 NaN 的点。
template <size_t N>
const Point<N> Point<N>::Void { Point<N>(nan("")) };

/**********************************************************************
【函数名称】 构造函数
【函数功能】 通过 Vector 初始化 Point 类型实例。
【参数】 
    AVector: 一个向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N>::Point(const Vector<double, N>& AVector): Vector<double, N>(AVector) {}

/**********************************************************************
【函数名称】 Distance
【函数功能】 求两个点之间的直线距离。
【参数】 
    Left: 第一个点。
    Right: 第二个点。
【返回值】
    两点之间的直线距离。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
double Point<N>::Distance(const Point<N>& Left, const Point<N>& Right) {
    return (Left - Right).Module();
}

/**********************************************************************
【函数名称】 Distance
【函数功能】 求自身与另一点之间的直线距离。
【参数】 
    Other: 另一个点。
【返回值】
    两点之间的直线距离。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
double Point<N>::Distance(const Point<N>& Other) const {
    return Distance(*this, Other);
}

/**********************************************************************
【函数名称】 GeneralDistance
【函数功能】 求两个点之间的广义直线距离。
【参数】 
    Left: 第一个点。
    Right: 第二个点。
【返回值】
    两点之间的直线距离。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
template <size_t M>
double Point<N>::GeneralDistance(const Point<N>& Left, const Point<M>& Right) {
    constexpr size_t ullMaxDimension = max(M, N);
    return Point<ullMaxDimension>::Distance(
        Left.template Promote<ullMaxDimension>(),
        Right.template Promote<ullMaxDimension>()
    );
}

/**********************************************************************
【函数名称】 GeneralDistance
【函数功能】 求自身与另一点之间的广义直线距离。
【参数】 
    Other: 另一个点。
【返回值】
    两点之间的直线距离。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
template <size_t M>
double Point<N>::GeneralDistance(const Point<M>& Other) const {
    return GeneralDistance(*this, Other);
}

/**********************************************************************
【函数名称】 IsVoid
【函数功能】 判断自身是否有分量为 NaN。
【参数】 无
【返回值】
    自身是否含有 NaN 分量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Point<N>::IsVoid() const {
    for (size_t i = 0; i < N; i++) {
        if (isnan(this->GetComponent(i))) {
            return true;
        }
    }
    return false;
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
    array<double, M> Components;
    for (size_t i = 0; i < M; i++) {
        Components[i] = this->GetComponent(i);
    }
    return Point<M>(Components);
}

/**********************************************************************
【函数名称】 Promote
【函数功能】 将自身从 N 维升至更高的 M 维。
【参数】 
    Padder: 可选，填充于高维坐标的数，默认 0。
【返回值】
    一个 M 维的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
template <size_t M>
Point<M> Point<N>::Promote(double Padder) const {
    static_assert(M >= N, "Cannot promote to a lower dimension.");
    if (M == N) {
        // 直接返回 *this，节省一次复制
        // 必须强制转换，否则 M != N 时编译不通过
        return *reinterpret_cast<const Point<M>*>(this);
    }
    array<double, M> Components;
    for (size_t i = 0; i < M; i++) {
        if (i < N) {
            Components[i] = this->GetComponent(i);
        }
        else {
            Components[i] = Padder;
        }
    }
    return Point<M>(Components);
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
    APoint: 要反转的点。
【返回值】 
    反转后的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Negate(const Point<N>& APoint) {
    return Point<N>(Vector<double, N>::Negate(APoint));
}

/**********************************************************************
【函数名称】 Add
【函数功能】 将自身与一向量相加并存储为新的点。
【参数】 
    Delta: 相加的向量。
【返回值】 
    点与向量相加形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Add(const Vector<double, N>& Delta) const {
    return Add(*this, Delta);
}

/**********************************************************************
【函数名称】 Add
【函数功能】 将点与一向量相加并存储为新的点。
【参数】 
    APoint: 相加的点
    Delta: 相加的向量。
【返回值】 
    点与向量相加形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Add(
    const Point<N>& APoint, 
    const Vector<double, N>& Delta
) {
    return Point<N>(Vector<double, N>::Add(APoint, Delta));
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将自身与一向量相减并存储为新的点。
【参数】 
    Delta: 相减的向量。
【返回值】 
    点与向量相减形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Subtract(const Vector<double, N>& Delta) const {
    return Subtract(*this, Delta);
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将自身与另一点相减并存储为向量。
【参数】 
    Other: 相减的点。
【返回值】 
    点与点相减形成的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Vector<double, N> Point<N>::Subtract(const Point<N>& Other) const {
    return Subtract(*this, Other);
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将点与一向量相减并存储为新的点。
【参数】 
    APoint: 相减的点。
    Delta: 相减的向量。
【返回值】 
    点与向量相减形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::Subtract(
    const Point<N>& APoint,
    const Vector<double, N>& Delta
) {
    return Point<N>(Vector<double, N>::Subtract(APoint, Delta));
}

/**********************************************************************
【函数名称】 Subtract
【函数功能】 将两点点相减并存储为向量。
【参数】 
    Left: 第一个点。
    Right: 第二个点。
【返回值】 
    点与点相减形成的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Vector<double, N> Point<N>::Subtract(
    const Point<N>& Left,
    const Point<N>& Right
) {
    return Vector<double, N>::Subtract(Left, Right);
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
    Delta: 相加的向量。
【返回值】 
    点与向量相加形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::operator+(const Vector<double, N>& Delta) const {
    return Add(Delta);
}

/**********************************************************************
【函数名称】 operator+=
【函数功能】 将自身与一向量相加。
【参数】 
    Delta: 相加的向量。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N>& Point<N>::operator+=(const Vector<double, N>& Delta) {
    Vector<double, N>::operator+=(Delta);
    return *this;
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 将自身与一向量相减并存储为新的点。
【参数】 
    Delta: 相减的向量。
【返回值】 
    点与向量相减形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Point<N>::operator-(const Vector<double, N>& Delta) const {
    return Subtract(Delta);
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 将自身与另一点相减并存储为向量。
【参数】 
    Other: 相减的点。
【返回值】 
    点与点相减形成的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Vector<double, N> Point<N>::operator-(const Point<N>& Other) const {
    return Subtract(Other);
}

/**********************************************************************
【函数名称】 operator-=
【函数功能】 将自身与一向量相减并存储为新的点。
【参数】 
    Delta: 相减的向量。
【返回值】 
    点与向量相减形成的新的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N>& Point<N>::operator-=(const Vector<double, N>& Delta) {
    Vector<double, N>::operator-=(Delta);
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
    string String = Vector<double, N>::ToString();
    String[0] = '(';
    String[String.size() - 1] = ')';
    return String;
}

}