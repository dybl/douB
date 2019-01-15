#
# 如果没有用户，可以通过这个注册界面进行注册
#

from PyQt5.QtWidgets import QDialog,QApplication,QLabel,QLineEdit,QPushButton,QMessageBox
from PyQt5.QtCore import pyqtSignal,Qt
from PyQt5.QtGui import *
from ui.base import Base


class Register(QDialog,Base):
    regSig = pyqtSignal(str) #注册请求

    def __init__(self):
        super().__init__()

        #界面基本设置
        self.setAttribute(Qt.WA_DeleteOnClose,True)
        self.setAttribute(Qt.WA_QuitOnClose,False)
        self.setWindowFlags(Qt.WindowCloseButtonHint)

        #界面标题和大小
        self.setWindowTitle("Register")
        self.setFixedSize(500,350)
        
        #移动到屏幕中央
        mv = self.frameGeometry()
        mv.moveCenter(QApplication.desktop().availableGeometry().center())
        self.move(mv.topLeft())

        self.initUI() #UI设置

    def initUI(self):

        pe = QPalette()
        pe.setColor(QPalette.WindowText,Qt.black)
        self.setAutoFillBackground(True)
        pe.setColor(QPalette.Window,QColor(192,253,123))
        self.setPalette(pe)
        #控件+布局
        infoLabel = QLabel(self)
        infoLabel.setAlignment(Qt.AlignCenter)
        infoLabel.setFont(QFont("黑体",16))
        infoLabel.setText("请输入要注册的用户名和密码")
        infoLabel.resize(infoLabel.sizeHint())
        infoLabel.move(self.width() / 2 - infoLabel.width() / 2,self.height() / 10)

        nameLabel = QLabel(self)
        nameLabel.setAlignment(Qt.AlignCenter)
        nameLabel.setFont(QFont("黑体",12))
        nameLabel.setText("用户名")
        nameLabel.resize(nameLabel.sizeHint())
        nameLabel.move(self.width() / 2 - nameLabel.width() - 50,infoLabel.y() + infoLabel.height() + 50)

        pwdLabel = QLabel(self)
        pwdLabel.setAlignment(Qt.AlignCenter)
        pwdLabel.setFont(QFont("黑体",12))
        pwdLabel.setText("密码")
        pwdLabel.resize(pwdLabel.sizeHint())
        pwdLabel.move(nameLabel.x(),nameLabel.y() + nameLabel.height() + 50)

        self.nameLineEdit = QLineEdit(self)
        self.nameLineEdit.resize(self.nameLineEdit.sizeHint())
        self.nameLineEdit.move(nameLabel.x() + 70, nameLabel.y())

        self.pwdLineEdit = QLineEdit(self)
        self.pwdLineEdit.setEchoMode(QLineEdit.Password)
        self.pwdLineEdit.resize(self.pwdLineEdit.sizeHint())
        self.pwdLineEdit.move(self.nameLineEdit.x(),pwdLabel.y())

        regBt = QPushButton(self)
        regBt.setDefault(True)
        regBt.setFont(QFont("黑体",12))
        regBt.setText("注册")
        regBt.resize(regBt.sizeHint())
        regBt.move(self.width() - regBt.width() - 10,self.height() - regBt.height() - 10)
        regBt.clicked.connect(self.regBtCk)

    #单击注册按钮
    def regBtCk(self):
        if self.nameLineEdit.text() == "" or self.pwdLineEdit.text() == "":
            QMessageBox.warning(self,"警告","用户名或密码不可为空！")
        else:
            self.regSig.emit(self.nameLineEdit.text() + ' ' + self.pwdLineEdit.text())
