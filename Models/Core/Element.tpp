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
    Points: 点构成的初始化列表。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S>::Element(initializer_list<Point<N>> Points): Points(Points) {}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用 FixedSet 初始化 Element 对象。
【参数】 
    Points: 点构成的集合。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S>::Element(const FixedSet<Point<N>, S>& Points): Points(Points) {}

/**********************************************************************
【函数名称】 SetPoint
【函数功能】 设置指定下标位置的点坐标。
【参数】 
    Index: 点的位置。
    Value: 新的坐标值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
void Element<N, S>::SetPoint(size_t Index, const Point<N>& Value) {
    Points.Set(Index, Value);
}

/**********************************************************************
【函数名称】 TrySetPoint
【函数功能】 尝试设置指定下标位置的点坐标。
【参数】 
    Index: 点的位置。
    Value: 新的坐标值。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
bool Element<N, S>::TrySetPoint(size_t Index, const Point<N>& Value) {
    return Points.TrySet(Index, Value);
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断自身和另一元素是否相等。
【参数】
    Other: 另一元素。
【返回值】
    两元素是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
bool Element<N, S>::IsEqual(const Element<N, S>& Other) const {
    return IsEqual(*this, Other);
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断两元素是否相等。
【参数】
    Left: 第一个元素。
    Right: 第二个元素。
【返回值】
    两元素是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
bool Element<N, S>::IsEqual(
    const Element<N, S>& Left, 
    const Element<N, S>& Right
) {
    return Left.Points == Right.Points;
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
    array<Point<N>, S> Points;
    for (size_t i = 0; i < S; i++) {
        Points[i] = Points[i].template Project<M>();
    }
    return Element<M, S>(FixedSet<Point<M>, S>(Points));
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
Element<M, S> Element<N, S>::Promote(double Padder) const {
    array<Point<N>, S> Points;
    for (size_t i = 0; i < S; i++) {
        Points[i] = Points[i].template Promote<M>(Padder);
    }
    return Element<M, S>(FixedSet<Point<M>, S>(Points));
}

/**********************************************************************
【函数名称】 Move
【函数功能】 将自身向指定方向移动指定长度并存储为新的元素。
【参数】 
    Delta: 移动的方向和长度。
【返回值】
    移动后的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S> Element<N, S>::Move(const Vector<double, N>& Delta) const {
    return Move(*this, Delta);
}

/**********************************************************************
【函数名称】 Move
【函数功能】 将元素向指定方向移动指定长度。
【参数】 
    AElement: 要移动的元素。
    Delta: 移动的方向和长度。
【返回值】
    移动后的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S> Element<N, S>::Move(
    const Element<N, S>& AElement,
    const Vector<double, N>& Delta
) {
    array<Point<N>, S> Points;
    for (size_t i = 0; i < S; i++) {
        Points[i] = AElement.Points[i] + Delta;
    }
    return Element<N, S>(FixedSet<Point<N>, S>(Points));
}

/**********************************************************************
【函数名称】 MoveInplace
【函数功能】 将自身向指定方向移动指定长度。
【参数】 
    Delta: 移动的方向和长度。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
void Element<N, S>::MoveInplace(const Vector<double, N>& Delta) const {
    // 不能对 FixedSet 的元素使用 +=
    // 因为 FixedSet::operator[] 只能返回常引用
    *this = Move(*this, Delta);
}

/**********************************************************************
【函数名称】 Scale
【函数功能】 将自身以定点为中心缩放并存储为新的元素。
【参数】 
    Ref: 参考点。
    Ratio: 缩放的比例。
【返回值】
    缩放后的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S> Element<N, S>::Scale(const Point<N>& Ref, double Ratio) const {
    return Scale(*this, Ref, Ratio);
}

/**********************************************************************
【函数名称】 Scale
【函数功能】 将元素以定点为中心缩放并存储为新的元素。
【参数】 
    AElement: 要缩放的元素。
    Ref: 参考点。
    Ratio: 缩放的比例。
【返回值】
    缩放后的元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
Element<N, S> Element<N, S>::Scale(
    const Element<N, S>& AElement,
    const Point<N>& Ref,
    double Ratio
) {
    array<Point<N>, S> Points;
    for (size_t i = 0; i < S; i++) {
        Points[i] = Ref + (AElement.Points[i] - Ref) * Ratio;
    }
    return Element<N, S>(FixedSet<Point<N>, S>(Points));
}

/**********************************************************************
【函数名称】 ScaleInplace
【函数功能】 将自身以定点为中心缩放。
【参数】 
    Ref: 参考点。
    Ratio: 缩放的比例。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
void Element<N, S>::ScaleInplace(const Point<N>& Ref, double Ratio) {
    // 不能对 FixedSet 的元素使用 +=
    // 因为 FixedSet::operator[] 只能返回常引用
    *this = Scale(*this, Ref, Ratio);
}

/**********************************************************************
【函数名称】 operator[]
【函数功能】 获取元素中指定下标的点。
【参数】
    Index: 点的下标。
【返回值】
    在指定下标的点。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
const Point<N>& Element<N, S>::operator[](size_t Index) const {
    return Points[Index];
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身和另一元素是否相等。
【参数】
    Other: 另一元素。
【返回值】
    两元素是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
bool Element<N, S>::operator==(const Element<N, S>& Other) const {
    return IsEqual(Other);
}

/**********************************************************************
【函数名称】 operator!=
【函数功能】 判断自身和另一元素是否相等。
【参数】
    Other: 另一元素。
【返回值】
    两元素是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, size_t S>
bool Element<N, S>::operator!=(const Element<N, S>& Other) const {
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
template <size_t N, size_t S>
string Element<N, S>::ToString() const {
    return Points.ToString();
}

}