import re

# 定义宏和变量的映射关系
macro_to_variable = {
    'CONFIG_OMNI_PLATFORM_SECTION_STM': 'OMNI_PLATFORM',
    'CONFIG_OMNI_TARGET_SECTION_STM32F407XX': 'OMNI_TARGET',
    'CONFIG_OMNI_BOARD_SECTION_STM32F407IG': 'OMNI_BOARD',
    'CONFIG_OMNI_LINKER_SCRIPT_SECTION_CUSTOM': 'OMNI_LINKER_SCRIPT',
    'CONFIG_OMNI_RTOS_SECTION_FREERTOS': 'OMNI_RTOS',
    'CONFIG_OMNI_USB_SECTION_CHERRYUSB': 'OMNI_USB',
    'CONFIG_OMNI_SHELL_SECTION_LETTER': 'OMNI_SHELL'
}

# 定义变量的值
variable_values = {
    'OMNI_PLATFORM': 'stm',
    'OMNI_TARGET': 'stm32f407xx',
    'OMNI_BOARD': 'f407ig',
    'OMNI_LINKER_SCRIPT': 'custom',
    'OMNI_RTOS': 'freertos',
    'OMNI_USB': 'cherryusb',
    'OMNI_SHELL': 'letter'
}

# 读取 omni_kconfig.h 文件
with open('omni/omni_kconfig.h', 'r') as file:
    kconfig_content = file.read()

# 读取 CMakeLists.txt 文件
with open('CMakeLists.txt', 'r') as file:
    cmake_content = file.readlines()

# 找到 # omni settings start 和 # omni settings end 注释行
start_index = None
end_index = None
for i, line in enumerate(cmake_content):
    if '# omni settings start' in line:
        start_index = i
    elif '# omni settings end' in line:
        end_index = i
        break

# 如果找到了 # omni settings start 和 # omni settings end 注释行，先删除之间的内容再插入新的变量值
if start_index is not None and end_index is not None:
    new_lines = []
    for macro, variable in macro_to_variable.items():
        if re.search(rf'#define {macro} 1', kconfig_content):
            new_lines.append(f'set({variable} "{variable_values[variable]}")\n')
    cmake_content[start_index + 1:end_index] = new_lines

# 写回 CMakeLists.txt 文件
with open('CMakeLists.txt', 'w') as file:
    file.writelines(cmake_content)

print("CMakeLists.txt is updated.")