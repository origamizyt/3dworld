/*************************************************************************
【文件名】 ObjImporter.cpp
【功能模块和目的】 为 ObjImporter.hpp 文件提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "ObjImporter.hpp"
#include "../../Core/Model.hpp"
#include "../../Core/Point.hpp"
#include "../../Core/Line.hpp"
#include "../../Core/Face.hpp"
#include "../../Errors/FileFormatException.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Errors;

namespace C3w {

namespace Storage {

namespace Obj {

/**********************************************************************
【函数名称】 InnerImport
【函数功能】 导入指定文件流到模型中。
【参数】 
    Stream: 已经打开的文件流。
    Model: 模型的可变引用。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
void ObjImporter::InnerImport(ifstream& Stream, Model<3>& Model) const {
    vector<Point<3>> Points;
    unsigned int LineNumber = 0;
    while (!Stream.eof()) {
        string LineString;
        getline(Stream, LineString);
        LineNumber++;
        if (LineString.empty()) continue;
        istringstream LineStream(LineString);
        char Tag;
        LineStream >> Tag;
        switch (Tag) {
            case '#': {
                break;
            }
            case 'g': {
                LineStream.ignore();
                getline(LineStream, Model.Name);
                break;
            }
            case 'v': {
                double x;
                double y;
                double z;
                LineStream >> x >> y >> z;
                if (LineStream.bad()) {
                    throw FileFormatException(
                        LineNumber,
                        "cannot parse point coordinates"
                    );
                }
                Points.push_back(Point<3> { x, y, z });
                break;
            }
            case 'l': {
                size_t Indices[2];
                LineStream >> Indices[0] >> Indices[1];
                if (LineStream.bad()) {
                    throw FileFormatException(
                        LineNumber,
                        "cannot parse indices"
                    );
                }
                if (
                    (Indices[0] == 0 || Indices[0] > Points.size()) ||
                    (Indices[1] == 0 || Indices[1] > Points.size())
                ) {
                    throw FileFormatException(LineNumber, "index overflow");
                }
                Model.Lines.Add(
                    Line<3>(Points[Indices[0]-1], Points[Indices[1]-1])
                );
                break;
            }
            case 'f': {
                size_t Indices[3];
                LineStream >> Indices[0] >> Indices[1] >> Indices[2];
                if (LineStream.bad()) {
                    throw FileFormatException(
                        LineNumber,
                        "cannot parse indices"
                    );
                }
                if (
                    (Indices[0] == 0 || Indices[0] > Points.size()) ||
                    (Indices[1] == 0 || Indices[1] > Points.size()) ||
                    (Indices[2] == 0 || Indices[2] > Points.size())
                ) {
                    throw FileFormatException(LineNumber, "index overflow");
                }
                Model.Faces.Add(
                    Face<3>(
                        Points[Indices[0]-1], 
                        Points[Indices[1]-1], 
                        Points[Indices[2]-1]
                    )
                );
                break;
            }
            default: {
                throw FileFormatException(
                    LineNumber,
                    string("unrecognized tag '") + Tag + string("'")
                );
            }
        }
    }
}

}

}

}