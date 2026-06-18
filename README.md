# version: c++ 20

1. use this tool to run project simple

https://github.com/WBhlietue/seewkRunner

2. install tools
```
seewkInit
```

3. install dependency
```
vcpkg install --x-feature=client
```
4. make and run 
```
seewk make
```
```
seewk start
```

## used tools:
- msvc 2022
- cmake
- vcpkg
- ninja 



# if intellisense of modules not working

add following code to your .vscode/c_cpp_properties.json files
``` 
{
  "configurations": [
    {
      "name": "Win32",
      "intelliSenseMode": "msvc-x64",
      "includePath": [
        "${workspaceFolder}/**"
      ],
      "defines": [],
    "compileCommands": "${workspaceFolder}/build/compile_commands.json",
      "cStandard": "c17",
      "cppStandard": "c++20"
    }
  ],
  "version": 4
}
```

then use ```seewk make``` and ```seewk start``` to generate ifc files to use intellisense.

