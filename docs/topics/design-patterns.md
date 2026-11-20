# 设计模式：接口抽象 & 依赖注入

> 主题：Design Patterns / 接口抽象 / 依赖注入（Dependency Injection）

## 概念解释

- **接口抽象（Interface-based Design）**：定义一个只含行为约定的接口（C++ 里是纯虚类），让上层依赖「约定」而非「具体实现」。
- **依赖注入（Dependency Injection，DI）**：类的依赖由外部传入（构造器 / setter / 方法参数），而不是在内部 `new`。常见形式有构造器注入、setter 注入、方法参数注入。

两者通常一起出现：接口定义了「能换的东西」，依赖注入提供了「怎么把东西换进来」。

## 你项目里的体现

- 接口：`include/storage/IStorage.h` — `load()` / `save()` 纯虚函数
- 两个实现：`include/storage/Storage.h`（写 JSON 文件）和 `tests/FakeStorage.h`（写内存）
- 注入点：`src/cli/CommandHandler.cpp` 里 `TodoManager manager(storage);`

## 进一步学习资源

- 待补：SOLID 原则（接口抽象对应其中的「接口隔离 I」和「依赖倒置 D」两条）
