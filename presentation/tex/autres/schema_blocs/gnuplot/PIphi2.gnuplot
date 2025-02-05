set terminal table; set output "gnuplot/PIphi2.table"; set format "%.5f"
set samples 200; set parametric; plot [t=0.5:90] log10(t), 57.2*atan(.100*t)-89.8 
