/*************************************************************************
*
*              Author: b51
*                Mail: b51live@gmail.com
*            FileName: eigen_extensions.cc
*
*          Created On: Thu 24 Oct 2019 11:06:41 AM CST
*     Licensed under The MIT License [see LICENSE for details]
*
************************************************************************/

#include <iostream>
#include <Python.h>
#include <Eigen/Geometry>
#include "numpy/arrayobject.h"

static PyObject* toRotationMatrix(PyObject* self, PyObject* args) {
  double roll, yaw, pitch;

  if (!PyArg_ParseTuple(args, "ddd", &roll, &yaw, &pitch)) {
    return nullptr;
  }

  Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitY());
  Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitZ());

  Eigen::Quaterniond q = yawAngle * pitchAngle * rollAngle;
  Eigen::Matrix3d Rotation = q.normalized().toRotationMatrix();
  std::cout << Rotation << std::endl;

  PyArrayObject *R;
  npy_intp dims[] = {3, 3};
  R = (PyArrayObject*) PyArray_SimpleNew(2, dims, NPY_DOUBLE);//, Rotation.data());

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      *((double*)R->data + 3 * i + j) = Rotation(i, j);
    }
  }
  return PyArray_Return(R);
}

static PyMethodDef EigenMethods[] = {
    {"toRotationMatrix", toRotationMatrix, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef eigen_module = {
    PyModuleDef_HEAD_INIT,
    "EigenToPy",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    EigenMethods
};

PyMODINIT_FUNC
PyInit_EigenToPy(void) {
    import_array();
    return PyModule_Create(&eigen_module);
}
