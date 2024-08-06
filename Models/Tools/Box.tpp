/*************************************************************************
【文件名】 Box.tpp
【功能模块和目的】 为 Box.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <array>
#include <cmath>
#include <cstddef>
#include <limits>
#include "Box.hpp"
#include "../Core/Point.hpp"
#include "../Containers/DynamicSet.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Containers;

namespace C3w {

namespace Tools {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用两个顶点初始化 Box 对象。
【参数】 
    vertex1: 第一个顶点。
    vertex2: 第二个顶点。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Box<N>::Box(const Point<N>& vertex1, const Point<N>& vertex2)
    : Vertex1(vertex1), Vertex2(vertex2) {}

/**********************************************************************
【函数名称】 拷贝构造函数
【函数功能】 使用另一 Box 对象初始化 Box 对象。
【参数】 
    other: 另一 Box 对象。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Box<N>::Box(const Box<N>& other): Box(other.Vertex1, other.Vertex2) {}

/**********************************************************************
【函数名称】 GetBoundingBoxOf
【函数功能】 获取可以容纳所有给定点的最小长方体。
【参数】 
    points: 包含点的集合。
【返回值】
    可以容纳所有给定点的最小长方体。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Box<N> Box<N>::GetBoundingBoxOf(const DynamicSet<Point<N>>& points) {
    if (points.Count() == 0) {
        return Box<N>(Point<N>::Origin, Point<N>::Origin);
    }
    array<double, N> max_coords;
    max_coords.fill(numeric_limits<double>::max());
    array<double, N> min_coords;
    max_coords.fill(numeric_limits<double>::min());
    Point<N> vertex1(max_coords);
    Point<N> vertex2(min_coords);
    for (auto& point: points) {
        for (size_t i = 0; i < N; i++) {
            if (point[i] < vertex1[i]) {
                vertex1[i] = point[i];
            }
            if (point[i] > vertex2[i]) {
                vertex2[i] = point[i];
            }
        }
    }
    return Box<N>(vertex1, vertex2);
}

/**********************************************************************
【函数名称】 GetVolume
【函数功能】 计算自身的体积。
【参数】 无。
【返回值】
    长方体体积。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
double Box<N>::GetVolume() const {
    double volume = 1;
    for (size_t i = 0; i < N; i++) {
        volume *= fabs(Vertex1[i] - Vertex2[i]);
    }
    return volume;
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断自身和另一元素是否相等。
【参数】
    other: 另一元素。
【返回值】
    两元素是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Box<N>::IsEqual(const Box<N>& other) const {
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
template <size_t N>
bool Box<N>::IsEqual(const Box<N>& left, const Box<N>& right) {
    return left.Vertex1 == right.Vertex1 && left.Vertex2 == right.Vertex2;
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身和另一长方体是否相等。
【参数】
    other: 另一长方体。
【返回值】
    两长方体是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Box<N>::operator==(const Box<N>& other) const {
    return IsEqual(other);
}

/**********************************************************************
【函数名称】 operator!=
【函数功能】 判断自身和另一长方体是否相等。
【参数】
    other: 另一长方体。
【返回值】
    两长方体是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Box<N>::operator!=(const Box<N>& other) const {
    return !IsEqual(other);
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将另一长方体赋值给自身。
【参数】
    other: 从之取值的长方体。
【返回值】
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Box<N>& Box<N>::operator=(const Box<N>& other) {
    if (this != &other) {
        Vertex1 = other.Vertex1;
        Vertex2 = other.Vertex2;
    }
    return *this;
}

}

}