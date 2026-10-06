# 董巾航 · Jinhang Dong

电子科技大学硕士在读，关注 **激光惯导 SLAM、机器人定位与多传感器融合**。

[项目主页](https://dddd-jh.github.io/) · [在线简历](https://dddd-jh.github.io/resume.html)

## 无人清扫车 · 国产计算平台与自主导航

参与“面向智慧环卫场景的国产系统无人清扫车关键技术攻关”团队项目，基于已有无人车平台，面向地平线征程 6 系列计算平台开展建图定位、导航和系统集成。

**我的工作主线是 SLAM。** 导航与运动规划由团队其他成员负责；这里链接团队公开资料，具体系统进度和测试状态以该资料为准。

[团队仓库](https://github.com/Doribelove/autolabor-robot-nav/tree/robot_j6m_ws) · [项目说明与工作安排](https://github.com/Doribelove/autolabor-robot-nav/blob/robot_j6m_ws/horizon_challenge.md)

## 工程基础与拓展

- 已有工程环境：Ubuntu 20.04、ROS 1。
- 关注方向：LiDAR / IMU、定位与建图、传感器协同、SLAM 评测。
- 正在拓展：ROS 2 生态、点云配准与 SLAM 工具的开源维护。
- 求职主线：机器人／无人车 SLAM 与定位算法，拓展自动驾驶定位与具身智能中的空间感知。

## 开源工作

截至 2026-10-06：22 项已提交 PR，4 项已合并、10 项待评审（其中 1 项草稿）、8 项已关闭未合并。关闭记录保留为工程尝试，不作为上游已接受成果。

[贡献计划](docs/CONTRIBUTION_PLAN.md) · [公开 PR 记录](https://github.com/pulls?q=is%3Apr+author%3Adddd-jh)

另有[上游评审与验证记录](docs/VALIDATION_REVIEWS.md)：为 evo 现有时间匹配优化 PR 提供兼容性补丁及三个回归用例，以公开 TUM 轨迹核对匹配结果；为 GLIM 现有编译修复提供三个 fmt 版本的独立 C++ 验证。这类工作不计入个人新提交 PR 数。

- **[evo #786](https://github.com/MichaelGrupp/evo/pull/786) · 已合并：** 在已有遍历中提取轨迹坐标系，移除 ROS bag 的第二次扫描和额外原始消息缓存；增加 ROS 1／ROS 2 回归测试。
- 本机验证：126 项测试与 2 项子测试通过，Black 和 mypy 检查通过。环境及验证范围见 PR。
- **[small_gicp #141](https://github.com/koide3/small_gicp/pull/141) · 已提交，待评审：** 修复串行、OpenMP、TBB 体素降采样错误保留越界点的问题；新增 16 项回归测试，覆盖有效坐标边界、混合点云及颜色平均。
- 本机原生 C++ 验证：相同测试修改前 7 项失败，修改后 16 项全部通过，包括 OpenMP 1／4 线程与真实 TBB 运行。完整上游测试状态见 PR。
- **[KISS-ICP #512](https://github.com/PRBonn/kiss-icp/pull/512) · 已关闭，未合并：** 修复过滤 NaN 点后逐点时间戳错位的问题，避免运动畸变补偿使用错误时间戳。
- 验证：19 项新增回归测试修改前 12 项失败，修改后全部通过；本机 20 项 Python 测试及 6 组真实 ROS 1／ROS 2 bag 与原生畸变补偿检查通过。原生扩展使用发布版 Windows wheel，完整上游构建状态见 PR。
- **[RKO-LIO #189](https://github.com/PRBonn/rko_lio/pull/189) · 已合并：** 修复激光／IMU 排序器在输入结束时丢弃已有 IMU 覆盖的缓存激光帧的问题，保留覆盖不足尾帧的处理规则。
- 验证：11 项新增排序测试修改前 3 项失败，修改后全部通过；全部 53 项 Python 测试及 Ruff 检查通过。本机使用发布版 Windows 原生扩展，完整源码构建与 ROS 运行状态见 PR。
- 评审跟进：维护者认可修复并希望只保留包内改动，PR 已精简为一行修复，2026-10-05 已被上游合并；原回归用例留存在本机。
- **[KISS-SLAM #60](https://github.com/PRBonn/kiss-slam/pull/60) · 已关闭，未合并：** 修复二维栅格导出为 ROS 地图时的图像尺寸与方向错误，保留栅格的世界坐标位置。
- 验证：13 项 PNG／YAML 文件回归测试在原导出方向下 10 项失败，修复后全部通过；覆盖非方形地图、正负原点、不同分辨率及占用／空闲／未知状态，并加入上游 CI。本机验证范围为文件导出及坐标约定，未运行完整 SLAM 或 ROS 地图服务器。
- **[MapClosures #118](https://github.com/PRBonn/MapClosures/pull/118) · 已关闭，未合并：** 修复二维闭环配准中错误的反射修正，使输出保持合法旋转，并使用一致的旋转计算平移。
- 验证：9 项原生 C++ 回归测试修改前 5 项失败，修改后全部通过；Release CTest 连续五轮通过，测试接入上游跨平台 CI。本机验证配准模块，完整库构建与地图闭环管线状态见 PR。
- **[GLIM #329](https://github.com/koide3/glim/pull/329) · 已提交，待评审：** 修复全局定位时间晚于已有里程计时轨迹管理器越界读取的问题；保留当前全局变换及插值样本，允许数据补齐后再次更新。
- 验证：启用容器边界检查时，8 项原生 C++ 测试中原实现 6 项越界终止，修复后全部通过。覆盖最新时间边界、重复更新、数据补齐、正常插值及历史样本保留；新增 Eigen 独立测试工程与 GCC／Clang CI，本机未运行完整 GLIM 或 ROS 管线。
- **[gtsam_points #106](https://github.com/koide3/gtsam_points/pull/106) · 已提交，待评审：** 修复 KNN／半径搜索结果引用临时索引回调产生的悬空引用，使结果对象持有回调，保留引用捕获的行为。
- 验证：12 项原生 C++／GoogleTest 回归测试原实现 8 项失败，修复后全部通过，独立 Release CMake／CTest 通过。测试自动纳入仓库现有 CI；[上游 Linux/GCC](https://github.com/koide3/gtsam_points/actions/runs/37332671677/job/112064704547) 完整构建及全部 98 项 CTest 已通过，包括新增 12 项测试。本机未构建完整 GTSAM／CUDA 库；上游 CUDA 构建被中断，其余取消配置仍未验证。

- **[MCAP #1862](https://github.com/foxglove/mcap/pull/1862) · 已提交，待评审：** 修复 ROS 2 Time／Duration 内置备用定义将秒数视为无符号整数的问题，使负秒数正确编码和解码；显式嵌套定义保留现有行为。
- 验证：50 项新增测试原实现 24 项失败，修复后全部通过；四个 Python 包共 119 项测试通过，格式、类型检查及源码包／wheel 构建通过。1 项 Windows 管道测试未完成并被排除；本机未运行 ROS 节点或跨语言一致性测试。上游 Linux Python CI 的完整测试、示例、lint、build 及跨语言 Python 一致性检查已通过，其他 CI 状态见 PR。

- **[Ouster SDK #726](https://github.com/ouster-lidar/ouster-sdk/pull/726) · 已提交，待评审：** 修复轨迹插值对 uint64 激光时间戳的减法溢出，保留纳秒精度及原始时间戳类型，覆盖逐列位姿写入和原生点云变换。
- 验证：52 项新增测试原实现 14 项失败；修复后全部 67 项相关测试在 NumPy 1.x／2.x 及无 SciPy 实现下通过。flake8 通过，mypy 保留 3 项原有类型诊断。使用发布版原生绑定验证，本机未重新构建完整 SDK 或运行硬件／ROS 管线；上游可见检查需维护者批准。

- **[pytransform3d #385](https://github.com/dfki-ric/pytransform3d/pull/385) · 已合并：** 修复默认时序位姿查询在最后一个采样时间发生数组越界的问题，保留真正越界时间的拒绝规则。
- 验证：21 项新增回归用例原实现 10 项失败，修复后全部通过；NumPy 1.x／2.x 下全部 49 项变换管理器测试通过。全仓库 898 项通过、3 项可选 Open3D 测试跳过，1 项原有旋转矩阵精度测试在本机失败，已在未修改源码上核对并说明；Black、Ruff 与 CI 阻断 flake8 检查通过。

- **[pytransform3d #386](https://github.com/dfki-ric/pytransform3d/pull/386) · 已合并：** 修复时序坐标变换查询异常后污染管理器当前时间的问题，确保后续正常查询使用原时间，保留原异常。
- 验证：15 项新增回归用例原实现 13 项失败，修复后全部通过；NumPy 1.x／2.x 下全部 43 项变换管理器测试通过。全仓库 892 项通过、3 项可选 Open3D 测试跳过、1 项原有精度测试失败；Black、Ruff 与 CI 阻断 flake8 检查通过。

- **[KISS-ICP #513](https://github.com/PRBonn/kiss-icp/pull/513) · 已关闭，未合并：** 修复读取组织点云时忽略 row_step 的问题，跳过行末填充字节，避免后续行坐标及逐点时间戳被错误解析；连续点云保留零拷贝读取。
- 验证：19 项新增回归用例原实现 11 项失败，修复后全部通过；NumPy 1.x／2.x 检查通过，本机全部 20 项 Python 测试通过。9 组真实 ROS1 bag、ROS2 SQLite／MCAP 文件验证解析、重读及原生去畸变结果；与 #512 合并后的 39 项测试通过。原生扩展使用发布版 Windows wheel，未运行完整 ROS／硬件管线。

- **[MCAP #1867](https://github.com/foxglove/mcap/pull/1867) · 已提交，待评审：** 修复 ROS2 写入器在同一话题换用消息定义时错误复用旧通道的问题，避免数据按错误定义解码；返回原定义时复用原通道。
- 验证：7 项新增回归用例原实现 6 项失败，修复后全部通过；ROS2 包全部 26 项、四个 Python 包共 76 项测试通过，1 项已有 Windows 管道测试被排除。3 组三种压缩的真实 MCAP 定位消息文件经独立 rosbags 解码器验证；格式、类型检查及源码包／wheel 构建通过。未运行 ROS 节点或硬件管线；[上游 Linux Python CI](https://github.com/foxglove/mcap/actions/runs/37422590642/job/112135037172) 的完整测试、lint、示例及构建通过，Python 一致性检查也通过，其他 CI 状态见 PR。

- **[SpatialMath #237](https://github.com/rai-opensource/spatialmath-python/pull/237) · 已提交，待评审：** 修复四元数对数使用 acos 导致小角度姿态增量丢失或失真的问题，标量与批量接口改用稳定角度计算，保持负标量主值分支及原有零向量规则。
- 验证：新增 3 个回归测试方法，包含 12 项子测试；原实现 8 项标量子测试、2 项批量子测试及负实轴精度检查失败，修复后全部通过。NumPy 1.x／2.x 下完整测试均为 350 项通过、3 项跳过；300 组独立 SciPy 对照检查通过，Black、语法检查及源码包／wheel 构建通过。未运行 ROS 或机器人硬件，上游 CI 待维护者批准。

- **[KISS-ICP #514](https://github.com/PRBonn/kiss-icp/pull/514) · 已关闭，未合并：** 修复 HeLiPR 二进制扫描在记录完整时丢失最后一点的问题，避免末尾时间戳丢失影响其他点的时间归一化；保留忽略不完整尾记录的规则。
- 验证：20 项新增回归测试原实现 15 项失败、5 项通过，修复后全部通过。NumPy 1.x／2.x 下完整 Python 测试均为 21 项通过；五种布局的 10 组生成文件经发布版原生去畸变接口核对解析结果，Black、isort 通过。未重新构建原生库、运行真实 HeLiPR 基准或 ROS／硬件管线；上游 CI 待维护者批准。

- **[manif #345](https://github.com/artivis/manif/pull/345) · 已提交，待评审：** 修复 SO(3) 小角度对数对等价四元数 q／-q 返回相反旋转向量的问题，使 SE(3) 位姿对数和 Jacobian 保持符号一致。
- 原生 C++ 验证：4 项 float／double 新测试覆盖 48 组场景，原实现全部失败、修复后通过；完整核心套件 17 个 CTest 程序、5,064 项 GoogleTest 全部通过，C++11 独立解析值与位姿往返检查通过。未运行可选 Ceres／autodiff、Python 绑定或 ROS／硬件管线；上游 CI 待维护者批准。

- **[pytransform3d #387](https://github.com/dfki-ric/pytransform3d/pull/387) · 已关闭，未合并：** 修复批量四元数乘法在输出数组与输入重叠时破坏姿态组合结果的问题，支持原地计算和连续／非连续重叠视图，保留输出对象与原有计算公式。
- 验证：28 项新增测试原实现 22 项失败，修复后通过；完整批量旋转模块 151 项通过。NumPy 1.x／2.x 下全库均为 941 项通过、3 项可选测试跳过、1 项已在原基线复现的矩阵极严容差测试失败；每套环境 512 次独立 SciPy 比较及 float32／float64 的 32 步原地姿态组合通过。Black、Ruff、CI 阻断 flake8 与 Git 空白检查通过；未运行 ROS／硬件管线，PR 尚无 CI 检查记录。

- **[pytransform3d #388](https://github.com/dfki-ric/pytransform3d/pull/388) · 已关闭，未合并：** 修复批量四元数 wxyz／xyzw 顺序转换在原地写入或输出视图与输入重叠时覆盖分量的问题；此前单位姿态原地转换会变成无效四元数。只在可能共享内存时复制输入，保留输出对象、dtype 和独立输出路径。
- 验证：74 项新增测试原实现 26 项失败，修复后通过；完整批量旋转模块 197 项通过。NumPy 1.x／2.x 下全库各 987 项通过、3 项跳过、1 项既有矩阵极严容差测试失败；每套环境 512 次独立 SciPy 旋转比较通过。格式及静态检查通过；未运行 ROS／硬件管线，PR 暂无 CI 检查记录。

- **[KISS-ICP #515](https://github.com/PRBonn/kiss-icp/pull/515) · 已关闭，未合并：** 修复反端序 PointCloud2 读取原地改动消息数据或拒绝只读缓冲区的问题，使坐标与时间戳能稳定重读，同端序路径保留零拷贝。
- 验证：36 项新增测试原实现 16 项失败，修复后通过；NumPy 1.x／2.x 下完整 Python 套件各 37 项通过。NumPy 2.x 下 6 组生成的 ROS1 bag／ROS2 SQLite／MCAP 文件通过读取、缓冲区保留、重读、重置和发布版原生去畸变检查。与 #512／#513 临时组合后两套环境各 75 项测试通过，另有 6 组端序与行填充组合检查通过；Black、isort、Git 空白检查通过。未重建完整原生库或运行 ROS／硬件管线，上游 CI 待维护者批准。

- 评审跟进：已[回复 pytransform3d 维护者的贡献动机问题](https://github.com/dfki-ric/pytransform3d/pull/387#issuecomment-6016875249)。后续优先处理既有反馈、真实用户报告与精简补丁，减少连续的小型提交；关闭状态及原因见贡献计划。

- **[PyPose #411](https://github.com/pypose/pypose/pull/411) · 草稿，待评审：** 针对已有用户 Issue，修复 EKF 更新时在旧状态计算观测 Jacobian 与残差的问题，使更新与预测状态一致；同步修正文档示例的测量时序。
- 验证：一个参数化测试覆盖四个线性／非线性、零／非零创新场景，原实现全部失败，补丁后通过；相关 EKF／动态模型／UKF 共 9 项通过。完整库 110 项通过、2 项跳过、1 项未修改计时器除零失败，同一失败在原主分支复现（106 项通过、2 项跳过、1 项失败）。Sphinx HTML 文档、语法及 Git 空白检查通过；本机 CPU 验证，未运行 CUDA、ROS 或硬件，上游 CI 尚无结果。

- **[gtsam_points #108](https://github.com/koide3/gtsam_points/pull/108) · 已提交，待评审：** 针对已有用户编译报告，验证并提交报告者提出的单行修复：将 Boost 分支的 NoneValue 从 constexpr 改为 inline const，使 GTSAM 4.2 可兼容旧版 Boost 的非字面量 none_t。
- 验证：真实 GTSAM／Boost 头文件的四组 C++17 编译与运行对照；原代码在 GTSAM 4.2＋Boost 1.74 失败，修复后四组均通过。空／非空矩阵默认参数及 optional 构造、重置正常；源码见贡献计划。本机 Windows／Clang 验证，未构建完整 GTSAM、gtsam_points、GLIM、CUDA 或 ROS，尚无上游 CI 结果。
