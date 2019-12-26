#pragma once

#include <map>
#include "object.hpp"

namespace ice_language
{
class DictObject : public Object
{
  public:
    struct ObjectCmp
    {
        bool operator()(const ObjectPtr &lhs, const ObjectPtr &rhs) const
        {
            return lhs->to_key() < rhs->to_key();
        }
    };

    using DataType = std::map<ObjectPtr, Ptr<ObjectPtr>, ObjectCmp>;

    DictObject();

    bool to_bool() override;
    std::string to_str() override;
    std::string to_key() override;
    Ptr<ObjectPtr> index(ObjectPtr) override;
    Ptr<ObjectPtr> load_member(const std::string &name) override;

    DataType &data();
    void insert(ObjectPtr key, ObjectPtr value);

  private:
    DataType data_;
};
}
