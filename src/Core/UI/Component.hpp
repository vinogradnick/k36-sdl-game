#pragma once

namespace UI {
template <const int PositionX, const int PositionY> struct UIComponent {
  static constexpr auto positionX = PositionX;
  static constexpr auto positionY = PositionY;

  UIComponent() = default;
  ~UIComponent() = default;
};
} // namespace UI
