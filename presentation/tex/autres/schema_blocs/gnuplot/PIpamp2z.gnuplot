set terminal table; set output "gnuplot/PIpamp2z.table"; set format "%.5f"
set samples 200; set parametric; plot [t=0.1:100] log10(t), 8.70*log(2.00*(1/t**2+.25)**(0.5)) 
