/*************************************************************************
【文件名】 Line.tpp
【功能模块和目的】 为 Line.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cmath>
#include "Element.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "Vector.hpp"
using namespace std;

namespace C3w {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用两个点初始化 Line 对象。
【参数】 
    Start: 起始点。
    End: 中止点。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>::Line(const Point<N>& Start, const Point<N>& End)
    : Element<N, 2>({ Start, End }) {}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用一个 Element 初始化 Line 对象。
【参数】 
    AElement: 一个包含两个点的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>::Line(const Element<N, 2>& AElement): Element<N, 2>(AElement) {}

/**********************************************************************
【函数名称】 拷贝构造函数
【函数功能】 使用另一 Line 对象初始化 Line 对象。
【参数】 
    Other: 另一个 Line 对象。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>::Line(const Line<N>& Other): Element<N, 2>(Other) {}

/**********************************************************************
【函数名称】 GetLength
【函数功能】 求此元素的长度。
【参数】 无
【返回值】
    此元素的长度。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
double Line<N>::GetLength() const {
    return Point<N>::Distance(Start, End);
}

/**********************************************************************
【函数名称】 GetArea
【函数功能】 求此元素的面积。由于线段没有面积故恒为 0。
【参数】 无
【返回值】
    此元素的面积。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
double Line<N>::GetArea() const {
    return 0;
}

/**********************************************************************
【函数名称】 IsParallel
【函数功能】 判断自身是否和指定的线段平行。
【参数】 
    Other: 要与之判断的线段。
【返回值】 
    自身和指定向量是否平行。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Line<N>::IsParallel(const Line<N>& Other) const {
    return IsParallel(*this, Other);
}

/**********************************************************************
【函数名称】 IsParallel
【函数功能】 判断两个线段是否平行。
【参数】 
    Left: 要判断的第一个线段。
    Right: 要判断的第二个线段。
【返回值】 
    两个向量是否平行。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Line<N>::IsParallel(
    const Line<N>& Left, 
    const Line<N>& Right
) {
    return Vector<double, N>::IsParallel(Left, Right);
}

/**********************************************************************
【函数名称】 IsPerpendicular
【函数功能】 判断自身是否和指定的线段垂直。
【参数】 
    Other: 要与之判断的线段。
【返回值】 
    自身和指定线段是否垂直。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Line<N>::IsPerpendicular(const Line<N>& Other) const {
    return IsPerpendicular(*this, Other);
}

/**********************************************************************
【函数名称】 IsPerpendicular
【函数功能】 判断两个线段是否垂直。
【参数】 
    Left: 要判断的第一个线段。
    Right: 要判断的第二个线段。
【返回值】 
    两个线段是否垂直。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Line<N>::IsPerpendicular(
    const Line<N>& Left,
    const Line<N>& Right
) {
    return Vector<double, N>::IsPerpendicular(Left, Right);
}

/**********************************************************************
【函数名称】 Intersection
【函数功能】 获取自身与另一线段的交点。无交点返回 Point<N>::Void。
【参数】 
    Other: 另一个线段。
【返回值】 
    两个线段的交点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Line<N>::Intersection(const Line<N>& Other) const {
    return Intersection(*this, Other);
}

/**********************************************************************
【函数名称】 Intersection
【函数功能】 获取两线段的交点。无交点返回 Point<N>::Void。
【参数】 
    Left: 第一个线段。
    Right: 第二个线段。
【返回值】 
    两个线段的交点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Line<N>::Intersection(
    const Line<N>& Left, 
    const Line<N>& Right
) {
    if (IsParallel(Left, Right)) {
        return Point<N>::Void;
    }
    // 矩阵 A = (Vec1 | Vec2)
    Vector<double, N> Vec1 = Left;
    Vector<double, N> Vec2 = Right;
    // 方程 Ax = b 中的 b 向量
    Vector<double, N> Coef = Right.Start - Left.Start;
    // 向量 x = (rRatio1 rRatio2)^T
    double rRatio1 = 0;
    double rRatio2 = 0;
    for (size_t i = 1; i < N; i++) {
        double rDet = Vec1[0] * Vec2[i] - Vec2[0] * Vec1[i];
        if (rDet != 0) {
            rRatio1 = 1 / rDet * (Vec2[i] * Coef[0] - Vec2[0] * Coef[i]);
            rRatio2 = 1 / rDet * (Vec1[i] * Coef[0] - Vec1[0] * Coef[i]);
            break;
        }
    }
    if (
        Left.Start + Vec1 * rRatio1 == Right.Start + Vec2 * rRatio1
        && 0 <= rRatio1 && rRatio1 <= 1 && 0 <= rRatio2 && rRatio2 <= 1
    ) {
        return Left.Start + Vec1 * rRatio1;
    }
    else {
        return Point<N>::Void;
    }
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将另一元素赋值给自身。
【参数】
    AElement: 从之取值的元素。
【返回值】
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>& Line<N>::operator=(const Element<N, 2>& AElement) {
    if (this != &AElement) {
        Element<N, 2>::operator=(AElement);
    }
    return *this;
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将另一线段赋值给自身。
【参数】
    Other: 从之取值的线段。
【返回值】
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>& Line<N>::operator=(const Line<N>& Other) {
    if (this != &Other) {
        Element<N, 2>::operator=(Other);
    }
    return *this;
}

/**********************************************************************
【函数名称】 operator Vector<double, N>
【函数功能】 将自身转化为向量。
【参数】 无
【返回值】
    从起点指向终点的向量。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>::operator Vector<double, N>() const {
    return End - Start;
}

}