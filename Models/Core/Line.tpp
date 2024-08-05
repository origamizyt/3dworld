/*************************************************************************
【文件名】 Line.tpp
【功能模块和目的】 为 Line.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include "Element.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "Vector.hpp"
using namespace std;

namespace C3w {

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
    // 终点 - 起点
    return this->Points[1] - this->Points[0];
}

}