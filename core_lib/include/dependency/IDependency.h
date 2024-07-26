#pragma once

#include <string>

class IDependency {
   public:
    virtual ~IDependency() = default;
    virtual bool isSimilar(const IDependency* other) const = 0;
    virtual std::string toString() const = 0;
};