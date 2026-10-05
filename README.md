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

[贡献计划](docs/CONTRIBUTION_PLAN.md) · [公开 PR 记录](https://github.com/pulls?q=is%3Apr+author%3Adddd-jh)

- **[evo #786](https://github.com/MichaelGrupp/evo/pull/786) · 已提交，待评审：** 在已有遍历中提取轨迹坐标系，移除 ROS bag 的第二次扫描和额外原始消息缓存；增加 ROS 1／ROS 2 回归测试。
- 本机验证：126 项测试与 2 项子测试通过，Black 和 mypy 检查通过。环境及验证范围见 PR。
- **[small_gicp #141](https://github.com/koide3/small_gicp/pull/141) · 已提交，待评审：** 修复串行、OpenMP、TBB 体素降采样错误保留越界点的问题；新增 16 项回归测试，覆盖有效坐标边界、混合点云及颜色平均。
- 本机原生 C++ 验证：相同测试修改前 7 项失败，修改后 16 项全部通过，包括 OpenMP 1／4 线程与真实 TBB 运行。完整上游测试状态见 PR。
- **[KISS-ICP #512](https://github.com/PRBonn/kiss-icp/pull/512) · 已提交，待评审：** 修复过滤 NaN 点后逐点时间戳错位的问题，避免运动畸变补偿使用错误时间戳。
- 验证：19 项新增回归测试修改前 12 项失败，修改后全部通过；本机 20 项 Python 测试及 6 组真实 ROS 1／ROS 2 bag 与原生畸变补偿检查通过。原生扩展使用发布版 Windows wheel，完整上游构建状态见 PR。
- **[RKO-LIO #189](https://github.com/PRBonn/rko_lio/pull/189) · 已提交，待评审：** 修复激光／IMU 排序器在输入结束时丢弃已有 IMU 覆盖的缓存激光帧的问题，保留覆盖不足尾帧的处理规则。
- 验证：11 项新增排序测试修改前 3 项失败，修改后全部通过；全部 53 项 Python 测试及 Ruff 检查通过。本机使用发布版 Windows 原生扩展，完整源码构建与 ROS 运行状态见 PR。
- **[KISS-SLAM #60](https://github.com/PRBonn/kiss-slam/pull/60) · 已提交，待评审：** 修复二维栅格导出为 ROS 地图时的图像尺寸与方向错误，保留栅格的世界坐标位置。
- 验证：13 项 PNG／YAML 文件回归测试在原导出方向下 10 项失败，修复后全部通过；覆盖非方形地图、正负原点、不同分辨率及占用／空闲／未知状态，并加入上游 CI。本机验证范围为文件导出及坐标约定，未运行完整 SLAM 或 ROS 地图服务器。
- **[MapClosures #118](https://github.com/PRBonn/MapClosures/pull/118) · 已提交，待评审：** 修复二维闭环配准中错误的反射修正，使输出保持合法旋转，并使用一致的旋转计算平移。
- 验证：9 项原生 C++ 回归测试修改前 5 项失败，修改后全部通过；Release CTest 连续五轮通过，测试接入上游跨平台 CI。本机验证配准模块，完整库构建与地图闭环管线状态见 PR。
- **[GLIM #329](https://github.com/koide3/glim/pull/329) · 已提交，待评审：** 修复全局定位时间晚于已有里程计时轨迹管理器越界读取的问题；保留当前全局变换及插值样本，允许数据补齐后再次更新。
- 验证：启用容器边界检查时，8 项原生 C++ 测试中原实现 6 项越界终止，修复后全部通过。覆盖最新时间边界、重复更新、数据补齐、正常插值及历史样本保留；新增 Eigen 独立测试工程与 GCC／Clang CI，本机未运行完整 GLIM 或 ROS 管线。
