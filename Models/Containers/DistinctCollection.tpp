/*************************************************************************
【文件名】 DistinctCollection.tpp
【功能模块和目的】 为 DistinctCollection.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include "CollectionBase.hpp"
#include "DistinctCollection.hpp"
using namespace std;

namespace C3w {

namespace Containers {

/**********************************************************************
【函数名称】 IsDistinct
【函数功能】 判断迭代器中是否无重复元素。
【参数】 
    Begin: 头部迭代器。
    End: 尾部迭代器。
【返回值】 
    是否没有重复元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
template <typename It>
bool DistinctCollection<T>::IsDistinct(It Begin, It End) {
    for (auto i = Begin; i < End - 1; i++) {
        for (auto j = i + 1; j < End; j++) {
            if (*i == *j) {
                return false;
            }
        }
    }
    return true;
}

/**********************************************************************
【函数名称】 IsEqualUnordered
【函数功能】 判断自身与另一容器中元素是否一一对应。
【参数】 
    Other: 另一个容器.
【返回值】 
    元素是否一一对应。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::IsEqualUnordered(
    const DistinctCollection<T>& Other
) const {
    return IsEqualUnordered(*this, Other);
}

/**********************************************************************
【函数名称】 IsEqualUnordered
【函数功能】 判断两个容器中元素是否一一对应。
【参数】 
    Left: 第一个容器。
    Right: 第二个容器。
【返回值】 
    元素是否一一对应。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::IsEqualUnordered(
    const DistinctCollection<T>& Left,
    const DistinctCollection<T>& Right
) {
    if (Left.Count() != Right.Count()) {
        return false;
    }
    auto Count = Left.Count();
    for (size_t i = 0; i < Count; i++) {
        if (!Right.Contains(Left.InnerGet(i))) {
            return false;
        }
    }
    return true;
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身与另一容器中元素是否一一对应。
【参数】 
    Other: 另一个容器.
【返回值】 
    元素是否一一对应。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::operator==(
    const DistinctCollection<T>& Other
) const {
    return IsEqualUnordered(Other);
}

/**********************************************************************
【函数名称】 operator!=
【函数功能】 判断两个容器中元素是否一一对应。
【参数】 
    Left: 第一个容器。
    Right: 第二个容器。
【返回值】 
    元素是否一一对应。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::operator!=(
    const DistinctCollection<T>& Other
) const {
    return !IsEqualUnordered(Other);
}

/**********************************************************************
【函数名称】 ShouldSet
【函数功能】 判断是否应该设置元素值。
【参数】 
    Index: 要设置的下标。
    Value: 要设置的值。
【返回值】 
    是否应该设置元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::ShouldSet(size_t Index, const T& Value) const {
    auto Count = this->Count();
    for (size_t i = 0; i < Count; i++) {
        if (Index == i) {
            continue;
        }
        if (this->InnerGet(i) == Value) {
            return false;
        }
    }
    return true;
}

/**********************************************************************
【函数名称】 ShouldAdd
【函数功能】 判断是否应该添加元素。
【参数】 
    Value: 要添加的值。
【返回值】 
    是否应该添加元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::ShouldAdd(const T& Value) const {
    return !this->Contains(Value);
}

/**********************************************************************
【函数名称】 ShouldInsert
【函数功能】 判断是否应该插入元素。
【参数】 
    Index: 要插入位置的下标。
    element: 新的元素。
【返回值】 
    是否应该插入元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::ShouldInsert(size_t Index, const T& Value) const {
    return !this->Contains(Value);
}

}

}