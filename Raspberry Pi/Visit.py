import datetime
import collections
import csv
import pathlib

class Visit:
    cowID: str
    time: datetime.datetime
    milkVolume: float

    def __init__(self, cowID: str, time: datetime.datetime, milkVolume: float):
        self.cowID = cowID
        self.time = time

visitList: collections.deque[Visit] = collections.deque[Visit]()
minTimeBetweenMilks: datetime.timedelta = datetime.timedelta(hours=2)

def LoadVisits(filePath: pathlib.Path):
    if not filePath.exists():
        return
    
    file = open(filePath, 'r', newline='')
    csvReader = csv.reader(file)

    global visitList
    for row in csvReader:
        visitList.appendleft(Visit(row[0], datetime.datetime.strptime(row[1], "%H:%M - %m/%d/%Y"), float(row[2])))

    file.close()

def SaveVisits(filePath: pathlib.Path):
    file = open(filePath, 'w', newline='')
    csvWriter = csv.writer(file)
    
    global visitList
    for visit in reversed(visitList):
        csvWriter.writerow([visit.cowID, datetime.datetime.strftime(visit.time, "%H:%M - %m/%d/%Y"), str(visit.milkVolume)])

    file.close()