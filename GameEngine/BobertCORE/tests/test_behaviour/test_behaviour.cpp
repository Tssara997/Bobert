#include <catch2/catch_all.hpp>
#include <Behaviours/Behaviour.h>

SCENARIO("Dynamic Behaviour creation", "[behaviours][behaviour]") {
    GIVEN("A dynamically allocated Behaviour") {
        auto test_behaviour = std::make_shared<Bobert::Behaviour>();

        THEN("The pointer should be valid and not null") {
            REQUIRE(test_behaviour != nullptr);
        }
    }
}