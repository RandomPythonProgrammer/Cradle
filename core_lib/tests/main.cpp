#include <catch2/catch_all.hpp>
#include "cpr/api.h"
#include "cpr/cprtypes.h"
#include <cpr/cpr.h>

int main(int argc, char* argv[]) {
    //This does some sort of internal init and fixes cpr for testing
    cpr::Get(cpr::Url("127.0.0.1"));

    return Catch::Session().run(argc, argv);
}