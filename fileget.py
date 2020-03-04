import math
import numpy as np
import matplotlib.pyplot as plt
import sys
import re
import glob
from natsort import natsorted

def main():

   file_list = glob.glob("/Users/maedamizuki/metrology/opencv/hama/*")
   file=[]
   for file_list in natsorted(file_list):
      print(file_list)
      file.append(file_list)
   print(file)

   f = open(sys.argv[1],'w')
   f.write(str(file))
   f.close()

main()
