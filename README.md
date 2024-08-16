# 构建三维世界 v2

❗请勿直接将本仓库中的代码用于大作业中❗

## Changelog

相比 v1 版本，v2 版本修改了以下内容：

- 增加了注释。
- 增加了命名空间，Models 位于 `C3w` 命名空间下，Controllers 位于 `C3w::Controllers` 命名空间下，Views 位于 `C3w::Views` 命名空间下。
- 为 `Point<N>` 增加了 `Vector<T, N>` 基类，并实现了加减、数乘、内积等操作。
- 为 `Element<N, S>` 增加了平移、缩放等操作。
- 增加了集合类容器的实现，如 `DynamicSet<T>` 以及 `FixedSet<T, N>`。
- `Element<N, S>` 由存储 `shared_ptr<Point<N>>` 改为直接存储 `Point<N>`。
- `Model<N>` 由存储 `vector<shared_ptr<Line<N>>>` 改为存储 `vector<Line<N>>`，Face 同理。
- 为 `ImporterBase<N>` 和 `ExporterBase<N>` 添加模板，实现不同维数的导入 / 导出器。
- 增加了导入 / 导出器的注册机制，见 `StorageFactory`。
- 增加了 `ControllerBase` 抽象基类。
- 优化了 Views 的设计。

## Compile

编译所有子目录下的 cpp 文件。由于我也不会 Makefile，所以就用 Python 了：
```py
import glob, os

cpp_list = glob.glob("**/*.cpp", recursive=True)

os.system("g++ -std=c++11 %s -o main" % ' '.join(cpp_list))
```

MSVC 比较麻烦：
```py
import glob, os

for cpp in glob.iglob("**\\*.cpp", recursive=True):
    os.system('cl %s /c /EHsc' % cpp)

obj_list = glob.glob('*.obj')

os.system('link /OUT:main.exe %s' % ' '.join(obj_list))
```

## Design

### `C3w::Tools::Representable`

位于: Models/Tools/Representable.hpp

代表一个可以被转化为字符串的对象。重载了流插入运算符，调用 `ToString` 纯虚函数。

### `C3w::Tools::Box<size_t N>`

位于: Models/Tools/Box.hpp

表示一个 N 维的长方体。用于 `C3w::Models<N>::GetBoundingBox` 的返回值。

### `C3w::Vector<typename T, size_t N>`

继承于: `C3w::Tools::Representable`

位于: Models/Core/Vector.hpp

实现一个基础的向量。使用 `std::array` 存储分量并提供下标访问以及向量的基础运算、模长等接口。

### `C3w::Point<size_t N>`

继承于: `C3w::Vector<double, N>`

位于: Models/Core/Point.hpp

实现一个 N 维的点，相比向量隐藏了加法、数乘、模长等接口，但增加了距离等接口。一个点可以通过 `Promote` 方法升至更高维，也可以通过 `Project` 方法投影到更低维，这使得不同维度的两个点可以通过 `GeneralDistance` 方法求距离（将低维点升维）。

### `C3w::Element<size_t N, size_t S>`

继承于: `C3w::Tools::Representable`

位于: Models/Core/Element.hpp

实现一个 N 维的，含有 S 个点的元素。点使用 `C3w::Containers::FixedSet<T, N>` 存储，这使得元素中的点无法重复。提供了平移、缩放等接口，以及未实现的长度、面积。

### `C3w::Line<size_t N>`

继承于: `C3w::Element<N, 2>`

位于: Models/Core/Line.hpp

相比 `C3w::Element<N, S>`，实现了长度，面积（恒为 0）。

### `C3w::Face<size_t N>`

继承于: `C3w::Element<N, 3>`

位于: Models/Core/Face.hpp

相比 `C3w::Element<N, S>`，实现了长度（周长），面积。

### `C3w::Model<size_t N>`

位于: Models/Core/Model.hpp

代表一个 N 维的模型，包括一系列的 Lines 和 Faces。提供了收集所有点以及获取外接长方体的接口。

### `C3w::Containers::CollectionBase<typename T>`

继承于: `C3w::Tools::Representable`

