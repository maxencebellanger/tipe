set terminal table; set output "gnuplot/corproptemp1.table"; set format "%.5f"
set samples 100; plot [x=0:2.5]  .909-.909*exp(-2.50*x)*cos(7.*x)-.326*exp(-2.50*x)*sin(7.*x) 
