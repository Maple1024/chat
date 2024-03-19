 #ifndef USERMODEL_H
 #define USERMODEL_H

 #include "user.hpp"

 //user表的数据操作类
 class UserModel{
public:
    //增
    bool insert(User&);

    //删
    bool delMsg(User&);

    //改

    //查

    User query(int id);

    bool updateState(User& user);
 };
 #endif