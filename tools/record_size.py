#!/usr/bin/python

from git import Repo
import os
import sys
from datetime import datetime
import gspread
from oauth2client.service_account import ServiceAccountCredentials

def isMasterBranch():
    repo = Repo(os.getcwd())
    try:
        return repo.active_branch.name == 'master'
    except:
        return False # Probably a detached head state

def getHeadHash():
    repo = Repo(os.getcwd())
    return str(repo.head.commit)

def getCommitLink(hash):
    return "https://github.com/joshpeterson/binarily/commit/" + hash

def getFileSize(path):
    return os.path.getsize(path)

def getDateAndTime():
    return datetime.now().strftime("%Y-%m-%d %H:%M")

def getCommitRow(worksheet, hash):
    commits = worksheet.col_values(2)
    try:
        return commits.index(hash) + 1
    except ValueError:
        return -1

def getFirstEmptyRow(worksheet):
    return len(worksheet.col_values(1)) + 1

def getSizeColumn(worksheet, name):
    columnNames = worksheet.row_values(1)
    for i in range(len(columnNames)):
        if columnNames[i] == name:
            return i + 1;
    raise ValueError("A column was not found with the name: " + name)

if len(sys.argv) != 3:
    print "Usage: size.py <size name> <file>"
    quit()

if not isMasterBranch():
    print "This is not the master branch - skipping size recording."
    quit()

name = sys.argv[1]
file = sys.argv[2]

date = getDateAndTime()
hash = getHeadHash()
link = getCommitLink(hash)
size = getFileSize(file)

scope = ['https://spreadsheets.google.com/feeds',
         'https://www.googleapis.com/auth/drive']

credentials = ServiceAccountCredentials.from_json_keyfile_name('Binarily Size Data Update-fbe2263a6cf6.json', scope)

gc = gspread.authorize(credentials)

worksheet = gc.open("Binarily Size Data").worksheet("Sizes")
commits = worksheet.col_values(2)
row = getCommitRow(worksheet, hash)
if row == -1:
    row = getFirstEmptyRow(worksheet)
    worksheet.update_cell(row, 1, date)
    worksheet.update_cell(row, 2, hash)
    worksheet.update_cell(row, 3, link)

column = getSizeColumn(worksheet, name)
worksheet.update_cell(row, column, size)

print "Added size data for %s at %s: %s" % (name, hash, size)
