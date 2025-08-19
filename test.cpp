/// @file main.cpp
/// @author your name (you@domain.com)
/// @brief 
/// @version 0.1
/// @date 2022-09-13 
/// @copyright Copyright (c) 2022


#include "udpsocket.hpp"
#include "udpserver.hpp"
#include "sender.h"
#include "dr_timer.h"
#include "receiver.h"
#include "motionexample.h"
#include <iostream>
#include <time.h>
#include <string.h>
#include <fstream>


using namespace std;

MotionExample robot;  


int main(int argc, char* argv[]){
    const std::string input_filename = "data.txt";    // 输入文件
    const std::string output_filename = "filtered_data.txt";  // 输出文件
    const int window_size = 5;  // 滑动窗口大小（建议3-5）

    // 存储关节数据：joints[关节序号][帧序号]
    std::vector<std::vector<double>> joints;

    // 1. 读取输入文件
    if (!robot.readJointData(input_filename, joints)) {
        return 1;
    }

    // 检查是否读取到12个关节
    if (joints.size() != 12) {
        std::cerr << "错误：输入文件应包含12个关节数据" << std::endl;
        return 1;
    }

    // 2. 对每个关节单独进行滑动平均滤波
    std::vector<std::vector<double>> filtered_joints;
    filtered_joints.reserve(12);
    for (const auto& joint_data : joints) {
        filtered_joints.push_back(robot.movingAverageFilter(joint_data, window_size));
    }

    // 3. 将滤波后的数据写入输出文件
    if (!robot.writeFilteredData(output_filename, filtered_joints)) {
        return 1;
    }

    std::cout << "滤波完成！结果已保存至 " << output_filename << std::endl;
    return 0;
}