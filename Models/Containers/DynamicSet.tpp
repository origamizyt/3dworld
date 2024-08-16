/*************************************************************************
【文件名】 DynamicSet.tpp
【功能模块和目的】 为 DynamicSet.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <vector>
#include "DistinctCollection.hpp"
#include "DynamicSet.hpp"
#include "../Errors/CollectionException.hpp"
using namespace std;
using namespace C3w::Errors;

namespace C3w {

namespace Containers {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用初始化列表初始化 DynamicSet 类型实例。
【参数】
    Elements: 元素初始化列表。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>::DynamicSet(initializer_list<T> Elements) {
    if (
        Elements.size() >= 2 &&
        !this->IsDistinct(Elements.begin(), Elements.end())
    ) {
        throw CollectionException("Construct");
    }
    m_Elements = vector<T>(Elements);
}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用 std::vector<T> 初始化 DynamicSet 类型实例。
【参数】
    Elements: 元素组成的向量。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>::DynamicSet(const vector<T>& Elements) {
    if (
        Elements.size() >= 2 &&
        !this->IsDistinct(Elements.begin(), Elements.end())
    ) {
        throw CollectionException("Construct");
    }
    m_Elements = Elements;
}

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
    Other: 另一集合。
【返回值】 
    两集合的交集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Intersection(const DynamicSet<T>& Other) const {
    return Intersection(*this, Other);
}

/**********************************************************************
【函数名称】 Intersection
【函数功能】 返回两集合的交集。
【参数】 
    Left: 第一个集合。
    Right: 第二个集合。
【返回值】 
    两集合的交集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Intersection(
    const DynamicSet<T>& Left,
    const DynamicSet<T>& Right
) {
    DynamicSet<T> Set;
    for (auto& Element: Left) {
        if (Right.Contains(Element)) {
            // 无需检查，使用 InnerAdd
            Set.InnerAdd(Element);
        }
    }
    return Set;
}

/**********************************************************************
【函数名称】 Union
【函数功能】 返回此集合与另一集合的并集。
【参数】 
    Other: 另一集合。
【返回值】 
    两集合的并集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Union(const DynamicSet<T>& Other) const {
    return Union(*this, Other);
}

/**********************************************************************
【函数名称】 Union
【函数功能】 返回两集合的并集。
【参数】 
    Left: 第一个集合。
    Right: 第二个集合。
【返回值】 
    两集合的并集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Union(
    const DynamicSet<T>& Left,
    const DynamicSet<T>& Right
) {
    DynamicSet<T> Set(Left);
    for (auto& Element: Right) {
        // 使用 TryAdd，忽略返回值
        Set.TryAdd(Element);
    }
    return Set;
}

/**********************************************************************
【函数名称】 Difference
【函数功能】 返回此集合与另一集合的差集。
【参数】 
    Other: 另一集合。
【返回值】 
    两集合的差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Difference(const DynamicSet<T>& Other) const {
    return Difference(*this, Other);
}

/**********************************************************************
【函数名称】 Difference
【函数功能】 返回两集合的差集。
【参数】 
    Left: 第一个集合。
    Right: 第二个集合。
【返回值】 
    两集合的差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::Difference(
    const DynamicSet<T>& Left,
    const DynamicSet<T>& Right
) {
    DynamicSet<T> Set;
    for (auto& Element: Left) {
        if (!Right.Contains(Element)) {
            // 无需检查，使用 InnerAdd
            Set.InnerAdd(Element);
        }
    }
    return Set;
}

/**********************************************************************
【函数名称】 SymmetricDifference
【函数功能】 返回此集合与另一集合的对称差集。
【参数】 
    Other: 另一集合。
【返回值】 
    两集合的对称差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::SymmetricDifference(
    const DynamicSet<T>& Other
) const {
    return SymmetricDifference(*this, Other);
}

/**********************************************************************
【函数名称】 SymmetricDifference
【函数功能】 返回两集合的对称差集。
【参数】 
    Left: 第一个集合。
    Right: 第二个集合。
【返回值】 
    两集合的对称差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::SymmetricDifference(
    const DynamicSet<T>& Left,
    const DynamicSet<T>& Right
) {
    return Union(Difference(Left, Right), Difference(Right, Left));
}

/**********************************************************************
【函数名称】 operator&
【函数功能】 返回此集合与另一集合的交集。
【参数】 
    Other: 另一集合。
【返回值】 
    两集合的交集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator&(const DynamicSet<T>& Other) const {
    return Intersection(Other);
}

/**********************************************************************
【函数名称】 operator&=
【函数功能】 将自身赋值为此集合与另一集合的交集。
【参数】 
    Other: 另一集合。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>& DynamicSet<T>::operator&=(const DynamicSet<T>& Other) {
    *this = Intersection(Other);
    return *this;
}

/**********************************************************************
【函数名称】 operator|
【函数功能】 返回此集合与另一集合的并集。
【参数】 
    Other: 另一集合。
【返回值】 
    两集合的并集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator|(const DynamicSet<T>& Other) const {
    return Union(Other);
}

/**********************************************************************
【函数名称】 operator|=
【函数功能】 将自身赋值为此集合与另一集合的并集。
【参数】 
    Other: 另一集合。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>& DynamicSet<T>::operator|=(const DynamicSet<T>& Other) {
    *this = Union(Other);
    return *this;
}

/**********************************************************************
【函数名称】 operator-
【函数功能】 返回此集合与另一集合的差集。
【参数】 
    Other: 另一集合。
【返回值】 
    两集合的差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator-(const DynamicSet<T>& Other) const {
    return Difference(Other);
}

/**********************************************************************
【函数名称】 operator-=
【函数功能】 将自身赋值为此集合与另一集合的差集。
【参数】 
    Other: 另一集合。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T>& DynamicSet<T>::operator-=(const DynamicSet<T>& Other) {
    *this = Difference(Other);
    return *this;
}

/**********************************************************************
【函数名称】 operator^
【函数功能】 返回此集合与另一集合的对称差集。
【参数】 
    Other: 另一集合。
【返回值】 
    两集合的对称差集。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator^(const DynamicSet<T>& Other) const {
    return SymmetricDifference(Other);
}

/**********************************************************************
【函数名称】 operator^=
【函数功能】 将自身赋值为此集合与另一集合的对称差集。
【参数】 
    Other: 另一集合。
【返回值】 
    自身的引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
DynamicSet<T> DynamicSet<T>::operator^=(const DynamicSet<T>& Other) {
    *this = SymmetricDifference(Other);
    return *this;
}

/**********************************************************************
【函数名称】 InnerGet
【函数功能】 无条件获取元素值。
【参数】 
    Index: 要获取的下标。
【返回值】 
    指定位置元素的常引用。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
const T& DynamicSet<T>::InnerGet(size_t Index) const {
    return m_Elements[Index];
}

/**********************************************************************
【函数名称】 InnerSet
【函数功能】 无条件设置元素值。
【参数】 
    Index: 要设置的下标。
    Value: 要设置的值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void DynamicSet<T>::InnerSet(size_t Index, const T& Value) {
    m_Elements[Index] = Value;
}

/**********************************************************************
【函数名称】 InnerAdd
【函数功能】 无条件添加元素。
【参数】 
    Value: 要添加的值。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void DynamicSet<T>::InnerAdd(const T& Value) {
    m_Elements.push_back(Value);
}

/**********************************************************************
【函数名称】 InnerRemove
【函数功能】 无条件删除元素。
【参数】 
    Index: 要删除的下标。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void DynamicSet<T>::InnerRemove(size_t Index) {
    m_Elements.erase(m_Elements.begin() + Index);
}

/**********************************************************************
【函数名称】 InnerInsert
【函数功能】 无条件插入元素。
【参数】 
    Index: 要插入位置的下标。
    Value: 新的元素。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T>
void DynamicSet<T>::InnerInsert(size_t Index, const T& Value) {
    m_Elements.insert(m_Elements.begin() + Index, Value);
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
    return m_Elements.cend();
}

}

}