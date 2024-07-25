#pragma once
#include <exception>
#include <string>

class MalformedDependencyException : public std::exception {
   private:
    std::string message;

   public:
    MalformedDependencyException(const std::string& dependency);
    virtual const char* what() const throw();
};
