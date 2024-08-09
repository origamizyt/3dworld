/*************************************************************************
【文件名】 ControllerBase.cpp
【功能模块和目的】 为 ControllerBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "../Models/Core/Errors.hpp"
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
【函数名称】 GetLines
【函数功能】 获取所有线段的字符串表达形式。
【参数】 无
【返回值】 
    所有线段的字符串表达形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
vector<ControllerBase::GetElementResult> ControllerBase::GetLines() const {
    vector<GetElementResult> result;
    for (size_t i = 0; i < m_Model.Lines.Count(); i++) {
        result.push_back({
            /* .String */ LineToString(m_Model.Lines[i], m_LineStatus[i]),
            /* .ElementStatus */ m_LineStatus[i],
        });
    }
    return result;
}

/**********************************************************************
【函数名称】 GetLinePoints
【函数功能】 获取指定线段中所有点的字符串表达形式。
【参数】
    index: 线段的下标。
    points: 要赋值的向量。
【返回值】 
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::GetLinePoints(
    size_t index, 
    vector<string>& points
) const {
    if (index >= m_Model.Lines.Count()) {
        return Result::INDEX_OVERFLOW;
    }
    for (auto& point: m_Model.Lines[index].Points) {
        points.push_back(PointToString(point));
    }
    return Result::OK;
}

/**********************************************************************
【函数名称】 AddLine
【函数功能】 添加一个线段。
【参数】
    x1, y1, z1: 第一个点的三维坐标。
    x2, y2, z2: 第二个点的三维坐标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::AddLine(
    double x1, double y1, double z1,
    double x2, double y2, double z2
) {
    try {
        Line<3> line { { x1, y1, z1 }, { x2, y2, z2 } };
        if (!m_Model.Lines.TryAdd(line)) {
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
    index: 线段的下标。
    pointIndex: 要修改的点在线段中的下标。
    x, y, z: 修改后点的三维坐标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::ModifyLine(
    size_t index,
    size_t pointIndex,
    double x, double y, double z
) {
    try {
        Line<3> line(m_Model.Lines[index]);
        try {
            if (!line.Points.TrySet(pointIndex, { x, y, z })) {
                return Result::POINT_COLLISION;
            }
        }
        catch (IndexOverflowException) {
            return Result::POINT_INDEX_OVERFLOW;
        }
        if (!m_Model.Lines.TrySet(index, line)) {
            return Result::ELEMENT_COLLISION;
        }
    }
    catch (IndexOverflowException) {
        return Result::INDEX_OVERFLOW;
    }
    m_LineStatus[index] = Status::MODIFIED;
    return Result::OK;
}

/**********************************************************************
【函数名称】 RemoveLine
【函数功能】 删除一个线段。
【参数】
    index: 要删除线段的下标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::RemoveLine(size_t index) {
    try {
        m_Model.Lines.Remove(index);
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
    vector<GetElementResult> result;
    for (size_t i = 0; i < m_Model.Faces.Count(); i++) {
        result.push_back({
            /* .String */  FaceToString(m_Model.Faces[i], m_FaceStatus[i]),
            /* .ElementStatus */  m_FaceStatus[i],
        });
    }
    return result;
}

