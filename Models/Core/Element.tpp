/*************************************************************************
【文件名】 Element.tpp
【功能模块和目的】 为 Element.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <array>
#include <cstddef>
#include <initializer_list>
#include <string>
#include "Element.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "../Containers/FixedSet.hpp"
using namespace std;
using namespace C3w::Containers;

namespace C3w {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用初始化列表初始化 Element 对象。
【参数】 
    points: 点构成的初始化列表。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S>::Element(initializer_list<Point<N>> points): Points(points) {}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用 FixedSet 初始化 Element 对象。
【参数】 
    points: 点构成的集合。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S>::Element(const FixedSet<Point<N>, S>& points): Points(points) {}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断自身和另一元素是否相等。
【参数】
    other: 另一元素。
【返回值】
    两元素是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
bool Element<N, S>::IsEqual(const Element<N, S>& other) const {
    return IsEqual(*this, other);
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断两元素是否相等。
【参数】
    left: 第一个元素。
    right: 第二个元素。
【返回值】
    两元素是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
bool Element<N, S>::IsEqual(
    const Element<N, S>& left, 
    const Element<N, S>& right
) {
    return left.Points == right.Points;
}

/**********************************************************************
【函数名称】 Project
【函数功能】 将自身投影至 M 维。
【参数】 无
【返回值】 一个 M 维的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
template <size_t M>
Element<M, S> Element<N, S>::Project() const {
    array<Point<N>, S> points;
    for (size_t i = 0; i < S; i++) {
        points[i] = Points[i].template Project<M>();
    }
    return Element<M, S>(FixedSet<Point<M>, S>(points));
}

/**********************************************************************
【函数名称】 Promote
【函数功能】 将自身升至 M 维。
【参数】 无
【返回值】 一个 M 维的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
template <size_t M>
Element<M, S> Element<N, S>::Promote(double pad) const {
    array<Point<N>, S> points;
    for (size_t i = 0; i < S; i++) {
        points[i] = Points[i].template Promote<M>(pad);
    }
    return Element<M, S>(FixedSet<Point<M>, S>(points));
}

/**********************************************************************
【函数名称】 Move
【函数功能】 将自身向指定方向移动指定长度并存储为新的元素。
【参数】 
    delta: 移动的方向和长度。
【返回值】
    移动后的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S> Element<N, S>::Move(const Vector<double, N>& delta) const {
    return Move(*this, delta);
}

/**********************************************************************
【函数名称】 Move
【函数功能】 将元素向指定方向移动指定长度。
【参数】 
    element: 要移动的元素。
    delta: 移动的方向和长度。
【返回值】
    移动后的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S> Element<N, S>::Move(
    const Element<N, S>& element,
    const Vector<double, N>& delta
) {
    array<Point<N>, S> points;
    for (size_t i = 0; i < S; i++) {
        points[i] = element.Points[i] + delta;
    }
    return Element<N, S>(FixedSet<Point<N>, S>(points));
}

/**********************************************************************
【函数名称】 MoveInplace
【函数功能】 将自身向指定方向移动指定长度。
【参数】 
    delta: 移动的方向和长度。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
void Element<N, S>::MoveInplace(const Vector<double, N>& delta) const {
    // 不能对 FixedSet 的元素使用 +=
    // 因为 FixedSet::operator[] 只能返回常引用
    *this = Move(*this, delta);
}

/**********************************************************************
【函数名称】 Scale
【函数功能】 将自身以定点为中心缩放并存储为新的元素。
【参数】 
    ref: 参考点。
    ratio: 缩放的比例。
【返回值】
    缩放后的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S> Element<N, S>::Scale(const Point<N>& ref, double ratio) const {
    return Scale(*this, ref, ratio);
}

/**********************************************************************
【函数名称】 Scale
【函数功能】 将元素以定点为中心缩放并存储为新的元素。
【参数】 
    element: 要缩放的元素。
    ref: 参考点。
    ratio: 缩放的比例。
【返回值】
    缩放后的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S> Element<N, S>::Scale(
    const Element<N, S>& element,
    const Point<N>& ref,
    double ratio
) {
    array<Point<N>, S> points;
    for (size_t i = 0; i < S; i++) {
        points[i] = ref + (element.Points[i] - ref) * ratio;
    }
    return Element<N, S>(FixedSet<Point<N>, S>(points));
}

/**********************************************************************
【函数名称】 ScaleInplace
【函数功能】 将自身以定点为中心缩放。
【参数】 
    ref: 参考点。
    ratio: 缩放的比例。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
void Element<N, S>::ScaleInplace(const Point<N>& ref, double ratio) {
    // 不能对 FixedSet 的元素使用 +=
    // 因为 FixedSet::operator[] 只能返回常引用
    *this = Scale(*this, ref, ratio);
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身和另一元素是否相等。
【参数】
    other: 另一元素。
【返回值】
    两元素是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
bool Element<N, S>::operator==(const Element<N, S>& other) const {
    return IsEqual(other);
}

/**********************************************************************
【函数名称】 operator!=
【函数功能】 判断自身和另一元素是否相等。
【参数】
    other: 另一元素。
【返回值】
    两元素是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
bool Element<N, S>::operator!=(const Element<N, S>& other) const {
    return !IsEqual(other);
}

/**********************************************************************
【函数名称】 ToString
【函数功能】 返回此对象的字符串表达形式。
【参数】 无
【返回值】 
    此对象的字符串表达形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
string Element<N, S>::ToString() const {
    return Points.ToString();
}

}