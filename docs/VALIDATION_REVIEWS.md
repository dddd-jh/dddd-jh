# 上游修复验证记录

记录对其他作者已有修复的复现与验证，单独列出，不计入个人提交 PR 数或个人代码修复成果。

## 2026-10-06：GLIM 日志指针格式化与新版 fmt

实际需求来自 [GLIM #326](https://github.com/koide3/glim/issues/326)：Linux/pixi 环境下使用新版 fmt 编译失败。修复由 [GLIM #327 的原作者](https://github.com/koide3/glim/pull/327)提供，本次检查对应提交 `46165a578c615d35dfbe70c628ca0303e2c015d1`。

个人贡献是独立兼容性验证，结果已[回复到现有 PR](https://github.com/koide3/glim/pull/327#issuecomment-6017563243)。原调用将 `std::shared_ptr` 直接传入 `fmt::ptr`；现有补丁先通过 `.get()` 获取裸指针，不改变共享对象所有权。

| 官方 fmt 版本 | 原调用 | 现有补丁 | 补丁输出检查 |
| --- | --- | --- | --- |
| 8.1.1 | 编译、运行通过 | 编译、运行通过 | 与对应 const void* 格式化一致 |
| 11.2.0 | 指针类型静态断言导致编译失败 | 编译、运行通过 | 与对应 const void* 格式化一致 |
| 12.1.0 | 非指针静态断言导致编译失败 | 编译、运行通过 | 与对应 const void* 格式化一致 |

测试环境为 Windows、Zig/Clang 18.1.6、C++17、`-O2`、fmt header-only。同一日志同时检查有值及空 shared_ptr。保留运行过的[原调用源码](validation/glim-fmt-original.cpp)及[补丁调用源码](validation/glim-fmt-patched.cpp)。使用对应版本的官方 `include` 目录，分别执行：

```sh
zig c++ -std=c++17 -O2 -I /path/to/fmt/include docs/validation/glim-fmt-original.cpp -o original.exe
zig c++ -std=c++17 -O2 -I /path/to/fmt/include docs/validation/glim-fmt-patched.cpp -o patched.exe
./patched.exe
```

退出码 0 表示补丁输出匹配；8.1.1 下也运行 `original.exe`，新版 fmt 的原调用应编译失败。官方源码固定引用：

- [fmt 8.1.1](https://github.com/fmtlib/fmt/tree/b6f4ceaed0a0a24ccf575fab6c56dd50ccf6f1a9)
- [fmt 11.2.0](https://github.com/fmtlib/fmt/tree/40626af88bd7df9a5fb80be7b25ac85b122d6c21)
- [fmt 12.1.0](https://github.com/fmtlib/fmt/tree/407c905e45ad75fc29bf0f9bb7c5c2fd3475976f)

验证边界：只检查受影响的参数调用模式，没有构建完整 GLIM/spdlog，没有复现报告者的完整 Linux/pixi 环境，也没有运行 ROS 或 SLAM 管线。该记录不代表修复已被上游合并。
