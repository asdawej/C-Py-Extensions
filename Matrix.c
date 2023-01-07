#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "__defines.h"

#define PyList PyObject*
#define PyFloat PyObject*
#define PyBool PyObject*
#define bool_t int


//  double** mat
//  int m
//  int n
TDF struct {
    DBL** mat;
    int m;
    int n;
} Matrix;


Matrix _arr2mat(PyList);
PyList _mat2arr(Matrix);
bool_t _isshape(Matrix, Matrix);
static PyBool isshape(PyObject*, PyObject*);


static char isshape_doc[] = {
"To check whether 2 arrays are the same shape\n\
in:\n\
    list[list[float]]\n\
    list[list[float]]\n\
out:\n\
    bool"
};


static PyMethodDef
MatrixMethods[] = {
    {
        "isshape",
        isshape,
        METH_VARARGS,
        isshape_doc
    },
    {NULL, NULL, 0, NULL}
};


static char Matrix_doc[] = "Matrix Module";


static struct PyModuleDef
MatrixModule = {
    PyModuleDef_HEAD_INIT,
    "Matrix",
    Matrix_doc,
    -1,
    MatrixMethods
};


PyMODINIT_FUNC
PyInit_Matrix(void){
    return PyModule_Create(&MatrixModule);
}


/*========================================================================*/


int main(){
    time_t t; time(&t);
    struct tm tt = *localtime(&t);
    PRF("Matrix Module by asdawej\n");
    PRF("Log in %d-%d-%d %d:%d:%d\n",
        tt.tm_year+1900, tt.tm_mon+1, tt.tm_mday,
        tt.tm_hour, tt.tm_min, tt.tm_sec
    );
    return 0;
}


// PRIVATE
//
// Convert a Python array to the Matrix
//
// in:
//  PyList[ PyList[ PyFloat ]]
// out:
//  Matrix
Matrix _arr2mat(PyList arr){
    // Initialize Matrix
    Matrix ret;
    ret.m = PyList_Size(arr);
    ret.n = PyList_Size(
        PyList_GetItem(arr, 0)
    );

    // Allocate memory
    DBL** mat = (DBL**)MLC(
        SZF(DBL*) * ret.m
    );
    for (RGT i = 0; i < ret.m; i++){
        mat[i] = (DBL*)MLC(
            SZF(DBL) * ret.n
        );
    }

    // Give value
    for (RGT i = 0; i < ret.m; i++){
        for (RGT j = 0; j < ret.n; j++){
            mat[i][j] = PyFloat_AsDouble(
                PyList_GetItem(
                    PyList_GetItem(arr, i), j
                )
            );
        }
    }
    return ret;
}


// PRIVATE
//
// Convert a Matrix to the Python array
//
// in:
//  Matrix
// out:
//  PyList[ PyList[ PyFloat ]]
PyList _mat2arr(Matrix mat){
    PyList arr = PyList_New(0);
    for (RGT i = 0; i < mat.m; i++){
        PyList temp = PyList_New(0);
        for (RGT j = 0; j < mat.n; j++){
            PyList_Append(
                temp, PyFloat_FromDouble(mat.mat[i][j])
            );
        }
        PyList_Append(arr, temp);
    }
    return arr;
}


// PRIVATE
//
// To check whether 2 Matrix have the same shape
//
// in:
//  Matrix
//  Matrix
// out:
//  bool_t
bool_t _isshape(Matrix arr1, Matrix arr2){
    if (arr1.m == arr2.m && arr1.n == arr2.n) return 1;
    else return 0;
}


// PUBLIC
//
// To check whether 2 Python array have the same shape
//
// in:
//  PyList[ PyList[ PyFloat ]]
//  PyList[ PyList[ PyFloat ]]
// out:
//  PyBool
static PyBool isshape(PyObject* self, PyObject* args){
    PyList arr_a = PyTuple_GetItem(args, 0);
    PyList arr_b = PyTuple_GetItem(args, 1);
    if (PyList_Check(arr_a) && PyList_Check(arr_b)){
        if (
            _isshape(
                _arr2mat(arr_a),
                _arr2mat(arr_b)
            )
        ) Py_RETURN_TRUE;
        else Py_RETURN_FALSE;
    }
    else return NULL;
}
