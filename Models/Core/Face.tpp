/*************************************************************************
【文件名】 Face.tpp
【功能模块和目的】 为 Face.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cmath>
#include "Element.hpp"
#include "Face.hpp"
#include "Point.hpp"
using namespace std;

namespace C3w {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用三个点初始化 Face 对象。
【参数】 
    First: 第一个点。
    Second: 第二个点。
    Third: 第三个点。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Face<N>::Face(
    const Point<N>& First, 
    const Point<N>& Second,
    const Point<N>& Third
): Element<N, 3>({ First, Second, Third }) {}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用一个 Element 初始化 Face 对象。
【参数】 
    AElement: 一个包含三个点的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Face<N>::Face(const Element<N, 3>& AElement): Element<N, 3>(AElement) {}

/**********************************************************************
【函数名称】 拷贝构造函数
【函数功能】 使用另一 Face 对象初始化 Face 对象。
【参数】 
    Other: 另一个 Face 对象。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Face<N>::Face(const Face<N>& Other): Element<N, 3>(Other) {}

/**********************************************************************
【函数名称】 GetLength
【函数功能】 求此元素的长度。
【参数】 无
【返回值】
    此元素的长度。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
double Face<N>::GetLength() const {
    return (
        Point<N>::Distance(First, Second) +
        Point<N>::Distance(Second, Third) +
        Point<N>::Distance(Third, First)
    );
}

/**********************************************************************
【函数名称】 GetArea
【函数功能】 求此元素的面积。
【参数】 无
【返回值】
    此元素的面积。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
double Face<N>::GetArea() const {
    double rA = Point<N>::Distance(First, Second);
    double rB = Point<N>::Distance(Second, Third);
    double rC = Point<N>::Distance(Third, First);
    double rP = (rA + rB + rC) / 2;
    return sqrt((rP - rA) * (rP - rB) * (rP - rC) * rP);
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
Face<N>& Face<N>::operator=(const Element<N, 3>& AElement) {
    if (this != &AElement) {
        Element<N, 3>::operator=(AElement);
    }
    return *this;
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将另一面赋值给自身。
【参数】
    Other: 从之取值的面。
【返回值】
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Face<N>& Face<N>::operator=(const Face<N>& Other) {
    if (this != &Other) {
        Element<N, 3>::operator=(Other);
    }
    return *this;
}

}