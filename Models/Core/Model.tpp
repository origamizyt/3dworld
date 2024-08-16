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
    Name: 模型的名称。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Model<N>::Model(string Name): Name(Name) {}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用名称、线段集合与面集合初始化 Model 类型实例。
【参数】
    Name: 模型的名称。
    Lines: 模型中的线集合。
    Faces: 模型中的面集合。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Model<N>::Model(
    string Name, 
    const DynamicSet<Line<N>>& Lines, 
    const DynamicSet<Face<N>>& Faces
): Name(Name), Lines(Lines), Faces(Faces) {}

/**********************************************************************
【函数名称】 Merged
【函数功能】 将两个模型融合为一个。
【参数】
    First: 第一个模型。
    Second: 第二个模型。
    Name: 融合后模型的名称。
【返回值】
    融合后的模型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
Model<N> Model<N>::Merged(
    const Model<N>& First, 
    const Model<N>& Second, 
    string Name
) {
    return Model<N>(
        Name,
        First.Lines | Second.Lines,
        First.Faces | Second.Faces
    );
}

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
    DynamicSet<Point<N>> Points;
    for (auto& Line: Lines) {
        for (auto& point: Line.Points) {
            Points.TryAdd(point);
        }
    }
    for (auto& Face: Faces) {
        for (auto& point: Face.Points) {
            Points.TryAdd(point);
        }
    }
    return Points;
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