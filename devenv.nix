{ pkgs, lib, config, inputs, ... }:
{
  packages = with pkgs; [
    git

    cmake
    gcc
    gdb
    ninja

    gitlab-ci-local
    cloc
    doxygen
    # mkdocs
  ];

  languages = {
    python = {
      enable = true;
      venv = {
        enable = true;
        requirements = ''
          conan
          # mkdoxy
          spdx_license_list
        '';
      };
    };

    # this specifically adds clang; I'm currently focused on gcc
    # cplusplus.enable = true;
  };

  scripts = {
    build.exec = builtins.readFile ./scripts/build.bash;

    clean.exec = ''
      rm -rf build $@
    '';

    line-report.exec = ''
      ${pkgs.cloc}/bin/cloc --vcs=git
    '';

    ci.exec = ''
      ${pkgs.gitlab-ci-local}/bin/gitlab-ci-local --volume personal_conan_cache:/root/.conan2 $@
    '';

    purge.exec = ''
      clean cmake-* .gitlab-ci-local site CMakeUserPresets.json conan_provider.cmake output_final $@
    '';

    reset.exec = ''
      purge .venv .devbox
    '';
  };
}
