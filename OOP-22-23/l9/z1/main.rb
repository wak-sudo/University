# Wojciech Kieloch
# PO lista 9 zad. 1
# ruby Main.rb

require_relative "function.rb"

obj = Function.new(lambda { |x| x**3 + x**2 + 1})
obj2 = Function.new(lambda { |x| x**2 - 2})
puts "Wzor: x**3 + x**2 + 1"
print "X: 3 Y: "
puts obj.value(3)
puts "Miejsca zerowe +- e:"
puts obj.zero(-2, 1, 0.01)
puts "Calka oznaczona:"
puts obj.field(-1, 3)
puts "Przyblizenie pochodnej w punkcie:"
puts obj.deriv(-0.5)
puts()
puts "Wzor: x**2 - 2"
print "X: 3 Y: "
puts obj2.value(3)
puts "Miejsca zerowe +- e:"
puts obj2.zero(-2, 2, 0.001)
puts "Calka oznaczona:"
puts obj2.field(-2, 2)
puts "Przyblizenie pochodnej w punkcie:"
puts obj2.deriv(-0.5)