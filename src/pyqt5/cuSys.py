'''
整个应用的主流程，启动文件，主要是最开始实例化数据处理类，然后登陆，成功了就进入主界面，addClass函数是用来连接信号和信号槽的
'''

from PyQt5.QtWidgets import QApplication,QDialog,QWidget
from PyQt5.QtGui import QIcon
import sys
from data import Data
from ui.login import Login
from ui.main import Main

cuSys = QApplication(sys.argv)
data = Data()
login = Login()
data.addClass(login)
login.show()
if login.exec() == QDialog.Accepted:
    main = Main()
    data.addClass(main)
    main.show()
    cuSys.exec()
