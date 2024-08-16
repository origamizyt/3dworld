/*************************************************************************
【文件名】 Element.hpp
【功能模块和目的】 Element 类定义了一个抽象的元素。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <cstddef>
#include <initializer_list>
#include <string>
#include "Point.hpp"
#include "Vector.hpp"
#include "../Containers/FixedSet.hpp"
#include "../Tools/Representable.hpp"
using namespace std;
using namespace C3w::Containers;

namespace C3w {

/*************************************************************************
【类名】 Element
【功能】 定义一个维数 N，点数 S 的抽象元素作为 Line 与 Face 的基类。
【接口说明】 求长度/面积，升维/降维，移动/缩放。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
template <size_t N, size_t S>
class Element: public Tools::Representable {
    public:
        // 成员

        // 元素的维度，与模板中 N 相等。
        static constexpr size_t Dimension { N };
        // 点数量，与模板中 S 相等。
        static constexpr size_t PointCount { S };
        // 点集合。
        FixedSet<Point<N>, S> Points;

        // 构造函数

        // 删除默认构造函数
        Element() = delete;
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用初始化列表初始化 Element 对象。
        【参数】 
            Points: 点构成的初始化列表。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Element(initializer_list<Point<N>> Points);
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用 FixedSet 初始化 Element 对象。
        【参数】 
            Points: 点构成的集合。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        explicit Element(const FixedSet<Point<N>, S>& Points);
        /**********************************************************************
        【函数名称】 拷贝构造函数
        【函数功能】 使用另一 Element 初始化 Element 对象。
        【参数】 
            Other: 另一 Element。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Element(const Element<N, S>& Other) = default;

        // 属性

        /**********************************************************************
        【函数名称】 GetLength
        【函数功能】 求此元素的长度。
        【参数】 无
        【返回值】
            此元素的长度。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual double GetLength() const = 0;
        /**********************************************************************
        【函数名称】 GetArea
        【函数功能】 求此元素的面积。
        【参数】 无
        【返回值】
            此元素的面积。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual double GetArea() const = 0;

        // 操作
        
        /**********************************************************************
        【函数名称】 SetPoint
        【函数功能】 设置指定下标位置的点坐标。
        【参数】 
            Index: 点的位置。
            Value: 新的坐标值。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void SetPoint(size_t Index, const Point<N>& Value);
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
        bool TrySetPoint(size_t Index, const Point<N>& Value);
        /**********************************************************************
        【函数名称】 IsEqual
        【函数功能】 判断自身和另一元素是否相等。
        【参数】
            Other: 另一元素。
        【返回值】
            两元素是否相等。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        bool IsEqual(const Element<N, S>& Other) const;
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
        static bool IsEqual(
            const Element<N, S>& Left, 
            const Element<N, S>& Right
        );
        /**********************************************************************
        【函数名称】 Project
        【函数功能】 将自身投影至 M 维。
        【参数】 无
        【返回值】 一个 M 维的元素。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        template <size_t M>
        Element<M, S> Project() const;
        /**********************************************************************
        【函数名称】 Promote
        【函数功能】 将自身升至 M 维。
        【参数】
            Padder: 可选，填充于高维坐标的数，默认 0。
        【返回值】 一个 M 维的元素。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        template <size_t M>
        Element<M, S> Promote(double Padder = 0) const;
        /**********************************************************************
        【函数名称】 Move
        【函数功能】 将自身向指定方向移动指定长度并存储为新的元素。
        【参数】 
            Delta: 移动的方向和长度。
        【返回值】
            移动后的元素。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Element<N, S> Move(const Vector<double, N>& Delta) const;
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
        static Element<N, S> Move(
            const Element<N, S>& AElement,
            const Vector<double, N>& Delta
        );
        /**********************************************************************
        【函数名称】 MoveInplace
        【函数功能】 将自身向指定方向移动指定长度。
        【参数】 
            Delta: 移动的方向和长度。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void MoveInplace(const Vector<double, N>& Delta) const;
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
        Element<N, S> Scale(const Point<N>& Ref, double Ratio) const;
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
        static Element<N, S> Scale(
            const Element<N, S>& AElement,
            const Point<N>& Ref,
            double Ratio
        );
        /**********************************************************************
        【函数名称】 ScaleInplace
        【函数功能】 将自身以定点为中心缩放。
        【参数】 
            Ref: 参考点。
            Ratio: 缩放的比例。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void ScaleInplace(const Point<N>& Ref, double Ratio);

        // 操作符

        /**********************************************************************
        【函数名称】 operator[]
        【函数功能】 获取元素中指定下标的点。
        【参数】
            Index: 点的下标。
        【返回值】
            在指定下标的点。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        const Point<N>& operator[](size_t Index) const;
        /**********************************************************************
        【函数名称】 operator==
        【函数功能】 判断自身和另一元素是否相等。
        【参数】
            Other: 另一元素。
        【返回值】
            两元素是否相等。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        bool operator==(const Element<N, S>& Other) const;
        /**********************************************************************
        【函数名称】 operator!=
        【函数功能】 判断自身和另一元素是否相等。
        【参数】
            Other: 另一元素。
        【返回值】
            两元素是否相等。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        bool operator!=(const Element<N, S>& Other) const;
        /**********************************************************************
        【函数名称】 operator=
        【函数功能】 将另一元素赋值给自身。
        【参数】
            Other: 从之取值的元素。
        【返回值】
            自身的引用。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Element<N, S>& operator=(const Element<N, S>& Other) = default;

        // 格式化

        /**********************************************************************
        【函数名称】 ToString
        【函数功能】 返回此对象的字符串表达形式。
        【参数】 无
        【返回值】 
            此对象的字符串表达形式。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        string ToString() const override;

        // 虚析构函数
        virtual ~Element() = default;
};

}

#include "Element.tpp"

#endif