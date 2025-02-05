set terminal table; set output "gnuplot/corpropblack1.table"; set format "%.5f"
set samples 200; set parametric; plot [t=0.1:30] 57.2*atan2(-5.*t,5.-1.*t**2),8.70*log(250/(25+15*t**2+t**4)**(0.5))
