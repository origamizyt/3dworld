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
    start: 起始点。
    end: 中止点。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>::Line(const Point<N>& start, const Point<N>& end)
    : Element<N, 2>({ start, end }) {}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用一个 Element 初始化 Line 对象。
【参数】 
    element: 一个包含两个点的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>::Line(const Element<N, 2>& element): Element<N, 2>(element) {}

/**********************************************************************
【函数名称】 拷贝构造函数
【函数功能】 使用另一 Line 对象初始化 Line 对象。
【参数】 
    other: 另一个 Line 对象。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>::Line(const Line<N>& other): Element<N, 2>(other) {}

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
    return Point<N>::Distance(this->Points[0], this->Points[1]);
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
    other: 要与之判断的线段。
【返回值】 
    自身和指定向量是否平行。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Line<N>::IsParallel(const Line<N>& other) const {
    return IsParallel(*this, other);
}

/**********************************************************************
【函数名称】 IsParallel
【函数功能】 判断两个线段是否平行。
【参数】 
    left: 要判断的第一个线段。
    right: 要判断的第二个线段。
【返回值】 
    两个向量是否平行。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Line<N>::IsParallel(
    const Line<N>& left, 
    const Line<N>& right
) {
    return Vector<double, N>::IsParallel(left, right);
}

/**********************************************************************
【函数名称】 IsPerpendicular
【函数功能】 判断自身是否和指定的线段垂直。
【参数】 
    other: 要与之判断的线段。
【返回值】 
    自身和指定线段是否垂直。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Line<N>::IsPerpendicular(const Line<N>& other) const {
    return IsPerpendicular(*this, other);
}

/**********************************************************************
【函数名称】 IsPerpendicular
【函数功能】 判断两个线段是否垂直。
【参数】 
    left: 要判断的第一个线段。
    right: 要判断的第二个线段。
【返回值】 
    两个线段是否垂直。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Line<N>::IsPerpendicular(
    const Line<N>& left,
    const Line<N>& right
) {
    return Vector<double, N>::IsPerpendicular(left, right);
}

/**********************************************************************
【函数名称】 Intersection
【函数功能】 获取自身与另一线段的交点。无交点返回 Point<N>::Void。
【参数】 
    other: 另一个线段。
【返回值】 
    两个线段的交点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Line<N>::Intersection(const Line<N>& other) const {
    return Intersection(*this, other);
}

/**********************************************************************
【函数名称】 Intersection
【函数功能】 获取两线段的交点。无交点返回 Point<N>::Void。
【参数】 
    left: 第一个线段。
    right: 第二个线段。
【返回值】 
    两个线段的交点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Point<N> Line<N>::Intersection(
    const Line<N>& left, 
    const Line<N>& right
) {
    if (IsParallel(left, right)) {
        return Point<N>::Void;
    }
    Vector<double, N> vector1 = left;
    Vector<double, N> vector2 = right;
    Vector<double, N> b = right.Start - left.Start;
    double ratio1 = 0;
    double ratio2 = 0;
    for (size_t i = 1; i < N; i++) {
        double det = vector1[0] * vector2[i] - vector2[0] * vector1[i];
        if (det != 0) {
            ratio1 = 1 / det * (vector2[i] * b[0] - vector2[0] * b[i]);
            ratio2 = 1 / det * (vector1[i] * b[0] - vector1[0] * b[i]);
            break;
        }
    }
    if (
        left.Start + vector1 * ratio1 == right.Start + vector2 * ratio1
        && 0 <= ratio1 && ratio1 <= 1 && 0 <= ratio2 && ratio2 <= 1
    ) {
        return left.Start + vector1 * ratio1;
    }
    else {
        return Point<N>::Void;
    }
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将另一元素赋值给自身。
【参数】
    other: 从之取值的元素。
【返回值】
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>& Line<N>::operator=(const Element<N, 2>& element) {
    if (this != &element) {
        Element<N, 2>::operator=(element);
    }
    return *this;
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将另一线段赋值给自身。
【参数】
    other: 从之取值的线段。
【返回值】
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Line<N>& Line<N>::operator=(const Line<N>& other) {
    if (this != &other) {
        Element<N, 2>::operator=(other);
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