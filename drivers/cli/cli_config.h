#ifndef CLI_CONFIG_H
#define CLI_CONFIG_H

#include "omni/omni_config.h"

/**
 * @brief 是否使用默认shell任务while循环
 *        使能此宏，则`shellTask()`函数会一直循环读取输入，一般使用操作系统建立shell
 *        任务时使能此宏，关闭此宏的情况下，一般适用于无操作系统，在主循环中调用`shellTask()`
 */
#if defined(CONFIG_SHELL_TASK_WHILE)
#define     SHELL_TASK_WHILE            CONFIG_SHELL_TASK_WHILE
#endif /* CONFIG_SHELL_TASK_WHILE */

/**
 * @brief 是否使用命令导出方式
 *        使能此宏后，可以使用`SHELL_EXPORT_CMD()`等导出命令
 *        定义shell命令，关闭此宏的情况下，需要使用命令表的方式
 */
#if defined(CONFIG_SHELL_USING_CMD_EXPORT)
#define     SHELL_USING_CMD_EXPORT      CONFIG_SHELL_USING_CMD_EXPORT
#endif /* CONFIG_SHELL_USING_CMD_EXPORT */

/**
 * @brief 是否使用shell伴生对象
 *        一些扩展的组件(文件系统支持，日志工具等)需要使用伴生对象
 */
#if defined(CONFIG_SHELL_USING_COMPANION)
#define     SHELL_USING_COMPANION       CONFIG_SHELL_USING_COMPANION
#endif /* CONFIG_SHELL_USING_COMPANION */

/**
 * @brief 支持shell尾行模式
 */
#if defined(CONFIG_SHELL_SUPPORT_END_LINE)
#define     SHELL_SUPPORT_END_LINE      CONFIG_SHELL_SUPPORT_END_LINE
#endif /* CONFIG_SHELL_SUPPORT_END_LINE */

/**
 * @brief 是否在输出命令列表中列出用户
 */
#if defined(CONFIG_SHELL_HELP_LIST_USER)
#define     SHELL_HELP_LIST_USER        CONFIG_SHELL_HELP_LIST_USER
#endif /* CONFIG_SHELL_HELP_LIST_USER */

/**
 * @brief 是否在输出命令列表中列出变量
 */
#if defined(CONFIG_SHELL_HELP_LIST_VAR)
#define     SHELL_HELP_LIST_VAR         CONFIG_SHELL_HELP_LIST_VAR
#endif /* CONFIG_SHELL_HELP_LIST_VAR */

/**
 * @brief 是否在输出命令列表中列出按键
 */
#if defined(CONFIG_SHELL_HELP_LIST_KEY)
#define     SHELL_HELP_LIST_KEY         CONFIG_SHELL_HELP_LIST_KEY
#endif /* CONFIG_SHELL_HELP_LIST_KEY */

/**
 * @brief 是否在输出命令列表中展示命令权限
 */
#if defined(CONFIG_SHELL_HELP_SHOW_PERMISSION)
#define     SHELL_HELP_SHOW_PERMISSION  CONFIG_SHELL_HELP_SHOW_PERMISSION
#endif /* CONFIG_SHELL_HELP_SHOW_PERMISSION */

/**
 * @brief 使用LF作为命令行回车触发
 *        可以和SHELL_ENTER_CR同时开启
 */
#if defined(CONFIG_SHELL_ENTER_LF)
#define     SHELL_ENTER_LF              CONFIG_SHELL_ENTER_LF
#endif /* CONFIG_SHELL_ENTER_LF */

/**
 * @brief 使用CR作为命令行回车触发
 *        可以和SHELL_ENTER_LF同时开启
 */
#if defined(CONFIG_SHELL_ENTER_CR)
#define     SHELL_ENTER_CR              CONFIG_SHELL_ENTER_CR
#endif /* CONFIG_SHELL_ENTER_CR */

/**
 * @brief 使用CRLF作为命令行回车触发
 *        不可以和SHELL_ENTER_LF或SHELL_ENTER_CR同时开启
 */
