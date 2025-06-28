#include "LoadingScene.hpp"
#include "../Core/Ticker.hpp"
#include "../Core/UI/UI.hpp"


namespace LoadingScene
{

using LoadingText = UI::UITextView<0, 0, AssetConfig::FONT_PATH>;


struct SceneState
{
    Ticker ticker;
    LoadingText text;
    int progress;
};

void Update(void * data, GameContext &)
{
    auto * state = static_cast<SceneState *>(data);

    if (state->ticker.tick())
    {
        state->progress++;
    }
}
void Render(void * data, GameContext & ctx)
{
    auto * state = static_cast<SceneState *>(data);
    UI::ImageRender<640, 480>(ctx, AssetConfig::LOADING_SCREEN);
    UI::SquareProgress<0, 480 - 30, 640, 30>(ctx, state->progress);
}
void OnDrop(void * data)
{
    delete static_cast<SceneState *>(data);
}


Scene createScene(GameContext & ctx)
{
    auto * ptr = new SceneState{Ticker(1000), LoadingText(ctx), 0};

    return Scene{
        ptr,
        &Update,
        &Render,
        &OnDrop,
    };
}
}