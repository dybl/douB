#
#后台数据处理类，所有可能需要耗时且和界面无关的请求将以信号的形式发到这里进行处理，完毕之后如果需要反馈再反馈
#

from PyQt5.QtCore import QObject,QThread,pyqtSignal
from pymysql import *
from ui.login import Login
from ui.reg import Register
from ui.main import Main
from ui.ok import Ok
from ui.de import Delete
from msg import Msg


class Data(QObject):
    lgSig = pyqtSignal() #登陆信号
    queResSig = pyqtSignal(list) #查询数据库信号
    msgSig = pyqtSignal(Msg) #给界面发送消息的信号

    def __init__(self):
        super().__init__()

        self.thread = QThread()
        self.moveToThread(self.thread)
        self.thread.started.connect(self.init) #线程初始化
        #资源管理
        self.destroyed.connect(self.thread.quit)
        self.thread.finished.connect(self.thread.deleteLater)
        self.thread.start() #启动线程

    def init(self):
        #数据库操作
        self.connection = connect(host="localhost",port=3306,user="cusys",password="123456",db="cusys",charset="utf8",cursorclass=cursors.DictCursor)
        self.cursor = self.connection.cursor()

    #添加与各个界面的信号交互
    def addClass(self,cl):
        #如果是登陆界面
        if type(cl) == Login:
            cl.lgSig.connect(self.loginSlot) #登陆请求
            cl.regSig.connect(self.regSlot) #注册请求
            self.lgSig.connect(cl.accept) #登陆成功
            self.msgSig.connect(cl.msgSlot) #发送消息
        #如果是主界面
        elif type(cl) == Main:
            cl.queSig.connect(self.queSlot) #数据库操作
            self.queResSig.connect(cl.queResSlot) #数据库操作结果
            cl.okSig.connect(self.okSlot) #导入请求
            cl.deSig.connect(self.deSlot) #删除请求
            self.msgSig.connect(cl.msgSlot) #发送消息

    #登陆信号槽
    def loginSlot(self,adminInfo):
        self.cursor.execute("select * from admin where username='%s'" % adminInfo.split(' ')[0])
        result = self.cursor.fetchone()
        #如果能够查询到这个用户的话
        if result:
            #如果密码对的话，则登陆
            if result["password"] == adminInfo.split(' ')[1]:
                self.lgSig.emit()
            else:
                self.msgSig.emit(Msg(Login,"错误","密码错误！"))
        #否则则说明没有这个用户
        else:
            self.msgSig.emit(Msg(Login,"错误","没有此用户！"))

    #注册信号槽
    def regSlot(self,adminInfo):
        self.cursor.execute("select * from admin where username='%s'" % adminInfo.split(' ')[0])
        result = self.cursor.fetchone()
        #判定注册的用户账号是否已经存在
        if result:
            self.msgSig.emit(Msg(Register,"警告","该用户已存在！"))
        else:
            #往表中插入相关用户数据
            self.cursor.execute("insert into admin values('%s','%s')" % (adminInfo.split(' ')[0],adminInfo.split(' ')[1]))
            self.connection.commit() #提交数据库更改
            self.msgSig.emit(Msg(Register,"成功","注册成功！"))

    #查询信号槽
    def queSlot(self,cuInfo):
        #查询所有
        if cuInfo.split(' ')[0] == "" and cuInfo.split(' ')[1] == "":
            self.cursor.execute("select * from cuinfo")
        #按照姓名和编号查询
        elif cuInfo.split(' ')[0] != "" and cuInfo.split(' ')[1] != "":
            self.cursor.execute("select * from cuinfo where name='%s' and num='%s'" % (cuInfo.split(' ')[0],cuInfo.split(' ')[1]))
        #否则按照姓名或编号查询
        else:
            self.cursor.execute("select * from cuinfo where name='%s' or num='%s'" % (cuInfo.split(' ')[0],cuInfo.split(' ')[1]))
        result = self.cursor.fetchall()
        self.queResSig.emit(list(result))

    #导入信息信号槽
    def okSlot(self,cuInfo):
        cuInfoList = cuInfo.split(' ')
        #首先查询一波，看看这个客户的信息是否已经被导入
        self.cursor.execute("select * from cuinfo where name='%s' and age='%s' and num='%s' and oc='%s'" % (cuInfoList[0],cuInfoList[1],cuInfoList[2],cuInfoList[3]))
        result = list(self.cursor.fetchall())
        if len(result) > 0:
            self.msgSig.emit(Msg(Enter,"错误","该客户信息已经导入！"))
        else:
            #否则就导入
            self.cursor.execute("insert into cuinfo values('%s','%s','%s','%s')" % (cuInfoList[0],cuInfoList[1],cuInfoList[2],cuInfoList[3]))
            self.connection.commit() #提交数据库更改
            self.msgSig.emit(Msg(Enter,"成功","导入客户信息成功！"))

    #删除信息信号槽
    def deSlot(self,cuInfo):
        cuInfoList = cuInfo.split(' ')
        #查询是否有这个客户的信息
        self.cursor.execute("select * from cuinfo where name='%s' and age='%s' and num='%s' and oc='%s'" % (cuInfoList[0],cuInfoList[1],cuInfoList[2],cuInfoList[3]))
        result = list(self.cursor.fetchall())
        #如果有的话则删除
        if len(result) > 0:
            self.cursor.execute("delete from cuinfo where name='%s' and age='%s' and num='%s' and oc='%s'" % (cuInfoList[0],cuInfoList[1],cuInfoList[2],cuInfoList[3]))
            self.connection.commit()
            self.msgSig.emit(Msg(Cl,"成功","删除客户信息成功！"))
        else:
            self.msgSig.emit(Msg(Cl,"错误","没有该客户信息！"))
