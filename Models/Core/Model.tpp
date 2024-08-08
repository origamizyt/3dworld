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
#include "../Containers/DynamicSet.hpp"
#include "../Tools/Box.hpp"
#include "Model.hpp"
using namespace std;
using namespace C3w::Containers;

namespace C3w {

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
【函数名称】 GetBoundingBox
【函数功能】 获取能包含此模型中所有元素的最小长方体。
【参数】 无
【返回值】
    能包含此模型中所有元素的最小长方体。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Tools::Box<N> Model<N>::GetBoundingBox() const {
    return Tools::Box<N>::GetBoundingBoxOf(CollectPoints());
}

}