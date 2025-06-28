#pragma once

#include "Context.hpp"


struct Scene
{
    using StorePointer = void *;
    StorePointer data; // указатель на данные конкретной сцены
    void (*update)(StorePointer data, GameContext & ctx);
    void (*render)(StorePointer data, GameContext & ctx);
    void (*destroy)(StorePointer data);
};


// Менеджер сцен
struct SceneManager
{
    Scene currentScene = {nullptr, nullptr, nullptr, nullptr};

    ~SceneManager()
    {
        if (currentScene.data && currentScene.destroy)
            currentScene.destroy(currentScene.data);
    }

    void setScene(Scene scene)
    {
        // Уничтожаем старую сцену
        if (currentScene.data && currentScene.destroy)
            currentScene.destroy(currentScene.data);

        currentScene = scene;
    }

    void update(GameContext & ctx) const noexcept
    {
        if (currentScene.update)
            currentScene.update(currentScene.data, ctx);
    }

    void render(GameContext & ctx) const noexcept
    {
        if (currentScene.render)
            currentScene.render(currentScene.data, ctx);
    }
};