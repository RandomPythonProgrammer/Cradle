#pragma once

class IDependency {
   public:
    virtual ~IDependency() = default;
    virtual bool isSimilar(const IDependency* other) const = 0;
};