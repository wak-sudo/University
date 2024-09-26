cyfry = {}

cyfry[0] = """
 ###  
#xxx#
#xxx#
#xxx#
 ###
"""

cyfry[1] = """
  #
 ##
  #
  #
 ###
"""

cyfry[4] = """
 # 
#
#####
  #
  #
"""


cyfry[2] = """
 ###  
#xxx#
  ##
 #
#####
"""

cyfry[5] = """
##### 
#xxx
####
 xxx#
####
"""

cyfry[8] = """
 ###  
#xxx#
 ### 
#xxx#
 ###
"""

cyfry[6] = """
 ###  
#xxx
#### 
#xxx#
 ###
"""

cyfry[9] = """
 ###  
#xxx#
 ####
 xxx#
 ###
"""

cyfry[3] = """
####  
 xxx#
 ### 
 xxx#
####
"""

cyfry[7] = """
#####
   #
 ###
 #
# 
"""

pytajnik = """
 ###  
#xxx#
  ##
   
  #
"""

def popraw(s):
    L = s.split('\n')
    for i in range(len(L)):
        if len(L[i]) < 5:
            L[i] += (5-len(L[i])) * " "
        else:
            L[i] = L[i][:5]   
    return L[1:-1]      

def daj_cyfre(n):
   if n not in range(10):
       return popraw(pytajnik)
   return popraw(cyfry[n])
   
