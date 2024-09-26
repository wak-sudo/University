require_relative "Jawna.rb"

class Zaszyfrowana
    def initialize(napis)
        @napis = napis
    end
    def odszyfruj(key)
        wynik = ""
        @napis.each_char { |el|
            if key.value?(el)
                wynik += key.key(el)
            else 
                wynik += el
            end
        }
        Jawna.new(wynik)
    end
    def to_s
        @napis
    end
end