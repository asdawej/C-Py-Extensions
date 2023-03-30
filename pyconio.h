#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <conio.h>
#include "__defines.h"


/*====================================声明区====================================*/


#define PyChar PyObject*
#define PyBool PyObject*


/*  模块函数声明  */


static PyBool py_kbhit(PyObject*, PyObject*);
static PyChar py_getch(PyObject*, PyObject*);


/*====================================配置区====================================*/


// 模块函数表
static PyMethodDef
pyconioMethods[] = {
    {
        "py_kbhit",
        py_kbhit,
        METH_VARARGS,
        NULL
    },
    {
        "py_getch",
        py_getch,
        METH_VARARGS,
        NULL
    },
    {NULL, NULL, 0, NULL}
};


// 模块配置
static struct PyModuleDef
pyconioModule = {
    PyModuleDef_HEAD_INIT,
    "pyconio",
    NULL,
    -1,
    pyconioMethods
};


// 模块初始化函数
PyMODINIT_FUNC
PyInit_pyconio(void){
    return PyModule_Create(&pyconioModule);
}
