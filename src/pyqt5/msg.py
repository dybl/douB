'''
整个应用相互发送通知的消息类，通过这个来进行一些通知
'''

#消息类
class Msg:
    #一个消息类实例化的构造函数需要传入目标界面类，消息标题，消息内容
    def __init__(self,target,title,msg):
        self.target = target
        self.title = title
        self.msg = msg

