from math import sin, cos
from numpy import array, arange
from pylab import plot,xlabel,show, ylabel, title, grid
PI = 3.1416
GRAVITY = 9.8
Xo = 79
Yo = 73
Vo = 96
Angle = 59
Angle = Angle*PI/180
print Angle
Vox = Vo*cos(Angle)
Voy = Vo*sin(Angle)
x = []
y = []
tiempo = arange(0,100,0.3)
for t in tiempo:
	xtemp = Xo + (Vox*t)
	ytemp = Yo + (Voy*t) - (0.5*GRAVITY*t*t)
	if (ytemp < 0):
		break
	x.append(xtemp)
	y.append(ytemp)
plot(x,y)
xlabel('x')
ylabel('y')
title('Lanzamiento de Proyectil')
grid(True)
show()