

cd vendor
git clone https://github.com/libsdl-org/SDL.git
cd SDL

mkdir build-aarch64
cd build-aarch64

../configure \
  --host=aarch64-linux-gnu \
  --prefix=/usr \
  --enable-video-opengl \
  --disable-video-opengles \
  --disable-pulseaudio \
  --disable-esd \
  --disable-video-wayland \
  --disable-video-x11 \
  --disable-video-directfb \
  --disable-video-vulkan \
  --disable-video-rpi \
  --disable-video-mir \
  --disable-video-fbcon \
  --disable-joystick \
  --disable-haptic \
  --disable-sensor \
  --disable-power \
  --disable-filesystem \
  --disable-file \
  CC=aarch64-linux-gnu-gcc-10 \
  CXX=aarch64-linux-gnu-g++-10 \
  CFLAGS="--sysroot=$(realpath ../../vendor/k36-sysroot)" \
  CXXFLAGS="--sysroot=$(realpath ../../vendor/k36-sysroot)" \
  LDFLAGS="--sysroot=$(realpath ../../vendor/k36-sysroot)"
  
make


mv ./include /home/vinograd/container/include/sdl2/arm


