#定义一个SRC_LIST变量，包含该目录下所有的源文件
aux_source_directory(. SRC_LIST)

aux_source_directory(./db SRC_LIST1)

#指定生成可执行文件
add_executable(chatServer ${SRC_LIST} ${SRC_LIST1})

#指定可执行文件链接时需要依赖的库文件
target_link_libraries(chatServer muduo_net muduo_base pthread mysqlclient)