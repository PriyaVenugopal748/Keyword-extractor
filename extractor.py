# -*- coding: utf-8 -*-
"""
Created on Sun Apr 14 07:23:19 2024

@author: dell
"""

import nltk
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer
import re
nltk.download('punkt')
nltk.download('stopwords')
stopword_list=stopwords.words('english')
stemmer=PorterStemmer()
def stem_words(text):
  text1=word_tokenize(text)
  stemmed_words= [stemmer.stem(word) for word in text1]
  stem1=list(set(stemmed_words))
  return " ".join(stem1)
def remove_punctuation(text):
  return re.sub('[^\w\s]','',text)
def eliminate_stopword(text):
  without_stopwords=[word for word in text if not word in stopword_list]
  return " ".join(without_stopwords)
def preprocess(text):
  text0=text.lower()
  text1=remove_punctuation(text0)
  text2=word_tokenize(text1)
  text3=eliminate_stopword(text2)
  #text4=stem_words(text3)
  return word_tokenize(text3)
file1=open("file1.txt","r")
sample_text=file1.read()
print(sample_text)
file1.close()
list2=list(preprocess(sample_text))
tuple2=tuple(preprocess(sample_text))
dic={}
for i in range(0,len(tuple2)):
  list3=[]
  for j in range(0,len(list2)):
    if(list2[j]==tuple2[i]):
      list3.append(j)
    p=tuple2[i]
  dic[p]=list3
print(dic)
dic2={}
u=0
for key in dic.keys():
  list4=[1,2]
  if(len(dic[key])==2):
    dic2[key]=dic[key]
  if(len(dic[key])>2):
    print(dic[key])
    list5=dic[key]
    list4[0]=list5[0]
    list4[1]=list5[1]
    dic2[key]=list4
print(dic2)
list_of_strings = [ f'{key}  {(str(dic2[key])[1:-1]).replace(","," ")}' for key in dic2 ]

# write string one by one adding newline
with open('out.txt', 'w') as my_file:
    [ my_file.write(f'{st}\n') for st in list_of_strings ]
