# -*- coding: utf-8 -*-
import csv
categories = ['Politics','Sports','Television','Twitter','Uplifting_news','Worldnews']
for cat in categories :
    with open(cat + '.csv') as csvfile :
        readCSV = csv.reader(csvfile,delimiter = ',')
        readCSV = [i[1] for i in readCSV]
        myfile = open(cat + '.tsv','w')
        for row in readCSV :
            print(row + "\t" + cat , file = myfile)
        
        
            
            
