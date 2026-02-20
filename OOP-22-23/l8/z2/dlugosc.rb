class Dlugosc
    def initialize(millimeters)
        @millimeters =  millimeters
    end
    def kilometers
        @millimeters / 1_000_000
    end
    def kilometers=(km)
        @millimeters = km * 1_000_000
    end
    def nauticalMile
        @millimeters * 0.000000539956
    end
    def nauticalMile=(miles)
        @millimeters = @miles / 0.000000539956
    end
    def millimeters
        @millimeters
    end
    def millimeters=(mm)
        @millimeters = mm
    end
    def feet
        @millimeters * 0.00328084
    end
    def feet=(f)
        @millimeters = f / 0.00328084
    end
end