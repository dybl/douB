'''
整个应用的主界面
'''

from PyQt5.QtWidgets import QWidget,QLabel,QLineEdit,QTableWidget,QTableWidgetItem,QAbstractItemView,QHeaderView,QPushButton,QMenuBar,QMenu,QAction,QGridLayout,QApplication
from PyQt5.QtCore import pyqtSignal,Qt
from PyQt5.QtGui import *
from ui.about import About
from ui.ok import Ok
from ui.de import Delete
from ui.base import Base


class Main(QWidget,Base):
    queSig = pyqtSignal(str) #查询请求
    okSig = pyqtSignal(str) #导入请求
    deSig = pyqtSignal(str) #删除请求

    def __init__(self):
        super().__init__()

        self.isOkUiOpen = False #导入界面是否打开
        self.isDeUiOpen = False #删除界面是否打开

        #界面基本设置
        self.setAttribute(Qt.WA_QuitOnClose,True)
        self.setAttribute(Qt.WA_DeleteOnClose,True)

        #设置标题和大小
        self.setWindowTitle("cuSys by dybl")
        self.resize(800,600)

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
        infoLabel.setFont(QFont("黑体",20))
        infoLabel.setText("客户管理系统")

        nameLabel = QLabel(self)
        nameLabel.setAlignment(Qt.AlignCenter)
        nameLabel.setFont(QFont("黑体",12))
        nameLabel.setText("客户姓名")
        
        numLabel = QLabel(self)
        numLabel.setAlignment(Qt.AlignCenter)
        numLabel.setFont(QFont("黑体",12))
        numLabel.setText("客户编号")

        self.nameLineEdit = QLineEdit(self)

        self.numLineEdit = QLineEdit(self)

        self.cuInfoList = QTableWidget(self)
        #选中项目编辑动作为不编辑
        self.cuInfoList.setEditTriggers(self.cuInfoList.NoEditTriggers)
        #取消掉每次新增条目的序号id显示
        self.cuInfoList.verticalHeader().setHidden(True)
        self.cuInfoList.setColumnCount(4)
        self.cuInfoList.setFont(QFont("黑体",12))
        self.cuInfoList.setHorizontalHeaderLabels(["姓名","年龄","编号","职业"])
        #选中条目的动作为选中那一行
        self.cuInfoList.setSelectionBehavior(QAbstractItemView.SelectRows)
        #将每个条目扩展到充满容器
        self.cuInfoList.horizontalHeader().setStretchLastSection(True)
        #将容器宽度平均分给所有条目
        self.cuInfoList.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)

        queBt = QPushButton(self)
        queBt.setText("查询")
        queBt.setDefault(True)
        queBt.clicked.connect(self.queBtCk)

        #菜单
        menuBar = QMenuBar(self)
        menuBar.setStyleSheet("QMenuBar{background-color:rgb(240,240,240)}")

        menu = QMenu(menuBar)
        menu.setTitle("菜单")
        menuBar.addMenu(menu)

        okAt = QAction(menu)
        okAt.setText("导入")
        okAt.triggered.connect(self.okAtTrg)
        menu.addAction(okAt)

        deAt = QAction(menu)
        deAt.setText("删除")
        deAt.triggered.connect(self.deAtTrg)
        menu.addAction(deAt)

        quitAt = QAction(menu)
        quitAt.setText("退出")
        quitAt.triggered.connect(self.close)
        menu.addAction(quitAt)

        abAt = QAction(menuBar)
        abAt.setText("关于")
        abAt.triggered.connect(self.abAtTrg)
        menuBar.addAction(abAt)

        #布局
        layout = QGridLayout(self)
        layout.addWidget(infoLabel,0,0,1,10)
        layout.addWidget(nameLabel,1,0,1,6)
        layout.addWidget(self.nameLineEdit,1,6,1,3)
        layout.addWidget(numLabel,2,0,1,6)
        layout.addWidget(self.numLineEdit,2,6,1,3)
        layout.addWidget(self.cuInfoList,3,0,5,-1)
        layout.addWidget(queBt,8,9,1,1)
        layout.setMenuBar(menuBar)

    #单击查询按钮
    def queBtCk(self):
        self.queSig.emit(self.nameLineEdit.text() + ' ' + self.numLineEdit.text())

    #返回来的查询结果显示到界面上
    def queResSlot(self,result):
        self.cuInfoList.setRowCount(len(result))
        for i in range(len(result)):
            self.cuInfoList.setItem(i,0,QTableWidgetItem(str(result[i]["name"])))
            self.cuInfoList.setItem(i,1,QTableWidgetItem(str(result[i]["age"])))
            self.cuInfoList.setItem(i,2,QTableWidgetItem(str(result[i]["num"])))
            self.cuInfoList.setItem(i,3,QTableWidgetItem(str(result[i]["oc"])))

    #导入信息界面
    def okAtTrg(self):
        if not self.isOkUiOpen:
            self.ok = Ok()
            self.ok.okSig.connect(self.okSig)
            self.ok.clSig.connect(self.okCloseSlot)
            self.msgSig.connect(self.ok.msgSlot)
            self.isOkUiOpen = True
            self.ok.show()

    #导入界面关闭
    def okCloseSlot(self):
        self.isOkUiOpen = False
        del self.ok

    #删除信息界面
    def deAtTrg(self):
        if not self.isDeUiOpen:
            self.de = Delete()
            self.de.deSig.connect(self.deSig)
            self.de.clSig.connect(self.deCloseSlot)
            self.msgSig.connect(self.de.msgSlot)
            self.isDeUiOpen = True
            self.de.show()

    #删除界面关闭
    def deCloseSlot(self):
        self.isDeUiOpen = False
        del self.de

    #关于界面
    def abAtTrg(self):
        about = About()
        about.exec()
