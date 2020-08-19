#include "../../src/object.hpp"

#include <fstream>

namespace anole
{
class FileObject : public Object
{
  public:
    FileObject(const String &, std::int64_t mode);
    Address load_member(const String &name) override;

    std::fstream &file();

  private:
    std::fstream file_;
};
}
