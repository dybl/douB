import mysql.connector
import sys, os
import time
import datetime
from tkinter import *
from tkinter.messagebox import *
class Libop:
  user = 'j8'
  pwd = 'junjc9'
  host = 'localhost'
  db = 'bms'
  data_file = 'mysql-test.dat'
  def __init__(self):
    print("init")
    try:
      self.library=mysql.connector.connect(user=Libop.user,password=Libop.pwd,host=Libop.host,database=Libop.db)
      self.cursor=self.library.cursor()
      print("Connect successfully")
    except mysql.connector.Error as err:
      print("WTF! initial wrong")
      print("Error: {}".format(err.msg))
      sys.exit()
  def select(self,str):
    try:
      self.cursor.execute(str)
      return self.cursor.fetchall()
    except mysql.connector.Error as err:
      print("WTF! select wrong")
      print("Error:{}".format(err.msg))
      print(str)
      showinfo("ERROR","Please input the parameter correctly")
  def update(self,str):
    try:
      self.cursor.execute(str)
      self.library.commit()
      return 1
    except mysql.connector.Error as err:
      print("WTF! update wrong")
      print("Error:{}".format(err.msg))
      return 0
  def delete(self,str):
    try:
      self.cursor.execute(str)
      self.library.commit()
    except mysql.connector.Error as err:
      print("WTF! delete wrong")
      print("Error:{}".format(err.msg))
  def insert(self,str):
    try:
      self.cursor.execute(str)
      self.library.commit()
      return 1
    except mysql.connector.Error as err:
      print("WTF! insert wrong")
      print("Error:{}".format(err.msg))
      return 0
LIB = Libop()      
root=Tk()
root.wm_title("图书管理系统by张文伟")
str1=str2=''
book_type=name=year=publisher=writer=price1=price2=order=''
cardid=''
def call_rent(en1,en2,brok):
  st1=en1.get()
  st2=en2.get()
  rent(st1,st2,brok)
def call_return(en1,en2):
  st1=en1.get()
  st2=en2.get()
  back(st1,st2)
def login():
  str1=ide.get()
  str2=pwde.get()
  curs=LIB.select("select manage_id,pswd from managers where manage_id='{}' and pswd='{}'".format(str1,str2))
  if ((str1,str2) in curs): 
    showinfo('message','login success')
    label_book_id=Label(root,text='BookID:').grid(row=0,column=4,sticky=W)
    label_card_id=Label(root,text='CardID:').grid(row=1,column=4,sticky=W)
    entry_book_id=Entry(root)
    entry_book_id.grid(row=0,column=5,sticky=W)
    entry_card_id=Entry(root)
    entry_card_id.grid(row=1,column=5,sticky=W)
    entry_cardid=Entry(root)
    entry_cardid.grid(row=5,column=0,sticky=W)
    #buttons
    button_insert=Button(root,text='insert book',command=inbook)
    button_insert.grid(row=0,column=2,sticky=W)
    button_return=Button(root,text='rent book')
    button_return.bind("<ButtonRelease-1>",lambda z:call_rent(entry_book_id,entry_card_id,str1))
    button_return.grid(row=0,column=3,sticky=W)
    button_rent=Button(root,text='return book')
    button_rent.bind("<ButtonRelease-1>",lambda l:call_return(entry_book_id,entry_card_id))
    button_rent.grid(row=1,column=2,sticky=W)
    button_delete=Button(root,text='delete card')
    button_delete.bind("<ButtonRelease-1>",lambda j:deletecard(entry_cardid))
    button_delete.grid(row=5,column=2,sticky=W)
    button_add=Button(root,text='add card',command=addwindow)
    button_add.grid(row=5,column=3,sticky=W)
    button_display=Button(root,text='display books')
    button_display.bind("<ButtonRelease-1>",lambda y:display_rent(entry_cardid))
    button_display.grid(row=5,column=1,sticky=W)
  else: 
    showinfo(title='login failure',message="WRONG ID OR PASSWORD!")
