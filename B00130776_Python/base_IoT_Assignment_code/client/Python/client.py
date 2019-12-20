import xml.etree.ElementTree as elet
import numpy as np
import urllib.request
import matplotlib.pyplot as pplot

response = urllib.request.urlopen("http://localhost:8080/")
TimeValue = []
TempValue = []
data = response.read().decode()
root = elet.fromstring(data.strip("\n"))

for reading in root.findall('reading'):
    time = reading.find('time').text
    TimeValue.append(time[time.find(' '):])
    TempValue.append(int(reading.find('temperature').text))
    
pplot.style.use('ggplot')
title_obj = pplot.title('Temperature Vs Time')
pplot.setp(title_obj, fontsize = '16', fontname = 'calibri', color = 'orange')
pplot.plot(TimeValue, TempValue, 'purple')
pplot.xlabel('Time')
pplot.ylabel('Temperature')
pplot.show()