#
#一个基本的界面类，包含了消息信号和消息信号槽，这样其他的界面只需继承这个类即可获得相应的信号和信号槽
#

from PyQt5.QtCore import pyqtSignal
from PyQt5.QtWidgets import QMessageBox
from msg import Msg


class Base:
    msgSig = pyqtSignal(Msg) #消息通知信号

    #接收到消息通知信号槽
    def msgSlot(self,msg):
        if msg.target == type(self): #如果消息的目标是自己的类型
            QMessageBox.about(self,msg.title,msg.msg) #则通知
        else:
            #否则继续发送（如果和其他的界面有联系的话）
            self.msgSig.emit(msg)