#if defined(CONFIG_SHELL_ENTER_CRLF)
#define     SHELL_ENTER_CRLF            CONFIG_SHELL_ENTER_CRLF
#endif /* CONFIG_SHELL_ENTER_CRLF */

/**
 * @brief 使用执行未导出函数的功能
 *        启用后，可以通过`exec [addr] [args]`直接执行对应地址的函数
 * @attention 如果地址错误，可能会直接引起程序崩溃
 */
#if defined(CONFIG_SHELL_EXEC_UNDEF_FUNC)
#define     SHELL_EXEC_UNDEF_FUNC       CONFIG_SHELL_EXEC_UNDEF_FUNC
#endif /* CONFIG_SHELL_EXEC_UNDEF_FUNC */

/**
 * @brief shell命令参数最大数量
 *        包含命令名在内，超过16个参数并且使用了参数自动转换的情况下，需要修改源码
 */
#if defined(CONFIG_SHELL_PARAMETER_MAX_NUMBER)
#define     SHELL_PARAMETER_MAX_NUMBER  CONFIG_SHELL_PARAMETER_MAX_NUMBER
#endif /* CONFIG_SHELL_PARAMETER_MAX_NUMBER */

/**
 * @brief 历史命令记录数量
 */
#if defined(CONFIG_SHELL_HISTORY_MAX_NUMBER)
#define     SHELL_HISTORY_MAX_NUMBER    CONFIG_SHELL_HISTORY_MAX_NUMBER
#endif /* CONFIG_SHELL_HISTORY_MAX_NUMBER */

/**
 * @brief 双击间隔(ms)
 *        使能宏`SHELL_LONG_HELP`后此宏生效，定义双击tab补全help的时间间隔
 */
#if defined(CONFIG_SHELL_DOUBLE_CLICK_TIME)
#define     SHELL_DOUBLE_CLICK_TIME     CONFIG_SHELL_DOUBLE_CLICK_TIME
#endif /* CONFIG_SHELL_DOUBLE_CLICK_TIME */

/**
 * @brief 快速帮助
 *        作用于双击tab的场景，当使能此宏时，双击tab不会对命令进行help补全，而是直接显示对应命令的帮助信息
 */
#if defined(CONFIG_SHELL_QUICK_HELP)
#define     SHELL_QUICK_HELP            CONFIG_SHELL_QUICK_HELP
#endif /* CONFIG_SHELL_QUICK_HELP */

/**
 * @brief 保存命令返回值
 *        开启后会默认定义一个`RETVAL`变量，会保存上一次命令执行的返回值，可以在随后的命令中进行调用
 *        如果命令的`SHELL_CMD_DISABLE_RETURN`标志被设置，则该命令不会更新`RETVAL`
 */
#if defined(CONFIG_SHELL_KEEP_RETURN_VALUE)
#define     SHELL_KEEP_RETURN_VALUE     CONFIG_SHELL_KEEP_RETURN_VALUE
#endif /* CONFIG_SHELL_KEEP_RETURN_VALUE */

/**
 * @brief 管理的最大shell数量
 */
#if defined(CONFIG_SHELL_MAX_NUMBER)
#define     SHELL_MAX_NUMBER            CONFIG_SHELL_MAX_NUMBER
#endif /* CONFIG_SHELL_MAX_NUMBER */

/**
 * @brief shell格式化输出的缓冲大小
 *        为0时不使用shell格式化输出
 */
#if defined(CONFIG_SHELL_PRINT_BUFFER)
#define     SHELL_PRINT_BUFFER          CONFIG_SHELL_PRINT_BUFFER
#endif /* CONFIG_SHELL_PRINT_BUFFER */

/**
 * @brief shell格式化输入的缓冲大小
 *        为0时不使用shell格式化输入
 * @note shell格式化输入会阻塞shellTask, 仅适用于在有操作系统的情况下使用
 */
#if defined(CONFIG_SHELL_SCAN_BUFFER)
#define     SHELL_SCAN_BUFFER           CONFIG_SHELL_SCAN_BUFFER
#endif /* CONFIG_SHELL_SCAN_BUFFER */

