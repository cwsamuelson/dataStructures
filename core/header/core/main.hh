#pragma once

#include "core/application.hh"
#include "core/layer.hh"

#include <memory>

namespace Core {

extern
std::shared_ptr<ApplicationBase> get_application();

extern
std::shared_ptr<Layer> get_app_layer();

extern
void Main(const Arguments& arguments, const Environment& environment);

}
