require_relative "dlugosc.rb"
require_relative "czas.rb"

class Przyspieszenie
    def initialize(km, sqSec)
        @dl = Dlugosc.new(0)
        @dl.kilometers = km
        @time = Czas.new(0)
        @time.seconds = Math.sqrt(sqSec)
    end
    def kmsPerSqSec
        @dl.kilometers / (@time.seconds * @time.seconds)
    end
    def mmPerSqH
        @dl.millimeters / (@time.hours * @time.hours)
    end
    def ftperSqS
        @dl.feet / (@time.seconds * @time.seconds)
    end
    def printTable
        puts("Si    Non-Si")
        puts(kmsPerSqSec.round(3).to_s + " km/s^2" + "    " + ftperSqS.round(3).to_s + " ft/s^2")
        puts(mmPerSqH.round(3).to_s + " mm/h^2")
        puts()
    end
end