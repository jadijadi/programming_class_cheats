#!/opt/homebrew/bin/python3
import sys
import requests
from bs4 import BeautifulSoup

word = sys.argv[1]
url = 'https://www.google.com/search?q=%s&source=lnms&tbm=isch' % word

html = requests.get(url).text

soup = BeautifulSoup(html, 'html.parser')

try:
    print (soup.find_all("img")[2]['src'])
except:
    print ("")