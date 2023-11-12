{
  cmake,
  gnumake,
  pkgsCross,
  gcc-arm-embedded,
}:
pkgsCross.arm-embedded.stdenv.mkDerivation rec {
  pname = "firmware";
  version = "nightly";
  src = builtins.path {
    path = ./.;
    name = "lab";
  };

  nativeBuildInputs = [cmake gnumake gcc-arm-embedded];

  dontPatch = true;
  dontFixup = true;
  dontStrip = true;
  dontPatchELF = true;

  device = "STM32F103RB";

  # buildFlags = "VERBOSE=1"; # increase build verbosity

  cmakeFlags = [
    "-DPROJECT_NAME=${pname}"
    "-DCMAKE_BUILD_TYPE=Debug"
    "-DDUMP_ASM=OFF"
  ];

  installPhase = ''
    mkdir -p $out/bin
    cp -r * $out
    mv $out/*.bin $out/*.elf $out/*.s $out/*.hex $out/*.map $out/bin
  '';
}
