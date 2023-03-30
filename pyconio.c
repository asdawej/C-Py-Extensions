#include "pyconio.h"


/*====================================函数区====================================*/


static PyBool
py_kbhit(PyObject* self, PyObject* args){
    if (!PyArg_ParseTuple(args, "")){
        return NULL;
    }
    return PyLong_FromLong(_kbhit());
}


static PyChar
py_getch(PyObject* self, PyObject* args){
    if (!PyArg_ParseTuple(args, "")){
        return NULL;
    }
    return PyLong_FromLong(_getch());
}