#add a card
def addwindow():
  top=Toplevel(root)
  label_card_id=Label(top,text='card id:').grid(row=0,column=0,sticky=W)
  label_name=Label(top,text='Name:').grid(row=1,column=0,sticky=W)
  label_unit=Label(top,text='Units:').grid(row=2,column=0,sticky=W)
  label_type=Label(top,text='type:').grid(row=3,column=0,sticky=W)
  entry_card_id=Entry(top)
  entry_card_id.grid(row=0,column=1,sticky=W)
  entry_name=Entry(top)
  entry_name.grid(row=1,column=1,sticky=W)
  entry_unit=Entry(top)
  entry_unit.grid(row=2,column=1,sticky=W)
  entry_type=Entry(top)
  entry_type.grid(row=3,column=1,sticky=W)
  button_constructe=Button(top,text='Add')
  button_constructe.bind("<ButtonRelease-1>",lambda q:addcard(entry_card_id,entry_name,entry_unit,entry_type))
  button_constructe.grid(row=4)
def addcard(en1,en2,en3,en4):
  cardid=en1.get()
  name=en2.get()
  unit=en3.get()
  c_type=en4.get()
  select="select card_id from lib_card where card_id='{}'".format(cardid)
  if (c_type not in ('T','S','O')): 
    showinfo('error',"NO SUCH TYPE")
    return 0
  line=LIB.select(select)
  if (len(line)!=0):
    showinfo('addition failure',"Already have this ID!")
  else:
    insert="insert into lib_card values('{}','{}','{}','{}')".format(cardid,name,unit,c_type)
    LIB.insert(insert)
    showinfo('ok','addition success')
  return 1
#insert book
def inbook():
  insert_book=Toplevel(root)
  insert_book.title('insert book')
  text_insert=Text(insert_book)
  text_insert.pack()
  button_confirm=Button(insert_book,text='confirm')
  button_confirm.bind("<ButtonRelease-1>",lambda x:booksin(text_insert))
  button_confirm.pack()
def booksin(text_insert):
  string=text_insert.get('0.0',END)
  string=string.split('\n')
  print(string)
  for line in string:
    if line=='':
      break
    lines=line.split(',')
    bookid=lines[0][1:]
    t=lines[1]
    name=lines[2]
    publisher=lines[3]
    year=lines[4]
    writer=lines[5]
    price=lines[6]
    total=lines[7]
    stock=lines[8][:-1]
    if (int(stock)>int(total) or int(price)<0): 
      showinfo('insert error!','stock wrong or price is below 0!')
      continue
    #print("insert into book values('{}','{}','{}','{}',{},'{}',{},{},{})".format(bookid,t,name,publisher,year,writer,price,total,stock))
    t=LIB.insert("insert into book values('{}','{}','{}','{}',{},'{}',{},{},{})".format(bookid,t,name,publisher,year,writer,price,total,stock))
    if (t==0):
      showinfo('error','book {} has been inserted'.format(bookid))
  showinfo('success','insert has been done')
#original window
label_type=Label(root,text='TYPE').grid(row=3,sticky=W,column=0)
label_name=Label(root,text='NAME').grid(row=3,sticky=W,column=1)
label_year=Label(root,text='YEAR(XXXX-XXXX)').grid(row=3,sticky=W,column=2)
label_publisher=Label(root,text='PUBLISHER').grid(row=3,sticky=W,column=3)
label_writer=Label(root,text='WRITER').grid(row=3,sticky=W,column=4)
label_lowprice=Label(root,text='lowestprice').grid(row=3,sticky=W,column=5)
label_highprice=Label(root,text='highestprice').grid(row=3,sticky=W,column=6)
label_order=Label(root,text='order by').grid(row=0,sticky=W,column=6)

