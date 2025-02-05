set terminal table; set output "gnuplot/PIpamp3z.table"; set format "%.5f"
set samples 200; set parametric; plot [t=0.1:100] log10(t), 8.70*log(10.0*(1/t**2+.1e-1)**(0.5)) 
