from matplotlib import pyplot as plt
import numpy as np
import scipy.stats
def is_between(a, x, b):
    return min(a, b) < x < max(a, b)
f = open('/home/thoma/Desktop/IMUcalibrationdata.dat')
dta = [[],[],[]]
names = ["x","y","z"]
minmax = [[],[],[]]
for line in f:
    row = line.split(" ")
    if is_between(-5,float(row[0]),5):
        dta[0].append(float(row[0].replace("x","")))
    if is_between(-5,float(row[1]),5):
        dta[1].append(float(row[1].replace("y","")))
    if is_between(0,float(row[2]),15) :
        dta[2].append(float(row[2].replace("z","")))
minmax[0] = [np.max(dta[0]),np.min(dta[0])]
minmax[1] = [np.max(dta[1]),np.min(dta[1])]
minmax[2] = [np.max(dta[2]),np.min(dta[2])]
colcount = 0
for column in dta:
    a = np.average(column)
    b = np.arange(min(column),max(column),.01)
    fig = plt.figure(figsize=(16,9))
    ax1 = fig.add_subplot(111)
    ax1.hist(column, bins = b, color="black", rwidth = 1, label= "{} Accelerations".format(str(names[colcount]))) #put data into plot
    ax1.axvline(a, label="Mean: {:.4f} $^\\mathrm{{m}}/_{{\\mathrm{{s}}^2}}$".format(a))
    #ax1.set_yscale('log')
    #ax1.set_ylabel('log(Count)')
    ax1.set_ylabel('Count')
    ax1.set_xlabel('Acceleration $^\mathrm{m}/_{\mathrm{s}^2}$')
    ax1.plot([],[],' ',label="St. Dev.:{0:.4f}".format(np.std(column)))
    ax1.plot([],[],' ',label="{0}: [{1:.2f},{2:.2f}]".format(names[colcount],minmax[colcount][1],minmax[colcount][0]))
    fig.set_dpi(150)
    plt.title("Static Acceleration Distribution for the ICM20649 in the {0} Direction".format(names[colcount].capitalize()))
    plt.legend()
    plt.show()
    colcount += 1
