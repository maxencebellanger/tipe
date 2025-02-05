set terminal table; set output "gnuplot/PIphi5a.table"; set format "%.5f"
set samples 100; set parametric; plot [t=0.1:1] log10(t), 57.2*atan(.100*t)-89.8 
