#ifndef __ANOLE_RUNTIME_COLLECTOR_HPP__
#define __ANOLE_RUNTIME_COLLECTOR_HPP__

#include "../base.hpp"

#include <set>

namespace anole
{
class Scope;
class Context;
class Variable;

/**
 * Collector will collect objects
 *  which are referenced and then deallocate others
 *
 * there is only one global Collector
*/
class Collector
{
  public:
    template<typename T>
    static void mark(T *ptr)
    {
        collector().mark_impl(ptr);
    }

    template<typename T>
    static void collect(T *p)
    {
        auto &ref = collector();
        if (p == nullptr || ref.visited_.count(p))
        {
            return;
        }
        ref.visited_.insert(p);
        ref.collect_impl(p);
    }

    static void try_gc();

  private:
    static Collector &collector();

    template<typename T>
    static std::set<T *> &marked()
    {
        static std::set<T *> mkd;
        return mkd;
    }

    /**
     * default ctor is private
     *  in order that we can only use the static collector
    */
    Collector() noexcept;

    /**
     * gc can only be called by the collector self
    */
    void gc();

    /**
     * record allocated address
     *  and only recorded address could be deallocated
     *
     * void record(address);
    */
    template<typename T>
    void mark_impl(T *ptr)
    {
        ++count_;
        marked<T>().insert(ptr);
    }

    /**
     * collect variables
    */
    void collect_impl(Scope *);
    void collect_impl(Object *);
    void collect_impl(Context *);

    std::set<void *> visited_;
    std::set<Object *> collected_;
    Size count_;
};
} // namespace anole

#endif
