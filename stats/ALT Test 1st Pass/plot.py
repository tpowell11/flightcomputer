from matplotlib import pyplot as plt
import numpy as np
def is_between(a, x, b):
    return min(a, b) < x < max(a, b)
f=open("./DATA.dat")
dta=[[],[]]
names = ["Transducer", "Altimiter"]
for line in f:
    row = line.split(" ")
    dta[0].append(float(row[0]))
    dta[1].append(float(row[1]))

min = np.min(dta)
max = np.max(dta)
TrnError = []
# Calculating error bars
for p in dta[0]:
    TrnError = p*(.25/100)*2
fig = plt.figure(figsize=(16,9))
ax1 = fig.add_subplot(111)
ax1.plot(range(len(dta[0])),dta[0],label="Transducer",color = "b")
ax1.errorbar(range(len(dta[0])),dta[0],yerr=2*(.25/100))
ax1.plot(range(len(dta[1])),dta[1],label="Altimiter",color = "r")
