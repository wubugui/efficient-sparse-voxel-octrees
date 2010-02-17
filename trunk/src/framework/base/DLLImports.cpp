/*
 *  Copyright 2009-2010 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
#include "base/DLLImports.hpp"

using namespace FW;

//------------------------------------------------------------------------

static struct
{
    const char* name;
    HMODULE     handle;
}
s_importDLLs[] =
{
    { "nvcuda.dll", NULL },
    { "winmm.dll", NULL },
    { "shlwapi.dll", NULL },
};

//------------------------------------------------------------------------

#define FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)   static RET (CALL *s_ ## NAME)PARAMS = NULL;
#define FW_DLL_IMPORT_VOID(RET, CALL, NAME, PARAMS, PASS)   FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#define FW_DLL_DECLARE_RETV(RET, CALL, NAME, PARAMS, PASS)  FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#define FW_DLL_DECLARE_VOID(RET, CALL, NAME, PARAMS, PASS)  FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#include "base/DLLImports.inl"
#undef FW_DLL_IMPORT_RETV
#undef FW_DLL_IMPORT_VOID
#undef FW_DLL_DECLARE_RETV
#undef FW_DLL_DECLARE_VOID

//------------------------------------------------------------------------

static const struct
{
    const char* name;
    void**      ptr;
}
s_importFuncs[] =
{
#define FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)   { #NAME, (void**)&s_ ## NAME },
#define FW_DLL_IMPORT_VOID(RET, CALL, NAME, PARAMS, PASS)   FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#define FW_DLL_DECLARE_RETV(RET, CALL, NAME, PARAMS, PASS)  FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#define FW_DLL_DECLARE_VOID(RET, CALL, NAME, PARAMS, PASS)  FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#include "base/DLLImports.inl"
#undef FW_DLL_IMPORT_RETV
#undef FW_DLL_IMPORT_VOID
#undef FW_DLL_DECLARE_RETV
#undef FW_DLL_DECLARE_VOID
};

//------------------------------------------------------------------------

void FW::initDLLImports(void)
{
    for (int i = 0; i < (int)FW_ARRAY_SIZE(s_importDLLs); i++)
    {
        if (!s_importDLLs[i].handle)
            s_importDLLs[i].handle = LoadLibrary(s_importDLLs[i].name);

        if (s_importDLLs[i].handle)
            for (int j = 0; j < (int)FW_ARRAY_SIZE(s_importFuncs); j++)
                if (!*s_importFuncs[j].ptr)
                    *s_importFuncs[j].ptr = (void*)GetProcAddress(s_importDLLs[i].handle, s_importFuncs[j].name);
    }
}

//------------------------------------------------------------------------

void FW::initGLImports(void)
{
    for (int i = 0; i < (int)FW_ARRAY_SIZE(s_importDLLs); i++)
        for (int i = 0; i < (int)FW_ARRAY_SIZE(s_importFuncs); i++)
            if (!*s_importFuncs[i].ptr)
                *s_importFuncs[i].ptr = (void*)wglGetProcAddress(s_importFuncs[i].name);
}

//------------------------------------------------------------------------

void FW::deinitDLLImports(void)
{
    for (int i = 0; i < (int)FW_ARRAY_SIZE(s_importDLLs); i++)
    {
        if (s_importDLLs[i].handle)
            FreeLibrary(s_importDLLs[i].handle);
        s_importDLLs[i].handle = NULL;
    }

    for (int i = 0; i < (int)FW_ARRAY_SIZE(s_importFuncs); i++)
        *s_importFuncs[i].ptr = NULL;
}

//------------------------------------------------------------------------

#define FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)   RET CALL NAME PARAMS { if (!s_ ## NAME) fail("Failed to import " #NAME "()!"); return s_ ## NAME PASS; }
#define FW_DLL_IMPORT_VOID(RET, CALL, NAME, PARAMS, PASS)   void CALL NAME PARAMS { if (!s_ ## NAME) fail("Failed to import " #NAME "()!"); s_ ## NAME PASS; }
#define FW_DLL_DECLARE_RETV(RET, CALL, NAME, PARAMS, PASS)  FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#define FW_DLL_DECLARE_VOID(RET, CALL, NAME, PARAMS, PASS)  FW_DLL_IMPORT_VOID(RET, CALL, NAME, PARAMS, PASS)
#include "base/DLLImports.inl"
#undef FW_DLL_IMPORT_RETV
#undef FW_DLL_IMPORT_VOID
#undef FW_DLL_DECLARE_RETV
#undef FW_DLL_DECLARE_VOID

//------------------------------------------------------------------------

#define FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)   bool isAvailable_ ## NAME(void) { return (s_ ## NAME != NULL); }
#define FW_DLL_IMPORT_VOID(RET, CALL, NAME, PARAMS, PASS)   FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#define FW_DLL_DECLARE_RETV(RET, CALL, NAME, PARAMS, PASS)  FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#define FW_DLL_DECLARE_VOID(RET, CALL, NAME, PARAMS, PASS)  FW_DLL_IMPORT_RETV(RET, CALL, NAME, PARAMS, PASS)
#include "base/DLLImports.inl"
#undef FW_DLL_IMPORT_RETV
#undef FW_DLL_IMPORT_VOID
#undef FW_DLL_DECLARE_RETV
#undef FW_DLL_DECLARE_VOID

//------------------------------------------------------------------------
