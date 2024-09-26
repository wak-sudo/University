class Czas
    def initialize(seconds)
        @seconds = seconds
    end
    def hours
        @seconds / 3600
    end
    def hours=(h)
        @seconds = h * 3600
    end
    def seconds
        @seconds
    end
    def seconds=(s)
        @seconds = s
    end
end