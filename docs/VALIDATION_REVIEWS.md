# 上游修复验证记录

记录对其他作者已有 PR 的复现、验证与补丁建议，单独列出，不计入个人新提交 PR 数或已合并成果。

## 2026-10-06：evo 时间匹配二分优化的兼容性评审

上游 [evo #787](https://github.com/MichaelGrupp/evo/pull/787) 由 dmalvezz 提出，以二分查找加速长轨迹关联。检查提交为 `38b5fd47403c77a95662ff8b14b5c704eda59f93`，对照主分支为 `9690a0cbf6ab6fe03ccc4a4d9d05bd9f36bccbe2`。

个人工作是复现匹配行为变化，准备[兼容性补丁与三个回归用例](https://github.com/dddd-jh/evo/commit/b68a9af482887ea09f027cdc60adb2aaed657fe2)，并[回复至原 PR](https://github.com/MichaelGrupp/evo/pull/787#issuecomment-6018021726)。补丁的直接父提交为原作者 PR 的真实提交，二分优化保留原作者归属。没有另开重复 PR，该建议尚未被上游接受。

| 场景 | 主分支原有行为 | 原优化 PR | 兼容性补丁 |
| --- | --- | --- | --- |
| 0.005 秒匹配 [0, 0.01]，容差 0.006 | 选择索引 0 | 选择索引 1 | 恢复索引 0 |
| 0 秒匹配乱序 [1, 0, 2] | 匹配索引 1 | 无匹配 | 恢复索引 1 |
| 1 秒匹配重复 [1, 1, 2] | 首次索引 0 | 索引 1 | 恢复首次索引 0 |

三个新增用例在原 PR 上均失败，补丁后通过。非递减目标时间戳保留二分查找，包括重复时间戳；乱序输入使用原线性算法，避免静默丢失匹配。等距时保留原 `argmin` 的首索引规则。

实际数据核对使用仓库自带的 `test/data/fr2_desk_groundtruth.txt`（20,957 个位姿）及 `fr2_desk_ORB.txt`（2,893 个位姿）。原主分支匹配 2,174 对；原优化 PR 数量相同但改变一对对应关系，补丁恢复全部对应索引。具体查询时间为 `1311868220.91065`，原主分支选择 `1311868220.909`，原优化 PR 选择等距的 `1311868220.9123`。

本机 Windows／Python 3.12／NumPy 2.5.3 下，最终补丁全部 130 项单元测试通过，其中同步模块 14 项；Black 及全库 mypy（67 个源文件）通过。实际 TUM APE CLI 的 SE(3) 对齐评测正常完成。

同一公开数据、默认容差、每种实现运行三次的时间中位数为：原线性实现约 41.7 ms、原作者二分实现约 5.3 ms、兼容性补丁约 8.0 ms。这只是本机单个输入的观测，不是通用性能结论；主要速度收益来自原作者的二分优化。

可在补丁分支复现：

```sh
python -m unittest discover -s test -p 'test_*.py' -q
python -m pytest test/test_sync.py -q
python -m black --check evo/core/sync.py test/test_sync.py
python -m mypy .
evo_ape tum test/data/fr2_desk_groundtruth.txt test/data/fr2_desk_ORB.txt --align --no_warnings
```

验证边界：本机 Python、公开轨迹和 CLI 检查，没有运行 ROS Docker 构建、Rerun 集成或机器人硬件；未声称上游合并或批准。

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
