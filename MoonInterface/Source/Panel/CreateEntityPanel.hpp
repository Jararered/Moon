#include "Panel.hpp"

class CreateEntityPanel final : public Panel
{
public:
    ~CreateEntityPanel() override = default;

    void Draw() override;
};
