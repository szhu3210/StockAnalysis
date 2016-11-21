#!usr/bin/env python
# -*- coding: utf-8 -*-

#This program is to add some values to the current database

#Search all files from the directory,read txt csv and create out object which is a txt
from datetime import datetime as dt
from os import listdir
from os.path import isfile, join
mypath='/home/troy/Stock Analysis/1Data/4stockdata-FPP/Test0'
outpath='/home/troy/Stock Analysis/1Data/5stockdata-final/Test0'
files=[f for f in listdir(mypath) if isfile(join(mypath,f))]

import csv
import re

def process():
	for x in files:
		filename=re.match(r'...(\d{6})....',x)
		#if 600000<=int(filename.group(1))<605000:
		#	continue
		#if 0<=int(filename.group(1))<405:
		#	continue
		print(x)
		with open(join(mypath,x),'r') as stockdata:
			f=open('/home/troy/Stock Analysis/1Data/7FinancialData/financial data.csv','rt',encoding='gbk')
			reader=csv.reader(f,delimiter=',')
			out=open(join(outpath,x),'w')
			temp=[]
			stock=re.match(r'...(\d{6})....',x)
			stock=stock.group(1)
			if stock[0]=='6':
				stock='sh'+stock
			else:
				stock='sz'+stock
			for row in reader:
				if row[0]==stock:
					temp.append(row)
			temp.reverse()
			#print(temp)
			# for row in temp:
			# 	if row[3]!='':
			# 		date_list=(row[3].split('-'))
			# 	else: 
			# 		date_list=(row[2].split('-'))
			# 		if date_list[1]!='12':
			# 			date_list[1]=str(int(date_list[1])+1)
			# 		else:
			# 			date_list[0]=str(int(date_list[0])+1)
			# 			date_list[1]='01'
			# 	row[3]=date_list[0]+date_list[1]+date_list[2]
			# 	print('!',row[3])

			last_value=[0]
			# ****** change the value in range func if I want to add more EPS data!
			# BE CAREFUL ! THE VALUE IN () IS SMALLER THAN THE NUMBER OF ADDED DATAS
			for i in range(2):
				last_value.append(0)
			for line in stockdata.readlines():
				line_list=line.split(' ')
				date=re.match(r'^(\d{8})...',line_list[0])
				#print('! ',line)
				# if (len(temp)>0): 
				# 	if (date.group(1)>=temp[0][3]):
				# 		if (len(temp)>1):
				# 			while(date.group(1)>=temp[1][3]):
				# 				temp.pop(0)
				# 				if (len(temp)==1):
				# 					break
				# 		#print('update fin. value!',date.group(1))
				# 		#calculate new value and save
				# 		for i in range(len(temp[0])):
				# 			if temp[0][i]=='':
				# 				temp[0][i]='0'
				# 		#if I want to add even more EPS data, add in the next line and change the first line in this block marked as ******, change the value in the range func.
				# 		new_value=[ 
				# 					round(float(temp[0][7]),4),
				# 					round(float(temp[0][8]),4),
				# 					#round(((float(temp[0][8])/float(last_value[1])-1)*100)if float(last_value[1])!=0 else 0,2),
				# 					round(epsup,2),
				# 					round(float(temp[0][42])*100,2),
				# 					round(((float(temp[0][42])*100/float(last_value[3])-1)*100)if float(last_value[3])!=0 else 0,2),
				# 					round(float(temp[0][5])/float(temp[0][4])/pow(10,8) if float(temp[0][4]) != 0 else 0,2)
				# 				  ]
				# 		last_value=new_value
				# 		#write new value
				# 		value=line.strip()+' '+" ".join(map(str,last_value))+'\n'
				# 		out.write(value)
				# 		temp.pop(0)
				# 	else:
				# 		#write old value
				# 		value=line.strip()+' '+" ".join(map(str,last_value))+'\n'
				# 		out.write(value)
				# else:
				# 	#write old value, the same as above
				# 	value=line.strip()+' '+" ".join(map(str,last_value))+'\n'
				# 	out.write(value)
				if len(temp)>0 :
					pointer = -1
					for i in range(len(temp)-1,-1,-1):
						if (temp[i][3]!='') :
							if (dt.strptime(temp[i][3], "%Y-%m-%d")<=dt.strptime(date.group(1), "%Y%m%d")) :
								pointer = i
								break
					lastpointer = -1
					if pointer >= 0 :
						for i in range(pointer-1,-1,-1) :
							#print(temp[pointer][2][6],temp[i][2][6],'original')
							if temp[pointer][2][6] == temp[i][2][6] :
								#print('matched!')
								lastpointer = i
								break
					if pointer >= 0 :
						for i in range(len(temp[pointer])):
							if temp[pointer][i] == '' :
								temp[pointer][i] = '0'
						if lastpointer >= 0 :
							for i in range(len(temp[lastpointer])):
								if temp[lastpointer][i] == '' :
									temp[lastpointer][i] = '0'
						new_value=[
									round(float(temp[pointer][7]),2),
									round(float((float(temp[pointer][7])/float(temp[lastpointer][7])-1)*100),2) if ( (lastpointer >= 0) & (float(temp[lastpointer][7]) >0) ) else 0,
									round(float(temp[pointer][7])/float(temp[pointer][9])*100.0 if float(temp[pointer][9]) > 0 else 0, 2)
						]
						last_value=new_value
						value=line.strip()+' '+" ".join(map(str,last_value))+'\n'
						out.write(value)
					else:
						value=line.strip()+' '+" ".join(map(str,last_value))+'\n'
						out.write(value)
				else:
					value=line.strip()+' '+" ".join(map(str,last_value))+'\n'
					out.write(value)
			out.close()
			f.close()
process()
	

	
