#pragma once
#include "UI.hpp";

namespace UI {

template <typename... Children> struct VStackView {
  std::tuple<Children...> children;

  explicit VStackView(Children &&...elems)
      : children(std::forward<Children>(elems)...) {}

  void Render(GameContext &ctx) {
    RenderImpl(ctx, 0, std::make_index_sequence<sizeof...(Children)>{});
  }

private:
  template <std::size_t... Is>
  void RenderImpl(GameContext &ctx, int yOffset, std::index_sequence<Is...>) {
    (..., RenderChild(std::get<Is>(children), ctx, yOffset));
  }

  template <typename Widget>
  void RenderChild(Widget &child, GameContext &ctx, int &yOffset) {
    child.Render(ctx, yOffset);
    yOffset += Widget::Height;
  }
};

} // namespace UI
