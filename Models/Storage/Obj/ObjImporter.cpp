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
    unsigned int uLineNumber = 0;
    while (!Stream.eof()) {
        string LineString;
        getline(Stream, LineString);
        uLineNumber++;
        if (LineString.empty()) continue;
        istringstream LineStream(LineString);
        char cTag;
        LineStream >> cTag;
        switch (cTag) {
            case '#' : {
                break;
            }
            case 'g' : {
                LineStream.ignore();
                getline(LineStream, Model.Name);
                break;
            }
            case 'v' : {
                double x;
                double y;
                double z;
                LineStream >> x >> y >> z;
                if (LineStream.bad()) {
                    throw FileFormatException(
                        uLineNumber,
                        "cannot parse point coordinates"
                    );
                }
                Points.push_back(Point<3> { x, y, z });
                break;
            }
            case 'l' : {
                size_t ullIndices[2];
                LineStream >> ullIndices[0] >> ullIndices[1];
                if (LineStream.bad()) {
                    throw FileFormatException(
                        uLineNumber,
                        "cannot parse indices"
                    );
                }
                if (
                    (ullIndices[0] == 0 || ullIndices[0] > Points.size()) ||
                    (ullIndices[1] == 0 || ullIndices[1] > Points.size())
                ) {
                    throw FileFormatException(uLineNumber, "index overflow");
                }
                Model.Lines.Add(
                    Line<3>(Points[ullIndices[0]-1], Points[ullIndices[1]-1])
                );
                break;
            }
            case 'f' : {
                size_t ullIndices[3];
                LineStream >> ullIndices[0] >> ullIndices[1] >> ullIndices[2];
                if (LineStream.bad()) {
                    throw FileFormatException(
                        uLineNumber,
                        "cannot parse indices"
                    );
                }
                if (
                    (ullIndices[0] == 0 || ullIndices[0] > Points.size()) ||
                    (ullIndices[1] == 0 || ullIndices[1] > Points.size()) ||
                    (ullIndices[2] == 0 || ullIndices[2] > Points.size())
                ) {
                    throw FileFormatException(uLineNumber, "index overflow");
                }
                Model.Faces.Add(
                    Face<3>(
                        Points[ullIndices[0]-1], 
                        Points[ullIndices[1]-1], 
                        Points[ullIndices[2]-1]
                    )
                );
                break;
            }
            default : {
                throw FileFormatException(
                    uLineNumber,
                    string("unrecognized tag '") + cTag + string("'")
                );
            }
        }
    }
}

}

}

}