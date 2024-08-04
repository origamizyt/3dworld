/*************************************************************************
【文件名】 Model.tpp
【功能模块和目的】 为 Model.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <string>
#include "Face.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "../Container/DynamicSet.hpp"
#include "../Tools/Box.hpp"
#include "Model.hpp"
using namespace std;
using namespace c3w::container;

namespace c3w {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用名称初始化 DynamicSet 类型实例。
【参数】
    name: 模型的名称。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Model<N>::Model(string name): Name(name) {}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用名称、线段集合与面集合初始化 Model 类型实例。
【参数】
    name: 模型的名称。
    lines: 模型中的线集合。
    faces: 模型中的面集合。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Model<N>::Model(
    string name, 
    const DynamicSet<Line<N>>& lines, 
    const DynamicSet<Face<N>>& faces
): Name(name), Lines(lines), Faces(faces) {}

/**********************************************************************
【函数名称】 拷贝构造函数
【函数功能】 使用另一 Model 对象初始化 Model 类型实例。
【参数】
    other: 另一 Model 对象。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Model<N>::Model(const Model<N>& other)
    : Model(other.Name, other.Lines, other.Faces) {}

/**********************************************************************
【函数名称】 CollectPoints
【函数功能】 收集模型中所有元素的点。
【参数】 无
【返回值】
    包含模型中所有点的集合。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
DynamicSet<Point<N>> Model<N>::CollectPoints() const {
    DynamicSet<Point<N>> points;
    for (auto& line: Lines) {
        for (auto& point: line.Points) {
            points.TryAdd(point);
        }
    }
    for (auto& face: Faces) {
        for (auto& point: face.Points) {
            points.TryAdd(point);
        }
    }
    return points;
}

/**********************************************************************
【函数名称】 BoundingBox
【函数功能】 获取能包含此模型中所有元素的最小长方体。
【参数】 无
【返回值】
    能包含此模型中所有元素的最小长方体。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
tools::Box<N> Model<N>::BoundingBox() const {
    return tools::Box<N>::BoundingBoxOf(CollectPoints());
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将其他模型赋值给自身。
【参数】 
    other: 从之取值的模型。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Model<N>& Model<N>::operator=(const Model<N>& other) {
    if (this != &other) {
        Name = other.Name;
        Lines = other.Lines;
        Faces = other.Faces;
    }
    return *this;
}

}