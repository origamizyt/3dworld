/*************************************************************************
【文件名】 ImporterBase.hpp
【功能模块和目的】 ImporterBase 类定义了一个抽象的导入器。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef IMPORTER_BASE_HPP
#define IMPORTER_BASE_HPP

#include <cstddef>
#include <fstream>
#include <string>
#include "../Core/Model.hpp"
using namespace std;
using namespace C3w;

namespace C3w {

namespace Storage {

/*************************************************************************
【类名】 ImporterBase
【功能】 定义一个抽象的导入器。
【接口说明】 
    构造与析构：
        虚析构函数。
    操作：
        Import: 使用文件名导入一个模型。
        InnerImport (protected): 使用文件流导入模型，纯虚函数。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
template <size_t N>
class ImporterBase {
    public:
        // 操作

        // 考虑子类实现，传引用作为参数而非直接返回 Model<N>。
        /**********************************************************************
        【函数名称】 Import
        【函数功能】 导入指定文件到模型中。
        【参数】 
            Path: 文件所在路径。
            Model: 模型的可变引用。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void Import(string Path, Model<N>& Model) const;

        // 虚析构函数
        virtual ~ImporterBase() = default;

    protected:
        /**********************************************************************
        【函数名称】 InnerImport
        【函数功能】 导入指定文件流到模型中。
        【参数】 
            Stream: 已经打开的文件流。
            Model: 模型的可变引用。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual void InnerImport(ifstream& Stream, Model<N>& Model) const = 0;
};

}

}

#include "ImporterBase.tpp"

#endif