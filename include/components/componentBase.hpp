#pragma once

#include <main/form.hpp>
#include <core/main/seewkObject.hpp>

class Component
{
public:
    Component(seewk::main::Form* form) {
        object = &form->CreateObject();
    }
    

protected:
    SeewkObject *object = nullptr;
};