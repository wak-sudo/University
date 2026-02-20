# Wocjciech Kieloch
# PO lista 10 zad 1
# ruby Main.rb

require_relative "Collection.rb"
require_relative "Sorter.rb"

obj = Collection.new()
sort = Sorter.new()

puts "Sort one:"
obj.rand(10, 11)
puts obj
sort.sort1(obj)
puts obj

puts "Sort two:"
obj.clear
obj.rand(10, 11)
puts obj
sort.sort2(obj)
puts obj

obj.pop
puts "\nZdejmujemy element, ponizej dlugosc:"
puts obj
puts obj.length

