require_relative "przyspieszenie.rb"
require_relative "predkosc.rb"

# Wojciech Kieloch
# Zadanie 2 lista 8 PO
# ruby Main.rb

puts()
acc = Przyspieszenie.new(4, 1)
acc.printTable
vel = Predkosc.new(40, 2)
vel.printTable