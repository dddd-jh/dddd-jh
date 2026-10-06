# SLAM 开源贡献计划

目标是积累可复现、可讨论、可验证的工程贡献，为机器人／无人车 SLAM 与定位岗位准备证据。

## 已核对的候选社区

以下是 2026-10-05 至 2026-10-06 通过 GitHub 仓库元数据核对的最近推送时间。推送记录说明仓库仍有更新，不代表每个 Issue 都会得到及时回复。

| 社区 | 与我的方向的联系 | 最近推送 | 切入点 |
| --- | --- | --- | --- |
| [evo](https://github.com/MichaelGrupp/evo) | SLAM／里程计轨迹评测 | 2026-09-08 | 输入格式、时间戳处理、轨迹检查、数值边界 |
| [small_gicp](https://github.com/koide3/small_gicp) | C++／Python 点云配准 | 2026-09-29 | 数据预处理、接口边界、配准结果与回归测试 |
| [KISS-ICP](https://github.com/PRBonn/kiss-icp) | 激光里程计与点云运动畸变补偿 | 2026-06-09 | 传感器数据接入、逐点时间戳与点云预处理 |
| [RKO-LIO](https://github.com/PRBonn/rko_lio) | 激光惯导里程计 | 2026-09-29 | 激光／IMU 时间排序、数据读取与传感器协同 |
| [KISS-SLAM](https://github.com/PRBonn/kiss-slam) | 激光 SLAM、局部地图与栅格地图导出 | 2026-08-11 | 地图坐标、文件导出与机器人系统接口 |
| [MapClosures](https://github.com/PRBonn/MapClosures) | 点云密度地图闭环检测与位姿配准 | 2026-08-14 | 二维配准、刚体变换与几何回归测试 |
| [GLIM](https://github.com/koide3/glim) | 点云定位与建图 | 2026-09-06 | 数据导入、评测与定位模块；需要对应运行环境 |
| [gtsam_points](https://github.com/koide3/gtsam_points) | 点云配准与 GTSAM 优化因子 | 2026-09-10 | 邻域搜索、几何容器与回归测试 |
| [MCAP](https://github.com/foxglove/mcap) | ROS 2 传感器数据记录与消息编码 | 2026-10-05 | CDR 消息定义、时间字段与数据往返验证 |
| [Ouster SDK](https://github.com/ouster-lidar/ouster-sdk) | 激光数据处理、位姿插值与点云变换 | 2026-09-01 | 传感器时间戳、逐列位姿及回归测试 |
| [pytransform3d](https://github.com/dfki-ric/pytransform3d) | 机器人刚体变换、时序位姿与插值 | 2026-10-02 | 末帧查询、坐标系链路及几何回归测试 |
| [rosbag2](https://github.com/ros2/rosbag2) | ROS 2 数据记录与回放 | 2026-10-01 | 时间戳、消息与回放问题；需要匹配的 ROS 2 环境 |

## 每项贡献的完成条件

1. 阅读贡献指南、许可、现有 Issue 与 PR，避免重复工作。
2. 用最小数据复现，记录预期行为、实际行为与环境。
3. 修改代码并增加能够发现原问题的回归测试。
4. 运行受影响模块及仓库要求的检查，写明未验证的环境。
5. 提交 PR 并跟进评审，记录提交、待评审、合并或关闭的真实状态。

## 与已有项目的连接

- 围绕无人清扫车公开项目中的建图定位与数据处理需求，寻找可复现的工程问题。
- 从 ROS 1 经验逐步拓展 ROS 2，通过实际复现与维护建立能力证据。

项目指标只有在测试条件与结果可核对时才写入成果描述。团队导航、规划、控制和语义任务模块保留成员职责归属。

## 首项贡献：evo ROS bag 轨迹读取

- PR：[MichaelGrupp/evo #786](https://github.com/MichaelGrupp/evo/pull/786)，2026-10-05 提交，2026-10-06 获维护者批准并合并。
- 问题：轨迹已解析后，代码再次遍历同一话题并将原始消息全部装入列表，仅用于获取第一条消息的坐标系。
- 修改：在首次遍历中保存坐标系，移除额外扫描和原始消息缓存，保留首条消息的空坐标系名称；空迭代器返回明确异常。
- 验证：真实写入和读取 ROS 1、ROS 2 bag，修改前两种格式均因扫描两次失败，修改后通过；全量 126 项测试、2 项子测试、Black 和 mypy 通过。
- 评审跟进：已向维护者[回复合并致谢](https://github.com/MichaelGrupp/evo/pull/786#issuecomment-5998931254)。
- 边界：仍需保存轨迹数组，未宣称恒定内存；本机 Windows／Python 3.12 验证，原生 ROS 2 Docker 构建和可选 Rerun 集成未在本机运行。

## 第二项贡献：small_gicp 体素降采样范围处理

- PR：[koide3/small_gicp #141](https://github.com/koide3/small_gicp/pull/141)，2026-10-05 提交，待评审。
- 问题：文档规定忽略越界点，但串行累加器及并行分块仍使用首个无效点初始化；全越界点云或仅含无效点的分块会输出错误质心。
- 修改：在串行、OpenMP 和 TBB 后端中跳过首个排序键为无效标记的点云或分块，保留已有有效体素的累加逻辑。
- 验证：原生 C++、OpenMP 1／4 线程及真实 TBB 运行；16 项回归测试修改前 7 项失败，修改后全部通过。覆盖空输入、全越界输入、跨分块混合点云、点与颜色平均及合法坐标边界。
- 边界：本机 Windows 使用独立测试目标验证受影响的头文件，未在本机运行完整 PCL 依赖测试套件；完整上游 CI 状态以 PR 为准。

## 第三项贡献：KISS-ICP 点云与逐点时间戳对齐

- PR：[PRBonn/kiss-icp #512](https://github.com/PRBonn/kiss-icp/pull/512)，2026-10-05 提交，待评审。
- 问题：点云读取器删除坐标含 NaN 的点后，保留了这些点的时间戳，使后续有效点与时间戳错位，导致运动畸变补偿错误。
- 修改：使用同一有效点掩码过滤坐标及逐点时间戳，保留无时间戳点云的既有行为。
- 验证：19 项新增回归测试覆盖 t／time／timestamp 三种字段及整数／单精度／双精度编码；修改前 12 项失败，修改后全部通过。全部 20 项 Python 测试、Black 和 isort 通过。
- 集成检查：真实写入和读取 ROS 1 Noetic／ROS 2 Humble bag，6 组输入通过原生畸变补偿验证。示例 x 坐标 [10, NaN, 30] 与时间戳 [0, 1, 2] 在相对 x 平移 2 的条件下，修改前错误输出 [8, 29]，修改后正确输出 [8, 30]。
- 边界：本机 Python 源码与已发布 KISS-ICP 1.3.0 Windows 原生扩展联合验证，未在本机重新构建 C++ 扩展或运行 ROS 节点；上游 CI 需要维护者批准后运行。

## 第四项贡献：RKO-LIO 激光／IMU 排序器丢帧修复

- PR：[PRBonn/rko_lio #189](https://github.com/PRBonn/rko_lio/pull/189)，2026-10-05 提交，已合并。
- 问题：最后一条输入 IMU 数据已经覆盖多个缓存激光帧，但排序器输出一帧后再次读取输入，在文件结束时退出，导致剩余已覆盖帧被丢弃。
- 修改：处理一帧后重新检查缓存，先输出具备覆盖条件的激光帧，再读取更多输入；保留 IMU 覆盖必须严格超过激光帧结束时间的条件。
- 验证：11 项新增排序测试修改前 3 项失败，修改后全部通过。覆盖文件末尾多个帧、IMU 顺序及仅输出一次、继续读取、空输入与不足覆盖等情况。
- 仓库检查：全部 53 项 Python 测试通过，包括原始 PLY／CSV、ROS bag 读取、LIO 管线与标量转换；Ruff 0.16.1 lint／format 和 Git 空白检查通过。
- 评审跟进：维护者认可修复，希望仅保留包内的一行改动；已移除 PR 中的新增测试并回复维护者。原回归用例留存在本机，上述 53 项验证结果包括原本新增的本地测试。维护者于 2026-10-05 合并该 PR。2026-10-06 已通过邮件回复致谢，回复已[同步至原 PR](https://github.com/PRBonn/rko_lio/pull/189#issuecomment-5998664085)。
- 边界：本机当前 Python 源码与已发布 RKO-LIO 0.4.0 Windows 原生扩展联合验证，未从当前 C++ 源码重新构建扩展或运行 ROS 节点；上游构建记录见已合并的 PR。

## 第五项贡献：KISS-SLAM 二维地图导出坐标修复

- PR：[PRBonn/kiss-slam #60](https://github.com/PRBonn/kiss-slam/pull/60)，2026-10-05 提交，待评审。
- 问题：内部栅格按 x／y 索引存储，直接写入 PNG 后却被按图像行／列解释，导致非方形地图尺寸交换，并使地图单元在 ROS 坐标约定下落到错误位置。
- 修改：按图像列对应 x、图像行从最大 y 向下的顺序转换栅格；保留 YAML 原点、分辨率、阈值和像素缩放。
- 测试结构：将 PNG／YAML 序列化移入可独立测试的模块，保留原有 mapper 方法入口，并在上游 Python CI 中运行新增测试。
- 验证：13 项回归测试在原导出方向下 10 项失败，修复后全部通过。实际写入和读取 PNG／YAML，核对非方形及单轴地图尺寸、正负原点、两种分辨率和占用／空闲／未知单元的世界坐标；Black、isort、Python 编译及 Git 空白检查通过。
- 边界：本机验证文件序列化与 ROS 地图坐标约定，未启动 ROS 地图服务器、运行原生 SLAM 管线或完整源码构建；上游 CI 需要维护者批准后运行。

## 第六项贡献：MapClosures 二维闭环配准旋转修复

- PR：[PRBonn/MapClosures #118](https://github.com/PRBonn/MapClosures/pull/118)，2026-10-05 提交，待评审。
- 问题：二维 Kabsch 配准用整个矩阵取负来修正反射，但二维矩阵整体取负不会改变行列式符号；平移使用的矩阵又与赋给变换的矩阵不同。原实现可返回反射位姿，或将合法旋转对应点全部排除后返回 NaN 平移。
- 修改：在 SVD 中仅翻转较小奇异值对应的方向，保证旋转行列式为 +1，并使用修正后的同一旋转计算平移。
- 验证：通过公开 RANSAC 接口新增 9 项原生 C++ 测试，覆盖六种旋转角度、非共线对应点及零／非零参考中心的反射输入。相同测试原实现 5 项失败，修复后全部通过；核对有限输出、内点数、旋转正交性、行列式、中心映射及预期位姿。
- 构建与检查：Windows／Clang 18.1.6／Eigen 3.4.0，独立 Release CMake 目标编译实际配准源文件，并使用提交的 CTest 注册代码连续运行五轮；clang-format 14、cmake-format、YAML 及 Git 空白检查通过。测试默认关闭，在上游两组 C++ CI 构建中启用。
- 边界：本机未构建完整 OpenCV／Sophus 依赖库或运行完整地图闭环管线；上游 CI 当前需要维护者批准后运行，合并状态以 PR 为准。

## 第七项贡献：GLIM 全局定位更新越界修复

- PR：[koide3/glim #329](https://github.com/koide3/glim/pull/329)，2026-10-05 提交，待评审。
- 问题：轨迹管理器通过二分查找定位全局定位时间对应的里程计样本；定位时间晚于最新样本时，结果指向容器末尾，原代码仍读取该索引，产生越界访问及未定义行为。
- 修改：在访问索引前检查末尾迭代器，无里程计覆盖时保留当前全局变换和缓存样本；不外推或自动缓存定位请求，调用方可以在数据补齐后再次更新。
- 验证：通过真实轨迹实现新增 8 项 C++ 测试。Windows／Clang 18.1.6／Eigen 3.4.0 下，启用 libc++ 容器边界检查时原实现 6 项越界终止，正常插值及最新时间点 2 项通过；修复后独立 Release CMake 构建及全部 8 项 CTest 通过。
- 覆盖：尚无里程计、时间晚于最新样本、恰好超过最新时间的浮点边界、重复定位更新、补齐数据后重试、历史样本保留、平移及四元数插值；核对全局变换、当前位姿和坐标转换接口。
- 工程检查：C++ 格式、YAML 及 Git 空白检查通过；新增仅依赖 Eigen 的测试工程和 Ubuntu GCC／Clang CI，不改变已有完整构建流程。
- 边界：本机未构建完整 GLIM 库或运行 ROS／可视化／SLAM 管线；新测试及完整构建 CI 当前均需要维护者批准后运行，合并状态以 PR 为准。

## 第八项贡献：gtsam_points 邻域搜索回调生命周期修复

- PR：[koide3/gtsam_points #106](https://github.com/koide3/gtsam_points/pull/106)，2026-10-05 提交，待评审。
- 问题：KNN 及半径搜索结果按引用保存索引回调，构造时传入临时对象、原回调离开作用域或复制结果存活更久时，会留下悬空引用。
- 修改：结果对象持有不可变的回调副本，保持现有构造接口。回调内的引用捕获仍指向原对象，该对象仍需在搜索期间存活。
- 验证：Windows／Clang 18.1.6／GoogleTest 1.15.2 下新增 12 项原生 C++ 测试，原实现 8 项生命周期测试失败，修复后全部通过；独立 Release CMake／CTest 全部通过。生命周期计数在调用前检查，不依赖对已销毁对象的访问来触发随机崩溃。
- 覆盖：静态 1／3 近邻、动态 KNN、半径搜索、临时回调、作用域结束、复制对象生命周期、结果排序、距离阈值及引用捕获观察外部索引更新。
- 工程检查：clang-format 14 与 Git 空白检查通过；新增测试由仓库现有 CMake 源文件搜索及 Docker CI 自动纳入，不修改构建流程。
- 上游验证与回复：2026-10-06 核对构建失败通知，Ubuntu Resolute／GCC 配置完整构建及全部 [98 项 CTest](https://github.com/koide3/gtsam_points/actions/runs/37332671677/job/112064704547) 通过，包括新增 12 项回归测试，许可证检查也通过。CUDA 12.5／Jammy 构建日志记录 runner 关闭和操作取消，尚未运行测试；同一日志还记录镜像仓库登录缺少凭据。其他矩阵配置被取消，不能宣称全部 CI 通过。已在[原 PR 回复](https://github.com/koide3/gtsam_points/pull/106#issuecomment-6009926857)核查结果，保留补丁。
- 边界：本机验证搜索结果容器，未构建完整 GTSAM／CUDA 库；上游其他配置及合并状态以 PR 为准。

## 第九项贡献：MCAP ROS 2 内置时间字段修复

- PR：[foxglove/mcap #1862](https://github.com/foxglove/mcap/pull/1862)，2026-10-05 提交，待评审。
- 问题：消息引用 Time／Duration 而省略其嵌套定义时，库使用的内置备用定义将 sec 声明为 uint32，违反 ROS 2 的 int32 定义；sec=-2 会被解码为 4294967294，负值写入抛出 struct.error。
- 修改：仅将内置 sec 字段改为 int32，保留 nanosec 为 uint32；显式拼接的嵌套定义仍覆盖备用定义，MCAP 记录本身的 log／publish 时间字段不受影响。
- 验证：Windows／Python 3.10.22、uv 冻结依赖环境。50 项新增回归测试原实现 24 项失败，修复后全部通过；受影响的 ROS 2 包共 69 项通过。
- 覆盖：Time／Duration 两种类型、负／零／正秒数、int32 上下界、大小端 CDR、显式嵌套定义，以及 NONE／LZ4／ZSTD 三种压缩下实际 MCAP 写入与读取；预期字节由独立 struct 编码构造。
- 仓库检查：MCAP 核心 39 项、Protobuf 支持 7 项、ROS 1 支持 4 项测试通过，加上 ROS 2 共 119 项。四个包的 flake8／Black／isort／Pyright、源码包及 wheel 构建通过；使用官方 LFS 数据并核对 SHA-256 与文件大小后运行数据读取测试。
- 上游验证：Linux Python CI 的 make lint、make test、make examples、make build 全部通过；跨语言 Python 一致性检查也已通过。MCAP 上游 CI 目前已全部完成，执行的检查无失败。验证记录：[Python CI](https://github.com/foxglove/mcap/actions/runs/37336646143/job/111853004457)、[Python 一致性](https://github.com/foxglove/mcap/actions/runs/37336646143/job/111853004886)。
- 边界：已有核心 test_make_not_seeking 管道测试在 Windows 下阻塞，最终本机运行排除这 1 项；未在本机验证其 POSIX 行为、跨语言一致性测试或 ROS 节点。新增测试由现有 Python CI 自动发现；其他 CI 和合并状态以 PR 为准。

## 第十项贡献：Ouster SDK 无符号轨迹时间戳溢出修复

- PR：[ouster-lidar/ouster-sdk #726](https://github.com/ouster-lidar/ouster-sdk/pull/726)，2026-10-06 提交，待评审。
- 问题：轨迹节点与查询使用 NumPy uint64 时间戳时，范围检查和左侧外推中的减法会溢出；合法内部查询被拒绝，允许外推时又可能生成极大的错误平移。真实激光帧的列时间完全位于轨迹内部时也会被拒绝。
- 修改：仅在内部索引和查询运算中将 NumPy 整数转为 Python 整数，使用有符号差值，保留纳秒整数精度、浮点时间行为、原始轨迹节点类型和查询数组；保持既有插值及外推策略。
- 验证：Windows／Python 3.12.14。52 项新增测试原实现 14 项失败，修复后加上全部 15 项已有位姿测试共 67 项通过。分别使用 NumPy 2.5.3／SciPy 1.18.1、NumPy 1.26.4／SciPy 1.15.3 及实际无 SciPy 后备实现验证同一组 67 项测试；数值运行警告设为错误。
- 覆盖：普通／有符号／无符号整数混用、标量及批量查询、重复与端点查询、有限及无限外推、越界拒绝、Unix 纳秒时间和 uint64 大值边界、节点类型与输入数组保留。
- 原生接口检查：真实 LidarFrame 状态掩码、原始及重映射列时间、逐列 body_to_world 位姿写入和原生 dewarp 点云变换；无效列保留原位姿。4 项相关原生接口用例在原实现中失败，修复后通过。
- 工程检查：CI 指定的 flake8 7.1.2 与 Git 空白检查通过。mypy 1.14.1 针对受影响源文件及测试仍报告 3 项原有 bisect_right／Numeric 类型诊断，与原代码核对后无新增诊断位置。
- 边界：测试加载当前 checkout 的真实 pose_util.py，原生接口使用已发布的 Ouster SDK 1.0.1 Windows wheel；未从本次源码重新构建完整 SDK，未运行完整 PCAP／OSF、可视化、硬件或 ROS 管线。新测试由现有 Python 测试任务自动发现；当前可见上游检查工作流需维护者批准，合并状态以 PR 为准。

## 第十一项贡献：pytransform3d 时序位姿末尾查询越界修复

- PR：[dfki-ric/pytransform3d #385](https://github.com/dfki-ric/pytransform3d/pull/385)，2026-10-06 提交至 develop，同日被维护者合并。
- 评审跟进：维护者感谢贡献；已通过 [PR 回复](https://github.com/dfki-ric/pytransform3d/pull/385#issuecomment-6011278898)致谢，GitHub 邮件通知与该讨论属于同一线程。
- 问题：默认 time_clipping=False 时，查询恰好等于最后一个采样时间通过范围校验，但后继采样索引越过数组末尾，标量、批量及坐标系链路查询均抛出 IndexError；单样本序列查询唯一时间也失败。
- 修改：仅将后继采样索引限制到最后一个有效样本；最后时间对应前后同一采样点，沿用已有零插值比例返回末尾位姿。真正超出范围的时间仍按既有规则抛出 ValueError，不开启外推。
- 验证：Windows／Python 3.12.14。21 项新增回归用例原实现 10 项失败，修复后全部通过；NumPy 2.5.3／SciPy 1.18.1 及 NumPy 1.26.4／SciPy 1.15.3 下全部 49 项变换管理器测试通过，包括 Graphviz PNG 导出。
- 覆盖：标量、零维数组、批量及重复末尾查询，非单位旋转与平移，解析可核对的螺旋运动插值，单样本序列，紧邻端点的合法及非法浮点时间，默认拒绝越界与可选截断，直接／逆向／多坐标系链路查询及成功查询后的时间状态恢复。
- 全仓库检查：NumPy 2.5.3 下 898 项通过、3 项因缺少可选 Open3D 跳过、1 项已有 test_matrix_requires_renormalization 在 1e-16 容差处失败；在未修改源文件上确认同一失败，NumPy 1.26.4 下也失败。本次未修改旋转实现或该测试。Black、Ruff、CI 阻断 flake8 及 Git 空白检查通过。
- 边界：验证 Python 刚体变换、ScLERP 与坐标系图接口，未运行真实机器人、ROS 节点或 SLAM 端到端管线；上游 CI 与合并状态以 PR 为准。

## 第十二项贡献：pytransform3d 异常查询后的时间状态恢复

- PR：[dfki-ric/pytransform3d #386](https://github.com/dfki-ric/pytransform3d/pull/386)，2026-10-06 提交至 develop，同日被维护者合并。
- 评审跟进：维护者再次感谢贡献，已在 [PR 回复](https://github.com/dfki-ric/pytransform3d/pull/386#issuecomment-6013002373)致谢；#385 和 #386 均被列入已合并的 [3.17.0 开发分支更新说明](https://github.com/dfki-ric/pytransform3d/pull/371)，不据此声称 PyPI 已发布该版本。
- 问题：get_transform_at_time 临时设置当前时间，但仅在查询成功后恢复；未知／不连通坐标系、超出时间范围或自定义变换异常会留下失败查询时间，后续普通查询使用错误时间或继续失败。
- 修改：在 finally 中恢复原 current_time，保持成功查询返回值、原异常对象和标量／数组时间类型与对象，不缓存或吞掉异常。
- 验证：Windows／Python 3.12.14。15 项新增回归用例原实现 13 项失败，修复后全部通过；NumPy 2.5.3／SciPy 1.18.1 和 NumPy 1.26.4／SciPy 1.15.3 下全部 43 项变换管理器测试通过。
- 覆盖：未知起点／终点、不连通坐标系、直接／逆向／多坐标系链路越界、自定义变换抛出特定异常对象、成功标量与批量查询；核对恢复原时间对象并使后续普通查询返回原有位姿。
- 全仓库检查：892 项通过、3 项可选 Open3D 测试跳过、1 项已有旋转矩阵 1e-16 容差测试在本机失败，与已核对的未修改源码结果一致；Black、Ruff、CI 阻断 flake8 和 Git 空白检查通过。
- 独立性与边界：基于官方 develop 独立提交，不包含或依赖 #385；Git 合并检查显示两项补丁可无冲突合并。验证 Python 刚体变换与时序坐标图，未运行 ROS 节点、硬件或端到端 SLAM；上游 CI 与合并状态以 PR 为准。

## 第十三项贡献：KISS-ICP 组织点云行填充解析修复

- PR：[PRBonn/kiss-icp #513](https://github.com/PRBonn/kiss-icp/pull/513)，2026-10-06 提交至 main，待评审。
- 问题：PointCloud2 的 row_step 可以大于 width × point_step。原 read_points 将数据按连续点读取，忽略每行末尾填充，从第二行开始错误解析坐标和逐点时间戳，影响点云输入及运动畸变补偿。
- 修改：按 height × width 和 row_step／point_step 构造具有行／点步长的 NumPy 视图，再按行展开；之后沿用字段选择、字节序转换及扁平索引规则。连续点云仍返回原始缓冲区的视图。
- 验证：Windows／Python 3.12.14。19 项新增测试原实现 11 项失败、8 项通过，修复后全部通过；NumPy 2.5.3 下全部 20 项仓库 Python 测试通过，NumPy 1.26.4 下 19 项读点测试通过；上游指定的 Black 23.1.0、isort 5.12.0 及 Git 空白检查通过。
- 覆盖：部分／整点大小的行末填充、点内空字节、单行／多行、三个支持的时间字段、无时间字段、字段筛选、重复扁平索引、组织输出点序、非本机字节序、空点云及无填充时的内存共享。
- 文件及原生模块验证：通过 rosbags 0.11.5 生成真实 ROS1 bag、ROS2 SQLite 与 ROS2 MCAP 文件并序列化真实消息，9 组格式／时间字段组合在原实现上均复现第二行错误；修复后坐标和时间正确，去畸变结果与解析可核对的纯平移运动一致，reset 重读通过。
- 已有 PR 兼容更新：为 [#512](https://github.com/PRBonn/kiss-icp/pull/512) 的合成测试消息补齐必需 row_step 字段，其原有 20 项测试仍通过；两项独立补丁无冲突合并，组合后的全部 39 项 Python 测试通过。未重复创建该问题的 PR。
- 边界：文件检查使用当前 checkout 的真实 Python 读点代码及发布版 KISS-ICP 1.3.0 Windows 原生扩展；未从源码重新构建原生库、安装完整 ROS 或运行硬件／端到端 SLAM。新测试由已有 Python CI 自动发现；上游 CI 与合并状态以 PR 为准。
- 邮件与评审：2026-10-06 刷新邮箱并核对先前 12 个 PR，无新的人工提问；此前已发送合并致谢并在 gtsam_points #106 回复 CI 核查结果，本轮无需重复回复自动通知。

## 第十四项贡献：MCAP ROS2 消息定义与通道绑定修复

- PR：[foxglove/mcap #1867](https://github.com/foxglove/mcap/pull/1867)，2026-10-06 基于最新 main 提交，待评审。
- 问题：ROS2 Writer 仅按 topic 缓存 channel。向同一话题写入另一已注册 schema 时，数据用新定义编码，却仍引用旧通道／旧定义；例如新 string data 消息被旧 int32 data 定义读成字符串长度，也可能使独立解码器拒绝消息。
- 修改：以 topic 和 schema.id 共同缓存通道，确保 Message 的编码定义与引用通道一致；切回原定义时复用原通道，同一 schema 跨话题仍分别创建并复用通道。
- 回归验证：Windows／Python 3.10.22。7 项新增测试原实现 6 项失败、1 项通过，修复后全部通过；覆盖不同消息类型、同名定义变更、独立注册的相同定义、返回原定义、同一定义跨话题，分别验证索引／顺序读取、无压缩／ZSTD 和多 chunk。
- 仓库验证：ROS2 包全部 26 项测试通过；MCAP 核心 39 项、Protobuf 支持 7 项、ROS1 支持 4 项，共 76 项通过。已有 Windows test_make_not_seeking 管道测试因之前在本机阻塞而排除。官方 LFS 测试数据经 SHA-256 校验，运行后恢复原指针。
- 独立实现验证：将两种自定义定位消息依次写入同一话题的真实磁盘文件，覆盖 NONE／ZSTD／LZ4 压缩。rosbags 0.11.5 独立 CDR 解码器在原实现上均拒绝定义与数据不匹配的消息，修复后正确读回三个定位结果及新增 frame_id。该外部检查使用不同类型名；同名多版本由 MCAP 回归测试验证，rosbags 本身按名称解析定义。
- 工程检查：Black、isort、flake8、pyright、Git 空白检查及隔离环境的 ROS2 源码包／wheel 构建通过。基于官方 f123d254 独立提交，不包含或依赖 #1862；测试自动纳入已有 Python CI。
- 上游验证：[Linux Python CI](https://github.com/foxglove/mcap/actions/runs/37422590642/job/112135037172) 的完整测试、lint、示例和四包构建已通过，[Python 跨语言一致性检查](https://github.com/foxglove/mcap/actions/runs/37422590642/job/112135037233)也已通过；其他语言检查状态以 PR 为准。
- 边界：验证 ROS2 CDR 与 MCAP 日志读写接口，未运行 ROS 节点、硬件或本机跨语言一致性测试；上游 CI 运行结果及合并状态以 PR 为准。
- 邮件与评审：2026-10-06 刷新网易邮箱并检查此前 13 个 PR，无新人工问题，已有合并致谢和 CI 分析回复无需重复发送。

## 第十五项贡献：SpatialMath 四元数对数小旋转精度修复

- PR：[rai-opensource/spatialmath-python #237](https://github.com/rai-opensource/spatialmath-python/pull/237)，2026-10-06 基于官方 master 的 2de78013 提交，待评审。
- 社区与方向：SpatialMath 提供机器人刚体姿态、四元数及李群运算；本次贡献对应 SLAM／定位中姿态增量与误差表示的数值计算。
- 问题：UnitQuaternion.Rx(1e-9).log().v 原来返回零，预期为 [5e-10, 0, 0]。acos(s / norm(q)) 在比值舍入为 1 时丢失角度，对稍大旋转也损失精度；标量、批量和非单位四元数均受影响。
- 修改：两个路径均以 atan2(norm(v), s) 计算主值角度，保留标量 log(norm(q))、原有零向量判定和负标量分支，不改变四元数的符号规范化或输入对象。
- 回归验证：新增 3 个方法，含 12 项子测试。原实现 8 项标量子测试、2 项批量子测试及负实轴精度检查失败；修复后通过。覆盖正负 1e-12 至 1e-4 弧度旋转、普通角度、单位与缩放四元数、标量／批量一致性、exp(log(q)) 往返、输入保留及接近负实轴的主值角度。
- 仓库验证：Windows／Python 3.12.14；NumPy 2.5.3／SciPy 1.18.1 和 NumPy 1.26.4／SciPy 1.15.3 下均完整执行 350 项测试通过、3 项跳过，并通过全部 12 项新子测试。使用 Agg 后端和上游 CI 的超时选项。
- 独立实现验证：100 个固定种子、不同轴和角度的旋转向量，经 SciPy Rotation 生成四元数并独立核对。分别验证单位标量、三倍缩放标量及单位批量，共 300 次比较；原实现 270 次超出 1e-13 相对误差阈值，修复后全部通过，最大相对误差约 3.6e-16，两套依赖结果一致。
- 工程检查：Black 23.10.0、flake8 的 E9／F63／F7／F82 语法及未定义名称检查、Git 空白检查通过；隔离环境源码包和 wheel 构建通过。只改动 quaternion.py 和已有四元数测试文件，测试由现有 CI 自动发现。
- 上游状态：[CI](https://github.com/rai-opensource/spatialmath-python/actions/runs/37426911749) 显示 action_required，等待维护者批准运行；尚未合并。另核对前一项 MCAP #1867，全部已执行检查已通过，部署／review 检查按工作流规则跳过。
- 边界：验证机器人姿态数学库及其完整 Python 测试，未运行 ROS 节点、机器人硬件或端到端 SLAM；不声称已改善实测定位精度。
- 邮件与评审：2026-10-06 刷新网易邮箱并核对此前 14 个 PR，无新的人工提问；先前合并致谢与 gtsam_points CI 分析回复已处理，无需重复回复自动通知。

## 第十六项贡献：KISS-ICP HeLiPR 完整末尾点读取修复

- PR：[PRBonn/kiss-icp #514](https://github.com/PRBonn/kiss-icp/pull/514)，2026-10-06 基于官方 main 的 1ffa7d75 独立提交，待评审。
- 问题：当文件恰好包含整数个完整记录时，get_data 使用严格小于边界，丢弃最后一个点；单记录文件因此在 np.stack([]) 处失败。丢失末尾时间戳还会使剩余点使用错误的时间归一化范围。
- 修改：将循环边界的 < 改为 <=；仅读取剩余字节至少为 chunk_size 的记录，保留 #338 为不完整尾记录引入的处理规则，不变更空文件、单时间戳归一化或其他读取策略。
- 回归验证：20 项新增参数化测试，原实现 15 项失败、5 项通过，修复后全部通过。覆盖 Avia、Aeva 原始／带 intensity 布局、Ouster、Velodyne 的单点与三点文件、不完整尾字节、全部字段，以及真实磁盘目录／GT 文件加载后的两帧公开 dataset 接口。
- 仓库验证：Windows／Python 3.12.14；NumPy 2.5.3 及 NumPy 1.26.4 下完整 Python 测试均为 21 项通过；上游固定版本 Black 23.1.0、isort 5.12.0 及 Git 空白检查通过。
- 原生接口验证：五种布局各两帧，共 10 组生成的二进制扫描文件。当前源码读取器与发布版 KISS-ICP 1.3.0 Windows 原生 Preprocessor 联合验证，纯平移去畸变结果与解析值一致；原实现均丢失末尾点，并使中间点的归一化时间与去畸变位置错误。两套 NumPy 环境结果一致。
- 独立性：只改动 HeLiPR 读取器的一行条件并新增专用测试文件，直接基于官方 main，不包含或依赖 #512／#513；测试自动纳入现有 Python API CI。
- 上游状态：[Python API CI](https://github.com/PRBonn/kiss-icp/actions/runs/37428708085) 及可见工作流均为 action_required，等待维护者批准运行，尚未合并。
- 边界：测试数据为按官方布局生成的磁盘文件，未下载真实 HeLiPR 录制数据、从源码重新构建完整原生库或运行 ROS 节点／机器人硬件／端到端里程计基准，不声称定位精度提升。
- 邮件与评审：刷新网易邮箱并核对此前 15 个 PR；pytransform3d #385 已合并并收到维护者致谢，已回复感谢审阅和合并。其他 PR 无新的人工问题；目前累计 16 项 PR，其中 3 项已合并。

## 第十七项贡献：manif 小角度 SO(3) 对数四元数符号修复

- PR：[artivis/manif #345](https://github.com/artivis/manif/pull/345)，2026-10-06 基于官方 devel 的 65166b3b 独立提交，待评审。
- 社区与方向：manif 是面向机器人状态估计的 C++ 李群库。本次贡献涉及 SLAM／定位中的旋转增量、SE(3) 位姿误差与解析 Jacobian。
- 问题：SO3Base::log 的一般角度分支根据 w 的符号选择主值分支，小角度分支却固定乘以 2。对表示相同旋转的 q 和 -q，后者返回相反旋转向量；例如绕 X 轴 1e-8 弧度的四元数全部取反后，原对数为 [-1e-8, 0, 0]，预期为 [1e-8, 0, 0]。SE(3) 的旋转／平移切向量及对数 Jacobian 也受影响。
- 修改：小角度系数在 w 小于 0 时选择 -2，否则为 2，与一般角度分支一致；保持阈值、一般角度计算、输入四元数和公开 API，补充解释主值分支的代码注释。
- 回归验证：在已有 SO3 和 SE3 测试文件中增加 float／double 类型测试，共 4 项测试、48 组轴／角度／类型／群组合；原实现 4 项均失败，修复后全部通过。覆盖正负单位四元数、轴向与非轴向旋转、小非零角度、阈值两侧；核对同一旋转／变换、相同切向量和 Jacobian、exp(log()) 往返，以及 SO3 的解析旋转向量。
- 完整核心验证：Windows／Clang 18.1.6、Eigen 3.4.0、GoogleTest 1.15.2；C++14 Debug 与基础 CPU 指令集构建。全部 17 个 CTest 程序、5,064 项 GoogleTest 通过，0 跳过、0 禁用；包括其他核心李群及 Bundle 测试。
- C++11 验证：单独编译 float／double 解析小角度和非零平移 SE3 往返检查，同一程序分别包含原始与修复头文件；原始版本失败，修复版本通过。该检查独立于 GoogleTest，不需要将库的最低标准升级到 C++14。
- 工程与上游：只改动一个库头文件及两个已有测试文件，Git 空白检查通过；单提交 9df3f60，不含其他社区补丁，测试自动进入已有跨平台 CI。[build-and-test](https://github.com/artivis/manif/actions/runs/37442637194)、release 和 documentation 均为 action_required，等待维护者批准运行，尚未合并。
- 边界：本机完整构建和运行核心 C++ 测试，未运行可选 Ceres／autodiff、Python 绑定、ROS 节点、机器人硬件或端到端 SLAM 基准，不声称实测定位精度提升。
- 邮件与评审：刷新网易邮箱并核对前 16 个 PR；pytransform3d #386 新近合并并收到维护者致谢，已回复感谢审阅、合并及更新说明中的贡献归属。其他 PR 没有新的人工提问；目前累计 17 项 PR，其中 4 项已合并。

## 第十八项贡献：pytransform3d 批量四元数重叠输出修复

- PR：[dfki-ric/pytransform3d #387](https://github.com/dfki-ric/pytransform3d/pull/387)，2026-10-06 基于官方 develop 的 7c0fd67 独立提交，待评审。
- 问题：batch_concatenate_quaternions 先写输出标量部，再计算向量部；当 out 与任一输入共享内存时，原标量已被覆盖。绕 X／Y 各 90° 的两个旋转，out=Q1 原输出约为 [0.5, 0.5, 0.353553, 0.5]，正确 Hamilton 乘积为 [0.5, 0.5, 0.5, 0.5]；连续原地姿态组合因此偏离独立输出结果。
- 修改：缓存标量结果，先在输入仍完整时计算并写入向量部，再写缓存的标量。支持与一个／两个操作数相同的 out，以及部分重叠和非连续视图；不复制完整输入或增加完整输出缓冲，保留公式、dtype、形状检查和返回的 out 对象，并在文档明确允许重叠。
- 回归验证：28 项新增参数化测试，原实现 22 项失败、6 项独立输出对照通过，修复后全部通过。覆盖 float32／float64、单四元数、一／二维批量、别名指向第一／第二／相同两输入、独立输出时输入保留，以及连续／跨步视图同时与两个输入重叠。参考值由标量四元数乘法计算；完整批量旋转模块 151 项通过。
- 全库验证：Windows／Python 3.12.14；NumPy 2.5.3／SciPy 1.18.1 及 NumPy 1.26.4／SciPy 1.15.3 下均为 941 项通过、3 项可选 Open3D 测试跳过、1 项 test_matrix_requires_renormalization 的 1e-16 容差测试失败。该问题已在库代码修改前复现，旋转实现和原测试未改动，不将结果表述为全库全部通过。
- 独立实现验证：两套依赖环境各 512 次固定种子随机旋转组合，使用 SciPy Rotation 独立核对矩阵及单位范数。原实现每套均有 384 次超出容差；修复后全部通过。float32／float64 各 32 步原地姿态组合与 SciPy 累积结果一致，最终矩阵最大绝对误差约 5.9e-8／2.2e-16，原误差均约 5.3e-4。
- 工程与独立性：Black、Ruff、上游 CI 阻断 flake8 和 Git 空白检查通过；只改批量四元数实现与已有测试文件，单提交 9677bd4。直接基于最新官方 develop，不包含其他未合并 PR；先前 #385／#386 已被上游合并。
- 上游状态：PR 尚未合并，创建后的 statusCheckRollup 为空；上游及个人 fork 均暂无本分支运行记录，不声称 CI 已通过。现有 Python 工作流配置为 push 触发。
- 边界：验证批量姿态数学 API、完整 Python 测试和独立数值实现，未运行 ROS 节点、机器人硬件或端到端 SLAM 基准，不声称实测定位精度提升。
- 邮件与评审：刷新网易邮箱并核对前 17 个 PR 的评论、行内评审和合并状态；无新人工问题，已处理的合并致谢不重复发送。目前累计 18 项 PR，其中 4 项已合并。

## 第十九项贡献：pytransform3d 四元数顺序转换重叠输出修复

- PR：[dfki-ric/pytransform3d #388](https://github.com/dfki-ric/pytransform3d/pull/388)，2026-10-06，待评审。
- 问题：batch_quaternion_xyzw_from_wxyz 与反向转换逐分量写入 out，输出与输入共享内存时覆盖后续读取所需的分量。wxyz 单位四元数 [1, 0, 0, 0] 原地转 xyzw，原实现返回全零；反向单位四元数转换返回全一。两者都会破坏姿态。ROS 常用的 xyzw 与数学库常用的 wxyz 之间转换涉及此类接口，但本轮没有运行 ROS 管线。
- 修改：用 NumPy may_share_memory 检查可能的共享内存，仅在需要时复制输入，再沿用已有逐分量赋值；保留输出对象、dtype、形状和独立输出时的分配方式。保守的内存边界检查可能对实际不重叠的部分视图产生复制，避免复杂跨步视图的精确重叠检查成本。两处 docstring 明确允许重叠。
- 回归验证：74 项新增参数化用例，原实现 26 项失败、48 项通过，修复后全部通过。覆盖双向转换、float32／float64／int64、单个／一维／二维批量、原地／独立／默认输出、只读独立输入、连续／跨步部分重叠、单位姿态和空批量。完整批量旋转模块 197 项通过。
- 全库验证：Windows／Python 3.12.14；NumPy 2.5.3／SciPy 1.18.1 及 NumPy 1.26.4／SciPy 1.15.3 下均为 987 项通过、3 项可选 Open3D 测试跳过、1 项 test_matrix_requires_renormalization 的 1e-16 容差测试失败。该失败此前已在原基线复现，对应实现和测试未修改，不声称全库全部通过。
- 独立实现验证：两套环境各 512 次固定种子随机旋转矩阵对照；原地顺序转换后使用 SciPy Rotation 解码，并与转换前矩阵核对。原实现每套 512 次均失败；修复后全部通过，最大矩阵绝对误差约 7.54e-8。
- 工程与独立性：Black、Ruff、CI 阻断 flake8 和 Git 空白检查通过；只改两个现有文件，基于官方 develop 的 7c0fd67 独立提交 dfa0e96，不包含 #387。Git HTTPS 超时后，通过本机 keyring 认证的官方 GitHub API 发布，并核对远端树与本地一致；保留 fork 原有分支。
- 上游状态：PR 未合并，创建后的 statusCheckRollup 为空，无 CI 通过声明。
- 边界：没有运行 ROS 节点、硬件或端到端 SLAM 基准，不声称定位精度提升。
- 邮件与评审：刷新网易邮箱并检查前 18 个 PR 的评论、行内评审和状态，无新人工问题，未重复发送已处理回复。目前累计 19 项 PR，其中 4 项已合并。

## 第二十项贡献：KISS-ICP 点云端序读取保留消息数据

- PR：[PRBonn/kiss-icp #515](https://github.com/PRBonn/kiss-icp/pull/515)，2026-10-06，待评审。
- 问题：read_points 对与主机端序不同的点云调用 byteswap(inplace=True)，其数组引用 cloud.data。只读 bytes 或 rosbags 解码出的只读 NumPy 数组因此报错；可写 bytearray／NumPy 缓冲区则被修改，第二次读取坐标不同，选择部分字段时还会只交换部分记录。
- 修改：仅将一行字节交换改为 inplace=False；反端序分支使用交换后的副本，同端序路径保留现有零拷贝行为。消息数据和端序标志保持一致，不影响后续消费者。
- 回归验证：新增 36 项参数化用例，原实现 16 项失败、20 项通过，修复后全部通过。覆盖大小端、bytes／bytearray／NumPy 缓冲区、全部／部分字段、float32 坐标、float64 时间戳、uint16 ring、重复读取、点云提取、uvs 选择、空点云及同端序内存共享。Windows／Python 3.12.14 下 NumPy 2.5.3 与 NumPy 1.26.4 的完整 Python 套件各 37 项通过。
- 日志与原生验证：NumPy 2.x 下生成 6 组 ROS1 bag／ROS2 SQLite／ROS2 MCAP 文件，分别含大小端 PointCloud2 负载。通过源代码 RosbagDataset 读取、原始消息缓冲区保留、同消息反复解析、非坐标字段读取、数据集 reset 和发布版原生去畸变的解析运动对照；原实现会拒绝三组反端序只读 rosbags 数据。这些是生成测试文件，不是传感器采集基准。
- 兼容性验证：仅在本机内存中组合 #512 NaN 时间戳过滤、#513 行填充修复与本轮修复，两套 NumPy 环境各 75 项 Python 测试通过；另有六组大小端与行填充组合验证重复读取和消息保留。公开分支保持独立，不含其他待合并 PR。
- 工程：Black、isort 与 Git 空白检查通过；仅改现有读取器一行，新增独立测试文件。基于官方 main 的 1ffa7d7，单提交 0a59fd9；使用本机 keyring 认证的官方 GitHub API 发布，并核对远端树与本地一致。
- 上游状态：PR 未合并；ROS nodes、Style Check、Python API、C++ API、Publish to PyPI.org 工作流均显示 action_required，需维护者批准运行，不表述为 CI 已通过。
- 边界：使用发布版原生绑定运行去畸变与导入测试，未重建完整 C++／Python 包，没有运行 ROS 节点、硬件或完整 SLAM 基准，不声称实测定位精度提升。
- 邮件与评审：刷新网易邮箱并检查前 19 个 PR 的评论、行内评审和状态，无新的人工问题，未重复发送已处理回复。目前累计 20 项 PR，其中 4 项已合并。
