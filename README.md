# uniqsconfiggenerator -- uconfig in short
uniqs design config generator, xlsx files to definition and data files. 

## 需求：
```
    每一个项目的策划配置都各有特色，每一个项目的服务端、客户端、脚本等使用配置的场景各有不同。
    希望有一套能够简单修改就能适配大多数场景需求的策划配置生成代码及数据的体系。uconfig应运而生
    有的人熟悉lua，有的人熟悉javascript，有的人熟悉python。要能让这些人都能简单的修改就能生成想要格式的结构和数据
    从XLSX生成代码。支持任意语言，只需要简单修改一下生成逻辑，就能生成任意语言。
    使用极为简单，生成逻辑与读取XLSX分离，使用非常简单的脚本语言lua/javascript/python
    嵌入脚本实现
```
## 实现：
        一、[lua implemention(implemented.)](https://github.com/uniqss/uconfiglua.git)
        二、javascript. 已实现(release only.)   https://github.com/uniqss/uconfigjs.git
        三、python. 未实现      https://github.com/uniqss/uconfigpython.git
## 使用.lua：
        一、git clone https://github.com/uniqss/uconfig.git  或者下载发布版本
        二、找到bin里面 cppcalllua_exe.exe OpenXLSX-shared.dll DT_Currency_Config.xlsx uniqs.lua test_generate_go_using_lua.bat 
        gofmt.exe 到你自己的文件夹中，执行test_generate_go_using_lua.bat即可在当前文件夹中生成gen_go文件夹以及一个DT_Currency_Config.go文件。
        三、说明：生成逻辑在 uniqs.lua 中。 生成路径在 uniqs.lua 的最开头部分。这里只是展示，生成的是go，可以生成其他任何语言的文件，也可以组织数
        据文件。生成代码有用到 os.execute 进行 gofmt操作，把文件格式化，如果其他语言有自己写的exe可以格式化，也可以执行。或者是对生成的代码做任何
        后续操作，也可以类似执行。test_generate_go_using_lua.bat 中有传一个6，这个参数是限制读取xlsx 的最大行数，也可以再在后面加一个限制列数。
        因为我们在生成代码的时候，只需要读取表头，并不需要对表的数据做什么操作。所以这里加了限制读取最大行数的功能来提高性能。
