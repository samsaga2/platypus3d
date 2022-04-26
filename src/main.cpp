#include "engine.h"

int main() {
    auto engine = PlatypusEngine{};
    engine.init();
    engine.run();
    return 0;
}
