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
    stream: 已经打开的文件流。
    model: 模型的可变引用。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
void ObjImporter::InnerImport(ifstream& stream, Model<3>& model) const {
    vector<Point<3>> points;
    unsigned int LineNumber = 0;
    while (!stream.eof()) {
        string line;
        getline(stream, line);
        LineNumber++;
        if (line.empty()) continue;
        istringstream lineStream(line);
        char kind;
        lineStream >> kind;
        switch (kind) {
            case '#': {
                break;
            }
            case 'g': {
                lineStream.ignore();
                getline(lineStream, model.Name);
                break;
            }
            case 'v': {
                double x;
                double y;
                double z;
                lineStream >> x >> y >> z;
                if (lineStream.bad()) {
                    throw FileFormatException(
                        LineNumber,
                        "cannot parse point coordinates"
                    );
                }
                points.push_back(Point<3> { x, y, z });
                break;
            }
            case 'l': {
                size_t p1;
                size_t p2;
                lineStream >> p1 >> p2;
                if (lineStream.bad()) {
                    throw FileFormatException(
                        LineNumber,
                        "cannot parse indices"
                    );
                }
                if (
                    (p1 == 0 || p1 > points.size()) ||
                    (p2 == 0 || p2 > points.size())
                ) {
                    throw FileFormatException(
                        LineNumber,
                        "index overflow"
                    );
                }
                model.Lines.Add(Line<3> { points[p1-1], points[p2-1] });
                break;
            }
            case 'f': {
                size_t p1;
                size_t p2;
                size_t p3;
                lineStream >> p1 >> p2 >> p3;
                if (lineStream.bad()) {
                    throw FileFormatException(
                        LineNumber,
                        "cannot parse indices"
                    );
                }
                if (
                    (p1 == 0 || p1 > points.size()) ||
                    (p2 == 0 || p2 > points.size()) ||
                    (p3 == 0 || p3 > points.size())
                ) {
                    throw FileFormatException(
                        LineNumber,
                        "index overflow"
                    );
                }
                model.Faces.Add(
                    Face<3> { points[p1-1], points[p2-1], points[p3-1] }
                );
                break;
            }
            default: {
                throw FileFormatException(
                    LineNumber,
                    string("unrecognized tag '") + kind + string("'")
                );
            }
        }
    }
}

}

}

}