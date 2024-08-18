/*************************************************************************
【文件名】 ControllerBase.cpp
【功能模块和目的】 为 ControllerBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "../Models/Errors/CollectionException.hpp"
#include "../Models/Errors/IndexOverflowException.hpp"
#include "../Models/Errors/FileOpenException.hpp"
#include "../Models/Errors/FileFormatException.hpp"
#include "../Models/Errors/StorageFactoryLookupException.hpp"
#include "../Models/Core/Model.hpp"
#include "../Models/Core/Line.hpp"
#include "../Models/Core/Face.hpp"
#include "../Models/Storage/ImporterBase.hpp"
#include "../Models/Storage/ExporterBase.hpp"
#include "../Models/Storage/StorageFactory.hpp"
#include "ControllerBase.hpp"
using namespace std;
using namespace C3w::Errors;
using namespace C3w::Storage;

namespace C3w {

namespace Controllers {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 创建一个默认的 ControllerBase 类型实例。
【参数】 无
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::ControllerBase(): m_Model("unnamed") {}

/**********************************************************************
【函数名称】 GetName
【函数功能】 获取模型的名称。
【参数】 无
【返回值】 
    模型的名称。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string ControllerBase::GetName() const {
    return m_Model.Name;
}

/**********************************************************************
【函数名称】 SetName
【函数功能】 设置模型的名称。
【参数】 
    Name: 模型的名称。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
void ControllerBase::SetName(string Name) {
    m_Model.Name = Name;
}

/**********************************************************************
【函数名称】 GetLines
【函数功能】 获取所有线段的字符串表达形式。
【参数】 无
【返回值】 
    所有线段的字符串表达形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
vector<ControllerBase::GetElementResult> ControllerBase::GetLines() const {
    vector<GetElementResult> Result;
    for (size_t i = 0; i < m_Model.Lines.Count(); i++) {
        Result.push_back({
            /* .String */ LineToString(m_Model.Lines[i], m_LineStatus[i]),
            /* .ElementStatus */ m_LineStatus[i],
        });
    }
    return Result;
}

/**********************************************************************
【函数名称】 GetLinePoints
【函数功能】 获取指定线段中所有点的字符串表达形式。
【参数】
    Index: 线段的下标。
    Points: 要赋值的向量。
【返回值】 
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::GetLinePoints(
    size_t Index, 
    vector<string>& Points
) const {
    if (Index >= m_Model.Lines.Count()) {
        return Result::INDEX_OVERFLOW;
    }
    for (auto& Point: m_Model.Lines[Index].Points) {
        Points.push_back(PointToString(Point));
    }
    return Result::OK;
}

/**********************************************************************
【函数名称】 AddLine
【函数功能】 添加一个线段。
【参数】
    X1, Y1, Z1: 第一个点的三维坐标。
    X2, Y2, Z2: 第二个点的三维坐标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::AddLine(
    double X1, double Y1, double Z1,
    double X2, double Y2, double Z2
) {
    try {
        if (!m_Model.Lines.TryEmplaceAdd(
            Point<3> { X1, Y1, Z1 },
            Point<3> { X2, Y2, Z2 }
        )) {
            return Result::ELEMENT_COLLISION;
        }
    }
    catch (CollectionException) {
        return Result::POINT_COLLISION;
    }
    m_LineStatus.push_back(Status::CREATED);
    return Result::OK;
}

/**********************************************************************
【函数名称】 ModifyLine
【函数功能】 修改一个线段。
【参数】
    Index: 线段的下标。
    PointIndex: 要修改的点在线段中的下标。
    X, Y, Z: 修改后点的三维坐标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::ModifyLine(
    size_t Index,
    size_t PointIndex,
    double X, double Y, double Z
) {
    try {
        Line<3> ALine(m_Model.Lines[Index]);
        try {
            if (!ALine.TrySetPoint(PointIndex, { X, Y, Z })) {
                return Result::POINT_COLLISION;
            }
        }
        catch (IndexOverflowException) {
            return Result::POINT_INDEX_OVERFLOW;
        }
        if (!m_Model.Lines.TrySet(Index, ALine)) {
            return Result::ELEMENT_COLLISION;
        }
    }
    catch (IndexOverflowException) {
        return Result::INDEX_OVERFLOW;
    }
    m_LineStatus[Index] = Status::MODIFIED;
    return Result::OK;
}

/**********************************************************************
【函数名称】 RemoveLine
【函数功能】 删除一个线段。
【参数】
    Index: 要删除线段的下标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::RemoveLine(size_t Index) {
    try {
        m_Model.Lines.Remove(Index);
    }
    catch (IndexOverflowException) {
        return Result::INDEX_OVERFLOW;
    }
    return Result::OK;
}

/**********************************************************************
【函数名称】 GetFaces
【函数功能】 获取所有面的字符串表达形式。
【参数】 无
【返回值】 
    所有面的字符串表达形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
vector<ControllerBase::GetElementResult> ControllerBase::GetFaces() const {
    vector<GetElementResult> Result;
    for (size_t i = 0; i < m_Model.Faces.Count(); i++) {
        Result.push_back({
            /* .String */  FaceToString(m_Model.Faces[i], m_FaceStatus[i]),
            /* .ElementStatus */  m_FaceStatus[i],
        });
    }
    return Result;
}

