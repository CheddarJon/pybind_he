#define PY_SSIZE_T_CLEAN
#include <Python.h>

static int numargs=0;

struct MockLweStruct {
	int32_t a;
	int32_t b;
	double c;
};

typedef struct MockLweStruct MockLweStruct;

static MockLweStruct lweParams[] = {
	{.a = 1, .b = 1, .c = 1.0},
	{.a = 2, .b = 2, .c = 2.0},
	{.a = 3, .b = 3, .c = 3.0}
};

static PyObject*
emb_getarg(PyObject *self, PyObject *args)
{
	int arg;
	if (!PyArg_ParseTuple(args, "i:getarg", &arg))
		return NULL;

	if (arg >= 0 && arg < 3) {
		MockLweStruct tmp = lweParams[arg];
		return Py_BuildValue("iid", tmp.a, tmp.b, tmp.c);
	}
	else {
		return NULL;
	}
}

/* Return the number of arguments of the application command line */
static PyObject*
emb_numargs(PyObject *self, PyObject *args)
{
	if(!PyArg_ParseTuple(args, ":numargs"))
		return NULL;
	return PyLong_FromLong(numargs);
}

static PyMethodDef EmbMethods[] = {
	{"numargs", emb_numargs, METH_VARARGS,
	 "Return the number of arguments received by the process."},
	{"getarg", emb_getarg, METH_VARARGS,
	 "Return the integer passed as argument."},
	{NULL, NULL, 0, NULL}
};

static PyModuleDef EmbModule = {
	PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods,
	NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_emb(void)
{
	return PyModule_Create(&EmbModule);
}

int
main(int argc, char *argv[])
{
	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;
	int i;

	if (argc < 3) {
		fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
		return 1;
	}

	numargs = argc;
	PyImport_AppendInittab("emb", &PyInit_emb);
    
	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault(argv[1]);
	/* Error checking of pName left out */

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule == NULL) {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		return 1;
	}

	pFunc = PyObject_GetAttrString(pModule, argv[2]);
	/* pFunc is a new reference */

	if (pFunc && PyCallable_Check(pFunc)) {
		pArgs = PyTuple_New(argc - 3);
		for (i = 0; i < argc - 3; ++i) {
			pValue = PyLong_FromLong(atoi(argv[i + 3]));
			if (!pValue) {
				Py_DECREF(pArgs);
				Py_DECREF(pModule);
				fprintf(stderr, "Cannot convert argument\n");
				return 1;
			}
			/* pValue reference stolen here: */
			PyTuple_SetItem(pArgs, i, pValue);
		}
		pValue = PyObject_CallObject(pFunc, pArgs);
		Py_DECREF(pArgs);
		if (pValue != NULL) {
			printf("Result of call: %ld\n", PyLong_AsLong(pValue));
			Py_DECREF(pValue);
		}
		else {
			Py_DECREF(pFunc);
			Py_DECREF(pModule);
			PyErr_Print();
			fprintf(stderr,"Call failed\n");
			return 1;
		}
	}
	else {
		if (PyErr_Occurred())
			PyErr_Print();
		fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
	}
	Py_XDECREF(pFunc);
	Py_DECREF(pModule);

	if (Py_FinalizeEx() < 0) {
		return 120;
	}
	return 0;
}
