#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // 文件绝对路径
    char filepath[1024] = {};
    // 文件的创建时间
    char CreationTime[21] = {};
    // 文件上一次访问的时间
    char LastAccessTime[21] = {};
    // 文件最近一次修改的时间
    char LastWriteTime[21] = {};
    // 年月日时分秒
    int year = 2000;
    int month = 1;
    int day = 1;
    int hour = 0;
    int minute = 0;
    int sec = 0;

    // 用于时间转换存储的变量
    SYSTEMTIME temp_time;

    // 修改编码
    system("chcp 65001");

    printf("请输入文件绝对或相对路径(回车结束） ：");
    gets(filepath);
    //scanf("%s", filepath);

    /* 
        打开文件句柄 
        允许对设备进行只写访问
        如果有其他对象要用该设备，我们要求它们不得修改设备的数据;
        如果有其他内核对象要使用该设备，则要求它们不得读取设备的数据;
        告诉CreateFile打开一个已有的文件或设备，如果文件或设备不存在，那么CreateFile调用会失败
        告诉系统忽略文件的重解析属性(重解析属性允许一个文件系统过滤器对打开文件、读取文件、写入文件以及关闭文件这些行为进行修改)
    */
    HANDLE hFile = CreateFile(filepath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("打开文件句柄失败，错误：%s\n", GetLastError());
        system("pause");
        return -1;
    }
    else
    {
        printf("文件打开成功\r\n");
    }

    printf("日期输入格式为：年-月-日 时:分:秒 （注意为英文，输入完后回车，例：2020-01-01 00:00:00)\r\n");
    printf("请输入新的创建时间 ：");
    gets(CreationTime);
    //scanf("%s", CreationTime);
    printf("请输入新的上一次访问的时间 ：");
    gets(LastAccessTime);
    //scanf("%s", LastAccessTime);
    printf("请输入新的最近一次修改的时间 ：");
    gets(LastWriteTime);
    //scanf("%s", LastWriteTime);

    // 定义FILETIME变量 用于存储设置时间的变量
    FILETIME ft, LocalFileTime1, LocalFileTime2, LocalFileTime3;

    // 星期 方便起见用0表示周日
    temp_time.wDayOfWeek = 0;
    // 毫秒
    temp_time.wMilliseconds = 0;

    // 解析字符串 写入temp_time变量
    sscanf(CreationTime, "%d-%d-%d %d:%d:%d", &temp_time.wYear, &temp_time.wMonth, &temp_time.wDay, 
        &temp_time.wHour, &temp_time.wMinute, &temp_time.wSecond);
    // 根据一个FILETIME结构的内容，载入一个SYSTEMTIME结构
    SystemTimeToFileTime(&temp_time, &ft);
    // 此函数根据UTC将本地文件时间转换为文件时间
    LocalFileTimeToFileTime(&ft, &LocalFileTime1);

    sscanf(LastAccessTime, "%d-%d-%d %d:%d:%d", &temp_time.wYear, &temp_time.wMonth, &temp_time.wDay, 
        &temp_time.wHour, &temp_time.wMinute, &temp_time.wSecond);
    SystemTimeToFileTime(&temp_time, &ft);
    LocalFileTimeToFileTime(&ft, &LocalFileTime2);

    sscanf(LastWriteTime, "%d-%d-%d %d:%d:%d", &temp_time.wYear, &temp_time.wMonth, &temp_time.wDay, 
        &temp_time.wHour, &temp_time.wMinute, &temp_time.wSecond);
    SystemTimeToFileTime(&temp_time, &ft);
    LocalFileTimeToFileTime(&ft, &LocalFileTime3);

    // 设置文件时间
    if(SetFileTime(hFile, &LocalFileTime1, &LocalFileTime2, &LocalFileTime3))
    {
        printf("修改文件时间成功！\r\n");
    }
    else
    {
        printf("修改文件时间失败，错误：%s\r\n", GetLastError());
        system("pause");
        return -1;
    }

    // 关闭文件句柄
    CloseHandle(hFile);

    system("pause");
    return 0;
}