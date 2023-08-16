#include "Layer.hpp"

class DebugInfoLayer : public Layer
{
public:
    DebugInfoLayer() = default;
    ~DebugInfoLayer() = default;

    void Update() override;
};