entry_type=Entry(root)
entry_type.grid(row=4,column=0,sticky=W)
entry_name=Entry(root)
entry_name.grid(row=4,column=1,sticky=W)
entry_year=Entry(root)
entry_year.grid(row=4,column=2,sticky=W)
entry_publisher=Entry(root)
entry_publisher.grid(row=4,column=3,sticky=W)
entry_writer=Entry(root)
entry_writer.grid(row=4,column=4,sticky=W)
entry_price1=Entry(root)
entry_price1.grid(row=4,column=5,sticky=W)
entry_price2=Entry(root)
entry_price2.grid(row=4,column=6,sticky=W)

#order the result
order_index=0
Lb_order=Listbox(root,selectmode=SINGLE,height=6)
order='name','book_type','T','writer','price','publisher'
Lb_order.insert(0,order[0])
Lb_order.insert(1,"type")
Lb_order.insert(2,"year")
Lb_order.insert(3,order[3])
Lb_order.insert(4,order[4])
Lb_order.insert(5,order[5])
Lb_order.grid(row=0,column=7,sticky=W)
Lb_order.selection_set(0)
def booksearch():
  select="select BookID,book_type,name,publisher,T,writer,price,total,stock from book"

  order_index=Lb_order.curselection()
  if (len(order_index)!=0):
    order_index=order_index[0]
  else:
    order_index=0;
  orders=order[order_index]
  name=entry_name.get()
  book_type=entry_type.get()
  publisher=entry_publisher.get()
  year=entry_year.get()
  writer=entry_writer.get()
  price1=entry_price1.get()
  price2=entry_price2.get()
  year1=year[0:4]
  year2=year[5:9]
  count=0
  if name!='':
    if count!=0:
      select+=" and"
    else:select+=" where"
    count+=1
    select+=" name='{}'".format(name)
  if book_type!='':
    if count!=0:
      select+=" and"
    else:select+=" where"
    count+=1
    select+=" book_type='{}'".format(book_type)
  if publisher!='':
    if count!=0:
      select+=" and"
    else:select+=" where"
    count+=1
    select+=" publisher='{}'".format(publisher)
  if year1!='':
    if year2=='':
      if count!=0:
        select+=" and"
      else:select+=" where"
      count+=1
      select+=" t={}".format(year1)
    else:
      if count!=0:
        select+=" and"
      else:select+=" where"
      count+=1
      select+=" T between {} and {}".format(year1,year2)
  if writer!='':
    if count!=0:
      select+=" and"
    else:select+=" where"
    count+=1
    select+=" writer='{}'".format(writer)
  if price1!='':
    if price2!='':
      if count!=0:
        select+=" and"
      else:select+=" where"
      count+=1
      select+=" price between {} and {}".format(price1,price2)
    else:
      if count!=0:
        selece+="and"
      else:select+=" where"
      count+=1
      select+=" price={}".format(price1)
  if orders=='':
    select+=" order by name"
  else:
    select+=" order by {}".format(orders)
  print(select)
  curs=LIB.select(select)
  searchresult=Toplevel(root)
  searchresult.title('result')
  text=Text(searchresult)
  text.insert(INSERT,"BookID\ttype\tname\tpublish\tyear\twriter\tprice\ttotal\tstock\n")
  for (BookIDs,book_types,names,publishers,years,writers,prices,totals,stocks) in curs:
    text.insert(INSERT,"{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\n".format(BookIDs,book_types,names,publishers,years,writers,prices,totals,stocks))
  text.pack()
def display_rent(en_cardid):
  cardid=en_cardid.get()
  select="select card_id from lib_card where card_id='{}'".format(cardid)
  curs=LIB.select(select)
  order_index=Lb_order.curselection()
  if len(order_index)!=0 :
    order_index=order_index[0]
  else:
    order_index=0;
  orders=order[order_index]
  if ((cardid,) in curs):
    select="select card_id,name,unit,c_type from lib_card where card_id='{}'".format(cardid)
    curs=LIB.select(select)
    top=Toplevel(root)
    text=Text(top)
    for (card_id,name,unit,c_type) in curs:
      text.insert(INSERT,"card_id:{}\n".format(card_id))
      text.insert(INSERT,"name:{}\n".format(name))
      text.insert(INSERT,"unit:{}\n".format(unit))
      text.insert(INSERT,"c_type:{}\n".format(c_type))
    select="select BookID,book_type,name,publisher,t,writer,price,total,stock from book natural join record where card_id='{}' and still=1 order by {}".format(cardid,orders)
    curs=LIB.select(select)
    text.insert(INSERT,"BookID\ttype\tname\tpublish\tyear\twriter\tprice\ttotal\tstock\n")
    for (BookID,book_type,name,publisher,t,writer,price,total,stock) in curs:
      text.insert(INSERT,"{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\n".format(BookID,book_type,name,publisher,t,writer,price,total,stock))
    text.pack()
  else:
    showinfo('Error',"NO SUCH CARD")
