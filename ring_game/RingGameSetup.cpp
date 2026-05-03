#include "RingGameSetup.h"

void setupRingGameObjects(Engine& engine) {
    engine.objects.clear();

    engine.objects.push_back({
        "Ball",
        ShapeType::Circle,
        BodyType::Dynamic,
        {0.0f, 0.0f},
        0.15f,
        {4.0f, 3.0f},
        {3.5f, 0.0f},
        {0.0f, -3.8f},
        false
    });

    float maxRadius = 2.8f;
    float startRadius = 0.3f;
    float spacing = (maxRadius - startRadius) / 99.0f;

    for (int i = 0; i < 100; i++) {
        engine.objects.push_back({
            "Ring",
            ShapeType::Ring,
            BodyType::Static,
            {0.0f, 0.0f},
            startRadius + i * spacing,
            {4.0f, 3.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            false
        });
    }
}
