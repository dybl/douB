'''
一个关于界面
'''

from PyQt5.QtWidgets import QDialog,QLabel,QPushButton,QApplication
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont,QPalette,QColor


class About(QDialog):
    def __init__(self):
        super().__init__()

        #界面基本设置
        self.setAttribute(Qt.WA_DeleteOnClose,True)
        self.setAttribute(Qt.WA_QuitOnClose,False)
        self.setWindowFlags(Qt.WindowCloseButtonHint)

        #界面标题和大小
        self.setWindowTitle("About")
        self.setFixedSize(350,500)

        #移动到屏幕中央
        mv = self.frameGeometry()
        mv.moveCenter(QApplication.desktop().availableGeometry().center())
        self.move(mv.topLeft())
        self.initUI() #UI启动

    def initUI(self):

        pe = QPalette()
        pe.setColor(QPalette.WindowText,Qt.red)
        self.setAutoFillBackground(True)
        pe.setColor(QPalette.Window,QColor(192,253,123))
        self.setPalette(pe)

        infoLabel = QLabel(self)
        infoLabel.setFont(QFont("黑体",18))
        infoLabel.setText("客户管理系统 v1.0\n")
        infoLabel.resize(infoLabel.sizeHint())
        infoLabel.move(self.width() / 2 - infoLabel.width() / 2,self.height() / 20)

        pfLabel = QLabel(self)
        pfLabel.setFont(QFont("黑体",12))
        pfLabel.setText("->开发平台：\n数据库：MySql\n开发语言：python\n图形库：Qt\n")
        pfLabel.resize(pfLabel.sizeHint())
        pfLabel.move(infoLabel.x(),infoLabel.y() + infoLabel.height() + 5)
        
        indexLabel = QLabel(self)
        indexLabel.setFont(QFont("黑体",12))
        indexLabel.setText("->实现功能：\n1.用户注册登录\n2.增删改查\n3.数据库连接诊断\n")
        indexLabel.resize(indexLabel.sizeHint())
        indexLabel.move(pfLabel.x(),pfLabel.y() + pfLabel.height() + 5)

        cyLabel = QLabel(self)
        cyLabel.setFont(QFont("黑体",10))
        cyLabel.setText("2018 © dybl")
        cyLabel.resize(cyLabel.sizeHint())
        cyLabel.move(abLabel.x(),abLabel.y() + abLabel.height() + 70)

        okBt = QPushButton(self)
        okBt.setDefault(True)
        okBt.setText("确定")
        okBt.resize(okBt.sizeHint())
        okBt.move(self.width() - okBt.width() - 20,self.height() - okBt.height() - 20)
        okBt.clicked.connect(self.close)