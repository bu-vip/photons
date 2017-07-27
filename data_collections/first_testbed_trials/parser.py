import os

file = open('empty_room/lights_off/lights_off_empty_room1.txt','r')
txt = file.read()
file.close()

values = []
row = []
group = []
num = ""
offset = 0
for i in range(0,len(txt)):
    if (txt[i].isdigit()):
        if (not txt[i-1].isalpha() and not txt[i-1].isdigit()):
            num = txt[i]
            if (txt[i+1].isdigit()):
                num = num + txt[i+1]
                if (txt[i+2].isdigit()):
                    num = num + txt[i+2]
            row.append(int(num))
            if (len(row)%9 == 0):
                group.append(row)
                row = []
                if (len(group) % 4 == 0):
                    values.append(group)
                    group = []
    num = ""

os.system("rm -rf parsed_trial/")
os.system("mkdir parsed_trial/")


print(values)
