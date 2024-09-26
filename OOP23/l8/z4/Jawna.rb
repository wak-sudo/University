require_relative "Zaszyfrowana.rb"

class Jawna
    def initialize(napis)
        @napis = napis 
    end
    def zaszyfruj(key)
        wynik = ""
        @napis.each_char { |el|
            if key.key?(el)
                wynik += key[el]
            else 
                wynik += el
            end
        }
        Zaszyfrowana.new(wynik)
    end
    def to_s
        @napis
    end
end