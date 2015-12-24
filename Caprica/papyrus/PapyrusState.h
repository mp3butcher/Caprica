#pragma once

#include <string>
#include <vector>

#include <papyrus/PapyrusFunction.h>

#include <pex/PexFile.h>
#include <pex/PexObject.h>
#include <pex/PexState.h>

namespace caprica { namespace papyrus {

struct PapyrusState final
{
  std::string name;
  std::vector<PapyrusFunction*> functions;

  PapyrusState() = default;
  ~PapyrusState() {
    for (auto f : functions)
      delete f;
  }

  void buildPex(pex::PexFile* file, pex::PexObject* obj) const {
    auto state = new pex::PexState();
    state->name = file->getString(name);
    for (auto f : functions)
      f->buildPex(file, obj, state);
    obj->states.push_back(state);
  }
};

}}
