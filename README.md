# Lite3 基于MotionSDK的动作录制与重播
### 运行
同官方文档，建立build文件夹后，进入build，先后运行：
```bash
cmake .. -DBUILD_PLATFORM=x86 # 或arm
make -j
```
之后即可运行`./record`进行动作录制，注意需等待提示可以录制后再行录制。

为解决示教动作的震颤问题，加入了滑动平均滤波，使用`smooth`即可平滑动作数据文件。

运行`./replay`即可重放录制。

录制前先删除`data.txt`或将其重命名为一个其他的动作文件。
### 代码说明
动作数据文件格式为每行一帧，12个关节角度，中间以空格隔开。

`src/motionexample.cpp`中加入了：
- Replay()，主要用于重放动作；
- SaveTraj()，主要用于录制动作；
- movingAverageFilter()，平滑滤波，使用readJointData()读取数据，对每列即每个关节的数据序列平滑，再使用writeFilteredData()写入新文件

`record.cpp`中先将机器人站起，后提示可以录制，将关节序列录制到`data.txt`10秒后结束。

`replay.cpp`中先将机器人站起，后读取`data.txt`，将每一行的关节角都用Replay()复现。

`smooth.cpp`中设置源数据文件以及输出的数据文件，以及滑动窗口的大小，数字越大越平滑，但动作幅度也会越小。
### 修改说明
目前的录制和重复频率都是50Hz，如需调整需修改除了smooth以外的三个代码文件。

如需其他动作开始录制，则修改站起部分。