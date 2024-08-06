/*************************************************************************
【文件名】 FixedSet.tpp
【功能模块和目的】 为 FixedSet.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <vector>
#include "DistinctCollection.hpp"
#include "DynamicSet.hpp"
#include "FixedSet.hpp"
#include "../Core/Errors.hpp"
using namespace std;
using namespace C3w::Errors;

namespace C3w {

namespace Containers {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用初始化列表初始化 FixedSet 类型实例。
【参数】
    elements: 元素初始化列表。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
FixedSet<T, N>::FixedSet(initializer_list<T> elements) {
    if (elements.size() != N) {
        throw InvalidSizeException();
    }
    if (
        N >= 2 &&
        !this->IsDistinct(elements.begin(), elements.end())
    ) {
        throw CollectionException();
    }
    copy(elements.begin(), elements.end(), m_Elements.begin());
}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用 std::array<T, N> 初始化 FixedSet 类型实例。
【参数】
    elements: 元素组成的数组。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
FixedSet<T, N>::FixedSet(const array<T, N>& elements) {
    if (
        N >= 2 &&
        !this->IsDistinct(elements.begin(), elements.end())
    ) {
        throw CollectionException();
    }
    m_Elements = elements;
}

/**********************************************************************
【函数名称】 拷贝构造函数
【函数功能】 使用另一 FixedSet 初始化 FixedSet 类的实例。
【参数】
    other: 另一 FixedSet 实例。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
FixedSet<T, N>::FixedSet(const FixedSet<T, N>& other)
    : FixedSet(other.m_Elements) {}

/**********************************************************************
【函数名称】 Count
【函数功能】 获取元素个数。
【参数】 无
【返回值】 
    容器中的元素个数。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
size_t FixedSet<T, N>::Count() const {
    return N;
}

/**********************************************************************
【函数名称】 ToDynamic
【函数功能】 将自身转化为 DynamicSet。
【参数】 无
【返回值】 
    转化后的对象。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
DynamicSet<T> FixedSet<T, N>::ToDynamic() const {
    return DynamicSet<T>(vector<T>(begin(), end()));
}

/**********************************************************************
【函数名称】 operator=
【函数功能】 将其他集合赋值给自身。
【参数】 
    other: 从之取值的集合。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
FixedSet<T, N>& FixedSet<T, N>::operator=(const FixedSet<T, N>& other) {
    if (this != &other) {
        // 使用 std::array 的赋值运算符
        m_Elements = other.m_Elements;
    }
    return *this;
}

/**********************************************************************
【函数名称】 operator DynamicSet<T>
【函数功能】 将自身转化为 DynamicSet。
【参数】 无
【返回值】 
    转化后的对象。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
FixedSet<T, N>::operator DynamicSet<T>() const {
    return ToDynamic();
}

/**********************************************************************
【函数名称】 begin
【函数功能】 获取头部迭代器。
【参数】 无
【返回值】 
    指向首个元素的迭代器。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
typename array<T, N>::const_iterator FixedSet<T, N>::begin() const {
    return m_Elements.cbegin();
}

/**********************************************************************
【函数名称】 begin
【函数功能】 获取尾部迭代器。
【参数】 无
【返回值】 
    指向最后元素之后的迭代器。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
typename array<T, N>::const_iterator FixedSet<T, N>::end() const {
    return m_Elements.cend();
}

/**********************************************************************
【函数名称】 InnerGet
【函数功能】 无条件获取元素值。
【参数】 
    index: 要获取的下标。
【返回值】 
    指定位置元素的常引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
const T& FixedSet<T, N>::InnerGet(size_t index) const {
    return m_Elements[index];
}

/**********************************************************************
【函数名称】 InnerSet
【函数功能】 无条件设置元素值。
【参数】 
    index: 要设置的下标。
    value: 要设置的值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void FixedSet<T, N>::InnerSet(size_t index, const T& value) {
    m_Elements[index] = value;
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
template <typename T, size_t N>
bool FixedSet<T, N>::ShouldAdd(const T& value) const {
    return false;
}

/**********************************************************************
【函数名称】 InnerAdd
【函数功能】 无条件添加元素。
【参数】 
    value: 要添加的值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void FixedSet<T, N>::InnerAdd(const T& value) {
    throw CollectionException();
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
template <typename T, size_t N>
bool FixedSet<T, N>::ShouldRemove(size_t index) const {
    return false;
}

/**********************************************************************
【函数名称】 InnerRemove
【函数功能】 无条件删除元素。
【参数】 
    index: 要删除的下标。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void FixedSet<T, N>::InnerRemove(size_t index) {
    throw CollectionException();
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
template <typename T, size_t N>
bool FixedSet<T, N>::ShouldInsert(size_t index, const T& element) const {
    return false;
}

/**********************************************************************
【函数名称】 InnerInsert
【函数功能】 无条件插入元素。
【参数】 
    index: 要插入位置的下标。
    element: 新的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, size_t N>
void FixedSet<T, N>::InnerInsert(size_t index, const T& element) {
    throw CollectionException();
}

}

}