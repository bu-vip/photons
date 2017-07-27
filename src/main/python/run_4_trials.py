import controller
import os


controller.initialize()


controller.run_trial()
controller.parse()
os.system("mv output.txt trial1.txt")

controller.run_trial()
controller.parse()
os.system("mv output.txt trial2.txt")

controller.run_trial()
controller.parse()
os.system("mv output.txt trial3.txt")

controller.run_trial()
controller.parse()
os.system("mv output.txt trial4.txt")
