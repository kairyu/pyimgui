/*
 * Additional config for imgui compilation.
 *
 * We don't want to touch sources from git submodule in order to configure
 * imgui so we force include using `-inlcude` flag during compilation.
 *
 * TODO: submit PR to imgui that allows configuring congiguration header
 # TODO: file using some other preprocessor directive
 */

#pragma once

extern "C" {
#include <Python.h>
}

#include "core.h"


// few macros to make IM_ASSERT cleaner
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define TOWRAP(x) "(" STRINGIFY(x) ")"
#define AT __FILE__ ":" TOSTRING(__LINE__)

// Redefine IM_ASSERT to raise Python specific exceptions
// note: enabling asserts as Python exceptions guards us from
//       possible segmentation faults when using functions that
//       does not return error values. Especially when pushing/poping
//       style stack variables.

#ifndef PYIMGUI_CUSTOM_EXCEPTION
#define IM_ASSERT(EX) (void)((EX) || (PyErr_SetString (PyExc_RuntimeError, "ImGui assertion error (" #EX ") at " AT),0))
#else
#define IM_ASSERT(EX) (void)((EX) || (PyErr_SetString (ImGuiException, "ImGui assertion error (" #EX ") at " AT),0))
#endif