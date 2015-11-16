import os
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
res = {}

for file in os.listdir("./results"):
    fname = file.replace(".c.txt", "")
    res[fname] = {}
    if file.endswith(".txt"):
        for l in open("./results/"+file):
            line = l.replace("\t","").replace("\n", "").split(": ")
            res[fname][line[0]] = line[1]
print(res)


x = [i for i in range(11)]
y = [i for i in range(11)]
labels = ['mm1', 'mm2', 'mm3', 'mm4', 'mm5', 'mm5a', 'mm5b', 'mm6', 'mm7', 'mm8', 'mm9']
opt = ["Level 1 cache misses", "Level 2 cache misses", "Level 3 cache misses", "Level 1 instruction cache misses"]
colors = ["red", "blue", "green", "black"]




patchs = {}
for i in range(4):
    y = [res[l][opt[i]] for l in labels]
    plt.plot(x, y, color=colors[i])
    patchs[i] = mpatches.Patch(color=colors[i], label=opt[i])
plt.legend(handles=[patchs[i] for i in range(4)])
plt.xticks(x, labels, rotation='vertical')
plt.margins(0.2)
plt.subplots_adjust(bottom=0.15)
plt.show()