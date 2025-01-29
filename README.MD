#### 依赖的三方库

* ****google benchmark ：****
  * 自行从github下载，并编译相应版本，本工程目前编译了msvc的debug版本
  * 下载以后，需要cmake --install . --config Debug --prefix "D:\\libs\\msvc-debug" 一下，将其都install到一个文件夹内
  * 在cmake中首先设置一个变量  benchmark_DIR，指向benchmark的.cmake文件所在的文件夹，例如
    "D:\Hera2.0\Dependencies\benchmark\install\msvc-debug\lib\cmake\benchmark"
  * 在cmake中，可以直接用find_package(benchmark REQUIRED)来配置所有
  * 接下来就是直接在target_link_libraries中链接它，就可以了
