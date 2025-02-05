set terminal table; set output "gnuplot/PIphi3a.table"; set format "%.5f"
set samples 100; set parametric; plot [t=0.1:1] log10(t), 57.2*atan(1.*t)-89.8 
