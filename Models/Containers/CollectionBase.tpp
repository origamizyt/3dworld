/*************************************************************************
【文件名】 CollectionBase.tpp
【功能模块和目的】 为 CollectionBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <sstream>
#include <string>
#include <utility>
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
    Index: 元素下标。
【返回值】 
    指定位置元素的常引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
const T& CollectionBase<T>::Get(size_t Index) const {
    if (Index >= Count()) {
        throw IndexOverflowException(Index, Count());
    }
    return InnerGet(Index);
}

/**********************************************************************
【函数名称】 TrySet
【函数功能】 尝试设置指定位置元素的值。如果越界抛出 IndexOverflowException。
【参数】 
    Index: 元素下标。
    Value: 新的值。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::TrySet(size_t Index, const T& Value) {
    if (Index >= Count()) {
        throw IndexOverflowException(Index, Count());
    }
    if (ShouldSet(Index, Value)) {
        InnerSet(Index, Value);
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
    Index: 元素下标。
    Value: 新的值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void CollectionBase<T>::Set(size_t Index, const T& Value) {
    if (!TrySet(Index, Value)) {
        throw CollectionException("Set");
    }
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断自身和另一容器是否相等。
【参数】 
    Other: 另一容器。
【返回值】 
    两容器是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::IsEqual(const CollectionBase<T>& Other) const {
    return IsEqual(*this, Other);
}

/**********************************************************************
【函数名称】 IsEqual
【函数功能】 判断两容器是否相等。
【参数】 
    Left: 第一个容器。
    Right: 第二个容器。
【返回值】 
    两容器是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::IsEqual(
    const CollectionBase<T>& Left,
    const CollectionBase<T>& Right
) {
    if (Left.Count() != Right.Count()) {
        return false;
    }
    for (size_t i = 0; i < Left.Count(); i++) {
        if (Left.InnerGet(i) != Right.InnerGet(i)) {
            return false;
        }
    }
    return true;
}

/**********************************************************************
【函数名称】 TryAdd
【函数功能】 尝试添加一个元素。
【参数】 
    Value: 新的元素。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::TryAdd(const T& Value) {
    if (ShouldAdd(Value)) {
        InnerAdd(Value);
        return true;
    }
    else {
        return false;
    }
}

/**********************************************************************
【函数名称】 TryEmplaceAdd
【函数功能】 尝试添加一个元素。
【参数】 
    Args: 转给 T 类型构造函数的参数。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
template <typename ...A>
bool CollectionBase<T>::TryEmplaceAdd(A&& ...Args) {
    return TryAdd(T(forward<A>(Args)...));
}

/**********************************************************************
【函数名称】 Add
【函数功能】 添加一个元素。如果操作失败抛出 CollectionException。
【参数】 
    Value: 新的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void CollectionBase<T>::Add(const T& Value) {
    if (!TryAdd(Value)) {
        throw CollectionException("Add");
    }
}

/**********************************************************************
【函数名称】 EmplaceAdd
【函数功能】 添加一个元素。如果操作失败抛出 CollectionException。
【参数】 
    Args: 转给 T 类型构造函数的参数。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
template <typename ...A>
void CollectionBase<T>::EmplaceAdd(A&& ...Args) {
    Add(T(forward<A>(Args)...));
}

/**********************************************************************
【函数名称】 TryRemove
【函数功能】 删除指定位置元素。如果越界抛出 IndexOverflowException。
【参数】 
    Index: 元素下标。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::TryRemove(size_t Index) {
    if (Index >= Count()) {
        throw IndexOverflowException(Index, Count());
    }
    if (ShouldRemove(Index)) {
        InnerRemove(Index);
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
    Index: 元素下标。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void CollectionBase<T>::Remove(size_t Index) {
    if (!TryRemove(Index)) {
        throw CollectionException("Remove");
    }
}

/**********************************************************************
【函数名称】 TryInsert
【函数功能】 将指定元素插入容器。如果越界抛出 IndexOverflowException。
【参数】 
    Index: 元素被插入位置的下标。
    Value: 新的元素。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::TryInsert(size_t Index, const T& Value) {
    // Index 可以为 Count()，此时与 Add 行为相同
    if (Index > Count()) {
        throw IndexOverflowException(Index, Count());
    }
    if (ShouldInsert(Index, Value)) {
        InnerInsert(Index, Value);
        return true;
    }
    else {
        return false;
    }
}

/**********************************************************************
【函数名称】 TryEmplaceInsert
【函数功能】 将指定元素插入容器。如果越界抛出 IndexOverflowException。
【参数】 
    Index: 元素被插入位置的下标。
    Args: 传给 T 类型构造函数的参数。
【返回值】 
    操作是否成功。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
template <typename ...A>
bool CollectionBase<T>::TryEmplaceInsert(size_t Index, A&& ...Args) {
    return TryInsert(Index, T(forward<A>(Args)...));
}

/**********************************************************************
【函数名称】 Insert
【函数功能】 
    将指定元素插入容器。
    如果操作失败抛出 CollectionException。
    如果越界抛出 IndexOverflowException。
【参数】 
    Index: 元素被插入位置的下标。
    Value: 新的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void CollectionBase<T>::Insert(size_t Index, const T& Value) {
    if (!TryInsert(Index, Value)) {
        throw CollectionException("Insert");
    }
}

/**********************************************************************
【函数名称】 Insert
【函数功能】 
    将指定元素插入容器。
    如果操作失败抛出 CollectionException。
    如果越界抛出 IndexOverflowException。
【参数】 
    Index: 元素被插入位置的下标。
    Args: 传给 T 类型构造函数的参数。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
template <typename ...A>
void CollectionBase<T>::EmplaceInsert(size_t Index, A&& ...Args) {
    Insert(Index, T(forward<A>(Args)...));
}

/**********************************************************************
【函数名称】 Contains
【函数功能】 判断给定的值是否在容器内。
【参数】 
    Value: 要进行判断的值。
【返回值】 
    值是否在容器内。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::Contains(const T& Value) const {
    for (size_t i = 0; i < Count(); i++) {
        if (InnerGet(i) == Value) {
            return true;
        }
    }
    return false;
}

/**********************************************************************
【函数名称】 FindIndex
【函数功能】 寻找给定值在容器中的下标。找不到则抛出 CollectionException。
【参数】 
    Value: 要寻找的值。
【返回值】 
    容器中的下标。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
size_t CollectionBase<T>::FindIndex(const T& Value) const {
    for (size_t i = 0; i < Count(); i++) {
        if (InnerGet(i) == Value) {
            return i;
        }
    }
    throw CollectionException("FindIndex");
}

/**********************************************************************
【函数名称】 operator[]
【函数功能】 获取指定下标处的元素。如果越界抛出 IndexOverflowException。
【参数】 
    Index: 元素下标。
【返回值】 
    指定位置元素的常引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
const T& CollectionBase<T>::operator[](size_t Index) const {
    return Get(Index);
}

/**********************************************************************
【函数名称】 operator==
【函数功能】 判断自身和另一容器是否相等。
【参数】 
    Other: 另一容器。
【返回值】 
    两容器是否相等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::operator==(const CollectionBase<T>& Other) const {
    return IsEqual(Other);
}

/**********************************************************************
【函数名称】 operator!=
【函数功能】 判断自身和另一容器是否不等。
【参数】 
    Other: 另一容器。
【返回值】 
    两容器是否不等。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::operator!=(const CollectionBase<T>& Other) const {
    return !IsEqual(Other);
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
    ostringstream Stream;
    Stream << "{";
    for (size_t i = 0; i < Count() - 1; i++) {
        Stream << InnerGet(i) << ", ";
    }
    Stream << InnerGet(Count() - 1) << "}";
    return Stream.str();
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
bool CollectionBase<T>::ShouldSet(size_t Index, const T& Value) const {
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
bool CollectionBase<T>::ShouldAdd(const T& Value) const {
    return true;
}

/**********************************************************************
【函数名称】 ShouldRemove
【函数功能】 判断是否应该删除元素。
【参数】 
    Index: 要删除的下标。
【返回值】 
    是否应该删除元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::ShouldRemove(size_t Index) const {
    return true;
}

/**********************************************************************
【函数名称】 ShouldInsert
【函数功能】 判断是否应该插入元素。
【参数】 
    Index: 要插入位置的下标。
    Value: 新的元素。
【返回值】 
    是否应该插入元素。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
bool CollectionBase<T>::ShouldInsert(size_t Index, const T& Value) const {
    return true;
}

}

}