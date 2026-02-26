#ifndef KTANKS_EDITORSCREEN_H
#define KTANKS_EDITORSCREEN_H

#include "ktanks/core/IScreen.h"
#include "ktanks/core/IWidget.h"

namespace ktanks {

    class EditorScreen final : public IScreen {
    public:
        explicit EditorScreen(const glm::uvec2& level_size, ScreenManager*);
        ~EditorScreen() override;

        void onInit() override;
        void onUpdate(float dt) override;
        void onDraw(Renderer&) override;
        void onEvent(const Event &) override;

    private:
        void updateMatrix();
        glm::vec2 screenToWorld() const;

        void paintTileAtMouse();

        float m_zoom{1.f};
        glm::vec2 m_offset{0.f};
        glm::vec2 m_mouse{0.f};
        glm::uvec2 m_view{0u};
        LevelMap<TerrainSprite> m_terrain_layer;
        LevelMap<BlockID> m_blocks_layer;
        glm::mat4 m_view_mat{1.f};
    };

}

#endif //KTANKS_EDITORSCREEN_H