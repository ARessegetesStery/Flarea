# Flarea, A Toy Game Engine

## Building

This project uses git submodules, so when cloning you need to add the `--recursive` prompt so that all the submodules are properly cloned. Please check this when encountering specific "library not found" problems (e.g. spdlog). Alternatively, you can run the following commands after cloning: 

``` bash
git submodule init
git submodule update
```

Currently only Windows is supported. Please make sure you have installed Visual Studio 2022, and run `Prebuild/WindowsSetup.bat` to generate the `.sln` and related project files. 