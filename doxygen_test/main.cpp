/**
 * @file
 * @brief      一个简单的文件注释
 * @details    文件注释,充当模板,测试使用
 *             多行的场景
 * @author     goodluck
 * @version    v1.0
 * @date       2023-12-11
 * @copyright  北京金橙子科技有限公司
 */

#include <iostream>


/**
 * @brief		结构体注释
 * @details	    详细描述一下这个数据结构是做什么的
 */
typedef struct
{
	int x;      ///< 点在三维空间中的x坐标
	int y;      ///< 点在三维空间中的y坐标
	int z;      ///< 点在三维空间中的z坐标
} Point;


/**
 * @brief		三原色
 * @details	    三原色红绿蓝
 */
enum COLOR{
    RED=0,      ///<  红色
    GREEN=1,    ///<  绿色
    YELLOW=2    ///<  黄色
};


#define TRUE		1           ///< 宏，定义TRUE为1
#define FALSE		0           ///< 宏，定义FALSE为0
int g_status = 0;               ///< 全局变量，返回当前状态
static int count = 0;           ///< 静态变量，统计计算了多少次
typedef unsigned short WORD;    ///< 类型别名，word









/**
 * @brief       cppstyle函数
 * @details	    This is the detail description.
 * @param[in]  *data              上报数据指针
 * @param[in]  len                上报数据长度
 * @param[in]  report_fail_try_type    上报失败重新注册类型 \n
 * @ref NB_REPFAIL_REG_TRY 出错立即重试 \n
 * @ref NB_REPFAIL_REG_DELAY_TRY 出错延缓重试，在延迟期间如果正常则重新延缓，适用于高频率上报（上报失败重新注册超时15min） \n
 * @ref NB_REPFAIL_REG_NO_TRY 出错不重试
 * @param[out]	outArgName output argument description
 * @return  函数执行结果
 * - NB_NOTIFY_SUCCESS      上报成功
 * - NB_NOTIFY_FAIL        上报失败
 * - NB_IOT_REGIST_FAILED 注册失败返回
 * - Others  其他错误
 * @retval		OK		成功
 * @retval		ERROR	错误
 * @par 示例:
 * @code
 *    int ret = register_all(&data, len, RT_TYPE_T1)
 * @endcode
 * @see :: xx表
 */
int cppstyle(int inArgName, int& outArgName)
{
    int a = inArgName;        /// 一个局部变量
    outArgName = a + a;
    return 0;
}



int main()
{
    std::cout << "simple doc test" << std::endl;
}
