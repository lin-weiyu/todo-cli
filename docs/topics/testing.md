# 测试：单元测试、GoogleTest、TDD

> 主题：Unit Testing / GoogleTest / TDD

## 概念解释

- **单元测试（Unit Testing）**：对最小单元（一个类 / 函数）做自动化验证，跑得飞快、不依赖外部环境。
- **GoogleTest**：C++ 的主流测试框架，提供断言（`EXPECT_EQ` 等）和测试发现。
- **TDD（Test-Driven Development）**：先写测试（红）→ 写实现让测试通过（绿）→ 重构（保持绿）。好处是「先想清楚要什么，再动手」。

## 你项目里的体现

- `tests/TodoManagerTest.cpp` — 用 GoogleTest 断言 `TodoManager` 的行为
- `tests/FakeStorage.h` — 测试替身（Fake），隔离文件 IO
- `CMakeLists.txt` — `gtest_discover_tests` 自动发现测试

## 进一步学习资源

- 待补：测试替身的分类（Fake / Stub / Mock）、测试覆盖率意味着什么
