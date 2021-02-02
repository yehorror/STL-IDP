# STL usage examples

To fetch GoogleTest:
```
git submodule update --init --recursive
```

To build run following in VS15 cmd

```
mkdir build
cd build
cmake .. -Dgtest_force_shared_crt=ON
msbuild ALL_BUILD.vcxproj
```

To run built application:
```
Debug\STL-IDP.exe
```
