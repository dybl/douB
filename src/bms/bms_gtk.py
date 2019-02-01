import pygtk
pygtk.require('2.0')
import gtk
import sys
import gobject
import sqlite3
import time
import datetime

class LibManager:
 bookColumName = (u"书本号", u"书名", u"作者", u"出版社", 
   u"价格", u"购入日期", u"分类", u"简介", u"馆藏数")

 readerColumName = (u"读者号", u"读者姓名", u"读者身份", u"备注")

 def __init__(self):
 self.dbconn = sqlite3.connect('sqlitefile.db')
 self.cursor = self.dbconn.cursor()
 
 self.nowDate = time.strftime("%Y-%m-%d").decode("utf-8")
 inputBookInitData = (u"书名", u"作者", u"出版社", 
   0.0, self.nowDate, u"分类", u"简介", 0)

 try:
  builder = gtk.Builder()
  builder.add_from_file("ui.glade")
 except BaseException, e:
  self.errorMessage("Fail to load UI file.")
  print e
  sys.exit(1)

 builder.connect_signals(self)
 self.window = builder.get_object("mainWindow")

 self.borrowView = builder.get_object("borrowView")
 self.borrowViewModel = builder.get_object("borrowViewModel")
 self.borrowViewInit()

 self.returnView = builder.get_object("returnView")
 self.returnViewModel = builder.get_object("returnViewModel")
 self.returnEntryReaderID = builder.get_object("returnReaderID")
 self.returnEntryBookID = builder.get_object("returnBookID")
 self.returnViewInit()

 self.queryView = builder.get_object("queryView")
 self.queryViewReaderModel = builder.get_object("queryViewReaderModel")
 self.queryViewBookModel = builder.get_object("queryViewBookModel")


 self.inputView = builder.get_object("inputView")
 self.inputViewBookModel = builder.get_object("inputViewBookModel")
 self.inputViewReaderModel = builder.get_object("inputViewReaderModel")
 self.inputViewModel = None


 def borrowViewInit(self):
 columName = (u"读者号", u"书号", u"借出日期")
 columEditAttr = (True, True, False)
 for columnNum in range(len(columName)):
  renderer = gtk.CellRendererText()
  renderer.set_data("column", columnNum)
  renderer.set_property("editable", columEditAttr[columnNum])
  if columEditAttr[columnNum]:
  renderer.connect("edited", self.on_borrow_cell_edited)
  column = gtk.TreeViewColumn(columName[columnNum], renderer, 
     text=columnNum)
  column.set_resizable(True)
  self.borrowView.append_column(column)

 def returnViewInit(self):
 columName = (u"借书记录", u"书本", u"读者姓名", u"读者资料", u"借出日期")
 for columnNum in range(len(columName)):
  renderer = gtk.CellRendererText()
  column = gtk.TreeViewColumn(columName[columnNum], renderer, 
     text=columnNum)
  column.set_resizable(True)
  self.returnView.append_column(column)

 # QueryView
 def queryViewSetColumn(self, columName):
 self.queryRecord = 0
 columns = self.queryView.get_columns()
 for c in columns:
  self.queryView.remove_column(c)
 
 self.queryViewModel.clear()
 self.queryView.set_model(self.queryViewModel)
 for columnNum in range(len(columName)):
  renderer = gtk.CellRendererText()
  renderer.set_property("editable", True)
  column = gtk.TreeViewColumn(columName[columnNum], renderer, 
     text=columnNum)
  column.set_resizable(True)
  self.queryView.append_column(column)


 def queryReader(self):
 self.queryViewModel = self.queryViewReaderModel
 self.queryViewSetColumn(self.readerColumName)
 self.cursor.execute("SELECT COUNT(*) FROM reader")
 self.maxRecords = self.cursor.fetchone()[0]
 print self.maxRecords

 def queryBook(self):
 self.queryViewModel = self.queryViewBookModel
 self.queryViewSetColumn(self.bookColumName)
 self.cursor.execute("SELECT COUNT(*) FROM books")
 self.maxRecords = self.cursor.fetchone()[0]
 print self.maxRecords

 #inputView
 def inputViewSetColumn(self, columName):
 columns = self.inputView.get_columns()
 for c in columns:
  self.inputView.remove_column(c)
 
 self.inputViewModel.clear()
 self.inputView.set_model(self.inputViewModel)
 for columnNum in range(len(columName)):
  renderer = gtk.CellRendererText()
  renderer.set_property("editable", True)
  renderer.set_data("column", columnNum)
  renderer.connect("edited", self.on_input_cell_edited)

  column = gtk.TreeViewColumn(columName[columnNum], renderer, 
     text=columnNum)
  column.set_resizable(True)
  self.inputView.append_column(column)

 def inputReader(self):
 self.inputViewModel = self.inputViewReaderModel
 self.inputViewSetColumn(self.readerColumName[1:])

 def inputBook(self):
 self.inputViewModel = self.inputViewBookModel
 self.inputViewSetColumn(self.bookColumName[1:])

 #Callback Functions
 def on_mainWindow_delete_event(self, widget, data=None):
 print "destroy signal occurred"
 gtk.main_quit()

 #BorrowView
 def on_borrowAdd_clicked(self, button, data = None):
 self.borrowViewModel.append((1001, 1, self.nowDate))

 def on_borrowDel_clicked(self, button, data = None):
 selection = self.borrowView.get_selection()
 model, iter = selection.get_selected()
 if iter:
  model.remove(iter)

 def on_borrowClear_clicked(self, button, data = None):
 self.borrowViewModel.clear()

 def on_borrowSubmit_clicked(self, button, data = None):
 for row in self.borrowViewModel:
  self.cursor.execute("INSERT INTO borrow VALUES (NULL, ?, ?, ?)", row)
 self.dbconn.commit()
 self.infoMessage(u"借书记录已经成功提交。")
 self.borrowViewModel.clear()

 def on_borrow_cell_edited(self, cell, path_string, new_text):
 model = self.borrowViewModel
 iter = model.get_iter_from_string(path_string)
 column = cell.get_data("column")
 try:
  id = int(new_text)
 except ValueError, e:
  print e
  self.errorMessage(u"请输入纯数字记录。")
  return

 if column == 0:
  self.cursor.execute("SELECT * FROM reader where ReaderID = ?", [new_text])
  if self.cursor.fetchone():
  model.set(iter, column, id)
  else:
  self.errorMessage(u"不存在该读者号: %d。" % id)

 if column == 1:
  self.cursor.execute("SELECT * FROM books where BookID = ?", [new_text])
  if self.cursor.fetchone():
  model.set(iter, column, id)
  else:
  self.errorMessage(u"不存在该书本号: %d。" % id)

 #QueryView
 def on_queryBooks_clicked(self, button, data = None):
 self.queryBook()
 self.cursor.execute("SELECT * FROM books LIMIT ? OFFSET ?", [15, 0])
 for row in self.cursor:
  self.queryViewModel.append(row)

 def on_queryReaders_clicked(self, button, data = None):
 self.queryReader()
 self.cursor.execute("SELECT * FROM reader LIMIT ? OFFSET ?", [15, 0])
 for row in self.cursor:
  self.queryViewModel.append(row)

 def on_queryPrev_clicked(self, button, data = None):
 if self.queryRecord == 0:
  self.errorMessage(u"已到最前页。")
  return
 self.queryRecord -= 15
 self.queryViewModel.clear()

 if self.queryViewModel.get_n_columns() == 9:
  self.cursor.execute("SELECT * FROM books LIMIT ? OFFSET ?",[15, self.queryRecord])

 elif self.queryViewModel.get_n_columns() == 4:
  self.cursor.execute("SELECT * FROM reader LIMIT ? OFFSET ?",[15, self.queryRecord])

 for row in self.cursor:
  self.queryViewModel.append(row)


 def on_queryNext_clicked(self, button, data = None):
 if self.queryRecord + 15 > self.maxRecords:
  self.errorMessage(u"已到最后页。")
  return

 self.queryRecord += 15
 self.queryViewModel.clear()

 if self.queryViewModel.get_n_columns() == 9:
  self.cursor.execute("SELECT * FROM books LIMIT ? OFFSET ?",[15, self.queryRecord])

 elif self.queryViewModel.get_n_columns() == 4:
  self.cursor.execute("SELECT * FROM reader LIMIT ? OFFSET ?",[15, self.queryRecord])

 for row in self.cursor:
  self.queryViewModel.append(row)


 def on_returnQuery_clicked(self, button, data = None):
 readerid = self.returnEntryReaderID.get_text()
 bookid = self.returnEntryBookID.get_text()

 if len(readerid) and len(bookid):
  self.cursor.execute("SELECT borrow.BorrowID, books.BookName, reader.ReaderName,\
    reader.ReaderSchool, borrow.BorrowDate FROM borrow,books,reader\
    WHERE books.BookID = borrow.BookID AND \
    reader.ReaderID = borrow.ReaderID AND\
    borrow.ReaderID = ? AND borrow.BookID = ?", [readerid, bookid])
 elif len(readerid):
  self.cursor.execute("SELECT borrow.BorrowID, books.BookName, reader.ReaderName,\
    reader.ReaderSchool, borrow.BorrowDate FROM borrow,books,reader\
    WHERE books.BookID = borrow.BookID AND \
    reader.ReaderID = borrow.ReaderID AND\
    borrow.ReaderID = ?", [readerid])
 elif len(bookid):
  self.cursor.execute("SELECT borrow.BorrowID, books.BookName, reader.ReaderName,\
    reader.ReaderSchool, borrow.BorrowDate FROM borrow,books,reader\
    WHERE books.BookID = borrow.BookID AND \
    reader.ReaderID = borrow.ReaderID AND\
    borrow.BookID = ?", [bookid])
 else:
  self.errorMessage(u"请输入查询条件。")
  return

 self.returnViewModel.clear()

 for row in self.cursor:
  self.returnViewModel.append(row)
  

 def on_returnCommit_clicked(self, button, data = None):
 selection = self.returnView.get_selection()
 model, iter = selection.get_selected()
 if iter:
  borrowDate = time.strptime(model.get_value(iter, 4), "%Y-%m-%d")
  timeDelta = datetime.date.today() - datetime.date(*borrowDate[0:3])
  borrowDays = timeDelta.days

  borrowID = model.get_value(iter, 0)
  self.cursor.execute("DELETE FROM borrow WHERE BorrowID = ?", [borrowID])
  self.dbconn.commit()
  readerName = model.get_value(iter, 2)
  bookName = model.get_value(iter, 1)
  self.infoMessage(u"读者 %s 所借书《%s》归还成功。 借出%d天" % (readerName, bookName, borrowDays))
  model.remove(iter)

 #inputView
 def on_inputReader_clicked(self, button, data = None):
 self.inputReader()

 def on_inputBooks_clicked(self, button, data = None):
 self.inputBook()

 def on_inputAdd_clicked(self, button, data = None):
 if not self.inputViewModel:
  self.errorMessage(u"请先选择录入类型。")
  return
 count = self.inputViewModel.get_n_columns()
 if count == 3:
  inputReaderInitData = (u"姓名", u"身份", u"备注")
  self.inputViewModel.append(inputReaderInitData)
 elif count == 8:
  inputBookInitData = (u"书名", u"作者", u"出版社", 
    0.0, self.nowDate, u"分类", u"简介", 0)
  self.inputViewModel.append(inputBookInitData)

 def on_inputDel_clicked(self, button, data = None):
 selection = self.inputView.get_selection()
 model, iter = selection.get_selected()
 if iter:
  model.remove(iter)

 def on_inputSubmit_clicked(self, button, data = None):
 count = self.inputViewModel.get_n_columns()
 for row in self.inputViewModel:
  #录入读者
  if count == 3:
  self.cursor.execute(u"INSERT INTO reader VALUES (NULL, ?, ?, ?)", 
     [s.decode("utf-8") for s in row])

  #录入书目
  elif count == 8:
  dataRow = []
  for obj in row:
   if isinstance(obj, str):
   dataRow.append(obj.decode("utf-8"))
   else:
   dataRow.append(obj)
  print dataRow
  self.cursor.execute(u"INSERT INTO books VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?)",\
     dataRow)
 self.dbconn.commit()
 self.infoMessage(u"记录已经成功提交。")
 self.inputViewModel.clear()

 def on_input_cell_edited(self, cell, path_string, new_text):
 iter = self.inputViewModel.get_iter_from_string(path_string)
 column = cell.get_data("column")
 columnCount = self.inputViewModel.get_n_columns()
 if columnCount == 3:
  self.inputViewModel.set(iter, column, new_text)
 elif columnCount == 8:
  if self.inputViewModel.get_column_type(column) == gobject.TYPE_FLOAT:
  try:
   self.inputViewModel.set(iter, column, float(new_text))
  except ValueError, e:
   self.errorMessage(u"请输入价格实数。")
   return
  elif self.inputViewModel.get_column_type(column) == gobject.TYPE_UINT:
  try:
   self.inputViewModel.set(iter, column, int(new_text))
  except ValueError, e:
   self.errorMessage(u"请输入整数。")
   return
  else:
  self.inputViewModel.set(iter, column, new_text)

 def errorMessage(self, message):
 print message
 dialog = gtk.MessageDialog(None,
     gtk.DIALOG_MODAL | gtk.DIALOG_DESTROY_WITH_PARENT,
     gtk.MESSAGE_ERROR, gtk.BUTTONS_OK, message)
 dialog.run()
 dialog.destroy()

 def infoMessage(self, message):
 print message
 dialog = gtk.MessageDialog(None,
     gtk.DIALOG_MODAL | gtk.DIALOG_DESTROY_WITH_PARENT,
     gtk.MESSAGE_INFO, gtk.BUTTONS_OK, message)
 dialog.run()
 dialog.destroy()

 def main(self):
 self.window.show()
 gtk.main()

