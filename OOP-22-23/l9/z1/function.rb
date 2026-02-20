class Function
    def initialize(fun)
        @function = fun
    end
    def isInDomain(x)
        begin
            @function.call(x)
            true
        rescue => exception
          false
        end
    end
    def value(x)
        begin
            @function.call(x)
        rescue => exception
          raise "x poza dziedzina"  
        end
    end
    def zero(a, b, e)
        zeros = []
        (a..b).step(0.001).each do |x|
            if(isInDomain(x) && (@function.call(x).abs() <= e))          
                if (zeros.empty? || (zeros.last - x).abs() > 2*e)              
                    zeros.push(x)
                end
            end
        end
        if zeros.empty?
            nil
        else
            zeros
        end
    end
    def field(a, b)
        sum = 0
        intervals = 100_000
        n = (b - a) / intervals.to_f
        (0...intervals).step(1).each do |i|
            begin
            sum += @function.call(a + n*i)*n
            rescue
                raise "Funkcja nie jest calkowalna w tym przedziale"
            end
        end      
        sum 
    end
    def deriv(x)
        e = 0.0001
        if !isInDomain(x) || !isInDomain(x + e) || !isInDomain(x - e)
            raise "Funkcja nie jest rozniczkowalna w tym punkcie"
        end
        (@function.call(x + e) -  @function.call(x - e)) / (2*e) 
    end
end