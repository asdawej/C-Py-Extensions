#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "__defines.h"


/*====================================声明区====================================*/


#define PyList PyObject*
#define PyFloat PyObject*
#define PyBool PyObject*
#define bool_t int


// double** mat
// int m
// int n
TDF struct {
    DBL** mat;
    int m;
    int n;
} Matrix;


/*  模块函数声明  */


Matrix _arr2mat(PyList);
PyList _mat2arr(Matrix);
bool_t _isshape(Matrix, Matrix);
static PyBool isshape(PyObject*, PyObject*);
static PyList mat_add(PyObject*, PyObject*);


/*==================================文档&配置区==================================*/


/*  函数文档  */


static char isshape_doc[] = {
"To check whether 2 arrays are the same shape\n\
in:\n\
list[list[float]]\n\
list[list[float]]\n\
out:\n\
bool\n"
};


static char mat_add_doc[] = {
"Add 2 arrays\n\
in:\n\
list[list[float]]\n\
list[list[float]]\n\
out:\n\
list[list[float]]\n"
};


// 模块函数表
static PyMethodDef
MatrixMethods[] = {
    {
        "isshape",
        isshape,
        METH_VARARGS,
        isshape_doc
    },
    {
        "mat_add",
        mat_add,
        METH_VARARGS,
        mat_add_doc
    },
    {NULL, NULL, 0, NULL}
};


// 模块文档
static char Matrix_doc[] = "Matrix Module";


// 模块配置
static struct PyModuleDef
MatrixModule = {
    PyModuleDef_HEAD_INIT,
    "Matrix",
    Matrix_doc,
    -1,
    MatrixMethods
};


// 模块初始化函数
PyMODINIT_FUNC
PyInit_Matrix(void){
    return PyModule_Create(&MatrixModule);
}
