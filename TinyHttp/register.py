#!/usr/bin/python

import MySQLdb
import os

conn=MySQLdb.connect('localhost','root','',"student_five")
cour=conn.cursor()
query_string =os.environ.get('QUERY_STRING')
str = str(query_string)
str = str+'&'
usr=str[str.find('=')+1:str.find('&')]
str = str[str.find('&')+1:]

	
pawd= str[str.find('=')+1:str.find('&')]
str = str[str.find('&')+1:]
name = str[str.find('=')+1:str.find('&')]
str = str[str.find('&')+1:]

age = str[str.find('=')+1:str.find('&')]
#cour.execute("insert into usr(id,username,passwod) values(1,usr,pawd)
#cour.execute("insert into usr values(1,'123','456')")

str1 = "insert into usrs values (%s,'%s','%s',%s)"%(usr,pawd,name,age)
cour.execute(str1)
conn.commit()
cour.close()
conn.close()

print"regester success"