/**********************************************************************
【函数名称】 GetLinePoints
【函数功能】 获取指定面中所有点的字符串表达形式。
【参数】
    index: 面的下标。
    points: 要赋值的向量。
【返回值】 
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::GetFacePoints(
    size_t index, 
    vector<string>& points
) const {
    if (index >= m_Model.Faces.Count()) {
        return Result::INDEX_OVERFLOW;
    }
    for (auto& point: m_Model.Faces[index].Points) {
        points.push_back(PointToString(point));
    }
    return Result::OK;
}

/**********************************************************************
【函数名称】 AddFace
【函数功能】 添加一个面。
【参数】
    x1, y1, z1: 第一个点的三维坐标。
    x2, y2, z2: 第二个点的三维坐标。
    x3, y3, z3: 第三个点的三维坐标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::AddFace(
    double x1, double y1, double z1,
    double x2, double y2, double z2,
    double x3, double y3, double z3
) {
    try {
        Face<3> face { { x1, y1, z1 }, { x2, y2, z2 }, { x3, y3, z3 } };
        if (!m_Model.Faces.TryAdd(face)) {
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
    index: 面的下标。
    pointIndex: 要修改的点在面中的下标。
    x, y, z: 修改后点的三维坐标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::ModifyFace(
    size_t index,
    size_t pointIndex,
    double x, double y, double z
) {
    try {
        Face<3> face(m_Model.Faces[index]);
        try {
            if (!face.Points.TrySet(pointIndex, { x, y, z })) {
                return Result::POINT_COLLISION;
            }
        }
        catch (IndexOverflowException) {
            return Result::POINT_INDEX_OVERFLOW;
        }
        if (!m_Model.Faces.TrySet(index, face)) {
            return Result::ELEMENT_COLLISION;
        }
    }
    catch (IndexOverflowException) {
        return Result::INDEX_OVERFLOW;
    }
    m_FaceStatus[index] = Status::MODIFIED;
    return Result::OK;
}

/**********************************************************************
【函数名称】 RemoveFace
【函数功能】 删除一个面。
【参数】
    index: 要删除面的下标。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::RemoveFace(size_t index) {
    try {
        m_Model.Faces.Remove(index);
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
    Statistics stats {
        /* .TotalPointCount     */  0,
        /* .TotalLineCount      */  m_Model.Lines.Count(), 
        /* .TotalLineLength     */  0,
        /* .TotalFaceCount      */  m_Model.Faces.Count(), 
        /* .TotalFaceArea       */  0,
        /* .BoundingBoxVolume   */  m_Model.GetBoundingBox().GetVolume()
    };
    stats.TotalPointCount = 
        stats.TotalLineCount * 2 + stats.TotalFaceCount * 3;
    for (auto& line: m_Model.Lines) {
        stats.TotalLineLength += line.GetLength();
    }
    for (auto& face: m_Model.Faces) {
        stats.TotalFaceArea += face.GetArea();
    }
    return stats;
}

/**********************************************************************
【函数名称】 LoadModel
【函数功能】 从文件加载一个模型。
【参数】
    path: 文件位置。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::LoadModel(string path) {
    unique_ptr<ImporterBase<3>> importer;
    try {
        importer = StorageFactory::GetImporter<3>(path);
    }
    catch (StorageFactoryLookupException) {
        return Result::STORAGE_LOOKUP_ERROR;
    }
    try {
        importer->Import(path, m_Model);
    }
    catch (FileOpenException) {
        return Result::FILE_OPEN_ERROR;
    }
    catch (FileFormatException) {
        return Result::FILE_FORMAT_ERROR;
    }
    catch (IndexOverflowException) {
        return Result::INDEX_OVERFLOW;
    }
    m_LineStatus.assign(m_Model.Lines.Count(), Status::UNTOUCHED);
    m_FaceStatus.assign(m_Model.Faces.Count(), Status::UNTOUCHED);
    m_Path = path;
    return Result::OK;
}

/**********************************************************************
【函数名称】 SaveModel
【函数功能】 向文件保存一个模型。
【参数】
    path: 文件位置。
【返回值】
    函数发生的错误类型。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ControllerBase::Result ControllerBase::SaveModel(string path) {
    if (path.empty()) {
        path = m_Path;
    }
    unique_ptr<ExporterBase<3>> exporter;
    try {
        exporter = StorageFactory::GetExporter<3>(path);
    }
    catch (StorageFactoryLookupException) {
        return Result::STORAGE_LOOKUP_ERROR;
    }
    try {
        exporter->Export(path, m_Model);
    }
    catch (FileOpenException) {
        return Result::FILE_OPEN_ERROR;
    }
    catch (FileFormatException) {
        return Result::FILE_FORMAT_ERROR;
    }
    return Result::OK;
}

}

}