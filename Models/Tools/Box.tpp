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
    Vertex1: 第一个顶点。
    Vertex2: 第二个顶点。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Box<N>::Box(const Point<N>& Vertex1, const Point<N>& Vertex2)
    : Vertex1(Vertex1), Vertex2(Vertex2) {}

/**********************************************************************
【函数名称】 GetBoundingBoxOf
【函数功能】 获取可以容纳所有给定点的最小长方体。
【参数】 
    Points: 包含点的集合。
【返回值】
    可以容纳所有给定点的最小长方体。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Box<N> Box<N>::GetBoundingBoxOf(const DynamicSet<Point<N>>& Points) {
    if (Points.Count() == 0) {
        return Box<N>();
    }
    array<double, N> MaxCoords;
    MaxCoords.fill(numeric_limits<double>::max());
    array<double, N> MinCoords;
    MinCoords.fill(numeric_limits<double>::min());
    Point<N> Vertex1(MaxCoords);
    Point<N> Vertex2(MinCoords);
    for (auto& Point: Points) {
        for (size_t i = 0; i < N; i++) {
            if (Point[i] < Vertex1[i]) {
                Vertex1[i] = Point[i];
            }
            if (Point[i] > Vertex2[i]) {
                Vertex2[i] = Point[i];
            }
        }
    }
    return Box<N>(Vertex1, Vertex2);
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
    double rVolume = 1;
    for (size_t i = 0; i < N; i++) {
        rVolume *= fabs(Vertex1[i] - Vertex2[i]);
    }
    return rVolume;
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
template <size_t N>
bool Box<N>::IsEqual(const Box<N>& Other) const {
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
template <size_t N>
bool Box<N>::IsEqual(const Box<N>& Left, const Box<N>& Right) {
    return Left.Vertex1 == Right.Vertex1 && Left.Vertex2 == Right.Vertex2;
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身和另一长方体是否相等。
【参数】
    Other: 另一长方体。
【返回值】
    两长方体是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Box<N>::operator==(const Box<N>& Other) const {
    return IsEqual(Other);
}

/**********************************************************************
【函数名称】 operator!=
【函数功能】 判断自身和另一长方体是否相等。
【参数】
    Other: 另一长方体。
【返回值】
    两长方体是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
bool Box<N>::operator!=(const Box<N>& Other) const {
    return !IsEqual(Other);
}

}

}