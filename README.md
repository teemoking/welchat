# welchat

  5月８日——5月22日，1300行，实现用户登录，用户注册，在线聊天，离线消息收发，建立好友关系，群发消息。
采用半同步半异步的MVC模式主线程利用sockpair进行子线程负载量的反馈和分配套接字,负载量存储在map表中，
保证子线程的任务数量平均;子线程将套接字加入到注册事件，对登陆、注册、聊天等多种任务视图进行处理；
MySQL保留用户信息和登录信息，json封装和解析请求和接收信息。
  在子线程中使用Libevent的非阻塞模式采用回调函数的方式处理活动的套接字，Redis解决了频繁活动套接字
上的发送消息请求，减少数据查找的次数。

