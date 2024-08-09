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
    first: 第一个点。
    second: 第二个点。
    third: 第三个点。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Face<N>::Face(
    const Point<N>& first, 
    const Point<N>& second,
    const Point<N>& third
): Element<N, 3>({ first, second, third }) {}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用一个 Element 初始化 Face 对象。
【参数】 
    element: 一个包含三个点的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Face<N>::Face(const Element<N, 3>& element): Element<N, 3>(element) {}

/**********************************************************************
【函数名称】 拷贝构造函数
【函数功能】 使用另一 Face 对象初始化 Face 对象。
【参数】 
    other: 另一个 Face 对象。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Face<N>::Face(const Face<N>& other): Element<N, 3>(other) {}

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
        Point<N>::Distance(this->Points[0], this->Points[1]) +
        Point<N>::Distance(this->Points[1], this->Points[2]) +
        Point<N>::Distance(this->Points[2], this->Points[0])
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
    auto a = Point<N>::Distance(this->Points[0], this->Points[1]);
    auto b = Point<N>::Distance(this->Points[1], this->Points[2]);
    auto c = Point<N>::Distance(this->Points[2], this->Points[0]);
    auto p = (a + b + c) / 2;
    return sqrt((p - a) * (p - b) * (p - c) * p);
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
Face<N>& Face<N>::operator=(const Element<N, 3>& element) {
    if (this != &element) {
        Element<N, 3>::operator=(element);
    }
    return *this;
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将另一面赋值给自身。
【参数】
    other: 从之取值的面。
【返回值】
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Face<N>& Face<N>::operator=(const Face<N>& other) {
    if (this != &other) {
        Element<N, 3>::operator=(other);
    }
    return *this;
}

}