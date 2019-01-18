<h1 align="center">cuSys 客户管理系统</h1>

![](https://img.shields.io/badge/cusys-project-ad2dec.svg)
![](https://img.shields.io/badge/pyqt5-mysql-0f9d58.svg)
![](https://img.shields.io/badge/licence-Apache2.0-ff69b4.svg)

## 简述：

> 由python开发的小型客户管理系统，麻雀虽小，五脏俱全，但是数据表设计的比较简陋，所以能够实现的功能也就只有最基本的增删改查，以后可能会加入一些新的功能巩固完善！

### 基本功能：

- 与本地MySQL数据库交互

- 连接诊断数据库

- 实现增删改查客户相关信息

- 用户注册登陆

- 版本说明


### 开发环境：

1. python: 3.6.x
2. pymysql: 0.9.2
3. Qt5
4. Mysql Commuity Server

### 界面设计

- 登陆界面
  - 登陆成功
  - 登陆失败
- 注册界面
  - 注册成功
  - 注册失败
- 主界面
  - 查询界面
    - 显示所有信息
    - 按录入信息查询
  - 导入数据界面
    - 导入成功
    - 导入失败
  - 删除数据界面
    - 导入成功
    - 导入失败
  - 版本说明界面

### 数据库设计

- 数据库名为cuSys，内有两张表，分别为admin和cuinfo

```sql
+-----------------+
| Tables_in_cusys |
+-----------------+
| admin           |
| cuinfo          |
+-----------------+
```

- **admin表**：存储用户账户
```sql
+----------+-----------+------+-----+---------+-------+
| Field    | Type      | Null | Key | Default | Extra |
+----------+-----------+------+-----+---------+-------+
| username | char(100) | NO   |     | NULL    |       |
| password | char(100) | NO   |     | NULL    |       |
+----------+-----------+------+-----+---------+-------+
```

- **cuinfo表**：存储客户信息
```sql
+-------+--------------+------+-----+---------+-------+
| Field | Type         | Null | Key | Default | Extra |
+-------+--------------+------+-----+---------+-------+
| name  | varchar(255) | NO   |     | NULL    |       |
| age   | char(50)     | NO   |     | NULL    |       |
| num   | char(50)     | NO   |     | NULL    |       |
| oc    | char(50)     | NO   |     | NULL    |       |
+-------+--------------+------+-----+---------+-------+
```
<br>

### 效果展示

<img src="img/login.png">
<img src="img/registry.png">
<img src="img/im.png">

### 代码示例

```python
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
```

```python
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
```
