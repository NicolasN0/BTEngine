#pragma once
#include "MonoBehaviour.h"
namespace dae
{
    class TextureComponent final:
        public MonoBehaviour
    {
    public:
        ~TextureComponent() override = default;
        TextureComponent(const std::string& filename);
        void Update(float ) override {}
        void FixedUpdate(float) override {}
        void Render() const override;
    private:
        std::shared_ptr<Texture2D> m_spTexture{};
    };

}

