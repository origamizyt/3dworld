/*************************************************************************
【文件名】 CollectionBase.tpp
【功能模块和目的】 为 CollectionBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <sstream>
#include <string>
#include "CollectionBase.hpp"
#include "../Errors/CollectionException.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Errors;

namespace C3w {

namespace Containers {

/**********************************************************************
【函数名称】 Get
【函数功能】 获取指定下标处的元素。如果越界抛出 IndexOverflowException。
【参数】 
    index: 元素下标。
【返回值】 
    指定位置元素的常引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
const T& CollectionBase<T>::Get(size_t index) const {
    if (index >= Count()) {
        throw IndexOverflowException(index, Count());
    }
    return InnerGet(index);
}

/**********************************************************************
【函数名称】 TrySet
【函数功能】 尝试设置指定位置元素的值。如果越界抛出 IndexOverflowException。
【参数】 
    index: 元素下标。
    value: 新的值。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::TrySet(size_t index, const T& value) {
    if (index >= Count()) {
        throw IndexOverflowException(index, Count());
    }
    if (ShouldSet(index, value)) {
        InnerSet(index, value);
        return true;
    }
    else {
        return false;
    }
}

/**********************************************************************
【函数名称】 Set
【函数功能】 
    设置指定位置元素的值。
    如果操作失败抛出 CollectionException。
    如果越界抛出 IndexOverflowException。
【参数】 
    index: 元素下标。
    value: 新的值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void CollectionBase<T>::Set(size_t index, const T& value) {
    if (!TrySet(index, value)) {
        throw CollectionException("Set");
    }
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断自身和另一容器是否相等。
【参数】 
    other: 另一容器。
【返回值】 
    两容器是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::IsEqual(const CollectionBase<T>& other) const {
    return IsEqual(*this, other);
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断两容器是否相等。
【参数】 
    left: 第一个容器。
    right: 第二个容器。
【返回值】 
    两容器是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::IsEqual(
    const CollectionBase<T>& left,
    const CollectionBase<T>& right
) {
    auto count = left.Count();
    if (count != right.Count()) {
        return false;
    }
    for (size_t i = 0; i < count; i++) {
        if (left.InnerGet(i) != right.InnerGet(i)) {
            return false;
        }
    }
    return true;
}

/**********************************************************************
【函数名称】 TryAdd
【函数功能】 尝试添加一个元素。
【参数】 
    element: 新的元素。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::TryAdd(const T& element) {
    if (ShouldAdd(element)) {
        InnerAdd(element);
        return true;
    }
    else {
        return false;
    }
}

/**********************************************************************
【函数名称】 Add
【函数功能】 添加一个元素。如果操作失败抛出 CollectionException。
【参数】 
    element: 新的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void CollectionBase<T>::Add(const T& element) {
    if (!TryAdd(element)) {
        throw CollectionException("Add");
    }
}

/**********************************************************************
【函数名称】 TryRemove
【函数功能】 删除指定位置元素。如果越界抛出 IndexOverflowException。
【参数】 
    index: 元素下标。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::TryRemove(size_t index) {
    if (index >= Count()) {
        throw IndexOverflowException(index, Count());
    }
    if (ShouldRemove(index)) {
        InnerRemove(index);
        return true;
    }
    else {
        return false;
    }
}

/**********************************************************************
【函数名称】 Remove
【函数功能】 
    删除指定位置元素。
    如果操作失败抛出 CollectionException。
    如果越界抛出 IndexOverflowException。
【参数】 
    index: 元素下标。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void CollectionBase<T>::Remove(size_t index) {
    if (!TryRemove(index)) {
        throw CollectionException("Remove");
    }
}

/**********************************************************************
【函数名称】 TryInsert
【函数功能】 将指定元素插入容器。如果越界抛出 IndexOverflowException。
【参数】 
    index: 元素被插入位置的下标。
    element: 新的元素。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::TryInsert(size_t index, const T& element) {
    // index 可以为 Count()，此时与 Add 行为相同
    if (index > Count()) {
        throw IndexOverflowException(index, Count());
    }
    if (ShouldInsert(index, element)) {
        InnerInsert(index, element);
        return true;
    }
    else {
        return false;
    }
}

/**********************************************************************
【函数名称】 Insert
【函数功能】 
    将指定元素插入容器。
    如果操作失败抛出 CollectionException。
    如果越界抛出 IndexOverflowException。
【参数】 
    index: 元素被插入位置的下标。
    element: 新的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void CollectionBase<T>::Insert(size_t index, const T& element) {
    if (!TryInsert(index, element)) {
        throw CollectionException("Insert");
    }
}

/**********************************************************************
【函数名称】 Contains
【函数功能】 判断给定的值是否在容器内。
【参数】 
    element: 要进行判断的值。
【返回值】 
    值是否在容器内。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::Contains(const T& element) const {
    auto count = Count();
    for (size_t i = 0; i < count; i++) {
        if (InnerGet(i) == element) {
            return true;
        }
    }
    return false;
}

/**********************************************************************
【函数名称】 FindIndex
【函数功能】 寻找给定值在容器中的下标。找不到则抛出 CollectionException。
【参数】 
    element: 要寻找的值。
【返回值】 
    容器中的下标。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
size_t CollectionBase<T>::FindIndex(const T& element) const {
    auto count = Count();
    for (size_t i = 0; i < count; i++) {
        if (InnerGet(i) == element) {
            return i;
        }
    }
    throw CollectionException("FindIndex");
}

/**********************************************************************
【函数名称】 operator[]
【函数功能】 获取指定下标处的元素。如果越界抛出 IndexOverflowException。
【参数】 
    index: 元素下标。
【返回值】 
    指定位置元素的常引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
const T& CollectionBase<T>::operator[](size_t index) const {
    return Get(index);
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身和另一容器是否相等。
【参数】 
    other: 另一容器。
【返回值】 
    两容器是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::operator==(const CollectionBase<T>& other) const {
    return IsEqual(other);
}

/**********************************************************************
【函数名称】 operator!=
【函数功能】 判断自身和另一容器是否不等。
【参数】 
    other: 另一容器。
【返回值】 
    两容器是否不等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::operator!=(const CollectionBase<T>& other) const {
    return !IsEqual(other);
}

/**********************************************************************
【函数名称】 ToString
【函数功能】 返回此对象的字符串表达形式。
【参数】 无
【返回值】 
    此对象的字符串表达形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
string CollectionBase<T>::ToString() const {
    if (Count() == 0) {
        return "{}";
    }
    ostringstream stream;
    stream << "{";
    auto count = Count();
    for (size_t i = 0; i < count - 1; i++) {
        stream << InnerGet(i) << ", ";
    }
    stream << InnerGet(count - 1) << "}";
    return stream.str();
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
bool CollectionBase<T>::ShouldSet(size_t index, const T& value) const {
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
bool CollectionBase<T>::ShouldAdd(const T& value) const {
    return true;
}

/**********************************************************************
【函数名称】 ShouldRemove
【函数功能】 判断是否应该删除元素。
【参数】 
    index: 要删除的下标。
【返回值】 
    是否应该删除元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::ShouldRemove(size_t index) const {
    return true;
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
bool CollectionBase<T>::ShouldInsert(size_t index, const T& element) const {
    return true;
}

}

}