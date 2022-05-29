import datetime
import csv

#getting file name
e = datetime.datetime.now()
date=e.strftime("%Y-%m-%d")
tail="_Flow.csv"
filename=date+tail

#opening file
file = open(filename)
csvreader = csv.reader(file)