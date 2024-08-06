/*************************************************************************
【文件名】 DistinctCollection.tpp
【功能模块和目的】 为 DistinctCollection.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include "CollectionBase.hpp"
#include "DistinctCollection.hpp"
using namespace std;

namespace C3w::Containers {

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
template <typename T>
template <typename It>
bool DistinctCollection<T>::IsDistinct(It begin, It end) {
    for (auto i = begin; i < end - 1; i++) {
        for (auto j = i + 1; j < end; j++) {
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
    other: 另一个容器.
【返回值】 
    元素是否一一对应。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::IsEqualUnordered(
    const DistinctCollection<T>& other
) const {
    return IsEqualUnordered(*this, other);
}

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
template <typename T>
bool DistinctCollection<T>::IsEqualUnordered(
    const DistinctCollection<T>& left,
    const DistinctCollection<T>& right
) {
    if (left.Count() != right.Count()) {
        return false;
    }
    for (size_t i = 0; i < left.Count(); i++) {
        if (!right.Contains(left.InnerGet(i))) {
            return false;
        }
    }
    return true;
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身与另一容器中元素是否一一对应。
【参数】 
    other: 另一个容器.
【返回值】 
    元素是否一一对应。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::operator==(
    const DistinctCollection<T>& other
) const {
    return IsEqualUnordered(other);
}

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
template <typename T>
bool DistinctCollection<T>::operator!=(
    const DistinctCollection<T>& other
) const {
    return !IsEqualUnordered(other);
}

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
template <typename T>
bool DistinctCollection<T>::ShouldSet(size_t index, const T& value) const {
    auto count = this->Count();
    for (size_t i = 0; i < count; i++) {
        if (index == i) {
            continue;
        }
        if (this->InnerGet(i) == value) {
            return false;
        }
    }
    return true;
}

/**********************************************************************
【函数名称】 ShouldAdd
【函数功能】 判断是否应该添加元素。
【参数】 
    value: 要添加的值。
【返回值】 
    是否应该添加元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::ShouldAdd(const T& value) const {
    return !this->Contains(value);
}

/**********************************************************************
【函数名称】 ShouldInsert
【函数功能】 判断是否应该插入元素。
【参数】 
    index: 要插入位置的下标。
    element: 新的元素。
【返回值】 
    是否应该插入元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool DistinctCollection<T>::ShouldInsert(size_t index, const T& value) const {
    return !this->Contains(value);
}

}