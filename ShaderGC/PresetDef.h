/*
ShaderGC: slangp shader compiler for ShaderGlass
Copyright (C) 2021-2025 mausimus (mausimus.net)
https://github.com/mausimus/ShaderGlass
GNU General Public License v3.0
*/

#pragma once

#include "framework.h"
#include "ShaderDef.h"
#include "TextureDef.h"

struct OverrideParamDef
{
    const char* name;
    float       value;
};

class PresetDef
{
public:
    PresetDef() : ShaderDefs {}, TextureDefs {}, Overrides {}, Name {}, Category {}, ImportPath {} { }

    virtual void Build() { }

    __declspec(noinline) void OverrideParam(const char* name, float value)
    {
        Overrides.emplace_back(name, value);
    }

    __declspec(noinline) void OverrideParams(const OverrideParamDef* params, int numParams)
    {
        for(int i = 0; i < numParams; i++)
        {
            const OverrideParamDef* p = params + i;
            Overrides.emplace_back(p->name, p->value);
        }
    }

    void MakeDynamic()
    {
        for(auto& s : ShaderDefs)
            s.Dynamic = true;
        for(auto& t : TextureDefs)
            t.Dynamic = true;
    }

    std::vector<ShaderDef>     ShaderDefs;
    std::vector<TextureDef>    TextureDefs;
    std::vector<ParamOverride> Overrides;
    std::string                Name;
    std::string                Category;
    std::filesystem::path      ImportPath;
};