代表一个带有规则的容器，存储 T 类型的元素。提供 `ShouldAdd`、`ShouldSet`、`ShouldRemove` 虚函数，让子类决定是否允许这些操作。

### `C3w::Containers::DistinctCollection<typename T>`

继承于: `C3w::Containers::CollectionBase<T>`

代表一个元素不能重复的容器。重写了 `ShouldAdd`、`ShouldSet` 函数以禁止重复元素。提供了 `IsDistinct` 静态函数判断集合中是否有重复元素。

### `C3w::Containers::DynamicSet<typename T>`

继承于: `C3w::Containers::DistinctCollection<T>`

代表一个动态大小的集合。使用 `std::vector` 存储元素。

### `C3w::Containers::FixedSet<typename T, size_t N>`

继承于: `C3w::Containers::DistinctCollection<T>`

代表一个静态大小的集合。使用 `std::array` 存储元素。

### `C3w::Storage::ImporterBase<size_t N>`

位于: Models/Storage/ImporterBase.hpp

代表一个 N 维的导入器。提供了 `InnerImport` 纯虚函数。

### `C3w::Storage::ExporterBase<size_t N>`

位于: Models/Storage/ExporterBase.hpp

代表一个 N 维的导出器。提供了 `InnerExport` 纯虚函数。

### `C3w::Storage::StorageFactory`

位于: Models/Storage/StorageFactory.hpp

寻找并创建合适导入 / 导出器的静态类。可以匹配相应的文件扩展名和维数。默认注册了 `C3w::Storage::obj::ObjImporter` 和 `C3w::Storage::obj::ObjExporter`。

### `C3w::Storage::Obj::ObjImporter`

继承于: `C3w::Storage::ImporterBase<3>`

位于: Models/Storage/Obj/ObjImporter.hpp

一个适用于 `*.obj` 文件的导入器。

### `C3w::Storage::Obj::ObjExporter`

继承于: `C3w::Storage::ExporterBase<3>`

位于: Models/Storage/Obj/ObjExporter.hpp

一个适用于 `*.obj` 文件的导出器。

### `C3w::Controllers::ControllerBase`

位于: Controllers/ControllerBase.hpp

所有控制器的基类。提供 `PointToString`、`LineToString`、`FaceToString` 纯虚函数供子类客制行为。禁止复制 / 拷贝。

### `C3w::Controllers::Cli::ConsoleController`

继承于: `C3w::Controllers::ControllerBase`

位于: Controllers/CLI/ConsoleController.hpp

一个适用于命令行的控制器。由于其只有私有构造函数，只能通过 `GetInstance` 静态函数获取一个 `std::shared_ptr`。

### `C3w::Views::ViewBase`

位于: Views/ViewBase.hpp

所有视图的基类。提供 `Display` 纯虚函数来显示视图。

### `C3w::Views::Cli::ConsoleViewBase`

继承于: `C3w::Views::ViewBase`

位于: Views/CLI/ConsoleViewBase.hpp

一个适用于命令行的基于命令的视图。覆盖了 `Display` 函数，每次读入一行并在存储的命令中进行匹配，执行对应的函数。虽然此类可以实例化，但由于 `RegisterCommand` 是受保护的，因此没有用处。默认提供 `?` 和 `quit` 命令，分别为显示帮助和退出。

### `C3w::Views::Cli::MainConsoleView`

继承于: `C3w::Views::ConsoleViewBase`

位于: Views/CLI/MainConsoleView.hpp

命令行的主视图。提供了 `lines`、`faces`、`stat`、`save` 命令。同时覆盖了 `Display`，在 REPL 前询问用户加载模型。

### `C3w::Views::Cli::LinesConsoleView`

继承于: `C3w::Views::ConsoleViewBase`

位于: Views/CLI/LinesConsoleView.hpp

为主视图提供 `lines` 命令。提供了 `add`、`edit`、`del`、`get`、`list` 命令。

### `C3w::Views::Cli::FacesConsoleView`

继承于: `C3w::Views::ConsoleViewBase`

位于: Views/CLI/FacesConsoleView.hpp

为主视图提供 `faces` 命令。提供了 `add`、`edit`、`del`、`get`、`list` 命令。