# Wojciech Kieloch
# PO lista 9 zad. 3
# ruby Main.rb

# gnuplotDataGen(a, b) tworzy plik wejsciowy do programu gnuplot 

require_relative "function.rb"

obj = Function.new(lambda { |x| x**3 + x**2 + 1})
obj2 = Function.new(lambda { |x| Math.log(x) })
obj3 = Function.new(lambda { |x| x**2 })
obj2.gnuplotDataGen(-2,2)