if __name__ == "__main__":
 app = LibManager()
 app.main()

LibDBInit.py

#!/usr/bin/python
#encoding:utf-8

import sqlite3

def LibDbInit(con):
 c = con.cursor()

 c.execute("""
 CREATE TABLE `books` (
 `BookID` INTEGER PRIMARY KEY,
 `BookName` TEXT ,
 `BookAuthor` TEXT ,
 `BookPublish` TEXT ,
 `BookPrice` FLOAT ,
 `BookDate` TEXT ,
 `BookType` TEXT ,
 `BookContent` TEXT ,
 `BookState` INTEGER
 )
 """)

 c.execute("""
 CREATE TABLE `reader` (
 `ReaderID` INTEGER PRIMARY KEY,
 `ReaderName` TEXT ,
 `ReaderSchool` TEXT ,
 `ReaderInfo` TEXT
 )
 """)

 c.execute("""
 CREATE TABLE `borrow` (
 `BorrowID` INTEGER PRIMARY KEY,
 `ReaderID` INTEGER ,
 `BookID` INTEGER ,
 `BorrowDate` TEXT
 )
 """)

 books = ((1, u"C语言程序设计", u"谭浩强", u"教育出版社", 29.90, u"2009-04-30", u"计算机", u"", 5),
 (2, u"数据结构", u"谭浩强", u"教育出版社", 29.90, u"2009-04-30", u"计算机", u"", 5),
 (3, u"数据库原理", u"谭浩强", u"教育出版社", 29.90, u"2009-04-30", u"计算机", u"", 5),
 (4, u"汇编语言", u"谭浩强", u"教育出版社", 29.90, u"2009-04-30", u"计算机", u"", 5),
 (5, u"大学国文", u"国立", u"教育出版社", 19.90, u"2009-04-30", u"文学", u"", 5),
 (6, u"古代诗词", u"国立", u"教育出版社", 19.90, u"2009-04-30", u"文学", u"", 5),
 (7, u"广州地图", u"工作", u"广州出版社", 9.90, u"2009-04-30", u"工具书", u"", 5),
 (8, u"牛津词典", u"词典", u"广州出版社", 9.90, u"2009-04-30", u"工具书", u"", 5))

 for r in books:
 c.execute("INSERT INTO books VALUES (?,?,?,?,?,?,?,?,?)", r)

 readers = ((1001, u"陈一", u"广州大学计算机学院", u"B15"),
 (1002, u"王二", u"广州大学计算机学院", u"B15"),
 (1003, u"刘三", u"广州大学美术学院", u"B12"),
 (1004, u"陈一明", u"广州大学人文学院", u"B10"),
 (1005, u"张三", u"广州大学人文学院", u"B5"),
 (1006, u"何明", u"广州大学土木工程学院", u"B22"),
 (1007, u"陈中", u"广州大学数学学院", u"B24"),
 (1008, u"黄六", u"广州大学体育学院", u"B25"))

 for r in readers:
 c.execute("INSERT INTO reader VALUES (?,?,?,?)", r)

 borrows = ((1, 1001, 1, u"2009-04-20"),
 (2, 1001, 2, u"2009-04-20"),
 (3, 1002, 3, u"2009-04-20"),
 (4, 1003, 5, u"2009-04-20"),
 (5, 1004, 4, u"2009-04-20"),
 (6, 1004, 2, u"2009-04-20"),
 (7, 1003, 7, u"2009-04-20"),
 (8, 1006, 8, u"2009-04-20"),
 (9, 1007, 2, u"2009-04-20"),
 (10, 1008, 8, u"2009-04-20"))

 for r in borrows:
 c.execute("INSERT INTO borrow VALUES (?,?,?,?)", r)

 # Save (commit) the changes
 con.commit()

if __name__ == "__main__":
 LibDbInit(sqlite3.connect('sqlitefile.db'))