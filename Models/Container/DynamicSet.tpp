/*************************************************************************
【文件名】 DynamicSet.tpp
【功能模块和目的】 为 DynamicSet.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <vector>
#include "DistinctCollection.hpp"
#include "DynamicSet.hpp"
#include "../Core/Errors.hpp"
using namespace std;
using namespace c3w::errors;

namespace c3w::container {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用初始化列表初始化 DynamicSet 类型实例。
【参数】
    elements: 元素初始化列表。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>::DynamicSet(initializer_list<T> elements) {
    if (
        elements.size() >= 2 &&
        !this->IsDistinct(elements.begin(), elements.end())
    ) {
        throw CollectionException();
    }
    m_Elements = vector<T>(elements);
}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用 std::vector<T> 初始化 DynamicSet 类型实例。
【参数】
    elements: 元素组成的向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>::DynamicSet(const vector<T>& elements) {
    if (
        elements.size() >= 2 &&
        !this->IsDistinct(elements.begin(), elements.end())
    ) {
        throw CollectionException();
    }
    m_Elements = elements;
}

/**********************************************************************
【函数名称】 拷贝构造函数
【函数功能】 使用另一 DynamicSet 初始化 DynamicSet 类的实例。
【参数】
    other: 另一 DynamicSet 实例。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>::DynamicSet(const DynamicSet<T>& other)
    : DynamicSet(other.m_Elements) {}

/**********************************************************************
【函数名称】 Count
【函数功能】 获取元素个数。
【参数】 无
【返回值】 
    集合中的元素个数。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
size_t DynamicSet<T>::Count() const {
    return m_Elements.size();
}

/**********************************************************************
【函数名称】 Intersection
【函数功能】 返回此集合与另一集合的交集。
【参数】 
    other: 另一集合。
【返回值】 
    两集合的交集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Intersection(const DynamicSet<T>& other) const {
    return Intersection(*this, other);
}

/**********************************************************************
【函数名称】 Intersection
【函数功能】 返回两集合的交集。
【参数】 
    left: 第一个集合。
    right: 第二个集合。
【返回值】 
    两集合的交集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Intersection(
    const DynamicSet<T>& left,
    const DynamicSet<T>& right
) {
    DynamicSet<T> set;
    for (auto& element: left) {
        if (right.Contains(element)) {
            // 无需检查，使用 InnerAdd
            set.InnerAdd(element);
        }
    }
    return set;
}

/**********************************************************************
【函数名称】 Union
【函数功能】 返回此集合与另一集合的并集。
【参数】 
    other: 另一集合。
【返回值】 
    两集合的并集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Union(const DynamicSet<T>& other) const {
    return Union(*this, other);
}

/**********************************************************************
【函数名称】 Union
【函数功能】 返回两集合的并集。
【参数】 
    left: 第一个集合。
    right: 第二个集合。
【返回值】 
    两集合的并集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Union(
    const DynamicSet<T>& left,
    const DynamicSet<T>& right
) {
    DynamicSet<T> set(left);
    for (auto& element: right) {
        // 使用 TryAdd，忽略返回值
        set.TryAdd(element);
    }
    return set;
}

/**********************************************************************
【函数名称】 Difference
【函数功能】 返回此集合与另一集合的差集。
【参数】 
    other: 另一集合。
【返回值】 
    两集合的差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Difference(const DynamicSet<T>& other) const {
    return Difference(*this, other);
}

/**********************************************************************
【函数名称】 Difference
【函数功能】 返回两集合的差集。
【参数】 
    left: 第一个集合。
    right: 第二个集合。
【返回值】 
    两集合的差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Difference(
    const DynamicSet<T>& left,
    const DynamicSet<T>& right
) {
    DynamicSet<T> set;
    for (auto& element: left) {
        if (!right.Contains(element)) {
            // 无需检查，使用 InnerAdd
            set.InnerAdd(element);
        }
    }
    return set;
}

/**********************************************************************
【函数名称】 SymmetricDifference
【函数功能】 返回此集合与另一集合的对称差集。
【参数】 
    other: 另一集合。
【返回值】 
    两集合的对称差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::SymmetricDifference(
    const DynamicSet<T>& other
) const {
    return SymmetricDifference(*this, other);
}

/**********************************************************************
【函数名称】 SymmetricDifference
【函数功能】 返回两集合的对称差集。
【参数】 
    left: 第一个集合。
    right: 第二个集合。
【返回值】 
    两集合的对称差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::SymmetricDifference(
    const DynamicSet<T>& left,
    const DynamicSet<T>& right
) {
    return Union(Difference(left, right), Difference(right, left));
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
template <typename T>
DynamicSet<T>& DynamicSet<T>::operator=(const DynamicSet<T>& other) {
    if (this != &other) {
        // 使用 std::vector<T> 的赋值运算符
        m_Elements = other.m_Elements;
    }
    return *this;
}

/**********************************************************************
【函数名称】 operator&
【函数功能】 返回此集合与另一集合的交集。
【参数】 
    other: 另一集合。
【返回值】 
    两集合的交集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator&(const DynamicSet<T>& other) const {
    return Intersection(other);
}

/**********************************************************************
【函数名称】 operator&=
【函数功能】 将自身赋值为此集合与另一集合的交集。
【参数】 
    other: 另一集合。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>& DynamicSet<T>::operator&=(const DynamicSet<T>& other) {
    *this = Intersection(other);
    return *this;
}

/**********************************************************************
【函数名称】 operator|
【函数功能】 返回此集合与另一集合的并集。
【参数】 
    other: 另一集合。
【返回值】 
    两集合的并集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator|(const DynamicSet<T>& other) const {
    return Union(other);
}

/**********************************************************************
【函数名称】 operator|=
【函数功能】 将自身赋值为此集合与另一集合的并集。
【参数】 
    other: 另一集合。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>& DynamicSet<T>::operator|=(const DynamicSet<T>& other) {
    *this = Union(other);
    return *this;
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 返回此集合与另一集合的差集。
【参数】 
    other: 另一集合。
【返回值】 
    两集合的差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator-(const DynamicSet<T>& other) const {
    return Difference(other);
}

/**********************************************************************
【函数名称】 operator-=
【函数功能】 将自身赋值为此集合与另一集合的差集。
【参数】 
    other: 另一集合。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>& DynamicSet<T>::operator-=(const DynamicSet<T>& other) {
    *this = Difference(other);
    return *this;
}

/**********************************************************************
【函数名称】 operator^
【函数功能】 返回此集合与另一集合的对称差集。
【参数】 
    other: 另一集合。
【返回值】 
    两集合的对称差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator^(const DynamicSet<T>& other) const {
    return SymmetricDifference(other);
}

/**********************************************************************
【函数名称】 operator^=
【函数功能】 将自身赋值为此集合与另一集合的对称差集。
【参数】 
    other: 另一集合。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator^=(const DynamicSet<T>& other) {
    *this = SymmetricDifference(other);
    return *this;
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
template <typename T>
const T& DynamicSet<T>::InnerGet(size_t index) const {
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
template <typename T>
void DynamicSet<T>::InnerSet(size_t index, const T& value) {
    m_Elements[index] = value;
}

/**********************************************************************
【函数名称】 InnerAdd
【函数功能】 无条件添加元素。
【参数】 
    value: 要添加的值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void DynamicSet<T>::InnerAdd(const T& value) {
    m_Elements.push_back(value);
}

/**********************************************************************
【函数名称】 InnerRemove
【函数功能】 无条件删除元素。
【参数】 
    index: 要删除的下标。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void DynamicSet<T>::InnerRemove(size_t index) {
    m_Elements.erase(m_Elements.begin() + index);
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
template <typename T>
void DynamicSet<T>::InnerInsert(size_t index, const T& element) {
    m_Elements.insert(m_Elements.begin() + index, element);
}

/**********************************************************************
【函数名称】 begin
【函数功能】 获取头部迭代器。
【参数】 无
【返回值】 
    指向首个元素的迭代器。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
typename vector<T>::const_iterator DynamicSet<T>::begin() const {
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
template <typename T>
typename vector<T>::const_iterator DynamicSet<T>::end() const {
    return m_Elements.end();
}

}