/*************************************************************************
【文件名】 DistinctCollection.hpp
【功能模块和目的】 DistinctCollection 类定义了一个元素不重复的抽象容器。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#pragma once

#include <cstddef>
#include "CollectionBase.hpp"
using namespace std;

namespace C3w::Containers {

/*************************************************************************
【类名】 DistinctCollection
【功能】 定义一个元素类型为 T 且不可重复的抽象容器。
【接口说明】 获取/设置/添加/删除元素，判断是否包含元素。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
template <typename T>
class DistinctCollection: public CollectionBase<T> {
    public:
        /**********************************************************************
        【函数名称】 IsDistinct
        【函数功能】 判断迭代器中是否无重复元素。
        【参数】 
            begin: 头部迭代器。
            end: 尾部迭代器。
        【返回值】 
            是否没有重复元素。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        template <typename It>
        static bool IsDistinct(It begin, It end);

        // 操作

        /**********************************************************************
        【函数名称】 IsEqualUnordered
        【函数功能】 判断自身与另一容器中元素是否一一对应。
        【参数】 
            other: 另一个容器.
        【返回值】 
            元素是否一一对应。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        bool IsEqualUnordered(const DistinctCollection<T>& other) const;
        /**********************************************************************
        【函数名称】 IsEqualUnordered
        【函数功能】 判断两个容器中元素是否一一对应。
        【参数】 
            left: 第一个容器。
            right: 第二个容器。
        【返回值】 
            元素是否一一对应。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        static bool IsEqualUnordered(
            const DistinctCollection<T>& left,
            const DistinctCollection<T>& right
        );

        // 操作符
        /**********************************************************************
        【函数名称】 operator==
        【函数功能】 判断自身与另一容器中元素是否一一对应。
        【参数】 
            other: 另一个容器.
        【返回值】 
            元素是否一一对应。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        bool operator==(const DistinctCollection<T>& other) const;
        /**********************************************************************
        【函数名称】 operator!=
        【函数功能】 判断两个容器中元素是否一一对应。
        【参数】 
            left: 第一个容器。
            right: 第二个容器。
        【返回值】 
            元素是否一一对应。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        bool operator!=(const DistinctCollection<T>& other) const;
    protected:
        /**********************************************************************
        【函数名称】 ShouldSet
        【函数功能】 判断是否应该设置元素值。
        【参数】 
            index: 要设置的下标。
            value: 要设置的值。
        【返回值】 
            是否应该设置元素。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual bool ShouldSet(size_t index, const T& value) const override;
        /**********************************************************************
        【函数名称】 ShouldAdd
        【函数功能】 判断是否应该添加元素。
        【参数】 
            value: 要添加的值。
        【返回值】 
            是否应该添加元素。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual bool ShouldAdd(const T& value) const override;
};

}

#include "DistinctCollection.tpp"