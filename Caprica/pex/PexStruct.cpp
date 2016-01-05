#include <pex/PexStruct.h>

#include <pex/PexFile.h>

namespace caprica { namespace pex {

PexStruct* PexStruct::read(PexReader& rdr) {
  auto struc = new PexStruct();
  struc->name = rdr.read<PexString>();
  auto mLen = rdr.read<uint16_t>();
  struc->members.reserve(mLen);
  for (size_t i = 0; i < mLen; i++)
    struc->members.push_back(PexStructMember::read(rdr));
  return struc;
}

void PexStruct::write(PexWriter& wtr) const {
  wtr.write<PexString>(name);
  wtr.boundWrite<uint16_t>(members.size());
  for (auto m : members)
    m->write(wtr);
}

void PexStruct::writeAsm(const PexFile* file, PexAsmWriter& wtr) const {
  // TODO: Handle the struct order info in the debug info.
  wtr.writeln(".struct %s", file->getStringValue(name).c_str());
  wtr.ident++;
  for (auto m : members)
    m->writeAsm(file, wtr);
  wtr.ident--;
  wtr.writeln(".endStruct");
}

}}