/**********************************************************************
【函数名称】 GetLinePoints
【函数功能】 获取指定面中所有点的字符串表达形式。
【参数】
    Index: 面的下标。
    Points: 要赋值的向量。
【返回值】 
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::GetFacePoints(
    size_t Index, 
    vector<string>& Points
) const {
    if (Index >= m_Model.Faces.Count()) {
        return Result::INDEX_OVERFLOW;
    }
    for (auto& Point: m_Model.Faces[Index].Points) {
        Points.push_back(PointToString(Point));
    }
    return Result::OK;
}

/**********************************************************************
【函数名称】 AddFace
【函数功能】 添加一个面。
【参数】
    X1, Y1, Z1: 第一个点的三维坐标。
    X2, Y2, Z2: 第二个点的三维坐标。
    X3, Y3, Z3: 第三个点的三维坐标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::AddFace(
    double X1, double Y1, double Z1,
    double X2, double Y2, double Z2,
    double X3, double Y3, double Z3
) {
    try {
        if (!m_Model.Faces.TryEmplaceAdd(
            Point<3> { X1, Y1, Z1 },
            Point<3> { X2, Y2, Z2 },
            Point<3> { X3, Y3, Z3 }
        )) {
            return Result::ELEMENT_COLLISION;
        }
    }
    catch (CollectionException) {
        return Result::POINT_COLLISION;
    }
    m_FaceStatus.push_back(Status::CREATED);
    return Result::OK;
}

/**********************************************************************
【函数名称】 ModifyFace
【函数功能】 修改一个面。
【参数】
    Index: 面的下标。
    PointIndex: 要修改的点在面中的下标。
    X, Y, Z: 修改后点的三维坐标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::ModifyFace(
    size_t Index,
    size_t PointIndex,
    double X, double Y, double Z
) {
    try {
        Face<3> AFace(m_Model.Faces[Index]);
        try {
            if (!AFace.TrySetPoint(PointIndex, { X, Y, Z })) {
                return Result::POINT_COLLISION;
            }
        }
        catch (IndexOverflowException) {
            return Result::POINT_INDEX_OVERFLOW;
        }
        if (!m_Model.Faces.TrySet(Index, AFace)) {
            return Result::ELEMENT_COLLISION;
        }
    }
    catch (IndexOverflowException) {
        return Result::INDEX_OVERFLOW;
    }
    m_FaceStatus[Index] = Status::MODIFIED;
    return Result::OK;
}

/**********************************************************************
【函数名称】 RemoveFace
【函数功能】 删除一个面。
【参数】
    Index: 要删除面的下标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::RemoveFace(size_t Index) {
    try {
        m_Model.Faces.Remove(Index);
    }
    catch (IndexOverflowException) {
        return Result::INDEX_OVERFLOW;
    }
    return Result::OK;
}

/**********************************************************************
【函数名称】 GetStatistics
【函数功能】 获取统计信息。
【参数】 无
【返回值】
    模型统计信息。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Statistics ControllerBase::GetStatistics() const {
    Statistics Stats {
        /* .TotalPointCount     */  0,
        /* .TotalLineCount      */  m_Model.Lines.Count(), 
        /* .TotalLineLength     */  0,
        /* .TotalFaceCount      */  m_Model.Faces.Count(), 
        /* .TotalFaceArea       */  0,
        /* .BoundingBoxVolume   */  m_Model.GetBoundingBox().GetVolume()
    };
    Stats.TotalPointCount = 
        Stats.TotalLineCount * 2 + Stats.TotalFaceCount * 3;
    for (auto& Line: m_Model.Lines) {
        Stats.TotalLineLength += Line.GetLength();
    }
    for (auto& Face: m_Model.Faces) {
        Stats.TotalFaceArea += Face.GetArea();
    }
    return Stats;
}

/**********************************************************************
【函数名称】 LoadModel
【函数功能】 从文件加载一个模型。
【参数】
    Path: 文件位置。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::LoadModel(string Path) {
    unique_ptr<ImporterBase<3>> pImporter;
    try {
        pImporter = StorageFactory::GetImporter<3>(GetExtension(Path));
    }
    catch (StorageFactoryLookupException) {
        return Result::STORAGE_LOOKUP_ERROR;
    }
    try {
        pImporter->Import(Path, m_Model);
    }
    catch (FileOpenException) {
        return Result::FILE_OPEN_ERROR;
    }
    catch (FileFormatException) {
        return Result::FILE_FORMAT_ERROR;
    }
    m_LineStatus.assign(m_Model.Lines.Count(), Status::UNTOUCHED);
    m_FaceStatus.assign(m_Model.Faces.Count(), Status::UNTOUCHED);
    m_Path = Path;
    return Result::OK;
}

/**********************************************************************
【函数名称】 SaveModel
【函数功能】 向文件保存一个模型。
【参数】
    Path: 文件位置。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::SaveModel(string Path) {
    if (Path.empty()) {
        Path = m_Path;
    }
    unique_ptr<ExporterBase<3>> pExporter;
    try {
        pExporter = StorageFactory::GetExporter<3>(GetExtension(Path));
    }
    catch (StorageFactoryLookupException) {
        return Result::STORAGE_LOOKUP_ERROR;
    }
    try {
        pExporter->Export(Path, m_Model);
    }
    catch (FileOpenException) {
        return Result::FILE_OPEN_ERROR;
    }
    return Result::OK;
}

/**********************************************************************
【函数名称】 GetExtension
【函数功能】 从路径中提取文件扩展名。
【参数】
    Path: 文件路径。
【返回值】
    文件的扩展名。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string ControllerBase::GetExtension(string Path) {
    string Name = Path;
    size_t SlashPosition = Path.find_last_of("/\\");
    if (SlashPosition != string::npos) {
        Name = Path.substr(SlashPosition + 1);
    }
    size_t DotPosition = Name.find_last_of('.');
    if (DotPosition == string::npos) {
        return "";
    }
    else {
        return Name.substr(DotPosition);
    }
}

}

}