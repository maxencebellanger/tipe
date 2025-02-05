set terminal table; set output "gnuplot/PIpamp3.table"; set format "%.5f"
set samples 200; set parametric; plot [t=0.5:90] log10(t), 8.70*log(2.00*(1/t**2+.1e-1)**(0.5)) 
