#include "adapter.h"

#include <vector>
#include <gtest/gtest.h>
#include <utility>

using namespace DSA::DesignPatterns;

namespace DSA::DesignPatterns::Tests {

class DesignPatternsFixture : public testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DesignPatternsFixture, Adapter) {
    OldComponent oldie{};
    NewComponent newbie{};
    Adapter adaptedOldie {oldie};
    oldie.doSthTheOldWay();
    newbie.doSthTheNewWay();
    adaptedOldie.doSthTheNewWay();
    std::vector<NewComponent*> componentsList {};
    componentsList.push_back(&newbie);
    //componentsList.push_back(&oldie); // not gonna happen
    componentsList.push_back(&adaptedOldie);
    for (auto& element: componentsList) {
        element->doSthTheNewWay();
    }
}


} /* namespace DSA::DesignPatterns::Tests */