def checkcard(cardid):
  select="select card_id from lib_card where card_id='{}'".format(cardid)
  curs=LIB.select(select)
  if (cardid,) in curs:
    return 1
  else:
    return 0

def rent(BookID,cardid,brokerage):
  if not (checkcard(cardid)): 
    showinfo('error','no such card')
    return 0
  select="select stock from book where BookID='{}'".format(BookID)
  stocks=LIB.select(select)
  #stocks=curs.fetchall()
  stock=stocks[0]
  if (stock>(0,)):
    update="update book set stock=stock-1 where BookID='{}'".format(BookID)
    flag=LIB.update(update)
    if flag:
      insert="insert into record values('','{}','{}',CURDATE(),DATE_ADD(CURDATE(),INTERVAL 1 MONTH),'{}',1)".format(cardid,BookID,brokerage)
      LIB.insert(insert)
      showinfo('rent success','OK')
    else:
      showinfo('rent failure',"stock wrong")
  else:
    select="select return_time from record where BookID='{}' and return_time>=all(select return_time from record where BookID='{}')".format(BookID,BookID)
    date=LIB.select(select)
    #date=curs.fetchall()
    date=str (date)
    showinfo('Out of stock',"There are no more such book,The recent returning will be at:{}-{}-{}".format(date[16:20],date[22:23],date[26:27]))
    
  return 1
def back(BookID,cardid):
  if not(checkcard(cardid)): return 0
  select="select BookID from record where BookID='{}' and card_id='{}' and still=1".format(BookID,cardid)
  curs=LIB.select(select)
  if (BookID,) in curs:
    select="select record_id from record where BookID='{}' and card_id='{}' and still=1 order by rent_time".format(BookID,cardid)
    cur=LIB.select(select)
    #cur=curss.fetchall()
    for record in cur:
      recordid=str (record)
      recordid=recordid[1:]
      recordid=recordid[:-2]
      update="update record set still=0 where record_id='{}'".format(recordid)
      LIB.update(update)
      update="update book set stock=stock+1 where BookID='{}'".format(BookID)
      LIB.update(update)
      break
    showinfo('message',"Return Success!")
    return 1
  else:
    showinfo('error',"You can't return the book!")
    return 1

def deletecard(card):
  cardid=card.get()
  if not (checkcard(cardid)):
    showinfo('error',"NO SUCH CARD")
    return 0
  select="select record_id from record where card_id='{}' and still=1".format(cardid)
  curs=LIB.select(select)
  for record_id in curs:
    showinfo('error',"Some books this card rented haven't been returned")
    return 0
  delete="delete from lib_card where card_id='{}'".format(cardid)
  LIB.delete(delete)
  showinfo('ok','success')
  return 1
label_id=Label(root,text='ID: ')
label_id.grid(row=0,sticky=W)
ide=Entry(root)
ide.grid(row=0,column=1,sticky=E)
label_psw=Label(root,text='PassWord: ').grid(row=1,sticky=W)
pwde=Entry(root,show='*')
pwde.grid(row=1,column=1,sticky=E)
log_button=Button(root,text='Login',command=login)
log_button.grid(row=2,column=1)

button_search=Button(root,text='Search Book',command=booksearch)
button_search.grid(row=4,column=7,sticky=W)
print("all done")
root.mainloop()