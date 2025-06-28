# console run


# qemu-aarch64-static -L ./vendor/k36-sysroot ./build-k36/main




qemu-system-aarch64 \
  -M virt \
  -cpu cortex-a53 \
  -m 2G \
  -bios /usr/share/qemu-efi-aarch64/QEMU_EFI.fd \
  -drive if=virtio,file=/home/vinograd/Downloads/EmuELEC-Amlogic-ng.aarch64-4.7-Generic.img,format=raw \
  -display sdl \
  -netdev user,id=net0 -device virtio-net,netdev=net0
