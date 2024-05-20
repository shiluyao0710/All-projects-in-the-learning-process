/*
1、包含Python.h头文件，以便使用Python API。
2、使用void Py_Initialize()初始化Python解释器，
3、使用PyObject *PyImport_ImportModule(const char *name)和PyObject *PyObject_GetAttrString(PyObject *o, const char *attr_name)获取sys.path对象，
   并利用int PyList_Append(PyObject *list, PyObject *item)将当前路径.添加到sys.path中，以便加载当前的Python模块(Python文件即python模块)。
4、使用PyObject *PyImport_ImportModule(const char *name)函数导入Python模块，并检查是否有错误。
5、使用PyObject *PyObject_GetAttrString(PyObject *o, const char *attr_name)函数获取Python函数对象，并检查是否可调用。
6、使用PyObject *Py_BuildValue(const char *format, ...)函数将C类型的数据结构转换成Python对象，作为Python函数的参数,没有参数不需要调用
7、使用PyObject *PyObject_CallObject(PyObject *callable, PyObject *args)函数调用Python函数，并获取返回值。
8、使用int PyArg_Parse(PyObject *args, const char *format, ...)函数将返回值转换为C类型，并检查是否有错误,没有返回值时不需要调用。
9、使用void Py_DECREF(PyObject *o)函数释放所有引用的Python对象。Orangepi Zero2 全志H616开发学习文档
10、结束时调用void Py_Finalize()函数关闭Python解释器。
相关的函数参数说明参考网站（网站左上角输入函数名即可开始搜索）：
https://docs.python.org/zh-cn/3/c-api/import.html
*/

#include <Python.h>
#include <stdio.h>

void garbage_init(void)
{
	Py_Initialize();

	//将当前路径添加到sys.path中
	PyObject *sys = PyImport_ImportModule("sys");
	PyObject *path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyUnicode_FromString("."));
}	

char *garbage_category(char *category)
{
	//导入para模块
	PyObject *pModule = PyImport_ImportModule("garbage");
	if(!pModule)
	{
		PyErr_Print();
		printf("ERROR:failed to load garbage.py.\n");
		goto FAILED_MODULE;
	}

	//导入say_funny函数对象
	PyObject *pFunc = PyObject_GetAttrString(pModule, "alibabacloud");
	if(!pFunc)
	{
		PyErr_Print();
		printf("ERROR:failed to load alibabacloud function.\n");
		goto FAILED_FUNC;
	}

	//调用say_funny函数并获取返回值
	PyObject *pValue = PyObject_CallObject(pFunc, NULL);
	if(!pValue)
	{
		PyErr_Print();
		printf("ERROR:function call failed.\n");
		goto FAILED_VALUE;
	}
	
	//将返回值转化为c类型
	char *result = NULL;
	if(!PyArg_Parse(pValue, "s", &result))
	{
		PyErr_Print();
		printf("ERROR:parase failed");
		goto FAILED_RESULT;
	}

	category = (char *)malloc(sizeof(char) * (strlen(result) + 1));
	memset(category, 0, (strlen(result) + 1));
	strncpy(category, result, (strlen(result) + 1));
	//释放所有引用的Python对象
FAILED_RESULT:
	Py_DECREF(pValue);
FAILED_VALUE:
	Py_DECREF(pFunc);
FAILED_FUNC:
	Py_DECREF(pModule);
FAILED_MODULE:
	return category;
}

void garbage_final(void)
{
	//释放所有引用的Python对象
	Py_Finalize();
}

