# 绘本阅读器

## 开发环境

* **IDE**: Qt Creator 4.11.1
* **Qt**: 5.14.2
* **编译器**: MSVC 2017 64bit

## 源码结构

### 1. PicaReader

主要包含两个类 `GlobalApplication` `MainWindow` 和主函数入口 `main.cpp`.

`GlobalApplication`: 继承自 `QApplication`, 用于实现自动锁屏功能.

`MainWindow`: 继承自 `QWidget`, 主窗口.

同时还有资源文件 `Resources.qrc`. `styl.css` 是样式表, `img/` 目录包含所有的图标或背景图片.

### 2. Pages

包含显示页面的控件类.

**`AbstractPage`**: 继承自 `QWidget`, 各个页面控件类的基类.

**`FavoritePage`**: 继承自 `AbstractPage`, 收藏页面.

**`IndexPage`**: 继承自 `AbstractPage`, 首页.

**`ReadingCompletePage`**: 继承自 `AbstractPage`, 阅读完成页面.

**`ReadingPage`**: 继承自 `AbstractPage`, 阅读绘本页面.

**`StoryPage`**: 继承自 `AbstractPage`, 故事绘本显示页面.

`ImgLoader`: 继承自 `QObject`, 用于多线程图片加载(未完善). 暂时先分类到此处.

### 3. CustomWidgets

包含所有的自定义控件.

**`CategoryBar`**: 继承自 `QWidget`, `StoryPage` 顶部的分类栏.

**`CategoryButton`**: 继承自 `QToolButton`, `CategoryBar` 里面的按钮.

**`CoverLabel`**: 继承自 `QLabel`, 用于显示绘本封面或标题. `CoverWidget`的子控件.

**`CoverWidget`**: 继承自 `QWidget`, 用于显示绘本封面和标题. 主要是`PicBookCoverBox`的子控件.

**`LockScreen`**: 继承自 `QWidget`, 锁屏控件.

**`PaginationButton`**: 继承自 `QPushButton`, 分页按钮. `PicBookCoverBox`的子控件.

**`PicBookCoverBox`**: 继承自 `QWidget`, 显示网格布局的绘本封面.

**`Sidebar`**: 继承自 `QWidget`, 侧栏按钮组.

**`SidebarButton`**: 继承自 `QToolButton`, 侧栏按钮. `Sidebar`的子控件.
