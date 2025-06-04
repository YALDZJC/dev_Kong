/**
 * @file assert.cpp
 * @author 竹节虫 (k.yixiang@qq.com)
 * @brief 断言.基于南航的断言修改而来，添加断言后log的显示
 * @version 1.0.0
 * @date 2025-06-04
 *
 * @copyright SZPU-RCIA (c) 2025
 *
 */

#include <cassert>

#include "User/HAL/LOGGER/logger.hpp"
#include <main.h>

const char *assert_file = nullptr;
int assert_line = 0;
const char *assert_function = nullptr;
const char *assert_expression = nullptr;

/**
 * @brief 断言函数
 * @param file 文件名
 * @param line 行号
 * @param function 函数名
 * @param expression 表达式
 */
void __assert_func(const char *file, int line, const char *function, const char *expression)
{
    __disable_irq();

    assert_file = file;
    assert_line = line;
    assert_function = function;
    assert_expression = expression;

    auto &logger = HAL::LOGGER::Logger::getInstance();

    // 打印断言失败信息
    logger.fatal("file:%s", assert_file);
    logger.fatal("line:%d", assert_line);
    logger.fatal("function:%s", assert_function);
    logger.fatal("Assertion failed: %s", assert_expression);

    while (true)
        __NOP();
}
