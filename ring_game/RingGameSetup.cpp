#include "RingGameSetup.h"
#include <memory>
#include "CircleObject.h"
#include "RingObject.h"

void setupRingGameObjects(Engine& engine) {
    engine.objects.clear();

    engine.objects.push_back(std::make_unique<CircleObject>(
        "Ball",
        BodyType::Dynamic,
        0.15f,
        Vec2{4.0f, 3.0f},
        Vec2{3.5f, 0.0f},
        Vec2{0.0f, -3.8f}
    ));

    float maxRadius = 2.8f;
    float startRadius = 0.3f;
    float spacing = (maxRadius - startRadius) / 99.0f;

    for (int i = 0; i < 100; i++) {
        engine.objects.push_back(std::make_unique<RingObject>(
            "Ring",
            BodyType::Static,
            startRadius + i * spacing,
            Vec2{4.0f, 3.0f},
            Vec2{0.0f, 0.0f},
            Vec2{0.0f, 0.0f}
        ));
    }
}
