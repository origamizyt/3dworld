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
    Stream: 已经打开的文件流。
    Model: 模型的引用。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
void ObjExporter::InnerExport(
    ofstream& Stream,
    const Model<3>& Model
) const {
    Stream << "g " << Model.Name << endl;
    
    auto Points = Model.CollectPoints();
    for (auto& Point: Points) {
        Stream << "v";
        Stream << " " << Point[0];
        Stream << " " << Point[1];
        Stream << " " << Point[2] << endl;
    }

    for (auto& Line: Model.Lines) {
        Stream << "l";
        for (auto& Point: Line.Points) {
            Stream << " ";
            Stream << Points.FindIndex(Point) + 1;
        }
        Stream << endl;
    }

    for (auto& Face: Model.Faces) {
        Stream << "f";
        for (auto& Point: Face.Points) {
            Stream << " ";
            Stream << Points.FindIndex(Point) + 1;
        }
        Stream << endl;
    }
}

}

}

}