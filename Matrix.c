#include "matrix.h"


/*====================================函数区====================================*/


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
// To check whether 2 Python arr have the same shape
//
// in:
//  PyList[ PyList[ PyFloat ]]
//  PyList[ PyList[ PyFloat ]]
// out:
//  PyBool
static PyBool isshape(PyObject* self, PyObject* args){
    PyList arr_a;
    PyList arr_b;
    if (!PyArg_ParseTuple(args, "OO", &arr_a, &arr_b)){
        return NULL;
    }
    if (PyList_Check(arr_a) && PyList_Check(arr_b)){
        if (
            _isshape(
                _arr2mat(arr_a), _arr2mat(arr_b)
            )
        ) Py_RETURN_TRUE;
        else Py_RETURN_FALSE;
    }
    else return NULL;
}


// PRIVATE
//
// Add 2 Matrix
//
// in:
//  Matrix
//  Matrix
// out:
//  Matrix
Matrix _mat_add(Matrix mat_a, Matrix mat_b){
    if (_isshape(mat_a, mat_b)){
        // Initialize Matrix
        DBL** ret = (DBL**)MLC(
            SZF(DBL*) * mat_a.m
        );

        // Allocate memory
        for (RGT i = 0; i < mat_a.m; i++){
            ret[i] = (DBL*)MLC(
                SZF(DBL) * mat_a.n
            );
        }

        // Give value
        for (RGT i = 0; i < mat_a.m; i++){
            for (RGT j = 0; j < mat_a.n; j++){
                ret[i][j] = mat_a.mat[i][j]+mat_b.mat[i][j];
            }
        }
        Matrix mat_ret = {ret, mat_a.m, mat_a.n};
        return mat_ret;
    }
}


// PUBLIC
//
// Add 2 Python arr
//
// in:
//  PyList[ PyList[ PyFloat ]]
//  PyList[ PyList[ PyFloat ]]
// out:
//  PyList[ PyList[ PyFloat ]]
static PyList mat_add(PyObject* self, PyObject* args){
    PyList arr_a;
    PyList arr_b;
    if (!PyArg_ParseTuple(args, "OO", &arr_a, &arr_b)){
        return NULL;
    }
    if (PyList_Check(arr_a) && PyList_Check(arr_b)){
        Matrix mat_a = _arr2mat(arr_a);
        Matrix mat_b = _arr2mat(arr_b);
        if (_isshape(mat_a, mat_b)){
            return _mat2arr(_mat_add(mat_a, mat_b));
        }
        else return NULL;
    }
    else return NULL;
}
