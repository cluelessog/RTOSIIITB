import math
fc = 20
fs = 120
ff = fc/fs
ita = 1/math.tan(math.pi*ff)
q = math.sqrt(2)
b0 = 1/(1+ q*ita + ita*ita)
b1 = 2*b0
b2 = b0
a1 = 2*(ita*ita - 1)*b0
a2 = -(1-q*ita + ita*ita)*b0
print ("b0 = " + str(b0) + "b1 = " +str(b1) +"b2 = " + str(b2) + "a1 = " + str(a1) + "a2 = " +str( a2))