/**
 * @brief 获取系统时间(ms)
 *        定义此宏为获取系统Tick，如`HAL_GetTick()`
 * @note 此宏不定义时无法使用双击tab补全命令help，无法使用shell超时锁定
 */
#define     SHELL_GET_TICK()            0

/**
 * @brief 使用锁
 * @note 使用shell锁时，需要对加锁和解锁进行实现
 */
#if defined(CONFIG_SHELL_USING_LOCK)
#define     SHELL_USING_LOCK            CONFIG_SHELL_USING_LOCK
#endif /* CONFIG_SHELL_USING_LOCK */

/**
 * @brief shell内存分配
 *        shell本身不需要此接口，若使用shell伴生对象，需要进行定义
 */
#define     SHELL_MALLOC(size)          0

/**
 * @brief shell内存释放
 *        shell本身不需要此接口，若使用shell伴生对象，需要进行定义
 */
#define     SHELL_FREE(obj)             0

/**
 * @brief 是否显示shell信息
 */
#if defined(CONFIG_SHELL_SHOW_INFO)
#define     SHELL_SHOW_INFO             CONFIG_SHELL_SHOW_INFO
#endif /* CONFIG_SHELL_SHOW_INFO */

/**
 * @brief 是否在登录后清除命令行
 */
#if defined(CONFIG_SHELL_CLS_WHEN_LOGIN)
#define     SHELL_CLS_WHEN_LOGIN        CONFIG_SHELL_CLS_WHEN_LOGIN
#endif /* CONFIG_SHELL_CLS_WHEN_LOGIN */

/**
 * @brief shell默认用户
 */
#if defined(CONFIG_SHELL_DEFAULT_USER)
#define     SHELL_DEFAULT_USER          CONFIG_SHELL_DEFAULT_USER
#endif /* CONFIG_SHELL_DEFAULT_USER */

/**
 * @brief shell默认用户密码
 *        若默认用户不需要密码，设为""
 */
#if defined(CONFIG_SHELL_DEFAULT_USER_PASSWORD)
#define     SHELL_DEFAULT_USER_PASSWORD CONFIG_SHELL_DEFAULT_USER_PASSWORD
#endif /* CONFIG_SHELL_DEFAULT_USER_PASSWORD */

/**
 * @brief shell自动锁定超时
 *        shell当前用户密码有效的时候生效，超时后会自动重新锁定shell
 *        设置为0时关闭自动锁定功能，时间单位为`SHELL_GET_TICK()`单位
 * @note 使用超时锁定必须保证`SHELL_GET_TICK()`有效
 */
#if defined(CONFIG_SHELL_LOCK_TIMEOUT)
#define     SHELL_LOCK_TIMEOUT          CONFIG_SHELL_LOCK_TIMEOUT
#endif /* CONFIG_SHELL_LOCK_TIMEOUT */

/**
 * @brief 使用函数签名
 *        使能后，可以在声明命令时，指定函数的签名，shell 会根据函数签名进行参数转换，
 *        而不是自动判断参数的类型，如果参数和函数签名不匹配，会停止执行命令
 */
#if defined(CONFIG_SHELL_USING_FUNC_SIGNATURE)
#define     SHELL_USING_FUNC_SIGNATURE  CONFIG_SHELL_USING_FUNC_SIGNATURE
#endif /* CONFIG_SHELL_USING_FUNC_SIGNATURE */

/**
 * @brief 支持数组参数
 *        使能后，可以在命令中使用数组参数，如`cmd [1,2,3]`
 *        需要使能 `SHELL_USING_FUNC_SIGNATURE` 宏，并且配置 `SHELL_MALLOC`, `SHELL_FREE`
 */
#if defined(CONFIG_SHELL_SUPPORT_ARRAY_PARAM)
#define     SHELL_SUPPORT_ARRAY_PARAM   CONFIG_SHELL_SUPPORT_ARRAY_PARAM
#endif /* CONFIG_SHELL_SUPPORT_ARRAY_PARAM */

#endif /* CLI_CONFIG_H */
