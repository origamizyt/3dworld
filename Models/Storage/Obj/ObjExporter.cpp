/*************************************************************************
【文件名】 ObjExporter.cpp
【功能模块和目的】 为 ObjExporter.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <fstream>
#include "../../Core/Model.hpp"
#include "ObjExporter.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Storage;

namespace C3w {

namespace Storage {

namespace Obj {

/**********************************************************************
【函数名称】 InnerExport
【函数功能】 导出指定模型到文件流中。
【参数】 
    stream: 已经打开的文件流。
    model: 模型的可变引用。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
void ObjExporter::InnerExport(
    ofstream& stream,
    const Model<3>& model
) const {
    stream << "g " << model.Name << endl;
    
    auto points = model.CollectPoints();
    for (auto& point: points) {
        stream << "v";
        stream << "  " << point[0];
        stream << "  " << point[1];
        stream << "  " << point[2] << endl;
    }

    for (auto& line: model.Lines) {
        stream << "l";
        for (auto& point: line.Points) {
            stream << "  ";
            stream << points.FindIndex(point) + 1;
        }
        stream << endl;
    }

    for (auto& face: model.Faces) {
        stream << "f";
        for (auto& point: face.Points) {
            stream << "  ";
            stream << points.FindIndex(point) + 1;
        }
        stream << endl;
    }
}

}

}

}