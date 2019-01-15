#
# 一个用来导入客户信息的界面
#
from PyQt5.QtWidgets import QWidget,QApplication,QLabel,QLineEdit,QPushButton,QGridLayout,QMessageBox
from PyQt5.QtCore import pyqtSignal,Qt,QRegExp
from PyQt5.QtGui import *
from ui.base import Base


class Ok(QWidget,Base):
    okSig = pyqtSignal(str) #导入请求
    clSig = pyqtSignal() #关闭信号

    def __init__(self):
        super().__init__()

        #界面基本设置
        self.setAttribute(Qt.WA_QuitOnClose,False)
        self.setAttribute(Qt.WA_DeleteOnClose,True)

        #设置界面标题和大小
        self.setWindowTitle("导入客户信息")
        self.resize(500,200)

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
        #控件
        infoLabel = QLabel(self)
        infoLabel.setAlignment(Qt.AlignCenter)
        infoLabel.setFont(QFont("黑体",15))
        infoLabel.setText("请输入你要导入的客户的信息")

        nameLabel = QLabel(self)
        nameLabel.setAlignment(Qt.AlignCenter)
        nameLabel.setFont(QFont("黑体",10))
        nameLabel.setText("客户姓名")

        ageLabel = QLabel(self)
        ageLabel.setAlignment(Qt.AlignCenter)
        ageLabel.setFont(QFont("黑体",10))
        ageLabel.setText("客户年龄")

        numLabel = QLabel(self)
        numLabel.setAlignment(Qt.AlignCenter)
        numLabel.setFont(QFont("黑体",10))
        numLabel.setText("客户编号")

        ocLabel = QLabel(self)
        ocLabel.setAlignment(Qt.AlignCenter)
        ocLabel.setFont(QFont("黑体",10))
        ocLabel.setText("客户职业")

        self.nameLineEdit = QLineEdit(self)

        self.ageLineEdit = QLineEdit(self)
        #正则表达式控制这里只能够输入数字
        self.ageLineEdit.setValidator(QRegExpValidator(QRegExp("[0-9]+$"),self.ageLineEdit))

        self.numLineEdit = QLineEdit(self)

        self.ocLineEdit = QLineEdit(self)

        okBt = QPushButton(self)
        okBt.setText("导入")
        okBt.clicked.connect(self.okBtCk)

        #布局
        layout = QGridLayout(self)
        layout.addWidget(infoLabel,0,0,2,12)
        layout.addWidget(nameLabel,2,0,1,3)
        layout.addWidget(ageLabel,2,3,1,3)
        layout.addWidget(numLabel,2,6,1,3)
        layout.addWidget(ocLabel,2,9,1,3)
        layout.addWidget(self.nameLineEdit,3,0,1,3)
        layout.addWidget(self.ageLineEdit,3,3,1,3)
        layout.addWidget(self.numLineEdit,3,6,1,3)
        layout.addWidget(self.ocLineEdit,3,9,1,3)
        layout.addWidget(okBt,4,11,1,1)

    #单击导入按钮
    def okBtCk(self):
        if self.nameLineEdit.text() == "" or self.ageLineEdit.text() == "" or self.numLineEdit.text() == "" or self.ocLineEdit.text() == "":
            QMessageBox.critical(self,"错误","客户信息不可为空！",QMessageBox.Ok)
        else:
            self.okSig.emit(self.nameLineEdit.text() + ' ' + self.ageLineEdit.text() + ' ' + self.numLineEdit.text() + ' ' + self.ocLineEdit.text())

    #界面关闭的时候发出这个信号表示界面已经关闭
    def closeEvent(self, QCloseEvent):
        self.clSig.emit()
        return super().closeEvent(QCloseEvent)
