set terminal table; set output "gnuplot/PIamp1z.table"; set format "%.5f"
set samples 200; set parametric; plot [t=0.1:100] log10(t), 4.35*log(1/t**2+1.) 
