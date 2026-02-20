# Wojciech Kieloch
# zad. 4 list 8
# ruby Main.rb

require_relative "Jawna.rb"
require_relative "Zaszyfrowana.rb"

napis = "ruby"

key = {
    'a' => 'b',
    'b' => 'r',
    'r' => 'y',
    'y' => 'u',
    'u' => 'a',
}

jawny = Jawna.new(napis)
puts(jawny)
zaszyfrowanyTekst = jawny.zaszyfruj(key)
puts(zaszyfrowanyTekst)
odszyfrowanyTekst = zaszyfrowanyTekst.odszyfruj(key)
puts(odszyfrowanyTekst)