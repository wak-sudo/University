require_relative "dlugosc.rb"
require_relative "czas.rb"

class Predkosc 
    def initialize(kms, hs)
        @Dl = Dlugosc.new(0)
        @time = Czas.new(0)
        @kmph = kms / hs
    end
    def kmph
        @kmph
    end
    def kmph=(kms, hs)
        @Dl.kilometers = kms
        @time.hours = hs
        @kmph = @Dl.kilometers / @time.hours
    end
    def knots
        @kmph / 1.852
    end
    def knots=(k)
        @kmph = k * 1.852
    end
    def printTable
        puts("Si    Non-Si")
        puts(kmph.round(3).to_s + " km/h" + "    " + knots.round(3).to_s + " knots")
        puts()
    end
end